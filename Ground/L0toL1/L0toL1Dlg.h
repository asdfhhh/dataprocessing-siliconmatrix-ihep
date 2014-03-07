// L0toL1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CL0toL1Dlg �Ի���
class CL0toL1Dlg : public CDialog
{
// ����
public:
	CL0toL1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_L0TOL1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//�б��
	CListBox LISTBOX_control;
	afx_msg void OnBnClickedBtn_Clearmsg();
	void Reset_Listbox();
	void Display_Listbox();
	//CRCУ��
	afx_msg void OnBnClickedBtn_CRCcheck();
	//����
	CProgressCtrl PROGRESS1_control;
	CStatic STATIC_PROGRESS_control;
	void Display_Process();
	void Reset_Process();
	//��ʱ��
	CStatic STATIC_TIMER_control;
	long timer_begin;
	int timer_used,timer_remain;
	int minute_used,second_used,minute_remain,second_remain;
	void Display_Timer();
	void Reset_Timer();
	//�ļ���
	CStatic STATIC_EVENT_control;
	void Display_Event();
	void Reset_Event();
	//��ʾ�߳�
	friend UINT Thread_Display(LPVOID params);
	//�ļ�
	afx_msg void OnBnClickedBtn_OpenL0Data();
	afx_msg void OnBnClickedBtn_OutputL1Data();
	//�˳�
	afx_msg void OnBnClicked_Exit();
};
