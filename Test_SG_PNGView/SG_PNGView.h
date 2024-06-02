///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////
// SG_PNGView.cpp
// 
// Author: Secured Globe, Inc.
//
// E-Mail: info@securedglobe.com
// 
// Function: An MFC PNG Picture Control to display
//           a PNG image on a Dialog with transparency.
// 
///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#pragma once

#include <afxwin.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class SG_PNGView : public CWnd
{
    ULONG_PTR gdiplusToken;
    Gdiplus::Bitmap* m_pBitmap;

    // Registers the window class for SG_PNGView
    BOOL RegisterWindowClass();

public:
    // Constructor: Initializes GDI+ and registers the window class
    SG_PNGView();

    // Destructor: Cleans up the GDI+ resources
    ~SG_PNGView();

    // Loads a PNG image from the specified resource ID
    Status SetPNGImage(UINT nIDResource);

protected:
    // Handles the WM_PAINT message to draw the PNG image
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
};
