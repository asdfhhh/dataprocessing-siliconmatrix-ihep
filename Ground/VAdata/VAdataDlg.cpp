// VAdataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VAdata.h"
#include "VAdataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectDlg �Ի���




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


// CProjectDlg ��Ϣ�������

BOOL CProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



	const int x_begin=240;
	const int y_begin=20;
	const int x_period=50;
	const int y_period=20;
	const int x_width=40;
	const int y_width=17;

	CEdit *pEdit;
	int xx=x_begin,yy=y_begin;
	for(int j=0;j<16;j++)//����
	{
		if(j==8) yy+=2*y_period;//�ָ�����VA

		for(int i=0;i<8;i++)//����
		{
			pEdit=new CEdit;
			pEdit->Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_CENTER,
				CRect(xx,yy,xx+x_width,yy+y_width),this,0);//���༭������
			v_edit.Add(pEdit);

			xx+=x_period;
		}
		xx=x_begin;
		yy+=y_period;
	}


	good=0;//��ʼΪû���ļ�
	VAID=-1;//��ʼVA IDΪ-1
	edit_vaid.SetWindowText(CString("-1"));//��ʼVA ID��ʾΪ-1


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProjectDlg::OnPaint()
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
HCURSOR CProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CProjectDlg::GetVAID()
{
	if(!good) return -1;//û������


	int tempVAID;CString str;
	edit_vaid.GetWindowText(str);
	tempVAID=_ttoi(str);//�ӱ༭��õ��µ�VA ID


	if(tempVAID>72 || tempVAID<1)//Խ����
	{
		str.Format(__T("%d"),VAID);
		edit_vaid.SetWindowText(str);//�༭����ʾ��ֵ
		return VAID;//���ؾ�ֵ
	}
	else
	{
		return tempVAID;//������ֵ
	}
}
void CProjectDlg::SetVAID(int tempVAID)
{
	if(!good) return;//û������


	if(tempVAID>72 || tempVAID<1) return;//Խ����


	if(tempVAID==VAID)return;//����û�б仯


	VAID=tempVAID;//����ֵ����VA ID
	
	
	CString str;
	str.Format(__T("%d"),VAID);
	edit_vaid.SetWindowText(str);//�༭����ʾ��ֵ


	for(int i=0;i<128;i++)//ѭ��2��VA�����ݣ��õ�ֵ
	{
		str.Format(__T("%d"),int(buffer[(VAID-1)*128+i]&0x00ff));//��buffer�õ�2��VA����
		v_edit[i]->SetWindowText(str);//�ڶԻ�������ʾ2��VA����
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
	if(!good) return;//�����ݴ�


	int tempdata;CString str;
	for(int i=0;i<128;i++)//ѭ�����б༭��
	{
		v_edit[i]->GetWindowText(str);
		tempdata=_ttoi(str);//�ӱ༭��õ�����


		if(tempdata<0 || tempdata>255) continue;//Խ����


		buffer[(VAID-1)*128+i]=tempdata;//��ֵ
	}
}

void CProjectDlg::BTN_OpenFile()
{
	CFileDialog mydlg(TRUE);//���ļ��Ի���
	if(mydlg.DoModal()!=IDOK) return;//û��ѡ���ļ�


	CString str=mydlg.GetPathName();
	ifstream ifile(str,ios::binary);//�������ļ�
	if(!ifile.is_open()) return;//�ļ�û��


	ifile.read(buffer,DET_NUM);//��ȡ�ļ�
	ifile.close();ifile.clear();


	good=1;
	SetVAID(1);
}

void CProjectDlg::BTN_Output()
{
	if(!good) return;//û������

	CFileDialog mydlg(FALSE);//���ļ��Ի���
	if(mydlg.DoModal()!=IDOK) return;//û��ѡ���ļ�


	CString str=mydlg.GetPathName();
	ofstream ofile(str,ios::binary);//�������ļ�
	if(!ofile.is_open()) return;//�ļ�û��


	ofile.write(buffer,DET_NUM);//д���ļ�
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
