#include "stdafx.h"
#include "OwnShape.h"

const int BUTTON_IMAGE_NUM = 2;

IMPLEMENT_DYNAMIC(COwnShape, CButton)

BEGIN_MESSAGE_MAP(COwnShape, CButton)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_CREATE()
END_MESSAGE_MAP()

COwnShape :: COwnShape()
{
    Pushed = FALSE;
    Width = 0;
    Height = 0;
}

void COwnShape::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct )
{
    CDC memDC;
	CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT state = lpDrawItemStruct->itemState;
	CRect rect = lpDrawItemStruct->rcItem;

    memDC.CreateCompatibleDC( NULL );
    CBitmap *oldBitmap = memDC.SelectObject( &Bitmap );

	/*if (state & ODS_SELECTED)
        pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
    else
        pDC->DrawFrameControl(rect, DFC_BUTTON, DFCS_BUTTONPUSH);*/
    if( Pushed == FALSE )
        BitBlt( lpDrawItemStruct->hDC, 0, 0, Width, Height, memDC, 0, 0, SRCCOPY );
    else
        BitBlt( lpDrawItemStruct->hDC, 0, 0, Width, Height, memDC, Width , 0, SRCCOPY );

	

   // memDC.SelectObject( oldBitmap );
}

BOOL COwnShape :: Open( int resource_id )
{
    Pushed = FALSE;

    Bitmap.LoadBitmap( resource_id );

    //adjust the button size
    BITMAP bm;
    Bitmap.GetObject(sizeof(BITMAP),&bm);
    Width = bm.bmWidth / BUTTON_IMAGE_NUM;
    Height = bm.bmHeight;

    RECT rect;
    GetWindowRect( &rect );
    GetParent()->ScreenToClient( &rect );

    rect.right = rect.left + Width;
    rect.bottom = rect.top + Height;
    MoveWindow( &rect );

    return TRUE;
}

void COwnShape::OnLButtonDown(UINT nFlags, CPoint point)
{
    Pushed = TRUE;
    Invalidate( FALSE );

    CButton::OnLButtonDown(nFlags, point);
}


void COwnShape::OnLButtonUp(UINT nFlags, CPoint point)
{
    Pushed = FALSE;
    Invalidate( FALSE );

    CButton::OnLButtonUp(nFlags, point);
}
