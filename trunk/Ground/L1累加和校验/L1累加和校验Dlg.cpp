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
	progress.SetWindowText(CString("1 / 1"));
	bar.SetRange(0,100);
	bar.SetPos(50);


	//��������ļ�
	good=0;
	ifile.close();ifile.clear();
	ofile.close();ofile.clear();


	//�ۼӺ�У��
	sum=-1;readsum=-1;
	mode=-1;readmode=-1;


	//ͳ��
	for(int i=0;i<MODENUM;i++)
	{
		mode_num[i]=0;
		error_num[i]=0;
		v_modenum[i]->SetWindowText(CString("1"));
		v_errornum[i]->SetWindowText(CString("1"));
	}


	//�б��
	for(int i=0;i<MODENUM;i++)
	{
		v_listbox[i]->ResetContent();
		v_listbox[i]->AddString(CString("10"));
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

void CSumDlg::ShowProcess(int p)
{
	char tempchar[100];
	if(p<0||p>100)
	{
		sprintf(tempchar,"%d / %d",int(ifile.tellg()),filelength);//�����ȡ���ַ������ַ�����ҪҪ��long
		progress.SetWindowText(CString(tempchar));//��̬�ı�����ʾ
		bar.SetPos(100.*int(ifile.tellg())/filelength);//��ʾ������
	}
	else
	{
		bar.SetPos(p);//ֱ�����ý�����
	}
}
CSumDlg::CSumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSumDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX,IDC_TAB1,tab);
	DDX_Control(pDX,IDC_STATIC_PROGRESS,progress);
	DDX_Control(pDX,IDC_PROGRESS1,bar);



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
	ShowProcess();//��ʾ����
}
UINT thread_SumCheck(LPVOID params)
{
	CSumDlg* dlg=(CSumDlg*)params;
	if(dlg->good!=1) return 0;//�����ļ�����ȷ


	if(dlg->ifile.tellg()<0 || dlg->ifile.tellg()>dlg->filelength) return 0;//������ļ����ļ��Ѷ���
	


	char ch,ch1,ch2;
	while(!dlg->ifile.eof())
	{
		dlg->ifile.get(ch);
		if(ch==0xEE)
		{
			dlg->ifile.get(ch);
			if(ch==0xBB)
			{
				//�ҵ�EEBB-----------------------------------------------
				dlg->ifile.get(ch);dlg->readmode=int((ch>>4)&0x000f);//��ȡ������
				if(mode!=Package::SetMode)//�������벻��
				{
					cout<<"��ȡ�İ������� "<<mode<<" ��Ԥ�õ������� "<<Package::SetMode<<" ��ͬ"<<endl;
					good=0;	return;
				}
				dlg->ifile.get(ch);fee=int(ch&0x00ff);//��ȡFEE
				dlg->ifile.get(ch);dlg->ifile.get(ch1);length=int((ch<<8)&0xff00)+int(ch1&0x00ff);//��ȡ������


				dlg->ifile.read(buffer,length-6);//һ���Զ�ȡһ�������ڵĿ�ѧ����


				dlg->ifile.get(ch);dlg->ifile.get(ch1);ch2=ch;
				trigger_stat=int((ch2>>4)&0x00ff);//��ȡ����״̬��ע����ǰ4��
				trigger_id=int((ch<<8)&0x0f00)+int(ch1&0x00ff);//��ȡ�����ţ�ע���ú�4��
				dlg->ifile.get(ch);dlg->ifile.get(ch1);
				sum=int((ch<<8)&0xff00)+int(ch1&0x00ff);//��ȡ�ۼӺ�


				readlength+=(length+2);


				break;//����ѭ�������ļ���ȡ����virtual void ReadFile()����buffer����
			}
		}
	}


	return 0;
}
void CSumDlg::BTN_Check()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CSumDlg::TAB_Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	for(int i=0;i<v_subdlg.GetSize();i++)
		v_subdlg[i]->ShowWindow(FALSE);


	v_subdlg[tab.GetCurSel()]->ShowWindow(TRUE);


	*pResult = 0;
}
