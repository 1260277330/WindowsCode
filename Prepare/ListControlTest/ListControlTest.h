
// ListControlTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CListControlTestApp: 
// �йش����ʵ�֣������ ListControlTest.cpp
//

class CListControlTestApp : public CWinApp
{
public:
	CListControlTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CListControlTestApp theApp;