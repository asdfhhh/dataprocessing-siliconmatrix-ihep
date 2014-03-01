// L1�ۼӺ�У��Dlg.h : ͷ�ļ�
//

#pragma once
#include"DLG1.h"
#include"DLG2.h"
#include"DLG3.h"
#include"DLG4.h"
#include"DLG5.h"
#include"DLG6.h"
#include"DLG7.h"
#include"DLG8.h"
#include<fstream>
using namespace std;
const int MODENUM=7;


// CSumDlg �Ի���
class CSumDlg : public CDialog
{
// ����
public:
	CSumDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_L1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//ѡ�
	CTabCtrl tab;
	afx_msg void TAB_Change(NMHDR *pNMHDR, LRESULT *pResult);


	//������
	int filelength;
	CProgressCtrl bar;
	CStatic progress;
	void ShowProcess(int p=-1);


	//�ļ�
	afx_msg void BTN_Open();
	ifstream ifile;
	ofstream ofile;
	int good;


	//�ۼӺ�У��
	int sum,readsum;//�ۼӺ�
	int mode,readmode;//0����ģʽ��1ԭʼģʽ��2�̶�ģʽ��3���߸��£�4�´�ģʽ��5��ռλ����6æռλ��
	char buffer[40000];//�ҵ�EEBB��һ�ζ�ȡ������������
	friend UINT thread_SumCheck(LPVOID params);//�߳�
	afx_msg void BTN_Check();


	//ͳ��
	int mode_num[MODENUM],error_num[MODENUM];
	CArray<CStatic*,CStatic*> v_modenum;
	CArray<int,int> v_modenumIDC;
	CArray<CStatic*,CStatic*> v_errornum;
	CArray<int,int> v_errornumIDC;
	void InitialStatic();


	//�ӶԻ���
	CArray<CDialog*,CDialog*> v_subdlg;
	CArray<CString,CString> v_subdlgname;
	CArray<int,int> v_subdlgIDD;
	void InitialSubDialog();


	//�б����ʾ����λ��
	CArray<CListBox*,CListBox*> v_listbox;
	CArray<int,int> v_listboxIDC;
	void InitialListBox();



	//����
	void ResetAll();
};
