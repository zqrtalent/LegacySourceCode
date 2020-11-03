// Crack_CCStudio3_0Dlg.cpp : implementation file
//
#include "stdafx.h"
#include "Crack_CCStudio3_0.h"
#include "Crack_CCStudio3_0Dlg.h"
#include ".\crack_ccstudio3_0dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HRGN GetBitmapRgn(HBITMAP hBmp,COLORREF crLow,COLORREF crHigh)
{
	if( hBmp )
	{
#define MAX_RECT 200

		HRGN hRgnBmp = NULL; //Handle To The Region
		HRGN hOr     = NULL; 
		HBITMAP hDib = NULL; //Handle The Dib Image
		HDC hMemDC   = NULL; //Destination Bitmaps DC
		HDC hSrc     = NULL; //Source Bitmaps DC
		LPVOID lpMap = NULL; //Pointer to the Dib Section

		// Initialization ...
		hMemDC = CreateCompatibleDC(NULL);

		hSrc   = CreateCompatibleDC(hMemDC);
		::SelectObject(hSrc,hBmp);

		BITMAP bmp;
		memset(&bmp,0,sizeof(BITMAP));
		GetObject(hBmp,sizeof(BITMAP),&bmp);

		BITMAPINFOHEADER bmpInfo32;
		memset(&bmpInfo32,0,sizeof(BITMAPINFOHEADER));
		bmpInfo32.biBitCount = 32;
		bmpInfo32.biCompression = BI_RGB;
		bmpInfo32.biPlanes = 1;
		bmpInfo32.biHeight = bmp.bmHeight;
		bmpInfo32.biSize = sizeof(BITMAPINFOHEADER);
		bmpInfo32.biWidth = bmp.bmWidth;

		hDib = CreateDIBSection(hMemDC,(BITMAPINFO*)&bmpInfo32,DIB_RGB_COLORS,&lpMap,NULL,0);
		if( hDib )
		{
			GetObject(hDib,sizeof(BITMAP),&bmp);
			SelectObject(hMemDC,hDib);
			ASSERT(BitBlt(hMemDC,0,0,bmp.bmWidth,bmp.bmHeight,hSrc,0,0,SRCCOPY));
			
			HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE,sizeof(RGNDATA)+MAX_RECT*sizeof(RECT));
			RGNDATA * pData = (RGNDATA*)GlobalLock(hGlobal);
			pData->rdh.iType = RDH_RECTANGLES;
			pData->rdh.dwSize= sizeof(RGNDATAHEADER);
			SetRect(&pData->rdh.rcBound,MAXLONG,MAXLONG,0,0);
			pData->rdh.nRgnSize = MAX_RECT*sizeof(RECT);
			pData->rdh.nCount = 0;

			BYTE * p = (BYTE*)bmp.bmBits + (bmp.bmHeight-1)*bmp.bmWidthBytes;
			for(int y = 0; y < bmp.bmHeight; y ++)
			{
				for(int x = 0; x < bmp.bmWidth; x ++)
				{
					LONG * pColor = (LONG*)p+x;
					int x1 = x;
					while( x < bmp.bmWidth )
					{
						if( *pColor <= (signed)crLow && *pColor >= (signed)crHigh )
							break;
						
						x++;
						pColor++;
					}
					if( x > x1 )
					{
						int nRcCount = pData->rdh.nRgnSize / sizeof(RECT);
						int nCount   = pData->rdh.nCount;
						if( nCount >= nRcCount )
						{
							pData->rdh.nRgnSize += MAX_RECT*sizeof(RECT);
							GlobalUnlock(hGlobal);
							hGlobal = GlobalReAlloc(hGlobal,sizeof(RGNDATA)+pData->rdh.nRgnSize,GMEM_MOVEABLE);
							pData = (RGNDATA*)GlobalLock(hGlobal);
						}

						RECT * pRect = (RECT*)&pData->Buffer;
						SetRect(&pRect[pData->rdh.nCount],x1,y,x,y+1);
						pData->rdh.nCount ++;
						
						if( x1 < pData->rdh.rcBound.left )
							pData->rdh.rcBound.left = x1;
						if( y < pData->rdh.rcBound.top )
							pData->rdh.rcBound.top = y;
						if( x > pData->rdh.rcBound.right )
							pData->rdh.rcBound.right = x;
						if( y+1 > pData->rdh.rcBound.bottom )
							pData->rdh.rcBound.bottom = y+1;
					}
				}
				p -= bmp.bmWidthBytes;
			}

			hRgnBmp = ExtCreateRegion(NULL,sizeof(RGNDATA)+pData->rdh.nRgnSize,pData);
			
			GlobalFree(hGlobal);
			::DeleteDC(hMemDC);
			::DeleteDC(hSrc);
			return hRgnBmp;
		}
		return hRgnBmp;
	}
	else
		return NULL;	
}

