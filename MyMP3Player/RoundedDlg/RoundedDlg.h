// RoundedDlg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRoundedDlgApp:
// See RoundedDlg.cpp for the implementation of this class
//

class CRoundedDlgApp : public CWinApp
{
public:
	CRoundedDlgApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRoundedDlgApp theApp;