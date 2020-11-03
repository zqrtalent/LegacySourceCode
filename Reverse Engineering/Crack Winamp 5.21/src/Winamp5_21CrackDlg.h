// Winamp5_21CrackDlg.h : header file
//

#pragma once


// CWinamp5_21CrackDlg dialog
class CWinamp5_21CrackDlg : public CDialog
{
// Construction
public:
	CWinamp5_21CrackDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WINAMP5_21CRACK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON   m_hIcon;
	CString  _sPath;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedCrack();
};
