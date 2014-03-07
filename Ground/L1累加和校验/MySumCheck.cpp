#include"stdafx.h"

void CMySumCheck::Reset()
{
	//����
	good=0;
	filelength=0;readlength=0;
	readevents=0;goodevents=0;
	ifile.close();ifile.clear();
	ofile.close();ofile.clear();
	l_msg.RemoveAll();

	//������Ϣ���
	l_msg_normal.RemoveAll();
	l_msg_raw.RemoveAll();
	l_msg_cali.RemoveAll();
	l_msg_pds.RemoveAll();
	l_msg_down.RemoveAll();
	l_msg_empty.RemoveAll();
	l_msg_busy.RemoveAll();


	//ģʽ���
	for(int i=0;i<MODENUM;i++)
	{
		mode_filenum[i]=0;
		mode_num[i]=0;
		error_num[i]=0;
	}


	//���ݰ�
	mode=-99;readmode=-99;


	//�ۼӺ�У��
	sum=-99;readsum=-99;

}
CMySumCheck::CMySumCheck()
{
	Reset();
}
void CMySumCheck::OpenFile()
{
	CString str;


	Reset();												//ȫ����λ



	ifile.open(InputFileName,ios::binary);					//�����ݣ��Ƽ������ƴ�
	if(!ifile.is_open())									//�Ƿ�ɹ���
	{
		l_msg.AddTail(__T("�ļ��򿪴���"));
		return ;
	}


	ifile.seekg(0,ios::end);								//�ҳ��ȱر�
	filelength=ifile.tellg();								//�ҵ�����
	if(filelength<2)         								//��ȡ�ֽڳ���̫С
	{
		str.Format(__T("�ļ����� %d ̫��"),filelength);
		l_msg.AddTail(str);
		return ;
	}
	ifile.seekg(0,ios::beg);								//��ȡָ��ص���ͷ


	good=1;													//��ǳɹ���������������������
}
void CMySumCheck::SetReadMode()
{
	int tempmode=int((buffer[0]>>4)&0x000f);//����������룬ע���飡����������
	switch(tempmode)
	{
		case 2:	
			readmode=0;break;//0010=����ģʽ(0)
		case 3:	
			readmode=1;break;//0011=ԭʼģʽ(1)
		case 4:	
			readmode=2;break;//0100=�̶�ģʽ(2)
		case 5:	
			readmode=3;break;//0101=���߸���(3)
		case 6:	
			readmode=4;break;//0110=�´�ģʽ(4)
		case 7:	
			readmode=5;break;//1100=��ռλ��(5)
		case 8:	
			readmode=6;break;//1101=æռλ��(6)
		default:	
			readmode=-1;break;//������(-1)
	}
}
void CMySumCheck::NewOutputFile()
{
	//�رվ��ļ�
	ofile.close();ofile.clear();


	//�������ļ�������
	CString str;char tempchar[100];
	sprintf(tempchar,"(%d).",mode_filenum[mode]);
	str=OutputFileTitle;
	str+=CString(tempchar);
	switch(mode)
	{
	case 0:
		str+=CString("normal");
		break;
	case 1:
		str+=CString("raw");
		break;
	case 2:
		str+=CString("cali");
		break;
	case 3:
		str+=CString("pedestal");
		break;
	case 4:
		str+=CString("down");
		break;
	case 5:
		str+=CString("empty");
		break;
	case 6:
		str+=CString("busy");
		break;
	default:
		str+=CString("error");
		break;
	}


	//�����ļ�
	ofile.open(str,ios::binary);
}
UINT thread_SumCheck(LPVOID params)
{
	if(my.good!=1)												//����ȷ�����ļ�							
	{
		my.l_msg.AddTail(CString("�����ļ�����ȷ"));
		return 0;
	}
	if(my.filelength<1)											//���ļ�����
	{
		my.l_msg.AddTail(CString("�ļ�����̫��"));
		return 0;
	}
	if(my.ifile.tellg()<0 || my.ifile.tellg()>=my.filelength)	//�Ѷ���
	{
		my.l_msg.AddTail(CString("�ļ��Ѷ���"));
		return 0;
	}


	CString str;
	char ch;
	while(!my.ifile.eof() && my.good==1)
	{
		my.ifile.get(ch);
		if((ch&0xff)==0xEE)
		{
			my.ifile.get(ch);
			if((ch&0xff)==0xBB)
			{
				//�ҵ�EEBB-----------------------------------------------
				++my.readevents;								//��ȡ��ѧ������+1
				my.ifile.read(my.buffer,4);


				//��ȡ�����ͣ�ת��Ϊ��ʱ����ģʽ
				my.SetReadMode();//����buffer[0]����readmode
				if(my.readmode==-1)//����ʶ��İ�����
				{
					//     To   Do  
					my.l_msg.AddTail(CString("����ʶ��İ�������"));
					continue;
				}


				//�Ƚ������ʱ����ģʽ����һ����ģʽ�Ƿ�һ��
				if(my.readmode!=my.mode)
				{
					my.mode=my.readmode;//���ð�����
					my.mode_filenum[my.mode]++;//��Ӧ�İ����ļ���Ŀ+1
					my.NewOutputFile();//�رվ��ļ������µ�����ļ�
				}
				my.mode_num[my.mode]++;//��Ӧ�����͵���Ŀ+1


				//��ȡFEE
				my.fee=int((my.buffer[1])&0x003f);


				//��ȡ���ȣ�Ȼ��һ������һ��������
				my.length=int(((my.buffer[2])<<8)&0xff00)+int((my.buffer[3])&0x00ff);
				if(my.length<6 || my.length>40000)//���ݳ���Խ��
				{
					//     To   Do  
					my.l_msg.AddTail(CString("������̫С"));
					continue;
				}
				my.ifile.read(my.buffer+4,my.length-2);//һ���Զ�ȡʣ������


				//����״̬�ʹ�����
				my.trigger_stat=int(((my.buffer[my.length-2])>>4)&0x00ff);//��ȡ����״̬��ע����ǰ4��
				my.trigger_id=int(((my.buffer[my.length-2])<<8)&0x0f00)+int((my.buffer[my.length-1])&0x00ff);//��ȡ�����ţ�ע���ú�4��


				//�ۼӺ�У��
				my.readsum=int(((my.buffer[my.length])<<8)&0xff00)+int((my.buffer[my.length+1])&0x00ff);
				my.sum=0;
				for(int i=0;i<my.length;i++)
				{
					(my.sum)+=int((my.buffer[i])&0xff);//ע����0x00ff
				}
				if(my.sum==my.readsum)//�ۼӺ�У��ͨ��
				{
					my.ofile.write(my.buffer+4,my.length-6);//������ļ�
				}
				else//�ۼӺ�У����󣡣�������������
				{
					(my.error_num)[my.mode]++;//��Ӧģʽ���ۼӺͳ���+1
					if((my.error_num)[my.mode]<100)//����̫��Ͳ���ʾ��
					{
						str.Format(__T("���=%4d�� EEBB���=%8d�� FEE=%2d�� ������=%5d�� ����״̬=%3d�� ������=%5d, �����ۼӺ�=%5d�� �����ۼӺ�=%5d")
							,my.error_num[my.mode],my.readevents,my.fee,my.length,my.trigger_stat,my.trigger_id,my.readsum,my.sum);
						switch(my.mode)
						{
						case 0:
							my.l_msg_normal.AddTail(str);
							break;
						case 1:
							my.l_msg_raw.AddTail(str);
							break;
						case 2:
							my.l_msg_cali.AddTail(str);
							break;
						case 3:
							my.l_msg_pds.AddTail(str);
							break;
						case 4:
							my.l_msg_down.AddTail(str);
							break;
						case 5:
							my.l_msg_empty.AddTail(str);
							break;
						case 6:
							my.l_msg_busy.AddTail(str);
							break;
						}
					}
					else
					{
						my.good=2;//��ǳ���̫�࣬��ֹ����
					}
				}
			}
		}
		my.readlength=my.ifile.tellg();
	}
	

	//ѭ������
	if(my.good==1)
	{
		my.readlength=my.filelength;
	}
	else if(my.good==2)
	{
		my.l_msg.AddTail(CString("����̫�࣬��ֹ����!!!"));
	}


	//�ر���������ļ�
	my.ifile.close();my.ifile.clear();
	my.ofile.close();my.ofile.clear();
	
	
	//����״̬
	my.good=0;



	return 0;
}


CMySumCheck my;