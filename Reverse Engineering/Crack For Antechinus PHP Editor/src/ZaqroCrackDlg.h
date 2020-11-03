// ZaqroCrackDlg.h : header file
//

#if !defined(AFX_ZAQROCRACKDLG_H__111863D4_05C2_4B1A_96C1_75C5F42D7074__INCLUDED_)
#define AFX_ZAQROCRACKDLG_H__111863D4_05C2_4B1A_96C1_75C5F42D7074__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZaqroCrackDlg dialog

class CZaqroCrackDlg : public CDialog
{
// Construction
public:
	CZaqroCrackDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZaqroCrackDlg)
	enum { IDD = IDD_ZAQROCRACK_DIALOG };
	CButton	m_browse;
	CButton	m_crack;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZaqroCrackDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HANDLE m_hFile;

	// Generated message map functions
	//{{AFX_MSG(CZaqroCrackDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnBrowse();
	afx_msg void OnDestroy();
	afx_msg void OnCrack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZAQROCRACKDLG_H__111863D4_05C2_4B1A_96C1_75C5F42D7074__INCLUDED_)
