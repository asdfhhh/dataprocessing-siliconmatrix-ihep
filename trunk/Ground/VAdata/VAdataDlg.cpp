// VAdataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VAdata.h"
#include "VAdataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectDlg 对话框




CProjectDlg::CProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX,IDC_EDIT1,edit_vaid);
	DDX_Control(pDX,IDC_SPIN1,ctrl_vaid);

}

BEGIN_MESSAGE_MAP(CProjectDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CProjectDlg::SPIN_VAID)
	ON_BN_CLICKED(IDC_BUTTON2, &CProjectDlg::BTN_NewVAData)
	ON_BN_CLICKED(IDC_BUTTON3, &CProjectDlg::BTN_OpenFile)
	ON_BN_CLICKED(IDC_BUTTON4, &CProjectDlg::BTN_Output)
	ON_BN_CLICKED(IDC_BUTTON5, &CProjectDlg::BTN_GenerateTest)
	ON_EN_CHANGE(IDC_EDIT1, &CProjectDlg::EDIT_Change)
END_MESSAGE_MAP()


// CProjectDlg 消息处理程序

BOOL CProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	const int x_begin=240;
	const int y_begin=20;
	const int x_period=50;
	const int y_period=20;
	const int x_width=40;
	const int y_width=17;

	CEdit *pEdit;
	int xx=x_begin,yy=y_begin;
	for(int j=0;j<16;j++)//横行
	{
		if(j==8) yy+=2*y_period;//分隔两个VA

		for(int i=0;i<8;i++)//竖行
		{
			pEdit=new CEdit;
			pEdit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
				CRect(xx,yy,xx+x_width,yy+y_width),this,0);//画编辑框阵列
			v_edit.Add(pEdit);

			xx+=x_period;
		}
		xx=x_begin;
		yy+=y_period;
	}


	good=0;//初始为没有文件
	VAID=-1;//初始VA ID为-1
	edit_vaid.SetWindowText(CString("-1"));//初始VA ID显示为-1


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CProjectDlg::GetVAID()
{
	if(!good) return -1;//没有数据


	int tempVAID;CString str;
	edit_vaid.GetWindowText(str);
	tempVAID=_ttoi(str);//从编辑框得到新的VA ID


	if(tempVAID>72 || tempVAID<1)//越界检查
	{
		str.Format(__T("%d"),VAID);
		edit_vaid.SetWindowText(str);//编辑框显示旧值
		return VAID;//返回旧值
	}
	else
	{
		return tempVAID;//返回新值
	}
}
void CProjectDlg::SetVAID(int tempVAID)
{
	if(!good) return;//没有数据


	if(tempVAID>72 || tempVAID<1) return;//越界检查


	if(tempVAID==VAID)return;//数据没有变化


	VAID=tempVAID;//把新值赋给VA ID
	
	
	CString str;
	str.Format(__T("%d"),VAID);
	edit_vaid.SetWindowText(str);//编辑框显示新值


	for(int i=0;i<128;i++)//循环2个VA的数据，得到值
	{
		str.Format(__T("%d"),int(buffer[(VAID-1)*128+i]&0x00ff));//从buffer得到2个VA数据
		v_edit[i]->SetWindowText(str);//在对话框中显示2个VA数据
	}
}

void CProjectDlg::ResetAll()
{
}
void CProjectDlg::SPIN_VAID(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	if(!good) return;
	if(pNMUpDown->iDelta==1)
	{
		SetVAID(VAID-1);
	}
	else
	{
		SetVAID(VAID+1);
	}


	*pResult = 0;
}

void CProjectDlg::BTN_NewVAData()
{
	if(!good) return;//无数据打开


	int tempdata;CString str;
	for(int i=0;i<128;i++)//循环所有编辑框
	{
		v_edit[i]->GetWindowText(str);
		tempdata=_ttoi(str);//从编辑框得到数据


		if(tempdata<0 || tempdata>255) continue;//越界检查


		buffer[(VAID-1)*128+i]=tempdata;//幅值
	}
}

void CProjectDlg::BTN_OpenFile()
{
	CFileDialog mydlg(TRUE);//打开文件对话框
	if(mydlg.DoModal()!=IDOK) return;//没有选择文件


	CString str=mydlg.GetPathName();
	ifstream ifile(str,ios::binary);//打开输入文件
	if(!ifile.is_open()) return;//文件没打开


	ifile.read(buffer,DET_NUM);//读取文件
	ifile.close();ifile.clear();


	good=1;
	SetVAID(1);
}

void CProjectDlg::BTN_Output()
{
	if(!good) return;//没有数据

	CFileDialog mydlg(FALSE);//打开文件对话框
	if(mydlg.DoModal()!=IDOK) return;//没有选择文件


	CString str=mydlg.GetPathName();
	ofstream ofile(str,ios::binary);//打开输入文件
	if(!ofile.is_open()) return;//文件没打开


	ofile.write(buffer,DET_NUM);//写入文件
	ofile.close();ofile.clear();
}

void CProjectDlg::BTN_GenerateTest()
{
	for(int i=0;i<72;i++)
	{
		for(int j=0;j<128;j++)
		{
			buffer[i*128+j]=i;
		}
	}
	

	good=1;
	SetVAID(1);
}

void CProjectDlg::EDIT_Change()
{
	SetVAID(GetVAID());
}
