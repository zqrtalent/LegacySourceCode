// Crack_CCStudio3_0Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "XP_Edit.h"

HRGN  GetBitmapRgn(HBITMAP hBmp,COLORREF crLow = 0x00ffffff,COLORREF crHigh = 0x00ffffff);

class CXP_Edit;
// CCrack_CCStudio3_0Dlg dialog
class CCrack_CCStudio3_0Dlg : public CDialog
{
// Construction
public:
	CCrack_CCStudio3_0Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CRACK_CCSTUDIO3_0_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	HRGN  m_hRgnDialog;

	bool CCStudio3_0GenerateSerialNumber (WORD* pSerial);
	bool CCStudio3_0GenerateActivationKey(WORD* pSerial,WORD* pInsCode,WORD* pActCode);
	
public:
	CXP_Edit m_editSerial;
	CXP_Edit m_editActKey;
	CXP_Edit m_editInstCode;
	CButton  m_butRegister;
	CButton  m_butGenerate;
	
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButGenSerialNumber();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButRegister();
	afx_msg void OnDestroy();
};
