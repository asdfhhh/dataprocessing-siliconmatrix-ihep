#!/home/rui/work/root/bin/root
#Filename: Pedestal.cpp
{
#include "Identifier.h"
	gROOT->ProcessLine(".L ReadRaw.cc");
	char filename[100];
	char crc_char;
	bool crc_flag=true;
	cout<< "please input the binary file name(.bin/.dat):" ;
	cin>>filename;
	cout<< "Do you need CRC check?(y/n):" ;
	cin>>crc_char;
	if(crc_char=='y')crc_flag=true;
	else if(crc_char=='n')crc_flag=false;
	else 
	{
		printf("input error!\n");
		exit(0);
	}
	ReadRaw(filename,crc_flag,1,RAW_ID);
}
