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

#include "pch.h"
#include "SG_PNGView.h"

#define SGPNGVIEW_CLASSNAME _T("SG_PNGView")  // Window class name

SG_PNGView::SG_PNGView()
    : m_pBitmap(nullptr)
{
    RegisterWindowClass();

    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

SG_PNGView::~SG_PNGView()
{
    if (m_pBitmap)
    {
        delete m_pBitmap;
        m_pBitmap = nullptr; // Set pointer to null after deletion
    }

    if (gdiplusToken)
    {
        GdiplusShutdown(gdiplusToken);
        gdiplusToken = 0; // Reset token value after shutdown
    }
}


BEGIN_MESSAGE_MAP(SG_PNGView, CWnd)
    ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL SG_PNGView::RegisterWindowClass()
{
    static BOOL bClassRegistered = FALSE;  // Static flag to track if the class is already registered
    if (bClassRegistered)
    {
        // Class is already registered, no need to register it again
        return TRUE;
    }

    // Get the instance handle of the application
    HINSTANCE hInst = AfxGetInstanceHandle();
    if (!hInst)
    {
        // Instance handle is NULL, unable to register window class
        return FALSE;
    }

    // Check if the window class is already registered
    WNDCLASS wndcls;
    if (!(::GetClassInfo(hInst, SGPNGVIEW_CLASSNAME, &wndcls)))
    {
        // Window class is not registered, register a new class
        wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc = ::DefWindowProc;
        wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
        wndcls.hInstance = hInst;
        wndcls.hIcon = NULL;
        wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
        wndcls.lpszMenuName = NULL;
        wndcls.lpszClassName = SGPNGVIEW_CLASSNAME;

        if (!AfxRegisterClass(&wndcls))
        {
            // Failed to register window class
            return FALSE;
        }
    }

    // Update the flag to indicate that the class is registered
    bClassRegistered = TRUE;
    return TRUE;
}

// Loads a PNG image from the specified resource ID
Status SG_PNGView::SetPNGImage(UINT nIDResource)
{
    // Get the instance handle of the application
    HINSTANCE hInstance = AfxGetInstanceHandle();

    // Find the specified resource in the application's executable file
    HRSRC hResource = ::FindResource(hInstance, MAKEINTRESOURCE(nIDResource), _T("PNG"));
    if (!hResource)
    {
        return GenericError; // Resource not found
    }

    // Get the size of the resource
    DWORD imageSize = ::SizeofResource(hInstance, hResource);

    // Get a pointer to the resource data
    const void* pResourceData = ::LockResource(::LoadResource(hInstance, hResource));
    if (!pResourceData)
    {
        return OutOfMemory; // Failed to lock resource
    }

    // Allocate global memory to hold the resource data
    HGLOBAL hBuffer = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
    if (!hBuffer)
    {
        return OutOfMemory; // Memory allocation failed
    }

    // Lock the allocated memory and copy the resource data into it
    void* pBuffer = ::GlobalLock(hBuffer);
    if (!pBuffer)
    {
        ::GlobalFree(hBuffer); // Failed to lock memory, free the buffer
        return OutOfMemory;
    }
    CopyMemory(pBuffer, pResourceData, imageSize);

    // Create an IStream object from the allocated memory
    IStream* pStream = NULL;
    if (::CreateStreamOnHGlobal(hBuffer, FALSE, &pStream) != S_OK)
    {
        ::GlobalUnlock(hBuffer);
        ::GlobalFree(hBuffer);
        return GenericError; // Failed to create stream
    }

    // Delete the previous bitmap if it exists
    delete m_pBitmap;

    // Create a GDI+ Bitmap object from the stream
    m_pBitmap = Bitmap::FromStream(pStream);

    // Release the IStream object
    pStream->Release();

    // Unlock and free the allocated memory
    ::GlobalUnlock(hBuffer);
    ::GlobalFree(hBuffer);

    // Check if the bitmap was created successfully
    if (m_pBitmap == NULL)
    {
        return OutOfMemory; // Failed to create bitmap
    }

    Status status = m_pBitmap->GetLastStatus();
    if (status != Ok)
    {
        delete m_pBitmap;
        m_pBitmap = NULL;
    }

    return status;
}

void SG_PNGView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    CRect rect;
    GetClientRect(&rect);

    if (m_pBitmap != nullptr)
    {
        Graphics graphics(dc.GetSafeHdc());

        // Get the dimensions of the image
        int imageWidth = m_pBitmap->GetWidth();
        int imageHeight = m_pBitmap->GetHeight();

        // Calculate the scaling factors to fit the image inside the control
        float scaleX = static_cast<float>(rect.Width()) / imageWidth;
        float scaleY = static_cast<float>(rect.Height()) / imageHeight;
        float scale = min(scaleX, scaleY); // Use the minimum scaling factor to preserve aspect ratio

        // Calculate the dimensions of the scaled image
        int scaledWidth = static_cast<int>(imageWidth * scale);
        int scaledHeight = static_cast<int>(imageHeight * scale);

        // Calculate the position to center the scaled image within the control
        int xPos = (rect.Width() - scaledWidth) / 2;
        int yPos = (rect.Height() - scaledHeight) / 2;

        // Draw the scaled image
        graphics.DrawImage(m_pBitmap, xPos, yPos, scaledWidth, scaledHeight);
    }
}