// CCrack_CCStudio3_0Dlg dialog
CCrack_CCStudio3_0Dlg::CCrack_CCStudio3_0Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCrack_CCStudio3_0Dlg::IDD, pParent)
{
	m_hIcon      = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hRgnDialog = NULL;
}

void CCrack_CCStudio3_0Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SERIAL, m_editSerial);
	DDX_Control(pDX, IDC_EDIT_ACTIVATION_KEY, m_editActKey);
	DDX_Control(pDX, IDC_BUT_REGISTER, m_butRegister);
	DDX_Control(pDX, IDC_BUT_GEN_SERIAL_NUMBER, m_butGenerate);
	DDX_Control(pDX, IDC_EDIT_INSTALATION_CODE, m_editInstCode);
}

BEGIN_MESSAGE_MAP(CCrack_CCStudio3_0Dlg, CDialog)
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_GEN_SERIAL_NUMBER, OnBnClickedButGenSerialNumber)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUT_REGISTER, OnBnClickedButRegister)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCrack_CCStudio3_0Dlg message handlers

BOOL CCrack_CCStudio3_0Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	HBITMAP h = (HBITMAP)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_REGION_BMP),IMAGE_BITMAP,353,249,LR_LOADMAP3DCOLORS);
	if( h ){
		CRect rc;
		GetClientRect (&rc);
		::SetWindowPos(m_hWnd,NULL,0,0,rc.left+353,rc.top+249,SWP_NOMOVE);
		::SetWindowRgn(m_hWnd,GetBitmapRgn(h),TRUE);
		::DeleteObject(h);
	}

	OnBnClickedButGenSerialNumber();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCrack_CCStudio3_0Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCrack_CCStudio3_0Dlg::OnPaint() 
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
HCURSOR CCrack_CCStudio3_0Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCrack_CCStudio3_0Dlg::OnBnClickedButGenSerialNumber()
{
	char szSerial [30];
	char szActCode[30];
	char szInsCode[30];
	WORD wSerial  [5];
	WORD wActCode [5];
	WORD wInsCode [] = {0x21E5,0xA027,0xA8CB,0x3904,0x83C5};

	if( CCStudio3_0GenerateSerialNumber((WORD*)&wSerial) && 
		CCStudio3_0GenerateActivationKey((WORD*)&wSerial,(WORD*)&wInsCode,(WORD*)&wActCode) ){
		
		sprintf(szSerial,"%.4X-%.4X-%.4X-%.4X-%.4X",wSerial[0],wSerial[1],wSerial[2],wSerial[3],wSerial[4]);
		sprintf(szActCode,"%.4X-%.4X-%.4X-%.4X-%.4X",wActCode[0],wActCode[1],wActCode[2],wActCode[3],wActCode[4]);
		sprintf(szInsCode,"%.4X-%.4X-%.4X-%.4X-%.4X",wInsCode[0],wInsCode[1],wInsCode[2],wInsCode[3],wInsCode[4]);
	}
	else{
		strcpy(szSerial,"Error");
		strcpy(szActCode,"Error");
		strcpy(szInsCode,"Error");
	}

	m_editSerial.SetWindowText  (szSerial);
	m_editActKey.SetWindowText  (szActCode);
	m_editInstCode.SetWindowText(szInsCode);
}

