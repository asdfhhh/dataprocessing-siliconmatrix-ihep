// VAdataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VAdata.h"
#include "VAdataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectDlg �Ի���



void CProjectDlg::ResetAll()
{
	good=0;
	VAID=-1;DVA=-1;DAQM=-1;
	for(int i=0;i<128;i++)
	{
		v_edit[i]->SetWindowText(CString(""));
	}
	edit_vaid.SetWindowText(CString("-1"));
	edit_daqm.SetWindowText(CString("-1"));
	edit_dva.SetWindowText(CString("-1"));

	static_address.SetWindowText(CString(""));
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
int CProjectDlg::GetDAQM()
{
	if(!good) return -1;//û������


	int tempDAQM;CString str;
	edit_daqm.GetWindowText(str);
	tempDAQM=_ttoi(str);//�ӱ༭��õ��µ�VA ID


	if(tempDAQM>11 || tempDAQM<0)//Խ����
	{
		str.Format(__T("%d"),DAQM);
		edit_daqm.SetWindowText(str);//�༭����ʾ��ֵ
		return DAQM;//���ؾ�ֵ
	}
	else
	{
		return tempDAQM;//������ֵ
	}
}
int CProjectDlg::GetDVA()
{
	if(!good) return -1;//û������


	int tempDVA;CString str;
	edit_dva.GetWindowText(str);
	tempDVA=_ttoi(str);//�ӱ༭��õ��µ�VA ID


	if(tempDVA>5 || tempDVA<0)//Խ����
	{
		str.Format(__T("%d"),DVA);
		edit_dva.SetWindowText(str);//�༭����ʾ��ֵ
		return DVA;//���ؾ�ֵ
	}
	else
	{
		return tempDVA;//������ֵ
	}
}
void CProjectDlg::SetVAID(int tempVAID)
{
	if(!good) return;//û������


	if(tempVAID>72 || tempVAID<1) return;//Խ����


	if(tempVAID==VAID)return;//����û�б仯


	VAID=tempVAID;//����ֵ����VA ID
	DAQM=(VAID-1)/6;DVA=(VAID-1)%6;//����DAQM��DVA
	
	
	CString str;
	//VAID�༭����ʾ��ֵ
	str.Format(__T("%d"),VAID);
	edit_vaid.SetWindowText(str);
	//DAQM�༭����ʾ��ֵ
	str.Format(__T("%d"),DAQM);
	edit_daqm.SetWindowText(str);
	//DVA�༭����ʾ��ֵ
	str.Format(__T("%d"),DVA);
	edit_dva.SetWindowText(str);


	for(int i=0;i<128;i++)//ѭ��2��VA�����ݣ��õ�ֵ
	{
		str.Format(__T("%d"),int(buffer[(VAID-1)*128+i]&0x00ff));//��buffer�õ�2��VA����
		v_edit[i]->SetWindowText(str);//�ڶԻ�������ʾ2��VA����
	}


	str.Format(__T("��ַ��Χ(��1��ʼ)��%d - %d"),(VAID-1)*128+1,VAID*128);
	static_address.SetWindowText(str);
}

void CProjectDlg::SetDAQM(int tempDAQM)
{
	if(!good) return;//û������


	if(tempDAQM>11 || tempDAQM<0) return;//Խ����


	if(tempDAQM==DAQM)return;//����û�б仯


	DAQM=tempDAQM;//����ֵ����VA ID
	int tempVAID=DAQM*6+DVA+1;//����VA ID
	
	
	SetVAID(tempVAID);
}

void CProjectDlg::SetDVA(int tempDVA)
{
	if(!good) return;//û������


	if(tempDVA>5 || tempDVA<0) return;//Խ����


	if(tempDVA==DVA)return;//����û�б仯


	DVA=tempDVA;//����ֵ����VA ID
	int tempVAID=DAQM*6+DVA+1;//����VA ID
	
	
	SetVAID(tempVAID);
}

CProjectDlg::CProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX,IDC_EDIT1,edit_vaid);
	DDX_Control(pDX,IDC_SPIN1,spin_vaid);

	DDX_Control(pDX,IDC_EDIT2,edit_daqm);
	DDX_Control(pDX,IDC_SPIN2,spin_daqm);

	DDX_Control(pDX,IDC_EDIT3,edit_dva);
	DDX_Control(pDX,IDC_SPIN3,spin_dva);

	DDX_Control(pDX,IDC_STATIC_ADDRESS,static_address);

}

BEGIN_MESSAGE_MAP(CProjectDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CProjectDlg::SPIN_vaid)
	ON_BN_CLICKED(IDC_BUTTON2, &CProjectDlg::BTN_NewVAData)
	ON_BN_CLICKED(IDC_BUTTON3, &CProjectDlg::BTN_OpenFile)
	ON_BN_CLICKED(IDC_BUTTON4, &CProjectDlg::BTN_Output)
	ON_BN_CLICKED(IDC_BUTTON5, &CProjectDlg::BTN_GenerateTest)
	ON_EN_CHANGE(IDC_EDIT1, &CProjectDlg::EDIT_vaid)
	ON_EN_CHANGE(IDC_EDIT2, &CProjectDlg::EDIT_daqm)
	ON_EN_CHANGE(IDC_EDIT3, &CProjectDlg::EDIT_dva)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CProjectDlg::SPIN_daqm)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &CProjectDlg::SPIN_dva)
END_MESSAGE_MAP()


// CProjectDlg ��Ϣ�������

BOOL CProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	//���༭������
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
				CRect(xx,yy,xx+x_width,yy+y_width),this,0);
			v_edit.Add(pEdit);

			xx+=x_period;
		}
		xx=x_begin;
		yy+=y_period;
	}


	ResetAll();//��������


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
	ResetAll();//�������


	CFileDialog mydlg(TRUE);//���ļ��Ի���
	if(mydlg.DoModal()!=IDOK) return;//û��ѡ���ļ�


	CString str=mydlg.GetPathName();
	ifstream ifile(str,ios::binary);//�������ļ�
	if(!ifile.is_open()) return;//�ļ�û��


	ifile.read(buffer,DET_NUM);//��ȡ�ļ�
	ifile.close();ifile.clear();


	good=1;
	SetVAID(1);//��ʾ����
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
	ResetAll();//�������


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

void CProjectDlg::EDIT_vaid()
{
	SetVAID(GetVAID());
}

void CProjectDlg::EDIT_daqm()
{
	SetDAQM(GetDAQM());
}

void CProjectDlg::EDIT_dva()
{
	SetDVA(GetDVA());
}
void CProjectDlg::SPIN_vaid(NMHDR *pNMHDR, LRESULT *pResult)
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


void CProjectDlg::SPIN_daqm(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if(!good) return;
	if(pNMUpDown->iDelta==1)
	{
		SetDAQM(DAQM-1);
	}
	else
	{
		SetDAQM(DAQM+1);
	}

	*pResult = 0;
}

void CProjectDlg::SPIN_dva(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if(!good) return;
	if(pNMUpDown->iDelta==1)
	{
		SetDVA(DVA-1);
	}
	else
	{
		SetDVA(DVA+1);
	}

	*pResult = 0;
}
