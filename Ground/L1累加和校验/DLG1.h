#pragma once


// CDLG1 �Ի���

class CDLG1 : public CDialog
{
	DECLARE_DYNAMIC(CDLG1)

public:
	CDLG1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