// generates activation code[5 word] from serial number & instalation code. 
// stores activation code in pActCode.
bool CCrack_CCStudio3_0Dlg::CCStudio3_0GenerateActivationKey(WORD* pSerial,WORD* pInsCode,WORD* pActCode)
{
	if( IsBadReadPtr(pSerial,5*sizeof(WORD))  ||
		IsBadReadPtr(pInsCode,5*sizeof(WORD)) ||
		IsBadReadPtr(pActCode,5*sizeof(WORD))  ) return false;

	for( int nLoop=0; nLoop<5; nLoop++ ){
		pActCode[nLoop] = (WORD)rand();
	}

	/////////////////////// First Decoder of Activation Code ////////
	// for Activation Code is 17 step to check validation of that code.
	// so i (zqr) can set that bits in Activation Code.
	pActCode[0] &= -1-0x100; // clear bit.
	pActCode[0] |= (((pInsCode[4]>>15)|(pSerial[2]>>15))<<8) & 0x100;// Set bit.
	pActCode[2] &= -1-0x4000;
	pActCode[2] |= (((pInsCode[2]>>11)&(pSerial[3]>>4))<<14) & 0x4000;
	pActCode[4] &= -1-0x20;
	pActCode[4] |= (((pInsCode[2]>>14)^(pSerial[0]>>11))<<5) & 0x20;
	pActCode[1] &= -1-0x8;
	pActCode[1] |= (((pSerial[4]>>12)^(pInsCode[3]>>8))<<3)  & 0x8;
	pActCode[3] &= -1-0x8;
	pActCode[3] |= (((pSerial[0]>>10)|(pInsCode[1]>>1))<<3)  & 0x8;
	pActCode[2] &= -1-0x80;
	pActCode[2] |= (((pInsCode[0]>>14)|(pSerial[3]>>12))<<7) & 0x80;
	pActCode[0] &= -1-0x10;
	pActCode[0] |= (((pInsCode[2]>>13)|(pSerial[1]>>6))<<4)  & 0x10;
	pActCode[1] &= -1-0x1000;
	pActCode[1] |= (((pInsCode[3]>>15)&(pSerial[0]>>3))<<12) & 0x1000;
	pActCode[2] &= -1-0x400;
	pActCode[2] |= (((pInsCode[4]>>11)&pSerial[0])<<10)      & 0x400;
	pActCode[3] &= -1-0x8000;
	pActCode[3] |= (((pSerial[4]>>10)&(pInsCode[1]>>4))<<15) & 0x8000;
	pActCode[4] &= -1-0x4;
	pActCode[4] |= (((pInsCode[3]>>4)&(pSerial[4]>>15))<<2)  & 0x4;
	pActCode[4] &= -1-0x2000;
	pActCode[4] |= (((pInsCode[3]>>10)^(pSerial[3]>>5))<<13) & 0x2000;
	pActCode[0] &= -1-0x8;
	pActCode[0] |= (((pSerial[2]>>4)|(pInsCode[3]>>2))<<3)   & 0x8;
	pActCode[1] &= -1-0x2;
	pActCode[1] |= (((pInsCode[0]>>11)&(pSerial[3]>>8))<<1)  & 0x2;
	pActCode[2] &= -1-0x2;
	pActCode[2] |= (((pInsCode[0]>>13)|(pSerial[0]>>12))<<1) & 0x2;
	pActCode[3] &= -1-0x1000;
	pActCode[3] |= (((pInsCode[2]>>3)^(pSerial[1]>>2))<<12)  & 0x1000;
	pActCode[4] &= -1-0x4000;
	pActCode[4] |= (((pInsCode[1]>>5)&(pSerial[0]>>1))<<14)  & 0x4000;


	/////////////////////// Second Decoder of Activation Code ////////
	//1) act[0]{0}  = 1. 2)  act[2]{15}  = 1.  3) act[0]{7} = 1.  4) act[1]{11} = 1. 5) act[1]{0} = 1.
	pActCode[0] |= 0x1;
	pActCode[2] |= 0x8000;
	pActCode[0] |= 0x80;
	pActCode[1] |= 0x800;
	pActCode[1] |= 0x1;
	//6) act[4]{1}  = 1. 7)  act[1]{2}  = 1.    8) act[0]{9} = 1.  9) act[2]{3} = 1.  10) act[4]{12} = 1.
	pActCode[4] |= 0x2;
	pActCode[1] |= 0x4;
	pActCode[0] |= 0x200;
	pActCode[2] |= 0x8;
	pActCode[4] |= 0x1000;
	//11) act[2]{5}  = 1. 12) act[3]{10}  = 1. 13) act[2]{8} = 1. 14) act[1]{13} = 1. 15) act[2]{9} = 1.
	pActCode[2] |= 0x20;
	pActCode[3] |= 0x400;
	pActCode[2] |= 0x100;
	pActCode[1] |= 0x2000;
	pActCode[2] |= 0x200;
	//16) act[0]{2}  = 1. 17) act[3]{1}  = 1.  18) act[0]{13} = 1. 19) act[3]{13} = 1. 20) act[1]{7} = 1.
	pActCode[0] |= 0x4;
	pActCode[3] |= 0x1;
	pActCode[0] |= 0x2000;
	pActCode[3] |= 0x2000;
	pActCode[1] |= 0x80;
	//21) act[3]{6}  = 1. 22) act[2]{12}  = 1. 23) act[4]{15} = 1. 24) act[2]{4} = 1. 25) act[4]{7} = 1.
	pActCode[3] |= 0x40;
	pActCode[2] |= 0x1000;
	pActCode[4] |= 0x8000;
	pActCode[2] |= 0x10;
	pActCode[4] |= 0x80;
	//26) act[0]{5}  = 1. 27) act[4]{9}  = 1.  28) act[4]{4} = 1.
	pActCode[0] |= 0x20;
	pActCode[4] |= 0x200;
	pActCode[4] |= 0x10;

	return true;
}

