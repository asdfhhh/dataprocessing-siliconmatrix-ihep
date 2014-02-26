#ifndef PACKAGE_H
#define PACKAGE_H

#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<iomanip>//��setw
using namespace std;
#include"Definition.h"

#include"TGraph.h"
#include"TH1.h"
#include"TH1F.h"
#include"TF1.h"
#include"TFile.h"
#include"TCanvas.h"
#include"TPolyMarker.h"
#include"TSpectrum.h"


//L1������ѧ���ݰ�
class Package
{
public:
	Package();
public://ģʽ
	static int SetMode;								//Ҫ�����ģʽ
	static void CinMode();							//��Ļ���빤��ģʽ��Ȼ�������������
public://��Ҫ�������
	long filelength;								//��¼Ҫ˳��򿪵��ļ�����
	long readlength;
	ifstream ifile;	ofstream ofile;
	int good;										//��������״̬������ִ��һ��OpenFile����ˢ��
public://���������޹�
	TH1F *hist[DET_NUM];
	int mode,fee,length,trigger_stat,trigger_id,sum;//�������룬FEE��ţ����ݰ���������״̬�������ţ��ۼӺ�
	char buffer[30000];								//һ����������Ŀ�ѧ����
	void OpenFile();								//ȷ��Ҫ�򿪵��ļ������浽vector<string> v_filename���棬�����Դ��ļ���ȡ���ȡ�
	void ReadOneTrigger();							//Ѱ��EEBB,��ȡ���������ݣ�ȷ�ϰ���������ȷ��Ȼ������ݴ���buffer����
	void ReadFile();								//ѭ����ȡ�����ļ�������ReadOneTrigger()��FillHist()
	TCanvas *c1;
public://��Ҫ�������������
	virtual void FillHist()=0;						//��buffer[30000]��������hist[DET_NUM]
	virtual void GenerateTestHist(int,int){};		//���������ף���Analysis��Output
	virtual void Analysis()=0;						//����hist[DET_NUM]���õ�ͳ�����ݽ����
	virtual void Output()=0;						//����ͳ�����ݣ���ͼ������ļ�
};
//ԭʼģʽ
class Package_Raw:public Package
{
public:
	Package_Raw();
	int RMS[DET_NUM],PDS[DET_NUM];					//ͨ����˹��ϵõ�PDS/RMS
	TGraph *gr_RMS,*gr_PDS;							//PDS/RMSͳ��ͼ

	virtual void FillHist();
	virtual void Analysis();						//���Hist���õ�PDS/RMS����
	virtual void Output();
	virtual void GenerateTestHist(int,int);			//������Hist���������ݣ���һ��������ƽ��ֵ���ڶ���������sigma
};
//�´�ģʽ
class Package_Down:public Package_Raw
{
public:
	Package_Down();
	int RMS_read[DET_NUM],PDS_read[DET_NUM];		//��������ݣ��ǵð�PDS����һλ
	TGraph *gr_RMS_read,*gr_PDS_read;				//�����PDS/RMSͳ��ͼ
	virtual void FillHist();
	virtual void Output();
};
//�̶�ģʽ
class Package_Cal:public Package
{
public:
	Package_Cal();
	int PeakNum[DET_NUM];								//��ϵķ����Ŀ
	double Slope[DET_NUM];								//��ϵ�б��
#ifdef TSPECTRUM_Search
	int Search(TH1F *S_hist,float* S_peaksx,float* S_peaksy,double S_sigma,double S_threshold);//SearchѰ��
#endif
#ifdef TSPECTRUM_SearchHighRes
	int SearchHighRes(TH1F *SHR_hist,float* SHR_peaksx,float* SHR_peaksy,float SHR_sigma,double SHR_threshold,bool SHR_backgroundRemove,int SHR_deconlterations,bool SHR_markov,int SHR_averWindow);//SearchHighResѰ��
#endif
	virtual void FillHist();
	virtual void Analysis();
	virtual void Output();
	virtual void GenerateTestHist(int,int);			//������Hist���������ݣ���һ�������Ƿ����Ŀ���ڶ���������sigma
};

