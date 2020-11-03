// GeneratorDlg.h : header file
//

#if !defined(AFX_GENERATORDLG_H__8473806D_E88C_48A2_A1A9_3260C168AEEF__INCLUDED_)
#define AFX_GENERATORDLG_H__8473806D_E88C_48A2_A1A9_3260C168AEEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGeneratorDlg dialog

class CGeneratorDlg : public CDialog
{
// Construction
public:
	CGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneratorDlg)
	enum { IDD = IDD_GENERATOR_DIALOG };
	CString	m_strName;
	CString	m_strCode;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGenerate();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERATORDLG_H__8473806D_E88C_48A2_A1A9_3260C168AEEF__INCLUDED_)
