// Winamp5_21CrackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Winamp5_21Crack.h"
#include "Winamp5_21CrackDlg.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinamp5_21CrackDlg dialog



CWinamp5_21CrackDlg::CWinamp5_21CrackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinamp5_21CrackDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinamp5_21CrackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinamp5_21CrackDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SELECT, OnBnClickedSelect)
	ON_BN_CLICKED(IDC_CRACK, OnBnClickedCrack)
END_MESSAGE_MAP()


// CWinamp5_21CrackDlg message handlers

BOOL CWinamp5_21CrackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinamp5_21CrackDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinamp5_21CrackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWinamp5_21CrackDlg::OnBnClickedSelect()
{
	CFileDialog fnd(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,"Winamp Executable (winamp.exe)|winamp.exe||",this);
	if( fnd.DoModal() != IDOK ) 
		return;

	GetDlgItem(IDC_CRACK)->EnableWindow (TRUE);
	GetDlgItem(IDC_SELECT)->EnableWindow(FALSE);
	_sPath  = fnd.GetPathName();
}

void CWinamp5_21CrackDlg::OnBnClickedCrack()
{
	// if have read & write access.
	if( !access(_sPath,0x06) )
	{
		char  code[2];
		DWORD written;

		HANDLE hWinamp = CreateFile(_sPath.GetBuffer(0),GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0L,OPEN_EXISTING,0L,0L);
		if( hWinamp != INVALID_HANDLE_VALUE )
		{
			code[0] = 0x6A;
			code[1] = 0x00;
			if( SetFilePointer(hWinamp,0x15525,NULL,FILE_CURRENT)           != 0x15525 ) goto error;
			WriteFile(hWinamp,&code,2,&written,0L);
			if( SetFilePointer(hWinamp,0x15529-0x15525-2,NULL,FILE_CURRENT) != 0x15529 ) goto error;
			WriteFile(hWinamp,&code,2,&written,0L);
			code[0] = 0x89;
			code[1] = 0x30;
			if( SetFilePointer(hWinamp,0x15371-0x15529-2,NULL,FILE_CURRENT) != 0x15371 ) goto error;
			WriteFile(hWinamp,&code,2,&written,0L);
			code[0] = 0x6A;
			code[1] = 0x00;
			if( SetFilePointer(hWinamp,0x1543F-0x15371-2,NULL,FILE_CURRENT) != 0x1543F ) goto error;
			WriteFile(hWinamp,&code,2,&written,0L);

			CloseHandle(hWinamp);
			GetDlgItem(IDC_CRACK)->EnableWindow (TRUE);
			AfxMessageBox("cracked successfull by <<ZQR>>");
		}
		else
			AfxMessageBox("can't open file");
		return;
	}	
error:
	AfxMessageBox("can't crack");
}