//ȫ�ֵı���
Package *mypackage;
int Package::SetMode=-1;
//Package��ľ���ʵ��
Package::Package()
{
	char ch[100];
	for(int i=0;i<DET_NUM;i++)//��ʼ��TH1F
	{
		sprintf(ch,"Hist%d",i+1);
		hist[i]=new TH1F(ch,ch,TH1F_CH,0,TH1F_MAX);
		hist[i]->SetStats(0);
	}
	c1=new TCanvas("c1","c1",800,800);

	//��ʼ��Ϊ����������״̬
	good=0;
	filelength=0;
	readlength=0;
}
void Package::CinMode()
{
	while(Package::SetMode!=MODE_RAW &&Package::SetMode!=MODE_CAL &&Package::SetMode!=MODE_DOWN)
	{
		cout<<"���������ݴ���ģʽ"<<endl;
		cout<<"ԭʼģʽ("<<MODE_RAW<<") �� �̶�ģʽ("<<MODE_CAL<<") ���´�ģʽ("<<MODE_DOWN<<")"<<endl;
		cin>>Package::SetMode;
		switch(Package::SetMode)
		{
		case MODE_RAW:
			cout<<"��ѡ����ԭʼģʽ"<<endl;
			mypackage=new Package_Raw();
			break;
		case MODE_CAL:
			cout<<"��ѡ���˿̶�ģʽ"<<endl;
			mypackage=new Package_Cal();
			break;
		case MODE_DOWN:
			cout<<"��ѡ�����´�ģʽ"<<endl;
			mypackage=new Package_Down();
			break;
		default:
			cout<<"����ģʽ����"<<endl;
			break;
		}
	}
	cout<<"cinmode"<<endl;
}
void Package::OpenFile()							
{
	good=0;
	filelength=0;
	readlength=0;


	ifile.close();ifile.clear();ifile.open(L1_FILENAME,ios::binary);
	if(ifile.is_open())
	{
		ifile.seekg(0,ios::beg);ifile.seekg(0,ios::end);
		filelength=ifile.tellg();
		good=1;
		cout<<"L1�ļ��򿪳ɹ����ܳ��� "<<filelength<<endl;
	}
	else//�򿪲��ɹ�
	{
		cout<<"L1�ļ���ʧ��"<<endl;
		filelength=0;
	}
}
void Package::ReadOneTrigger()												///Ѱ��EEBB,��ȡ���������ݣ�ȷ�ϰ���������ȷ
{
	char ch,ch1,ch2;
	while(!ifile.eof())
	{
		ifile.get(ch);++readlength;
		if(ch==0xEE)
		{
			ifile.get(ch);++readlength;
			if(ch==0xBB)
			{
				//�ҵ�EEBB-----------------------------------------------
				ifile.get(ch);mode=int(ch&0x00ff);//��ȡ������
				if(mode!=Package::SetMode)//�������벻��
				{
					cout<<"��ȡ�İ������� "<<mode<<" ��Ԥ�õ������� "<<Package::SetMode<<" ��ͬ"<<endl;
					good=0;	return;
				}
				ifile.get(ch);fee=int(ch&0x00ff);//��ȡFEE
				ifile.get(ch);ifile.get(ch1);length=int((ch<<8)&0xff00)+int(ch1&0x00ff);//��ȡ������


				ifile.read(buffer,length-6);//һ���Զ�ȡһ�������ڵĿ�ѧ����


				ifile.get(ch);ifile.get(ch1);ch2=ch;
				trigger_stat=int((ch2>>4)&0x00ff);//��ȡ����״̬��ע����ǰ4��
				trigger_id=int((ch<<8)&0x0f00)+int(ch1&0x00ff);//��ȡ�����ţ�ע���ú�4��
				ifile.get(ch);ifile.get(ch1);
				sum=int((ch<<8)&0xff00)+int(ch1&0x00ff);//��ȡ�ۼӺ�


				readlength+=(length+2);


				break;//����ѭ�������ļ���ȡ����virtual void ReadFile()����buffer����
			}
		}
	}
}

