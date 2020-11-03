// MemoryWriterDlg.h : header file
//

#if !defined(AFX_MEMORYWRITERDLG_H__A93B5817_BF05_4EEF_9F92_DCD232B01961__INCLUDED_)
#define AFX_MEMORYWRITERDLG_H__A93B5817_BF05_4EEF_9F92_DCD232B01961__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMemoryWriterDlg dialog

class CMemoryWriterDlg : public CDialog
{
// Construction
public:
	CMemoryWriterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMemoryWriterDlg)
	enum { IDD = IDD_MEMORYWRITER_DIALOG };
	CString	m_strFile;
	UINT	m_idProcess;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryWriterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMemoryWriterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnWrite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMORYWRITERDLG_H__A93B5817_BF05_4EEF_9F92_DCD232B01961__INCLUDED_)
