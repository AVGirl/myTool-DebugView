
// DebugView.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDebugViewApp: 
// �йش����ʵ�֣������ DebugView.cpp
//

class CDebugViewApp : public CWinApp
{
public:
	CDebugViewApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDebugViewApp theApp;