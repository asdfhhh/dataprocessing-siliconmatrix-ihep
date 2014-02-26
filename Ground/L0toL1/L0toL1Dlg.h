// L0toL1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "My_Frame.h"

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
	afx_msg void OnBnClickedBtn_Clearmsg();
	afx_msg void OnBnClickedBtn_CRCcheck();
	afx_msg void OnBnClickedBtn_OpenL0Data();
	afx_msg void OnBnClickedBtn_OutputL1Data();
	afx_msg void OnBnClicked_Exit();
public:
	CListBox m_list_log;
	CStatic text_packet,text_size,text_allsize;
	void Show_Log(CString s);
	void Show_Log(char* s);
	afx_msg void OnBnClickedBtn_GenerateTest();
};
