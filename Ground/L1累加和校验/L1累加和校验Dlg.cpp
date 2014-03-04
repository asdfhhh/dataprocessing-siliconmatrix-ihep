// L1�ۼӺ�У��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "L1�ۼӺ�У��.h"
#include "L1�ۼӺ�У��Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSumDlg �Ի���

void CSumDlg::ResetAll()
{
	//ѡ�
	tab.SetCurSel(0);
	for(int i=0;i<v_subdlg.GetSize();i++)
		v_subdlg[i]->ShowWindow(FALSE);
	v_subdlg[0]->ShowWindow(TRUE);


	//����
	filelength=0;
	readlength=0;
	progress.SetWindowText(CString("0 / 0"));
	bar.SetRange(0,100);
	bar.SetPos(0);
	mytimer.SetWindowText(CString(""));


	//��������ļ�
	good=0;
	ifile.close();ifile.clear();
	ofile.close();ofile.clear();
	for(int i=0;i<MODENUM;i++)
	{
		mode_filenum[i]=0;
	}


	//���ݰ�
	mode=-99;readmode=99;


	//�ۼӺ�У��
	sum=-99;readsum=-99;


	//ͳ��
	for(int i=0;i<MODENUM;i++)
	{
		mode_num[i]=0;
		error_num[i]=0;
		v_modenum[i]->SetWindowText(CString("0"));
		v_errornum[i]->SetWindowText(CString("0"));
	}


	//�б��
	for(int i=0;i<MODENUM;i++)
	{
		v_listbox[i]->ResetContent();
//		v_listbox[i]->AddString(CString("10"));
	}
}
void CSumDlg::InitialListBox()
{
	for(int i=0;i<MODENUM;i++)
	{
		v_listboxIDC.Add(IDC_LIST1+i);
		v_listbox.Add((CListBox*)v_subdlg[i+1]->GetDlgItem(v_listboxIDC[i]));//v_listboxIDC[i]
	}
}
void CSumDlg::InitialStatic()
{
	for(int i=0;i<MODENUM;i++)
	{
		v_modenumIDC.Add(IDC_STATIC11+i);
		v_errornumIDC.Add(IDC_STATIC12+i);
		v_modenum.Add((CStatic*)v_subdlg[0]->GetDlgItem(v_modenumIDC[i]));
		v_errornum.Add((CStatic*)v_subdlg[0]->GetDlgItem(v_errornumIDC[i]));
	}
}
void CSumDlg::InitialSubDialog()
{
	//�ӶԻ������
	v_subdlg.Add(new CDLG1); 
	v_subdlg.Add(new CDLG2); 
	v_subdlg.Add(new CDLG3); 
	v_subdlg.Add(new CDLG4); 
	v_subdlg.Add(new CDLG5); 
	v_subdlg.Add(new CDLG6); 
	v_subdlg.Add(new CDLG7); 
	v_subdlg.Add(new CDLG8); 


	//�ӶԻ��������
	v_subdlgname.Add(CString("ͳ������"));
	v_subdlgname.Add(CString("����ģʽ"));
	v_subdlgname.Add(CString("ԭʼģʽ"));
	v_subdlgname.Add(CString("�̶�ģʽ"));
	v_subdlgname.Add(CString("���߸���"));
	v_subdlgname.Add(CString("�´�ģʽ"));
	v_subdlgname.Add(CString("��ռλ��"));
	v_subdlgname.Add(CString("æռλ��"));


	//�ӶԻ����IDD
	v_subdlgIDD.Add(IDD_DIALOG1);
	v_subdlgIDD.Add(IDD_DIALOG2);
	v_subdlgIDD.Add(IDD_DIALOG3);
	v_subdlgIDD.Add(IDD_DIALOG4);
	v_subdlgIDD.Add(IDD_DIALOG5);
	v_subdlgIDD.Add(IDD_DIALOG6);
	v_subdlgIDD.Add(IDD_DIALOG7);
	v_subdlgIDD.Add(IDD_DIALOG8);
}