// generates serial number[5 word] & stores it in pSerial.
bool CCrack_CCStudio3_0Dlg::CCStudio3_0GenerateSerialNumber(WORD* pSerial)
{
	if ( IsBadReadPtr(pSerial,5*sizeof(WORD)) ) return false;
generate:
	for( int nLoop=0; nLoop<5; nLoop++ ){
		pSerial[nLoop] = (WORD)rand();
	}

	// for serial number is 28 step to check validation of serial.
	// so i (zqr) can set that bits in serial number code.
	pSerial[1] &= -1-0x1; // clear bit.
	pSerial[1] |= ((pSerial[0]>>9)&(pSerial[2]>>5))         & 0x1; // set bit.
	pSerial[1] &= -1-0x2;
	pSerial[1] |= (((pSerial[4]>>7)^(pSerial[0]>>2))<<1)    & 0x2;
	pSerial[1] &= -1-0x10;
	pSerial[1] |= (((pSerial[0]>>12)&(pSerial[4]>>14))<<4)  & 0x10;
	pSerial[4] &= -1-0x4;
	pSerial[4] |= (((pSerial[3]>>9)^(pSerial[1]>>5))<<2)    & 0x4;
	pSerial[1] &= -1-0x40;
	pSerial[1] |= (((pSerial[3]>>15)|(pSerial[2]>>13))<<6)  & 0x40;
	pSerial[1] &= -1-0x200;
	pSerial[1] |= (((pSerial[4]>>13)|(pSerial[4]>>6))<<9)   & 0x200;
	pSerial[2] &= -1-0x8;
	pSerial[2] |= (((pSerial[0]>>6)^(pSerial[1]>>10))<<3)   & 0x8;
	pSerial[1] &= -1-0x800;
	pSerial[1] |= (((pSerial[1]>>12)|(pSerial[3]>>4))<<11)  & 0x800;
	pSerial[2] &= -1-0x800;
	pSerial[2] |= (((pSerial[1]>>14)^(pSerial[4]>>12))<<11) & 0x800;
	pSerial[1] &= -1-0x8000;
	pSerial[1] |= (((pSerial[0]>>13)|(pSerial[3]>>10))<<15) & 0x8000;
	pSerial[2] &= -1-0x4;
	pSerial[2] |= (((pSerial[4]>>15)|(pSerial[1]>>7))<<2)   & 0x4;
	pSerial[3] &= -1-0x1;
	pSerial[3] |= ((pSerial[2]>>6)^(pSerial[0]>>11))        & 0x1;
	pSerial[2] &= -1-0x200;
	pSerial[2] |= (((pSerial[1]>>2)&(pSerial[2]))<<9)       & 0x200;
	pSerial[2] &= -1-0x400;
	pSerial[2] |= (((pSerial[0]>>14)^(pSerial[0]>>3))<<10)  & 0x400;
	pSerial[2] &= -1-0x8000;
	pSerial[2] |= (((pSerial[0]>>10)&(pSerial[4]>>1))<<15)  & 0x8000;
	pSerial[3] &= -1-0x8;
	pSerial[3] |= (((pSerial[3]>>13)|(pSerial[0]>>7))<<3)   & 0x8;
	pSerial[3] &= -1-0x20;
	pSerial[3] |= (((pSerial[4]>>11)&(pSerial[0]>>2))<<5)   & 0x20;
	pSerial[3] &= -1-0x40;
	pSerial[3] |= (((pSerial[0]>>15)^(pSerial[0]>>3))<<6)   & 0x40;
	pSerial[3] &= -1-0x80;
	pSerial[3] |= (((pSerial[2]>>14)^(pSerial[4]>>4))<<7)   & 0x80;
	pSerial[3] &= -1-0x100;
	pSerial[3] |= (((pSerial[2]>>8)|(pSerial[0]>>4))<<8)    & 0x100;
	pSerial[3] &= -1-0x800;
	pSerial[3] |= (((pSerial[0]>>8)|(pSerial[2]>>4))<<11)   & 0x800;
	pSerial[3] &= -1-0x1000;
	pSerial[3] |= (((pSerial[4]>>6)&(pSerial[0]>>5))<<12)   & 0x1000;
	pSerial[3] &= -1-0x4000;
	pSerial[3] |= (((pSerial[2]>>1)&(pSerial[1]>>8))<<14)   & 0x4000;
	pSerial[4] &= -1-0x1;
	pSerial[4] |= ((pSerial[2]>>7)|(pSerial[0]))            & 0x1;
	pSerial[4] &= -1-0x20;
	pSerial[4] |= (((pSerial[0]>>15)|(pSerial[4]>>3))<<5)   & 0x20;
	pSerial[4] &= -1-0x100;
	pSerial[4] |= (((pSerial[3]>>1)^(pSerial[1]>>13))<<8)   & 0x100;
	pSerial[4] &= -1-0x200;
	pSerial[4] |= (((pSerial[0]>>6)&(pSerial[1]>>3))<<9)    & 0x200;
	pSerial[4] &= -1-0x400;
	pSerial[4] |= (((pSerial[2]>>12)&(pSerial[0]>>1))<<10)  & 0x400;

	if( (BYTE)(pSerial[0]) >= 0x11 && (BYTE)(pSerial[0]) <= 0x1E ) 
		__asm jmp generate;
	
	return true; 
}

void CCrack_CCStudio3_0Dlg::OnLButtonDown(UINT nFlags, CPoint point){
	::SendMessage(m_hWnd,WM_NCLBUTTONDOWN,HTCAPTION,0);
}

void CCrack_CCStudio3_0Dlg::OnBnClickedButRegister()
{
	
}

void CCrack_CCStudio3_0Dlg::OnDestroy()
{
	CDialog::OnDestroy();
	if( m_hRgnDialog )
		::DeleteObject(m_hRgnDialog);
}
