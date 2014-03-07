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
#include<time.h>
#include<stdio.h>
#include "afxwin.h"
using namespace std;


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
	afx_msg void BTN_Open();
	afx_msg void BTN_Check();
	//ѡ�
	CTabCtrl tab;
	afx_msg void TAB_Change(NMHDR *pNMHDR, LRESULT *pResult);
	void Reset_Tab();


	//������
	CProgressCtrl PROGRESS1_control;
	CStatic STATIC_PROGRESS_control;
	void Display_Process();
	void Reset_Process();


	//ʱ��
	CStatic STATIC_TIMER_control;
	long timer_begin;
	int timer_used,timer_remain;
	int minute_used,second_used,minute_remain,second_remain;
	void Display_Timer();
	void Reset_Timer();


	//�ӶԻ���
	CArray<CDialog*,CDialog*> v_subdlg;
	CArray<CString,CString> v_subdlgname;
	CArray<int,int> v_subdlgIDD;
	void InitialSubDialog();


	//�б����ʾ����λ��
	CArray<CListBox*,CListBox*> v_listbox;
	CArray<int,int> v_listboxIDC;
	void InitialListBox();
	void Display_ErrorMessage();//���б����ʾ�ۼӺ�У��������Ϣ
	void Reset_ErrorMessage();


	//�༭����ʾ����İ���Ŀ���ۼӺͳ�����Ŀ
	CArray<CStatic*,CStatic*> v_modenum;
	CArray<int,int> v_modenumIDC;
	CArray<CStatic*,CStatic*> v_errornum;
	CArray<int,int> v_errornumIDC;
	void InitialStatic();//��ʼ������
	void Reset_Statistic();
	void Display_Statistic();//��ʾĳһ��ģʽ��Ŀ����Ŀ���ۼӺͳ������Ŀ


	//����
	void ResetAll();


	//ֱ����ʾ��Ϣ
	void Display_SystemMessage();


	//�Ի�����߳�
	void DisplayAll();
	friend UINT Thread_Display(LPVOID params);
};
