#pragma once


// CDLG7 �Ի���

class CDLG7 : public CDialog
{
	DECLARE_DYNAMIC(CDLG7)

public:
	CDLG7(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG7();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
