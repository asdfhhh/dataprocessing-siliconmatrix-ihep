//��¼һ����ѧ����֡��������Ϣ-------------------------------------------
#ifndef _MY_FRAME_H
#define _MY_FRAME_H

#include<fstream>
using namespace std;


class MyClass
{
public:
	MyClass();
	int good;									//�Ƿ�������ͨ�����ļ�ˢ��good
public://��ѧ����֡������
	int counts;									//��ȡ����֡����
	int fee;									//FEE���
	int length;									//����֡��
	int readevents,goodevents;					//�ڼ�����ѧ����
	char buffer[2000];							//һ��֡������
public://CRCУ��
	unsigned short CheckCRC(char* buf,int len);//������֡����CRCУ��
	unsigned char crc_reg[16];
	friend UINT CheckCRC_Thread( LPVOID params );
public://�ļ�����
	CString InputFileName;
	CString OutputFileName;
	ofstream ofile;
	ifstream ifile;
	void OpenFile();							//��L0���ݣ��½�L1�ļ����ļ�����+0��
	int filelength;								//һ�����ļ��ĳ���
	int readlength;								//�Ѷ�ȡ�ļ��ĳ���
public://��Ϣ
	CList<CString,CString> l_msg;				//��Ϣ

	void Reset();
};

extern MyClass my;//��������Դ��������---------------------


#endif	//#ifndef _MY_FRAME_H
