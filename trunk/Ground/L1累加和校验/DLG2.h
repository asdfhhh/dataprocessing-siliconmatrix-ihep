#pragma once


// CDLG2 �Ի���

class CDLG2 : public CDialog
{
	DECLARE_DYNAMIC(CDLG2)

public:
	CDLG2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
