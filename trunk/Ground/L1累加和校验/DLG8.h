#pragma once


// CDLG8 �Ի���

class CDLG8 : public CDialog
{
	DECLARE_DYNAMIC(CDLG8)

public:
	CDLG8(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDLG8();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
