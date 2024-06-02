
// Test_SG_PNGView.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTest_SG_PNGViewApp:
// See Test_SG_PNGView.cpp for the implementation of this class
//

class CTest_SG_PNGViewApp : public CWinApp
{
public:
	CTest_SG_PNGViewApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

};

extern CTest_SG_PNGViewApp theApp;
