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
	//�޸�VA ID��һϵ�в���
	int VAID;//VA��ID����1~72
	CEdit edit_vaid;//VA ID�ı༭��
	int GetVAID();//��VA ID�ı༭��õ�VA ID
	void SetVAID(int);//��ֵ�µ�VA ID��ˢд����
	afx_msg void EDIT_vaid();//�༭��༭
	CSpinButtonCtrl spin_vaid;//VA ID�����¼�ͷ
	afx_msg void SPIN_vaid(NMHDR *pNMHDR, LRESULT *pResult);//������¼�ͷ


	//�޸�DAQM��һϵ�в���
	int DAQM;//VA��DAQM����0-11
	CEdit edit_daqm;
	int GetDAQM();
	void SetDAQM(int);
	afx_msg void EDIT_daqm();
	CSpinButtonCtrl spin_daqm;
	afx_msg void SPIN_daqm(NMHDR *pNMHDR, LRESULT *pResult);


	//�޸�DVA��һϵ�в���
	int DVA;//VA��DVA����0-5
	CEdit edit_dva;
	int GetDVA();
	void SetDVA(int);
	CSpinButtonCtrl spin_dva;
	afx_msg void EDIT_dva();
	afx_msg void SPIN_dva(NMHDR *pNMHDR, LRESULT *pResult);


	//�༭�����еĲ���
	afx_msg void BTN_NewVAData();//���µ�VA���ݸ�ֵ��buffer
	CArray<CEdit*,CEdit*> v_edit; //�༭������
	char buffer[DET_NUM];//�洢ÿ��ͨ��������


	afx_msg void BTN_OpenFile();//�������ļ�
	afx_msg void BTN_GenerateTest();//������������
	int good;//�Ƿ���ȷ�����ļ�


	afx_msg void BTN_Output();//������ļ�


	CStatic static_address;


	void ResetAll();//���
};
