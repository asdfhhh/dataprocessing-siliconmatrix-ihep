#pragma once


// CDLG4 �Ի���

class CDLG4 : public CDialog
{
	DECLARE_DYNAMIC(CDLG4)

public:
	CDLG4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG4();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
