#pragma once


// CDLG6 �Ի���

class CDLG6 : public CDialog
{
	DECLARE_DYNAMIC(CDLG6)

public:
	CDLG6(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG6();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
