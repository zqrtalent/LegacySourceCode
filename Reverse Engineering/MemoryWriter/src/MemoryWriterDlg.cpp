// MemoryWriterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MemoryWriter.h"
#include "MemoryWriterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemoryWriterDlg dialog

CMemoryWriterDlg::CMemoryWriterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMemoryWriterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMemoryWriterDlg)
	m_strFile = _T("");
	m_idProcess = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemoryWriterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemoryWriterDlg)
	DDX_Text(pDX, IDC_CODE_FILE, m_strFile);
	DDX_Text(pDX, IDC_PROCESS_ID, m_idProcess);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMemoryWriterDlg, CDialog)
	//{{AFX_MSG_MAP(CMemoryWriterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemoryWriterDlg message handlers

BOOL CMemoryWriterDlg::OnInitDialog()
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

void CMemoryWriterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMemoryWriterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMemoryWriterDlg::OnWrite() 
{
	if( UpdateData() )	
	{
		HANDLE hProc = OpenProcess(MAXIMUM_ALLOWED,FALSE,m_idProcess);
		HANDLE hFile = CreateFile (m_strFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
		DWORD cbRead = 0;

		if( hFile && hProc )
		{
			DWORD dwAddress = 0;
			DWORD dwSize    = 0;
			DWORD dwOldProtect = 0;
			DWORD dwProtect = 0;
			
			ASSERT(ReadFile(hFile,&dwAddress,4,&cbRead,NULL));
			ASSERT(ReadFile(hFile,&dwSize,4,&cbRead,NULL));

			void* p = ::malloc(dwSize);
			ASSERT(ReadFile(hFile,p,dwSize,&cbRead,NULL));

			// query for memory to have read_write access.
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQueryEx(hProc,(void*)dwAddress,&mbi,sizeof(MEMORY_BASIC_INFORMATION));
			VERIFY(VirtualProtectEx(hProc,mbi.BaseAddress,mbi.RegionSize,PAGE_READWRITE,&dwProtect));
			
			ASSERT(WriteProcessMemory(hProc,(void*)dwAddress,p,dwSize,&cbRead));
			
			// Change the protection back.
			VERIFY(VirtualProtectEx(hProc,mbi.BaseAddress,mbi.RegionSize,mbi.Protect,&dwOldProtect));

			free(p);
			CloseHandle(hFile);
		}
		
		CloseHandle(hProc);
	}
}
