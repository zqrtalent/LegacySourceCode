// MemoryWriter.h : main header file for the MEMORYWRITER application
//

#if !defined(AFX_MEMORYWRITER_H__907D1179_0115_467C_B2ED_305B7DE6E5E4__INCLUDED_)
#define AFX_MEMORYWRITER_H__907D1179_0115_467C_B2ED_305B7DE6E5E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMemoryWriterApp:
// See MemoryWriter.cpp for the implementation of this class
//

class CMemoryWriterApp : public CWinApp
{
public:
	CMemoryWriterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryWriterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMemoryWriterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYWRITER_H__907D1179_0115_467C_B2ED_305B7DE6E5E4__INCLUDED_)
