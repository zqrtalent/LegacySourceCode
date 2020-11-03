#if !defined(AFX_XP_EDIT_H__77724FB4_FF59_4C6E_83FF_441598D43B94__INCLUDED_)
#define AFX_XP_EDIT_H__77724FB4_FF59_4C6E_83FF_441598D43B94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XP_Edit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXP_Edit window

class CXP_Edit : public CEdit
{
// Construction
public:
	CXP_Edit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXP_Edit)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXP_Edit();

	// Generated message map functions
protected:
	BOOL m_bHovBoard;                // when mouse hover edit then draw special Board
	BOOL m_bFocused;                 // if window is Focused

	//{{AFX_MSG(CXP_Edit)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnMouseLeave( WPARAM,LPARAM );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XP_EDIT_H__77724FB4_FF59_4C6E_83FF_441598D43B94__INCLUDED_)