void CSumDlg::DisplayProcess(int p)
{
	char tempchar[100];
	if(p<0||p>100)
	{
		sprintf(tempchar,"%d / %d",readlength,filelength);//�����ȡ���ַ������ַ�����ҪҪ��long
		progress.SetWindowText(CString(tempchar));//��̬�ı�����ʾ
		bar.SetPos(100.*readlength/filelength);//��ʾ������
	}
	else
	{
		bar.SetPos(p);//ֱ�����ý�����
	}
}
void CSumDlg::DisplayTimer()
{
	time_now=GetTickCount();
	long deltatime=(time_now-time_start)/1000;
	minute_used=deltatime/60;//�������˵ķ���
	second_used=deltatime-minute_used*60;//���˵���
	if(readlength>10000)
	{
		long tempremain=double(deltatime)*(filelength-readlength)/readlength;
		minute_remain=tempremain/60;//�������˵ķ���
		second_remain=tempremain-minute_remain*60;//���˵���
		str_mytimer.Format("���� %d��%d�� / ���� %d��%d��",minute_used,second_used,minute_remain,second_remain);
	}
	else
	{
		str_mytimer.Format("���� %d��%d�� / ���� 99��59��",minute_used,second_used);
	}
	mytimer.SetWindowText(str_mytimer);
}
void CSumDlg::DisplayModeNum()
{
	CString str;
	for(int i=0;i<MODENUM;i++)
	{
		str.Format(__T("%d"),mode_num[i]);
		v_modenum[i]->SetWindowText(str);
	}
}
void CSumDlg::DisplayErrorNum()
{
	CString str;
	for(int i=0;i<MODENUM;i++)
	{
		str.Format(__T("%d"),error_num[i]);
		v_errornum[i]->SetWindowText(str);
	}
}
void CSumDlg::DisplayErrorMessage()
{
	CString str;
	str.Format(__T("���=%4d�� λ��=%9d�� FEE=%2d�� ������=%5d�� ����״̬=%3d�� ������=%5d, �����ۼӺ�=%5d�� �����ۼӺ�=%5d")
		,error_num[mode],readlength,fee,length,trigger_stat,trigger_id,readsum,sum);
	v_listbox[mode]->InsertString(v_listbox[mode]->GetCount(),str);
}
void CSumDlg::NewOutputFile()
{
	//�رվ��ļ�
	ofile.close();ofile.clear();


	//�������ļ�������
	CString str;char tempchar[100];
	sprintf(tempchar,"(%d).",mode_filenum[mode]);
	str=ofilename;
	str+=CString(tempchar);
	switch(mode)
	{
	case 0:
		str+=CString("normal");
		break;
	case 1:
		str+=CString("raw");
		break;
	case 2:
		str+=CString("cali");
		break;
	case 3:
		str+=CString("pds");
		break;
	case 4:
		str+=CString("down");
		break;
	case 5:
		str+=CString("empty");
		break;
	case 6:
		str+=CString("busy");
		break;
	default:
		str+=CString("error");
		break;
	}


	//�����ļ�
	ofile.open(str,ios::binary);
}
void CSumDlg::SetReadMode()
{
	int tempmode=int((buffer[0]>>4)&0x000f);//����������룬ע���飡����������
	switch(tempmode)
	{
		case 2:	
			readmode=0;break;//0010=����ģʽ(0)
		case 3:	
			readmode=1;break;//0011=ԭʼģʽ(1)
		case 4:	
			readmode=2;break;//0100=�̶�ģʽ(2)
		case 5:	
			readmode=3;break;//0101=���߸���(3)
		case 6:	
			readmode=4;break;//0110=�´�ģʽ(4)
		case 7:	
			readmode=5;break;//1100=��ռλ��(5)
		case 8:	
			readmode=6;break;//1101=æռλ��(6)
		default:	
			readmode=-1;break;//������(-1)
	}
}
CSumDlg::CSumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSumDlg::IDD, pParent)
	, str_mytimer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CSumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX,IDC_TAB1,tab);
	DDX_Control(pDX,IDC_STATIC_PROGRESS,progress);
	DDX_Control(pDX,IDC_PROGRESS1,bar);



	DDX_Control(pDX, IDC_STATIC_TIME, mytimer);
	DDX_Text(pDX, IDC_STATIC_TIME, str_mytimer);
}

