// L1�ۼӺ�У��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "L1�ۼӺ�У��.h"
#include "L1�ۼӺ�У��Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSumDlg �Ի���
void CSumDlg::Reset_Tab()
{
	tab.SetCurSel(0);
	for(int i=0;i<v_subdlg.GetSize();i++)
		v_subdlg[i]->ShowWindow(FALSE);
	v_subdlg[0]->ShowWindow(TRUE);
}
void CSumDlg::Reset_Process()
{
	PROGRESS1_control.SetRange(0,100);
	PROGRESS1_control.SetPos(0);
	STATIC_PROGRESS_control.SetWindowText(__T("�Ѵ���(MB) 0.0  /  �ܳ���(MB) 0.0"));
}
void CSumDlg::Display_Process()
{
	if(my.filelength<10)
	{
		my.l_msg.AddTail(CString("BUG: L0 Data Length <10"));
		my.good=3;
		return;
	}
	if(my.readlength<0)
	{
		my.l_msg.AddTail(CString("BUG: readlength <0"));
		my.good=3;
		return;
	}
	if(my.readlength>my.filelength)
	{
		my.l_msg.AddTail(CString("BUG: readlength > filelength"));
		my.good=3;
		return;
	}


	timer_used=(GetTickCount()-timer_begin)/1000;
	if(timer_used<0)
	{
		my.l_msg.AddTail(CString("BUG: timer_used <0"));
		my.good=3;
		return;
	}


	CString str;

	str.Format(__T("�Ѵ���(MB) %.1lf  /  �ܳ���(MB) %.1lf"),my.readlength/1000000.,my.filelength/1000000.);
	STATIC_PROGRESS_control.SetWindowText(str);

	PROGRESS1_control.SetPos(int(100.*my.readlength/my.filelength));

}

void CSumDlg::Reset_Timer()
{
	STATIC_TIMER_control.SetWindowText(__T("��ʱ 0��0��  /  ���� 0��0��"));
}
void CSumDlg::Display_Timer()
{
	if(my.filelength<10)
	{
		my.l_msg.AddTail(CString("BUG: L0 Data Length <10"));
		my.good=3;
		return;
	}
	if(my.readlength<0)
	{
		my.l_msg.AddTail(CString("BUG: readlength <0"));
		my.good=3;
		return;
	}
	if(my.readlength>my.filelength)
	{
		my.l_msg.AddTail(CString("BUG: readlength > filelength"));
		my.good=3;
		return;
	}


	CString str;
	minute_used=timer_used/60;
	second_used=timer_used-60*minute_used;
	if(my.readlength<100)
	{
		str.Format(__T("��ʱ %2d��%2d��  /  ���� 99��00��"),minute_used,second_used);
	}
	else
	{
		timer_remain=timer_used*(my.filelength-my.readlength)/(my.readlength);
		minute_remain=timer_remain/60;
		second_remain=timer_remain-60*minute_remain;
		str.Format(__T("��ʱ %3d��%2d��  /  ���� %3d��%2d��"),minute_used,second_used,minute_remain,second_remain);
	}
	STATIC_TIMER_control.SetWindowText(str);
}