void Package::ReadFile()
{
	if(!good)
	{
		cout<<"�����ļ�����ȷ��ִֹͣ��ReadFile"<<endl;
		return;
	}
	if(readlength>=filelength)
	{
		cout<<"�ļ��Ѿ���ȡ���"<<endl;
		good=0;
		return;
	}
	//��ʼ��ȡ����
	ifile.seekg(0,ios::beg);
	while(!ifile.eof()&&good)
	{
		ReadOneTrigger();
		FillHist();
		cout<<right<<setw(11)<<filelength<<" / "<<left<<setw(11)<<readlength<<right<<setw(8)<<100.*readlength/filelength<<"%"<<endl;
	}
}
//Package_Raw��ľ���ʵ��
Package_Raw::Package_Raw(){}
void Package_Raw::FillHist()
{
	//--------------- TO DO -----------------------
}
void Package_Raw::Analysis()
{
	//��ϣ��õ�ÿ��TH1F��PDS��RMS����Ϊ�Ǹ�˹��ϵ�sigma�����¼������Լ�������
	TF1 *gausfit=new TF1("gausfit","[0]*exp(-0.5*pow(((x-[1])/[2]),2))",0,TH1F_MAX);
	for(int i=0;i<DET_NUM;i++)
	{
		gausfit->SetParameter(1,hist[i]->GetMean());
		gausfit->SetParameter(2,hist[i]->GetRMS());
		hist[i]->GetXaxis()->SetRangeUser(hist[i]->GetMean()-hist[i]->GetRMS()*5,hist[i]->GetMean()+hist[i]->GetRMS()*5);
		hist[i]->Fit("gausfit","Q");
		PDS[i]=gausfit->GetParameter(1);
		RMS[i]=gausfit->GetParameter(2);


		if((i+1)%10==0) cout<<"Fitting "<<i+1<<" / "<<DET_NUM<<endl;
	}
}
void Package_Raw::Output()
{
	//�õ������PDS/RMSͳ��ͼ
	int xaxis[DET_NUM];
	for(int i=0;i<DET_NUM;i++)
	{
		xaxis[i]=i+1;
	}
	TGraph *gr_RMS=new TGraph(DET_NUM,xaxis,RMS);
	gr_RMS->SetTitle("RMS Distribution");
	gr_RMS->GetXaxis()->SetTitle("Channel");
	gr_RMS->GetXaxis()->CenterTitle(1);
	gr_RMS->GetYaxis()->SetTitle("RMS");
	gr_RMS->GetYaxis()->CenterTitle(1);
//	gr_RMS->GetYaxis()->SetRangeUser(0,250);
	TGraph *gr_PDS=new TGraph(DET_NUM,xaxis,PDS);
	gr_PDS->SetTitle("Pedestal Distribution");
	gr_PDS->GetXaxis()->SetTitle("Channel");
	gr_PDS->GetXaxis()->CenterTitle(1);
	gr_PDS->GetYaxis()->SetTitle("PDS");
	gr_PDS->GetYaxis()->CenterTitle(1);
//	gr_PDS->GetYaxis()->SetRangeUser(0,500);


	//�����н����Ϊͼ��PDF
	char tempchar[100];
	sprintf(tempchar,"%s%s",RAW_PDFNAME,"[");c1->Print(tempchar);//����PDF�ļ�

	gr_RMS->Draw("AL");c1->Print(RAW_PDFNAME);
	gr_PDS->Draw("AL");c1->Print(RAW_PDFNAME);
	for(int i=0;i<DET_NUM;i++)
	{
		hist[i]->Draw();c1->Print(RAW_PDFNAME);
	}
	sprintf(tempchar,"%s%s",RAW_PDFNAME,"]");c1->Print(tempchar);//����PDF�ļ�


	//���RMS/PDSע�����RMSռ1���ֽڣ�PDS����1λռ1���ֽ�
	ofstream oRMS(RAW_RMSNAME,ios::binary);
	ofstream oPDS(RAW_PDSNAME,ios::binary);
	char ch_RMS[DET_NUM],ch_PDS[DET_NUM];
	for(int i=0;i<DET_NUM;i++)
	{
		ch_RMS[i]=int(RMS[i]&0x00ff);
		ch_PDS[i]=int((PDS[i]>>1)&0x00ff);//����1λ
	}
	oRMS.write(ch_RMS,DET_NUM);
	oPDS.write(ch_PDS,DET_NUM);
	oRMS.close();oRMS.clear();
	oPDS.close();oPDS.clear();
}
void Package_Raw::GenerateTestHist(int mean,int sigma)
{
	TF1 *gausfit=new TF1("gausfit","[0]*exp(-0.5*pow(((x-[1])/[2]),2))",0,TH1F_MAX);
	gausfit->SetParameter(0,1);
	gausfit->SetParameter(1,mean);
	gausfit->SetParameter(2,sigma);


	hist[0]->FillRandom("gausfit",10000);
	char tempchar[100];
	for(int i=1;i<DET_NUM;i++)
	{
		strcpy(tempchar,hist[i]->GetName());
		delete hist[i];
		hist[i]=(TH1F*)hist[0]->Clone(tempchar);
		hist[i]->SetTitle(tempchar);
	}
}
//Package_Down��ľ���ʵ��
Package_Down::Package_Down(){}
void Package_Down::FillHist()
{
	//--------------- TO DO -----------------------
}
void Package_Down::Output()
{
	//�õ������PDS/RMSͳ��ͼ
	int xaxis[DET_NUM];
	for(int i=0;i<DET_NUM;i++)
	{
		xaxis[i]=i+1;
	}
	TGraph *gr_RMS=new TGraph(DET_NUM,xaxis,RMS);
	gr_RMS->SetTitle("RMS Distribution");
	gr_RMS->GetXaxis()->SetTitle("Channel");
	gr_RMS->GetXaxis()->CenterTitle(1);
	gr_RMS->GetYaxis()->SetTitle("RMS");
	gr_RMS->GetYaxis()->CenterTitle(1);
	gr_RMS->GetYaxis()->SetRangeUser(0,250);
	TGraph *gr_PDS=new TGraph(DET_NUM,xaxis,PDS);
	gr_PDS->SetTitle("Pedestal Distribution");
	gr_PDS->GetXaxis()->SetTitle("Channel");
	gr_PDS->GetXaxis()->CenterTitle(1);
	gr_PDS->GetYaxis()->SetTitle("PDS");
	gr_PDS->GetYaxis()->CenterTitle(1);
	gr_PDS->GetYaxis()->SetRangeUser(0,500);


	//����RMS/PDSע�����RMSռ1���ֽڣ��ǵð�PDS����1λ
	ifstream iRMS(RAW_RMSNAME,ios::binary);
	ifstream iPDS(RAW_PDSNAME,ios::binary);
	char ch_RMS[DET_NUM],ch_PDS[DET_NUM];
	iRMS.read(ch_RMS,DET_NUM);
	iPDS.read(ch_PDS,DET_NUM);
	for(int i=0;i<DET_NUM;i++)
	{
		RMS_read[i]=int(ch_RMS[i]);
		PDS_read[i]=int(ch_PDS[i]<<1);
	}
	iRMS.close();iRMS.clear();
	iPDS.close();iPDS.clear();


	//�õ������RMS/PDSͳ��ͼ
	TGraph *gr_RMS_read=new TGraph(DET_NUM,xaxis,RMS_read);
	gr_RMS_read->SetTitle("RMS_read Distribution Comparison");
	gr_RMS_read->GetXaxis()->SetTitle("Channel");
	gr_RMS_read->GetXaxis()->CenterTitle(1);
	gr_RMS_read->GetYaxis()->SetTitle("RMS_read");
	gr_RMS_read->GetYaxis()->CenterTitle(1);
	gr_RMS_read->GetYaxis()->SetRangeUser(0,250);
	gr_RMS_read->SetLineColor(2);//������Ǻ�ɫ����
	TGraph *gr_PDS_read=new TGraph(DET_NUM,xaxis,PDS_read);
	gr_PDS_read->SetTitle("Pedestal Distribution Comparison");
	gr_PDS_read->GetXaxis()->SetTitle("Channel");
	gr_PDS_read->GetXaxis()->CenterTitle(1);
	gr_PDS_read->GetYaxis()->SetTitle("PDS_read");
	gr_PDS_read->GetYaxis()->CenterTitle(1);
	gr_PDS_read->GetYaxis()->SetRangeUser(0,500);
	gr_PDS_read->SetLineColor(2);//������Ǻ�ɫ����


	//�����н����Ϊͼ��PDF
	char tempchar[100];
	sprintf(tempchar,"%s%s",DOWN_PDFNAME,"[");c1->Print(tempchar);//����PDF�ļ�

	gr_RMS_read->Draw("AL");gr_RMS->Draw("L");c1->Print(DOWN_PDFNAME);
	gr_PDS_read->Draw("AL");gr_PDS->Draw("L");c1->Print(DOWN_PDFNAME);
	for(int i=0;i<DET_NUM;i++)
	{
		hist[i]->Draw();c1->Print(DOWN_PDFNAME);
	}
	sprintf(tempchar,"%s%s",DOWN_PDFNAME,"]");c1->Print(tempchar);//����PDF�ļ�
}
//Package_Cal��ľ���ʵ��
Package_Cal::Package_Cal(){}
void Package_Cal::FillHist()
{
	//--------------- TO DO -----------------------
}

