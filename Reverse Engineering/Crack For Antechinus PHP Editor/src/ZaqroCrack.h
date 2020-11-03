// ZaqroCrack.h : main header file for the ZAQROCRACK application
//

#if !defined(AFX_ZAQROCRACK_H__47289860_C4DE_432D_9326_2F33E102F56F__INCLUDED_)
#define AFX_ZAQROCRACK_H__47289860_C4DE_432D_9326_2F33E102F56F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZaqroCrackApp:
// See ZaqroCrack.cpp for the implementation of this class
//

class CZaqroCrackApp : public CWinApp
{
public:
	CZaqroCrackApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZaqroCrackApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZaqroCrackApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZAQROCRACK_H__47289860_C4DE_432D_9326_2F33E102F56F__INCLUDED_)
