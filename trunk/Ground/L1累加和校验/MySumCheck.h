#ifndef MYSUMCHECK_H
#define MYSUMCHECK_H

#include<fstream>
using namespace std;


const int MODENUM=7;


class CMySumCheck
{
public:
	CMySumCheck();


	//�ļ�
	ifstream ifile;
	ofstream ofile;
	int good;
	int filelength,readlength;
	int readevents,goodevents;
	CString InputFileName;
	CString OutputFileName;
	void OpenFile();


	//���ݰ�
	int mode,readmode;//0����ģʽ��1ԭʼģʽ��2�̶�ģʽ��3���߸��£�4�´�ģʽ��5��ռλ����6æռλ��
	void SetReadMode();//buffer[0]�����������(0010~~1101)��Ȼ������Ӧ��ģʽ(0~~6)����ֵ��readmode
	int fee,length,trigger_stat,trigger_id;

	//ÿ��ģʽ�ж��ٸ�L1.5���ݰ��ļ�
	int mode_filenum[MODENUM];
	void NewOutputFile();//�ر�����ļ���Ȼ�����mode���½�����ļ�
	CString OutputFileTitle;


	//�ۼӺ�У��
	int sum,readsum;//�ۼӺ�
	char buffer[50000];//�ҵ�EEBB��һ�ζ�ȡ������������
	friend UINT thread_SumCheck(LPVOID params);//�߳�


	//ͳ��
	int mode_num[MODENUM],error_num[MODENUM];

	
	//ϵͳ��Ϣ
	CList<CString,CString> l_msg;
	//ÿ��ģʽ����Ϣ
	CList<CString,CString> l_msg_normal,l_msg_raw,l_msg_cali,l_msg_pds,l_msg_down,l_msg_empty,l_msg_busy;


	void Reset();

};
extern CMySumCheck my;


#endif