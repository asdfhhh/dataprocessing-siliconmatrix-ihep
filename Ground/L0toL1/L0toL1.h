// L0toL1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CL0toL1App:
// �йش����ʵ�֣������ L0toL1.cpp
//

class CL0toL1App : public CWinApp
{
public:
	CL0toL1App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CL0toL1App theApp;