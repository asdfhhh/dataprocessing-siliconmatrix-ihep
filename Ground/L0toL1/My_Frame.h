//��¼һ����ѧ����֡��������Ϣ-------------------------------------------
#ifndef _MY_FRAME_H
#define _MY_FRAME_H

#include<fstream>
#include<iostream>
#include <cstring>
using namespace std;
#include"L0toL1.h"
#include"L0toL1Dlg.h"
#include"Resource.h"


class MyClass
{
public:
	MyClass();
	int good;									//�Ƿ�������ͨ�����ļ�ˢ��good
public://��ѧ����֡������
	int counts;									//��ȡ����֡����
	int fee;									//FEE���
	int length;									//����֡��
	int events;									//�ڼ�����ѧ����
public://CRCУ��
	unsigned short CheckCRC(char* buf,int len);//������֡����CRCУ��
	unsigned char crc_reg[16];
	friend UINT CheckCRC_Thread( LPVOID params );
public://�ļ�����
	CString InputFileName;
	CString OutputFileName;
	ofstream ofile;
	ifstream ifile;
	void OpenFiles(LPVOID params);				//��L0���ݣ��½�L1�ļ����ļ�����+0��
	long buffersize;							//һ�����ļ��ĳ���
public://������������
	void GenerateTestData();
	void Test(LPVOID params);
};

extern MyClass my;//��������Դ��������---------------------


#endif	//#ifndef _MY_FRAME_H