#ifdef TSPECTRUM_Search//SearchѰ��
int Package_Cal::Search(TH1F *S_hist,float* S_peaksx,float* S_peaksy,double S_sigma,double S_threshold)
{
	float *PeakArray;

	//�½�һ��TSpectrum
	TSpectrum *s = new TSpectrum();

	//Ѱ��
	int number=s->Search(S_hist,S_sigma,"",S_threshold);

	//������Ͻ���õ�X��Yλ��
	PeakArray = s->GetPositionX();//���ص���TH1F�ĺ����꣡������������
	for(int i=0;i<number&&i<100;i++)//��Ϊ���100����
	{
			S_peaksx[i]=PeakArray[i];
			S_peaksy[i]=S_hist->GetBinContent(S_hist->FindBin(S_peaksx[i]));
	}

	//����Marker��ע��λ�ã����󶨵�TH1F
	TPolyMarker* pm=new TPolyMarker(number,S_peaksx,S_peaksy);
	pm->SetMarkerStyle(23);
	pm->SetMarkerColor(kRed);
	pm->SetMarkerSize(1.3);
	S_hist->GetListOfFunctions()->Add(pm);

	return number;
}
#endif
#ifdef TSPECTRUM_SearchHighRes//SearchHighResѰ��
int Package_Cal::SearchHighRes(TH1F *SHR_hist,float* SHR_peaksx,float* SHR_peaksy,float SHR_sigma,double SHR_threshold,bool SHR_backgroundRemove,int SHR_deconlterations,bool SHR_markov,int SHR_averWindow)
{
	float dest[100], *PeakArray;

	//�½�һ��TSpectrum
	TSpectrum *s = new TSpectrum();

	//�õ�TH1F��ÿ��������
	float *source;
	source=SHR_hist->GetArray()+1;

	//Ѱ��
	int number=s->SearchHighRes(source,dest,SHR_hist->GetNbinsX(),SHR_sigma,SHR_threshold,SHR_backgroundRemove,SHR_deconlterations,SHR_markov,SHR_averWindow);
	cout<<"Ѱ����Ŀ "<<number<<endl;

	//������Ͻ���õ�X��Yλ��
	PeakArray = s->GetPositionX();//���ص��Ƿ�ֵ��source�����еĵڼ����������Ǻ����꣡������������
	for(int i=0;i<number&&i<100;i++)//��Ϊ���100����
	{
		SHR_peaksy[i]=(int(PeakArray[i]+1)-PeakArray[i]) * source[int(PeakArray[i])]   +   source[int(PeakArray[i]+1)] * (PeakArray[i]-int(PeakArray[i]));
		SHR_peaksx[i]=(int(PeakArray[i]+1)-PeakArray[i]) * SHR_hist->GetBinCenter(int(PeakArray[i]+1))    +    SHR_hist->GetBinCenter(int(PeakArray[i]+2)) * (PeakArray[i]-int(PeakArray[i]));
	}

	//����Marker��ע��λ�ã����󶨵�TH1F
	TPolyMarker* pm=new TPolyMarker(number,SHR_peaksx,SHR_peaksy);
	pm->SetMarkerStyle(23);
	pm->SetMarkerColor(kRed);
	pm->SetMarkerSize(1.3);
	SHR_hist->GetListOfFunctions()->Add(pm);

	return number;
}
#endif
void Package_Cal::Analysis()
{
	float Peak_X[100],Peak_Y[100];						//����Ѱ����
	float Peak_Xmax,Peak_Xmin;							//�����λ�����Сֵ�����ڵõ�б��
	//ѭ��Ѱ��ÿ��̽�����Ŀ̶��ף����õ�б�ʺͷ���Ŀ
	for(int i=0;i<DET_NUM;i++)
	{
		//Ѱ��
#ifdef TSPECTRUM_Search//SearchѰ��
		PeakNum[i]=Search(hist[i],Peak_X,Peak_Y,CALFIT_SIGMA,CALFIT_THRE);
#endif
#ifdef TSPECTRUM_SearchHighRes//SearchHighResѰ��
		PeakNum[i]=SearchHighRes(hist[i],Peak_X,Peak_Y,CALFIT_SIGMA,CALFIT_THRE,CALFIT_BGRM,CALFIT_DECON,CALFIT_MARK,CALFIT_AVER);
#endif

		//�õ�б�ʣ���������3���򷵻�б��Ϊ1
		if(PeakNum[i]<3){
			Slope[i]=1;
		} else {
			//��ʼ�������Сֵ
			Peak_Xmax=Peak_X[0];Peak_Xmin=Peak_X[0];
			for(int j=1;j<PeakNum[i];j++)
			{
				if(Peak_X[j]<Peak_Xmin)
				{
					Peak_Xmin=Peak_X[j];//����ȷ����Сֵ
				}
				else if(Peak_X[j]>Peak_Xmax)
				{
					Peak_Xmax=Peak_X[j];//����ȷ�����ֵ
				}
			}
			Slope[i]=(Peak_Xmax-Peak_Xmin) / (PeakNum[i]-1);//б��
		}


		cout<<"Searching Peak "<<i+1<<" / "<<DET_NUM<<endl;
	}
}
void Package_Cal::Output()
{


	//����ͳ��ͼ:б��vsͨ����б��vsѰ����
	double ch[DET_NUM];
	for(int i=0;i<DET_NUM;i++)
	{
		ch[i]=i+1;//ͨ��idΪ��1~DET_NUM
	}
	TGraph *gr_SlopeVsChannel=new TGraph(DET_NUM,ch,Slope);
	gr_SlopeVsChannel->SetTitle("Slope vs Channel");
	gr_SlopeVsChannel->GetXaxis()->SetTitle("Channel");gr_SlopeVsChannel->GetXaxis()->CenterTitle(1);
	gr_SlopeVsChannel->GetYaxis()->SetTitle("Slope");gr_SlopeVsChannel->GetYaxis()->CenterTitle(1);
	for(int i=0;i<DET_NUM;i++)
	{
		ch[i]=PeakNum[i];//ͨ��idΪ��1~DET_NUM
	}
	TGraph *gr_SlopeVsNumber=new TGraph(DET_NUM,ch,Slope);
	gr_SlopeVsNumber->SetTitle("Slope vs Number");
	gr_SlopeVsNumber->GetXaxis()->SetTitle("Number");gr_SlopeVsNumber->GetXaxis()->CenterTitle(1);
	gr_SlopeVsNumber->GetYaxis()->SetTitle("Slope");gr_SlopeVsNumber->GetYaxis()->CenterTitle(1);


	//�����н����Ϊͼ��PDF
	char tempchar[100];
	sprintf(tempchar,"%s%s",CAL_PDFNAME,"[");
	c1->Print(tempchar);
	gr_SlopeVsChannel->Draw("AL");c1->Print(CAL_PDFNAME);
	gr_SlopeVsNumber->Draw("A*");c1->Print(CAL_PDFNAME);
	for(int i=0;i<DET_NUM;i++)
	{
		hist[i]->Draw();c1->Print(CAL_PDFNAME);
	}
	sprintf(tempchar,"%s%s",CAL_PDFNAME,"]");
	c1->Print(tempchar);
}
void Package_Cal::GenerateTestHist(int peaknumber,int sigma)
{
	TF1 *gausfit=new TF1("gausfit","[0]*exp(-0.5*pow(((x-[1])/[2]),2))",0,TH1F_MAX);
	gausfit->SetParameter(0,1);
	gausfit->SetParameter(2,sigma);
//	c1->Print("test.pdf[");
	for(int i=0;i<DET_NUM;i++)
	{
		for(int j=0;j<peaknumber;j++)
		{
			gausfit->SetParameter(1,double(TH1F_MAX)/peaknumber*(j+0.5));
			hist[i]->FillRandom("gausfit",10000);
		}
		hist[i]->Draw();
//		c1->Print("test.pdf");
	}
//	c1->Print("test.pdf]");

}






#endif