#pragma once


// CDLG3 �Ի���

class CDLG3 : public CDialog
{
	DECLARE_DYNAMIC(CDLG3)

public:
	CDLG3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG3();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
