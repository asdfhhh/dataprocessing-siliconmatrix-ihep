// L0toL1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "L0toL1.h"
#include "L0toL1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CL0toL1Dlg::Reset_Listbox()
{
	LISTBOX_control.ResetContent();
}
void CL0toL1Dlg::Display_Listbox()
{
	while(!my.l_msg.IsEmpty())
	{
		if(my.l_msg.GetCount()>100)//����̫����
		{
			my.good=2;
		}
		LISTBOX_control.InsertString(LISTBOX_control.GetCount(),my.l_msg.RemoveHead());
	}
}
void CL0toL1Dlg::Reset_Process()
{
	PROGRESS1_control.SetRange(0,100);
	PROGRESS1_control.SetPos(0);
	STATIC_PROGRESS_control.SetWindowText(__T("�Ѵ���(MB) 0.0  /  �ܳ���(MB) 0.0"));
}
void CL0toL1Dlg::Display_Process()
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

void CL0toL1Dlg::Reset_Timer()
{
	STATIC_TIMER_control.SetWindowText(__T("��ʱ 0��0��  /  ���� 0��0��"));
}
void CL0toL1Dlg::Display_Timer()
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
void CL0toL1Dlg::Reset_Event()
{
	STATIC_EVENT_control.SetWindowText(__T("���¼� 0  /  ���¼� 0"));
}
void CL0toL1Dlg::Display_Event()
{
	if(my.readevents<0)
	{
		my.l_msg.AddTail(CString("BUG: readevents <0"));
		my.good=3;
		return;
	}
	if(my.goodevents<0)
	{
		my.l_msg.AddTail(CString("BUG: goodevents <0"));
		my.good=3;
		return;
	}


	CString str;
	str.Format(__T("���¼� %.1d  /  ���¼� %.1d"),my.readevents,my.goodevents);
	STATIC_EVENT_control.SetWindowText(str);
}
UINT Thread_Display(LPVOID params)
{
	CL0toL1Dlg *dlg=(CL0toL1Dlg*)params;
	while(my.good==1)
	{
		dlg->Display_Listbox();
		dlg->Display_Process();
		dlg->Display_Event();
		dlg->Display_Timer();
		Sleep(500);
	}	
	dlg->Display_Process();
	dlg->Display_Event();
	dlg->Display_Timer();
	dlg->Display_Listbox();

	return 0;
}
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
CL0toL1Dlg::CL0toL1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CL0toL1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CL0toL1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_MSG,LISTBOX_control);
	DDX_Control(pDX, IDC_PROGRESS, PROGRESS1_control);
	DDX_Control(pDX, IDC_STATIC_PROGRESS, STATIC_PROGRESS_control);
	DDX_Control(pDX, IDC_STATIC_TIMER, STATIC_TIMER_control);
	DDX_Control(pDX, IDC_STATIC_EVENT, STATIC_EVENT_control);
}

BEGIN_MESSAGE_MAP(CL0toL1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CLEARMSG, &CL0toL1Dlg::OnBnClickedBtn_Clearmsg)
	ON_BN_CLICKED(IDC_CheckCRC, &CL0toL1Dlg::OnBnClickedBtn_CRCcheck)
	ON_BN_CLICKED(IDC_OpenL0Data, &CL0toL1Dlg::OnBnClickedBtn_OpenL0Data)
	ON_BN_CLICKED(IDCANCEL, &CL0toL1Dlg::OnBnClicked_Exit)
END_MESSAGE_MAP()
BOOL CL0toL1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	//��ʼ������
	Reset_Listbox();
	Reset_Process();
	Reset_Timer();
	Reset_Event();


	return TRUE;
}

void CL0toL1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
void CL0toL1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CL0toL1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CL0toL1Dlg::OnBnClickedBtn_OpenL0Data()
{
	//ȫ����ʼ��
	Reset_Listbox();
	Reset_Process();
	Reset_Event();
	Reset_Timer();
	my.Reset();


	//�õ���L0�����ļ���
	char szFileFilter[]=
		"Dat File(*.dat)|*.dat|"
		"All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,(CString)szFileFilter);
	if (dlg.DoModal()==IDOK)
	{
		my.InputFileName=dlg.GetPathName();
	}

	
	//����MyClass::OpenFile()
	my.OpenFile();
	if(my.good!=1)
	{
		Display_Listbox();
		return; 
	}


	//��Ļ��ʾ
	Display_Listbox();
	Display_Process();
}
void CL0toL1Dlg::OnBnClickedBtn_CRCcheck()
{
	if(my.good!=1)
	{
		MessageBox(CString("Status Not Ready, Please Open File"));
		return ;
	}


	//��ʱ��
	timer_begin=GetTickCount();


	//�����߳�
	AfxBeginThread(&CheckCRC_Thread, this);	
	AfxBeginThread(&Thread_Display, this);	
}

void CL0toL1Dlg::OnBnClicked_Exit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
void CL0toL1Dlg::OnBnClickedBtn_Clearmsg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LISTBOX_control.ResetContent();
}
