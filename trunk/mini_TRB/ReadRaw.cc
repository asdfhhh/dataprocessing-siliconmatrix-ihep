TFile* ReadRaw(char* filename, bool crc_flag, bool rms_flag,unsigned int data_mode)
{
	if(rms_flag)gROOT->ProcessLine(".L WriteRMS.cc");
	int count=0;
	bool home_run=true;
	char home_suf[4]=".dat";
	int err_time=0;
	int data_q,adc,ch;
	char Hname[10];
	char rsuffix[10]=".root" ;
	char rootname[100];
	char ch_data;
	char time_data[8];
	int seq_check=0;
	int t_adc[CH_NUM];
	char Tname[10];

	ifstream f(filename,ifstream::binary);
	if(f.is_open())
	{  
		home_run=strcmp(home_suf,filename+strlen(filename)-4);
		strcpy(rootname,filename);
		strcat(rootname,rsuffix);
		TFile * rootf= new TFile(rootname,"RECREATE" );
		//convert to histogram;
		TH1F *h[CH_NUM];
		for (int i= 0; i< CH_NUM; i++)
		{
			sprintf(Hname, "Ch%d",i);
			h[i] = new TH1F(Hname,"spectrum" ,8192,0,16384);
		}
		//make event analysis
		TTree*t= new TTree("event" ,"data of event");
		for (int i= 0; i< CH_NUM; i++)
		{
			sprintf(Hname, "t_Ch%d",i);
			sprintf(Tname, "adc%d/I",i);
			t->Branch(Hname,&t_adc[i],Tname);
			t_adc[i]=0;
		}
		t->Branch("trigger",&seq_check,"trigger/I");
		while (!f.eof())
		{
			f.read(&ch_data,1);
			if(((ch_data)&0x00ff)==0x90)
			{
				f.read(&ch_data,1);
				if(((ch_data)&0x00ff)==0xeb)
				{
					//read the ID
					f.read(&ch_data,1);
					/*if(count&&int(ch_data&0x00ff))
					{
						if((seq_check+1)!=int(ch_data&0x00ff))
						{
							cout<<"The triger count error!"<<endl;
							cout<<"the last triger is "<<seq_check<<endl;
							cout<<"This triger is "<<int(ch_data&0x00ff)<<endl;
						}
						seq_check=int(ch_data&0x00ff);
					}
					else seq_check=int(ch_data&0x00ff);*/
					//read the data model
					f.read(&ch_data,1);
					if(unsigned int((ch_data)&0x00ff)!=data_mode)continue;

					//reading the channels
					for(int i=0;i<CH_NUM;i++)
					{
						//calculate the channel number
						ch= (i%2)*192+i/2;
						if((ch>(CH_NUM-1)))continue ;
						//read the ADC
						f.read(( char *)&adc,2);
						adc= int(adc&0x0000ffff);
						t_adc[ch]=adc;
						h[ch]->Fill(adc);
					}
					for(int ii=0;ii<8;ii++)f.read(&ch_data,1);

					count++;
					t->Fill();
					for (int i= 0; i< CH_NUM; i++)
					{
						t_adc[i]=0;
					}
				}
				else continue;			
			}
			else continue ;
		}
		f.close();
		rootf->Write();
		//if(rms_flag)WriteRMS(filename,h);
	}
	else
	{
		cout << "Error opening file" ;
	}
	return rootf;
}