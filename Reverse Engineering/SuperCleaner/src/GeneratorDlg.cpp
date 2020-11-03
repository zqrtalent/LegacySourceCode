// GeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Generator.h"
#include "GeneratorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneratorDlg dialog

CGeneratorDlg::CGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneratorDlg)
	m_strName = _T("");
	m_strCode = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneratorDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strCode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CGeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnGenerate)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneratorDlg message handlers

BOOL CGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu("About");
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGeneratorDlg::OnPaint() 
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
HCURSOR CGeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGeneratorDlg::OnGenerate() 
{
	if( UpdateData(TRUE) )
		if( !m_strName.IsEmpty() )
		{
			DWORD dwTemp = 0;
			DWORD dwDecoders[4];
			memset(&dwDecoders,0,16);
			LPSTR lpBuffer = m_strName.GetBuffer(0);
			
			int  loop = 0;
			while(lpBuffer[loop])
			{
				dwTemp = 0x26 +  lpBuffer[loop];
				dwDecoders[0] += dwTemp;
				loop ++;
			}
			
			loop = 0;
			while(lpBuffer[loop])
			{
				dwTemp = 0x34 *  lpBuffer[loop];
				dwDecoders[1] += dwTemp;
				loop ++;
			}
			
			loop = 0;
			while(lpBuffer[loop])
			{
				dwTemp = 0xC  +  lpBuffer[loop];
				dwDecoders[2] += dwTemp;
				loop ++;
			}
			
			loop = 0;
			while(lpBuffer[loop])
			{
				dwTemp = 0xE  *  lpBuffer[loop];
				dwDecoders[3] += dwTemp;
				loop ++;
			}

			m_strCode.Format("%d-%d-%d-%d",dwDecoders[0],dwDecoders[1],dwDecoders[2],dwDecoders[3]);
			UpdateData(FALSE);

			return;
		}
	m_strCode.Format("Error");
	UpdateData(FALSE);
}

void CGeneratorDlg::OnButton2() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
