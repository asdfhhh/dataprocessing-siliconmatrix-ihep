#pragma once


// CDLG5 �Ի���

class CDLG5 : public CDialog
{
	DECLARE_DYNAMIC(CDLG5)

public:
	CDLG5(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG5();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