void CSumDlg::Display_Statistic()
{
	CString str;
	for(int i=0;i<MODENUM;i++)
	{
		str.Format(__T("%d"),my.mode_num[i]);
		v_modenum[i]->SetWindowText(str);
		str.Format(__T("%d"),my.error_num[i]);
		v_errornum[i]->SetWindowText(str);
	}
}
void CSumDlg::Reset_Statistic()
{
	for(int i=0;i<MODENUM;i++)
	{
		v_modenum[i]->SetWindowText(CString("0"));
		v_errornum[i]->SetWindowText(CString("0"));
	}
}
void CSumDlg::Reset_ErrorMessage()
{
	for(int i=0;i<MODENUM;i++)
	{
		v_listbox[i]->ResetContent();
	}
}
void CSumDlg::Display_ErrorMessage()
{
	while(!my.l_msg_normal.IsEmpty())
	{
		v_listbox[0]->InsertString(v_listbox[0]->GetCount(),my.l_msg_normal.RemoveHead());
	}
	while(!my.l_msg_raw.IsEmpty())
	{
		v_listbox[1]->InsertString(v_listbox[1]->GetCount(),my.l_msg_raw.RemoveHead());
	}
	while(!my.l_msg_cali.IsEmpty())
	{
		v_listbox[2]->InsertString(v_listbox[2]->GetCount(),my.l_msg_cali.RemoveHead());
	}
	while(!my.l_msg_pds.IsEmpty())
	{
		v_listbox[3]->InsertString(v_listbox[3]->GetCount(),my.l_msg_pds.RemoveHead());
	}
	while(!my.l_msg_down.IsEmpty())
	{
		v_listbox[4]->InsertString(v_listbox[4]->GetCount(),my.l_msg_down.RemoveHead());
	}
	while(!my.l_msg_empty.IsEmpty())
	{
		v_listbox[5]->InsertString(v_listbox[5]->GetCount(),my.l_msg_empty.RemoveHead());
	}
	while(!my.l_msg_busy.IsEmpty())
	{
		v_listbox[6]->InsertString(v_listbox[6]->GetCount(),my.l_msg_busy.RemoveHead());
	}
}
void CSumDlg::Display_SystemMessage()
{
	while(!my.l_msg.IsEmpty())
	{
		MessageBox(my.l_msg.RemoveHead());
	}

}
void CSumDlg::ResetAll()
{
	Reset_Tab();
	Reset_Process();
	Reset_Timer();
	Reset_Statistic();
	Reset_ErrorMessage();
}
void CSumDlg::DisplayAll()
{
	Display_Process();
	Display_Timer();
	Display_Statistic();
	Display_ErrorMessage();
	Display_SystemMessage();
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

CSumDlg::CSumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSumDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CSumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX,IDC_TAB1,tab);


	DDX_Control(pDX,IDC_STATIC_PROGRESS,STATIC_PROGRESS_control);
	DDX_Control(pDX,IDC_PROGRESS1,PROGRESS1_control);
	DDX_Control(pDX, IDC_STATIC_TIME, STATIC_TIMER_control);
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
	OutputFileTitle.Format(__T("%s"),tempchar);
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
	//ȫ����ʼ��
	ResetAll();
	my.Reset();


	//���ļ��Ի���
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()!=IDOK) return;
	my.InputFileName=dlg.GetPathName();


	//����MySumCheck::OpenFile()
	my.OpenFile();
	if(my.good!=1)
	{
		Display_SystemMessage();
		return ;
	}
	else
	{
		//�����ļ��к��ļ���ǰ׺
		my.OutputFileTitle=dlg.GetPathName();
		int nPos=my.OutputFileTitle.ReverseFind('\\');
		my.OutputFileTitle=my.OutputFileTitle.Left(nPos);
		my.OutputFileTitle+=CString('\\');
		my.OutputFileTitle+=dlg.GetFileTitle();
		my.OutputFileTitle+=CString('\\');
		CreateDirectory(my.OutputFileTitle,NULL);
		my.OutputFileTitle+=dlg.GetFileTitle();
	}




	//��ʾ����
	Display_Process();


	//��ʾϵͳ��Ϣ
	Display_SystemMessage();
}
UINT Thread_Display(LPVOID params)
{
	CSumDlg* dlg=(CSumDlg*)params;

	while(my.good==1)
	{
		dlg->DisplayAll();
		Sleep(500);
	}
	dlg->DisplayAll();

	return 0;
}
void CSumDlg::BTN_Check()
{
	if(my.good!=1)
	{
		MessageBox(CString("Status Not Ready, Please Open File"));
		return;
	}


	//��ʱ��
	timer_begin=GetTickCount();


	//�����߳�
	AfxBeginThread(&thread_SumCheck,this);
	AfxBeginThread(&Thread_Display,this);
}

void CSumDlg::TAB_Change(NMHDR *pNMHDR, LRESULT *pResult)
{
	for(int i=0;i<v_subdlg.GetSize();i++)
		v_subdlg[i]->ShowWindow(FALSE);


	v_subdlg[tab.GetCurSel()]->ShowWindow(TRUE);


	*pResult = 0;
}
