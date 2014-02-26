//������Ҫ����
#ifndef DEFINITION_H
#define DEFINITION_H


//�������ݴ���ģʽ�����ݰ��еİ�������
const int MODE_RAW=1;			//ԭʼģʽ
const int MODE_CAL=2;			//�̶�ģʽ
const int MODE_DOWN=3;			//�´�ģʽ

//�������ݴ������
const int DET_NUM=10;			//̽������Ŀ
const int TH1F_CH=8192;			//TH1F�ֵ���Ŀ
const int TH1F_MAX=16384;		//TH1F������

//Ҫ�򿪵�L1��ѧ����
const char L1_FILENAME[]="1.txt";



//ԭʼģʽ������ļ���
const char RAW_PDFNAME[100]="PDF_Raw.pdf";
const char RAW_RMSNAME[100]="Package_RMS.txt";//RMSע���
const char RAW_PDSNAME[100]="Package_PDS.txt";//PDSע���
//�̶�ģʽ������ļ���
const char CAL_PDFNAME[100]="PDF_Cal.pdf";
//�´�ģʽ������ļ���
const char DOWN_PDFNAME[100]="PDF_Down.pdf";



//�̶�ģʽ��Ѱ�����������ѡ��SearchѰ�廹��SearchHighResѰ��
//#define TSPECTRUM_SearchHighRes
#define TSPECTRUM_Search
	#ifdef TSPECTRUM_Search
	//Search�Ĳ���
		const double	CALFIT_SIGMA=8;//Search��sigma
		const double	CALFIT_THRE=0.1;//Search����ֵ
	#endif
	#ifdef TSPECTRUM_SearchHighRes
	//SearchHighRes�Ĳ���
		const float		CALFIT_SIGMA=8;//SearchHighRes��sigma
		const double	CALFIT_THRE=2;//SearchHighRes����ֵ
		const bool		CALFIT_BGRM=true;//SearchHighRes��ȥ������
		const int		CALFIT_DECON=3;//SearchHighRes��deconlteration
		const bool		CALFIT_MARK=true;//SearchHighRes��markov
		const int		CALFIT_AVER=3;//SearchHighRes��averwindow
	#endif


#endif
