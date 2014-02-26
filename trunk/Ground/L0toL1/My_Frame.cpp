#include "stdafx.h"//����������ұ���������.h�ļ�֮ǰ�������ǳ���
#include"My_Frame.h"

//#define Error(err) ErrorCode=err;exit(0);

MyClass::MyClass()
{
	buffersize=-1;events=0;
	good=0;
}
unsigned short MyClass::CheckCRC(char* buf,int len)//ģ���ŷɵĳ���
{
	int i,j;
	char t;
	memset(crc_reg,1,16);
	for(i=0;i<len;i++)
	{
		for(j=0;j<8;j++)
		{	
			t=crc_reg[15]^((buf[i]>>(7-j))&0x01);//��֡������ʼ����CRCУ��
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


	unsigned short tt;
	for(i=0;i<16;i++)
	{
		tt|=(crc_reg[i]<<i);
	}
	return tt;
}

void MyClass::OpenFiles(LPVOID params)
{
	CL0toL1Dlg *p_dlg=(CL0toL1Dlg*)params;					//�õ����ھ��
	if(!buffersize)	buffersize=0;							//��ֹ�Ѿ�����һ��
	good=0;


	ifile.close();ifile.clear();							//���������
	ifile.open(InputFileName,ios::binary);					//��L0���ݣ��Ƽ������ƴ�
	if(!ifile.is_open())									//�Ƿ�ɹ���
	{
		p_dlg->Show_Log(my.InputFileName+(CString)"  Not Opened");Sleep(300);
		p_dlg->Show_Log(__T("---------------------------------------------------------------------------------------------------------------------"));
		return ;
	}


	ifile.seekg(0,ios::end);								//�ҳ��ȱر�
	buffersize=ifile.tellg();								//�ҵ�����
	if(buffersize<2)         								//��ȡ�ֽڳ���̫С
	{
		p_dlg->Show_Log(my.InputFileName+(CString)"  Buffersize too small");
		return ;
	}
	ifile.seekg(0,ios::beg);								//��ȡָ��ص���ͷ
	p_dlg->Show_Log(my.InputFileName+(CString)"  L0 DataFile Successfully Opened");Sleep(500);
	p_dlg->Show_Log(__T("---------------------------------------------------------------------------------------------------------------------"));


	ofile.close();ofile.clear();							//��������
	ofile.open((InputFileName+(CString)"0"),ios::binary);	//�½�L1�ļ�
	if(!ofile.is_open())									//�Ƿ�ɹ���
	{
		p_dlg->Show_Log(my.InputFileName+(CString)"0  Not Created");
		return ;
	}


	good=1;
	p_dlg->Show_Log(my.InputFileName+(CString)"0  L1 DataFile Successfully Created");Sleep(500);
	p_dlg->Show_Log(__T("---------------------------------------------------------------------------------------------------------------------"));
}
UINT CheckCRC_Thread( LPVOID params )
{
	CL0toL1Dlg *p_dlg=(CL0toL1Dlg*)params;
	char msg[1000];
	char buffer[2000];							//һ��֡������
	int readnumber=0;								//�ܹ������������

//	p_dlg->Show_Log(("######################"));
//	p_dlg->Show_Log("Check Start");

	char buf;
	while(!my.ifile.eof())
	{
		my.ifile.get(buf);readnumber++;
		if(buf==0xEB)
		{
			my.ifile.get(buf);readnumber++;
			if(buf==0x90)									//�ҵ�eb90
			{
				my.events++;									//��ȡ��ѧ������+1

				my.ifile.read(buffer,4);

				my.counts=int(buffer[0]&0x00ff);				//��ȡ����֡����
				my.fee=int(buffer[1]&0x003f);					//��ȡfee��ע��ռ6bit
				my.length=int((buffer[2]<<8)&0xff00)+int(buffer[3]&0x00ff);//��ȡfee��ע��ռ6bit
				

				my.ifile.read(buffer+4,my.length-2);				//��ȡһ��֡�Ŀ�ѧ����+CRCУ����
				readnumber+=(my.length+2);


				if(my.CheckCRC(buffer,my.length+2))				//CRCУ�飬����Ϊ����֡��+2
				{
					sprintf(msg,"CRC Error: FrameCount=%d, FEE=%d, FrameLength=%d��FrameID",my.counts,my.fee,my.length,my.events);
					p_dlg->Show_Log(msg);
				}
				else
				{
					my.ofile.write(buffer+4,my.length-4);			//д��һ��֡�Ŀ�ѧ���ݵ��ļ�
				}


				if(my.events%10==0)							//ÿ��100��֡��ӡһ��
				{
					sprintf(msg,"Process %04d event",my.events);
					p_dlg->text_packet.SetWindowTextW((CString)msg);
					sprintf(msg,"Processed %04d Bytes --> %3.1f%%",readnumber+1,(readnumber+1)*100.0/my.buffersize);
					p_dlg->text_size.SetWindowTextW((CString)msg);
				}
			}
		}
	}

	//�ر���������ļ�
	my.ifile.close();my.ifile.clear();
	my.ofile.close();my.ofile.clear();

	//CRCУ�����
//	p_dlg->Show_Log(("Check End!"));
//	p_dlg->Show_Log(("######################"));
	sprintf(msg,"Process %04d event",my.events);
	p_dlg->text_packet.SetWindowTextW((CString)msg);
	sprintf(msg,"Processed %04d Bytes --> %3.1f%%",my.buffersize,100);
	p_dlg->text_size.SetWindowTextW((CString)msg);

	return 0;
}
int GenerateEvent(char* ch,int len)
{
	int i=0,j;
	ch[i++]=(char)1;
	ch[i++]=(char)2;
	ch[i++]=(char)3;
	ch[i++]=(char)4;
	ch[i++]=(char)5;
	ch[i++]=(char)6;
	ch[i++]=(char)7;
	ch[i++]=(char)8;
	ch[i++]=(char)9;
	ch[i++]=(char)10;

	ch[i++]=0xeb;
	ch[i++]=0x90;
	ch[i++]=(char)20;//֡����
	ch[i++]=(char)30;//FEE
	ch[i++]=((len&0xFF00)>>8);//֡����1
	ch[i++]=(len&0x00FF);//֡����2

	for(j=0;j<len-4;j++)
	{
		ch[i+j]=(char)j;
	}

	ch[i+len-4]=(char)40;//CRC 1
	ch[i+len-3]=(char)50;//CRC 2

	return i+len-2;
}
void MyClass::GenerateTestData()
{
	ofstream oofile("test.txt",ios::binary);
	char ch[10000];
	int l,i;
	for(i=500;i<600;i++)
	{
		l=GenerateEvent(ch,i*2);	oofile.write(ch,l);
	}
	oofile.close();
}
void MyClass::Test(LPVOID params)
{
	CL0toL1Dlg *p_dlg=(CL0toL1Dlg*)params;

	p_dlg->Show_Log(CString("hahahahahahahahahaha"));
}

MyClass my;//��ʼ�������������ļ�����
