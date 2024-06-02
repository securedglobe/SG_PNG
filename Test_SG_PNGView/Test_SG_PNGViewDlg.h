
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////
// Test_SG_PNGViewDlg.h
// 
// Author: Secured Globe, Inc.
//
// E-Mail: info@securedglobe.com
// 
// Function: a test application for SG_PNGView - An MFC PNG Picture Control to display
//           a PNG image on a Dialog with transparency.
// 
///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

#pragma once
#include "SG_PNGView.h"

// CTest_SG_PNGViewDlg dialog
class CTest_SG_PNGViewDlg : public CDialogEx
{
// Construction
public:
	CTest_SG_PNGViewDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Test_SG_PNGView_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	SG_PNGView m_picture, m_picture2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
