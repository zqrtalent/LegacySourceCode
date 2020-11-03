// XP_Edit.cpp : implementation file
//
#include "stdafx.h"
#include "XP_Edit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXP_Edit
CXP_Edit::CXP_Edit()
{
	m_bHovBoard = FALSE;
	m_bFocused  = FALSE;
}

CXP_Edit::~CXP_Edit()
{

}

BEGIN_MESSAGE_MAP(CXP_Edit, CEdit)
	//{{AFX_MSG_MAP(CXP_Edit)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXP_Edit message handlers

void CXP_Edit::PreSubclassWindow() 
{
	ModifyStyle( GetStyle()|WS_BORDER,WS_VISIBLE|WS_CHILD|WS_TABSTOP|ES_AUTOHSCROLL);
	CEdit::PreSubclassWindow();
}

void CXP_Edit::OnPaint() 
{
	CEdit::OnPaint();                           // redraw Edit.Becouse Edit text is Lost & then...

	CDC * pdc = GetDC(); 
    COLORREF crEditBoard = RGB(182,189,210);    // color of Edit Board
	UINT nPenStyle = PS_SOLID;                  // specifis pen style

	if( m_bFocused )
		nPenStyle  = PS_DOT;

	if( m_bHovBoard )
		crEditBoard = RGB(10,36,106);            // change Board color

	CRect rcEdit;                                // rect of EditBox
	CPen  pen(nPenStyle,1,crEditBoard);           // pen for Board
	GetClientRect( &rcEdit );					 // get Edit Rect			
	rcEdit.InflateRect( 2,2,1,0 );               // Inflate Rect 
	
	pdc->SelectObject( &pen );
	pdc->MoveTo( CPoint(rcEdit.left,rcEdit.top) );
	pdc->LineTo( CPoint(rcEdit.right,rcEdit.top) );
	pdc->LineTo( CPoint(rcEdit.right,rcEdit.bottom) );
	pdc->LineTo( CPoint(rcEdit.left,rcEdit.bottom) );
	pdc->LineTo( CPoint(rcEdit.left,rcEdit.top) );

	ReleaseDC(pdc);
}

void CXP_Edit::OnMouseMove(UINT nFlags, CPoint point) 
{
	//  first time, when mouse start hover.
	if( !m_bHovBoard )
	{
		m_bHovBoard = TRUE;
		Invalidate();
	}

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = GetSafeHwnd();

	_TrackMouseEvent( &tme );

	CEdit::OnMouseMove(nFlags, point);
}

LRESULT CXP_Edit::OnMouseLeave( WPARAM,LPARAM )
{
	m_bHovBoard = FALSE;
	Invalidate();
	return 0;
}

void CXP_Edit::OnKillFocus(CWnd* pNewWnd) 
{
	m_bFocused = FALSE;
	Invalidate();
	CEdit::OnKillFocus(pNewWnd);
}
	

void CXP_Edit::OnSetFocus(CWnd* pOldWnd) 
{
	m_bFocused = TRUE;
	Invalidate();
	CEdit::OnSetFocus(pOldWnd);
}
