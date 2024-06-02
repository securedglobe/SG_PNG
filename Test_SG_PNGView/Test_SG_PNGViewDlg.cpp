
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////
// Test_SG_PNGViewDlg.cpp
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
#include "pch.h"
#include "framework.h"
#include "Test_SG_PNGView.h"
#include "Test_SG_PNGViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CTest_SG_PNGViewDlg dialog

CTest_SG_PNGViewDlg::CTest_SG_PNGViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Test_SG_PNGView_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest_SG_PNGViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_picture);
}

BEGIN_MESSAGE_MAP(CTest_SG_PNGViewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTest_SG_PNGViewDlg message handlers

HBRUSH CTest_SG_PNGViewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// Check if the control is the dialog background
	if (nCtlColor == CTLCOLOR_DLG)
	{
		
		pDC->SetBkColor(RGB(173, 216, 230)); // Light blue color
		hbr = ::CreateSolidBrush(RGB(173, 216, 230));
	}

	return hbr;
}
BOOL CTest_SG_PNGViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hicon;
	hicon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hicon, true);
	Status result = m_picture.SetPNGImage(IDB_PNG);
	if (result != Status::Ok)
	{
		// Handle error loading IDB_PNG
		// For example: MessageBox or log the error
		CString strError;
		strError.Format(_T("Failed to load IDB_PNG. Error code: %d"), result);
		AfxMessageBox(strError, MB_ICONERROR);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}




// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTest_SG_PNGViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

