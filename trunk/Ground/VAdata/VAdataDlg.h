// VAdataDlg.h : ͷ�ļ�
//

#pragma once
#include<fstream>
using namespace std;

const int DET_NUM=9216;

// CProjectDlg �Ի���
class CProjectDlg : public CDialog
{
// ����
public:
	CProjectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VADATA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	int VAID;//VA��ID����1~72
	CEdit edit_vaid;//VA ID�ı༭��
	int GetVAID();//��VA ID�ı༭��õ�VA ID
	void SetVAID(int);//��ֵ�µ�VA ID��ˢд����
	afx_msg void EDIT_Change();//�༭��༭
	CSpinButtonCtrl ctrl_vaid;//VA ID�����¼�ͷ
	afx_msg void SPIN_VAID(NMHDR *pNMHDR, LRESULT *pResult);//������¼�ͷ


	afx_msg void BTN_NewVAData();//���µ�VA���ݸ�ֵ��buffer
	CArray<CEdit*,CEdit*> v_edit; //�༭������
	char buffer[DET_NUM];//�洢ÿ��ͨ��������


	afx_msg void BTN_OpenFile();//�������ļ�
	afx_msg void BTN_GenerateTest();//������������
	int good;//�Ƿ���ȷ�����ļ�


	afx_msg void BTN_Output();//������ļ�


	void ResetAll();//���
};
