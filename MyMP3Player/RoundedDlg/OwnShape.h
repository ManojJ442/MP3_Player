#pragma once

#include <afxwin.h>

class COwnShape : public CButton
{
    DECLARE_DYNAMIC(COwnShape)

protected:

    enum EButtonState
    {
        NORMAL = 0,
        PUSHED = 1
    };

public:
    COwnShape();

    BOOL Open( int resource_id );
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
    int Width, Height;
    BOOL Pushed;
    CBitmap Bitmap;
};