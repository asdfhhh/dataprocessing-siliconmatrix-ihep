#include<iostream>
using namespace std;

#include"Package.h"
#include"Definition.h"



void main()
{
	Package::CinMode();


	//mypackage->OpenFile();

	//	mypackage->ReadFile();

	//����TH1F[DET_NUM]��������
	if(Package::SetMode==MODE_RAW)
	{
		mypackage->GenerateTestHist(300,10);
	} else if(Package::SetMode==MODE_DOWN)
	{
		mypackage->GenerateTestHist(200,20);
	} else if(Package::SetMode==MODE_CAL)
	{
		mypackage->GenerateTestHist(50,10);
	}
	mypackage->Analysis();

	mypackage->Output();

}