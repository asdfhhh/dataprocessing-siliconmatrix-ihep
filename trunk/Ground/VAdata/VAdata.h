// VAdata.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVAdataApp:
// �йش����ʵ�֣������ VAdata.cpp
//

class CVAdataApp : public CWinApp
{
public:
	CVAdataApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVAdataApp theApp;