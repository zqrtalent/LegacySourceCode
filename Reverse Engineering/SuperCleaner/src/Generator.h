// Generator.h : main header file for the GENERATOR application
//

#if !defined(AFX_GENERATOR_H__DD91009C_E8D8_4D36_9637_C79203C67BA4__INCLUDED_)
#define AFX_GENERATOR_H__DD91009C_E8D8_4D36_9637_C79203C67BA4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGeneratorApp:
// See Generator.cpp for the implementation of this class
//

class CGeneratorApp : public CWinApp
{
public:
	CGeneratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGeneratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATOR_H__DD91009C_E8D8_4D36_9637_C79203C67BA4__INCLUDED_)
