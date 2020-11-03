// Crack_CCStudio3_0.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Crack_CCStudio3_0.h"
#include "Crack_CCStudio3_0Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCrack_CCStudio3_0App

BEGIN_MESSAGE_MAP(CCrack_CCStudio3_0App, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCrack_CCStudio3_0App construction

CCrack_CCStudio3_0App::CCrack_CCStudio3_0App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCrack_CCStudio3_0App object

CCrack_CCStudio3_0App theApp;


// CCrack_CCStudio3_0App initialization

BOOL CCrack_CCStudio3_0App::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();

	CWinApp::InitInstance();

	CCrack_CCStudio3_0Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
