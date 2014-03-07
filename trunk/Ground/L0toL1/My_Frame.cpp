#include"stdafx.h"

void MyClass::Reset()
{
	good=0;
	filelength=0;readlength=0;
	readevents=0;goodevents=0;
	ifile.close();ifile.clear();
	ofile.close();ofile.clear();
	l_msg.RemoveAll();	
}
MyClass::MyClass()
{
	Reset();
}
unsigned short MyClass::CheckCRC(char* buf,int len)//ģ���ŷɵĳ���
{
	int i,j;
	unsigned char t;
	memset(crc_reg,1,16);
	for(i=0;i<len;i++)
	{
		for(j=0;j<8;j++)
		{	
			t=crc_reg[15]^(((buf[i]&0x00ff)>>(7-j))&0x01);//��֡������ʼ����CRCУ��
			crc_reg[15]=crc_reg[14];
			crc_reg[14]=crc_reg[13];
			crc_reg[13]=crc_reg[12];
			crc_reg[12]=crc_reg[11]^t;
			crc_reg[11]=crc_reg[10];
			crc_reg[10]=crc_reg[9];
			crc_reg[9]=crc_reg[8];
			crc_reg[8]=crc_reg[7];
			crc_reg[7]=crc_reg[6];
			crc_reg[6]=crc_reg[5];
			crc_reg[5]=crc_reg[4]^t;
			crc_reg[4]=crc_reg[3];
			crc_reg[3]=crc_reg[2];
			crc_reg[2]=crc_reg[1];
			crc_reg[1]=crc_reg[0];
			crc_reg[0]=t;
		}
	}


	unsigned short tt=0;
	for(i=0;i<16;i++)
	{
		tt|=(crc_reg[i]<<i);
	}
	return tt;
}

void MyClass::OpenFile()
{
	CString str;


	Reset();												//ȫ����λ


	ifile.open(InputFileName,ios::binary);					//��L0���ݣ��Ƽ������ƴ�
	if(!ifile.is_open())									//�Ƿ�ɹ���
	{
		str=InputFileName;
		str+=CString(" Not Opened");
		l_msg.AddTail(str);
		return ;
	}


	ifile.seekg(0,ios::end);								//�ҳ��ȱر�
	filelength=ifile.tellg();								//�ҵ�����
	if(filelength<2)         								//��ȡ�ֽڳ���̫С
	{
		str=InputFileName;
		str+=CString(" Buffersize too small");
		l_msg.AddTail(str);
		return ;
	}


	ifile.seekg(0,ios::beg);								//��ȡָ��ص���ͷ
	str=InputFileName;
	str+=CString(" Successfully Opened");
	l_msg.AddTail(str);


	OutputFileName=InputFileName;OutputFileName+=CString("0");//��������ļ���
	ofile.open(OutputFileName,ios::binary);					//�½�L1�ļ�
	if(!ofile.is_open())									//�Ƿ�ɹ���
	{
		str=OutputFileName;
		str+=CString(" Not Opened");
		l_msg.AddTail(str);
		return ;
	}
	else
	{
		str=OutputFileName;
		str+=CString(" Successfully Created");
		l_msg.AddTail(str);
	}


	good=1;													//��ǳɹ���������������������
}
UINT CheckCRC_Thread( LPVOID params )
{
	if(my.good!=1) return 0;									//����ȷ�����ļ�
	if(my.filelength<1)return 0;								//���ļ�����
	if(my.ifile.tellg()<0 || my.ifile.tellg()>my.filelength)return 0;//�Ѷ���
	my.l_msg.AddTail(CString("######################"));
	my.l_msg.AddTail(CString("CRC Check Start"));


	CString str;
	char ch;
	while(!my.ifile.eof() && my.good==1)
	{
		my.ifile.get(ch);
		if((ch&0xff)==0xEB)
		{
			my.ifile.get(ch);
			if((ch&0xff)==0x90)								
			{
				//�ҵ�eb90------------------------------------------------------------
				++my.readevents;								//��ȡ��ѧ������+1
				my.ifile.read(my.buffer,4);


				my.counts=int(my.buffer[0]&0x00ff);				//��ȡ����֡����
				my.fee=int(my.buffer[1]&0x003f);					//��ȡfee��ע��ռ6bit
				my.length=int((my.buffer[2]<<8)&0xff00)+int(my.buffer[3]&0x00ff);//��ȡ����
//				if(my.length<16 || my.length>1996)//���ݳ���Խ��
				if(my.length<1 || my.length>1996)//���ݳ���Խ��
				{
					//     To   Do  
					str.Format(__T("������Խ�磬����Ϊ%d��λ��%d"),my.length,int(my.ifile.tellg()));
					my.l_msg.AddTail(str);
					continue;
				}


				my.ifile.read(my.buffer+4,my.length-2);				//��ȡһ��֡�Ŀ�ѧ����+CRCУ����


				if(my.CheckCRC(my.buffer,my.length+2))				//CRCУ�飬����Ϊ����֡��+2
				{
					str.Format(__T("CRC Error: EventID(��1��ʼ)=%d,FrameCount=%d, FEE=%d, Length=%d")
						,my.readevents,my.counts,my.fee,my.length);
					my.l_msg.AddTail(str);
					continue;
				}
				else
				{
					++my.goodevents;
					my.ofile.write(my.buffer+4,my.length-4);			//д��һ��֡�Ŀ�ѧ���ݵ��ļ�
				}
			}
		}
		my.readlength=my.ifile.tellg();
	}


	//CRCУ�����
	if(my.good==1)
	{
		my.readlength=my.filelength;
		my.l_msg.AddTail(CString("Check End!"));
	}
	else if(my.good==2)
	{
		my.l_msg.AddTail(CString("Too Much Error, Program Break!!!"));
	}
	else if(my.good==3)
	{
		my.l_msg.AddTail(CString("BUG Exist, Program Break!!!"));
	}
	my.l_msg.AddTail(CString("######################"));


	//�ر���������ļ�
	my.ifile.close();my.ifile.clear();
	my.ofile.close();my.ofile.clear();
	
	
	//����״̬
	my.good=0;


	return 0;
}
MyClass my;//��ʼ�������������ļ�����
