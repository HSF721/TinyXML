
// XML_Operate_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXML_Operate_MFCApp: 
// �йش����ʵ�֣������ XML_Operate_MFC.cpp
//

class CXML_Operate_MFCApp : public CWinApp
{
public:
	CXML_Operate_MFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CXML_Operate_MFCApp theApp;