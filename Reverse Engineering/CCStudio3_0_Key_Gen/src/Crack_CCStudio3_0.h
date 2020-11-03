// Crack_CCStudio3_0.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CCrack_CCStudio3_0App:
// See Crack_CCStudio3_0.cpp for the implementation of this class
//

class CCrack_CCStudio3_0App : public CWinApp
{
public:
	CCrack_CCStudio3_0App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCrack_CCStudio3_0App theApp;