BEGIN_MESSAGE_MAP(CSumDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSumDlg::BTN_Open)
	ON_BN_CLICKED(IDC_BUTTON2, &CSumDlg::BTN_Check)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSumDlg::TAB_Change)
END_MESSAGE_MAP()


// CSumDlg ��Ϣ�������

BOOL CSumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	//��ʼ���ӶԻ���
	InitialSubDialog();
	for(int i=0;i<v_subdlg.GetSize();i++)
	{
		v_subdlg[i]->Create(v_subdlgIDD[i],&tab);
		tab.InsertItem(i,v_subdlgname[i]);
//		v_subdlg[i]->MoveWindow(rs);
		v_subdlg[i]->ShowWindow(FALSE);
	}
		

	//��ʼ����̬�ı���
	InitialStatic();
	

	//��ʼ���б��
	InitialListBox();


	//����
	ResetAll();

	
	//��������ļ���Ϊǰ׺Ϊʱ��
	/*
	time_t mytime=time(0);
	char tempchar[100];
	strftime(tempchar,100,"%Y%m%d%H%M%S",localtime(&mytime));
	ofilename.Format(__T("%s"),tempchar);
*/
		
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSumDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSumDlg::BTN_Open()
{
	ResetAll();


	CFileDialog tempdlg(TRUE);//���ļ��Ի���
	if(tempdlg.DoModal()!=IDOK) return;


	ifile.open(tempdlg.GetPathName(),ios::binary);//���ļ�
	if(!ifile.is_open()) return;//ȷ���ļ���


	ifile.seekg(0,ios::beg);ifile.seekg(0,ios::end);
	filelength=ifile.tellg();ifile.seekg(0,ios::beg);//�õ��ļ�����
	if(filelength<1) return;//�ļ�����̫С


	good=1;
	DisplayProcess();//��ʾ����


	//�����ļ��к��ļ���ǰ׺
	ofilename=tempdlg.GetPathName();
	int nPos=ofilename.ReverseFind('\\');
	ofilename=ofilename.Left(nPos);
	ofilename+=CString('\\');
	ofilename+=tempdlg.GetFileTitle();
	ofilename+=CString('\\');
	CreateDirectory(ofilename,NULL);
	ofilename+=tempdlg.GetFileTitle();
}
UINT thread_SumCheck(LPVOID params)
{
	CSumDlg* dlg=(CSumDlg*)params;

	if(dlg->good!=1)//�����ļ�����ȷ
	{
		dlg->MessageBox(CString("�����ļ�����ȷ"));
		 return 0;
	}
	if(dlg->ifile.tellg()<0 || dlg->ifile.tellg()>dlg->filelength)//������ļ����ļ��Ѷ���
	{
		dlg->MessageBox(CString("�ļ��Ѷ���"));
		dlg->good=0;
		 return 0;
	}
	


	char ch;
	while(!dlg->ifile.eof() && dlg->good)
	{
		dlg->ifile.get(ch);
		if((ch&0xff)==0xEE)
		{
			dlg->ifile.get(ch);
			if((ch&0xff)==0xBB)
			{
				//�ҵ�EEBB-----------------------------------------------


				//��ȡ�����ͣ�ת��Ϊ��ʱ����ģʽ
				dlg->ifile.get(dlg->buffer[0]);
				dlg->SetReadMode();//����buffer[0]����readmode
				if(dlg->readmode==-1)//����ʶ��İ�����
				{
					//     To   Do  
					dlg->MessageBox(CString("����ʶ��İ�������"));
					continue;
				}


				//�Ƚ������ʱ����ģʽ����һ����ģʽ�Ƿ�һ��
				if(dlg->readmode!=dlg->mode)
				{
					dlg->mode=dlg->readmode;//���ð�����
					dlg->mode_filenum[dlg->mode]++;//��Ӧ�İ����ļ���Ŀ+1
					dlg->NewOutputFile();//�رվ��ļ������µ�����ļ�
				}
				dlg->mode_num[dlg->mode]++;//��Ӧ�����͵���Ŀ+1
//				dlg->DisplayModeNum();//�ھ�̬�ı�����ʾ��Ŀ+1


				//��ȡFEE
				dlg->ifile.get(dlg->buffer[1]);
				dlg->fee=int((dlg->buffer[1])&0x003f);


				//��ȡ���ȣ�Ȼ��һ������һ��������
				dlg->ifile.get(dlg->buffer[2]);dlg->ifile.get(dlg->buffer[3]);
				dlg->length=int(((dlg->buffer[2])<<8)&0xff00)+int((dlg->buffer[3])&0x00ff);
				if(dlg->length<6 || dlg->length>40000)//���ݳ���Խ��
				{
					//     To   Do  
//					dlg->MessageBox(CString("������̫С"));
					continue;
				}
				dlg->ifile.read(dlg->buffer+4,dlg->length-2);//һ���Զ�ȡʣ������


				//����״̬�ʹ�����
				dlg->trigger_stat=int(((dlg->buffer[dlg->length-2])>>4)&0x00ff);//��ȡ����״̬��ע����ǰ4��
				dlg->trigger_id=int(((dlg->buffer[dlg->length-2])<<8)&0x0f00)+int((dlg->buffer[dlg->length-1])&0x00ff);//��ȡ�����ţ�ע���ú�4��


				//�ۼӺ�У��
				dlg->readsum=int(((dlg->buffer[dlg->length])<<8)&0xff00)+int((dlg->buffer[dlg->length+1])&0x00ff);
				dlg->sum=0;
				for(int i=0;i<dlg->length;i++)
				{
					(dlg->sum)+=int((dlg->buffer[i])&0xff);//ע����0x00ff
				}
				if(dlg->sum==dlg->readsum)//�ۼӺ�У��ͨ��
				{
					dlg->ofile.write(dlg->buffer+4,dlg->length-6);//������ļ�
				}
				else
				{
					(dlg->error_num)[dlg->mode]++;//��Ӧģʽ���ۼӺͳ���+1
					dlg->DisplayErrorNum();//�ھ�̬�ı�����ʾ��Ŀ+1
					if((dlg->error_num)[dlg->mode]<100)//����̫��Ͳ���ʾ��
					{
						dlg->DisplayErrorMessage();//���б����ʾ��ϸ��Ϣ
					}
				}
			}
		}
		dlg->readlength=dlg->ifile.tellg();
//		dlg->DisplayProcess();//ˢ�½�����
	}
	

	//�����ļ�״̬
	dlg->ofile.close();dlg->ofile.clear();
	dlg->ifile.close();dlg->ifile.clear();
	dlg->good=0;

	return 0;
}
UINT thread_Show(LPVOID params)
{
	CSumDlg* dlg=(CSumDlg*)params;

	while(dlg->good)
	{
		dlg->DisplayTimer();
		dlg->DisplayErrorNum();
		dlg->DisplayModeNum();
		dlg->DisplayProcess();
		Sleep(1000);
	}

	return 0;
}
void CSumDlg::BTN_Check()
{
	time_start=GetTickCount();
	AfxBeginThread(&thread_SumCheck,this);
	AfxBeginThread(&thread_Show,this);
}

void CSumDlg::TAB_Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	for(int i=0;i<v_subdlg.GetSize();i++)
		v_subdlg[i]->ShowWindow(FALSE);


	v_subdlg[tab.GetCurSel()]->ShowWindow(TRUE);


	*pResult = 0;
}
