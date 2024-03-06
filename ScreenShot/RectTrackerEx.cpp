#include "stdafx.h"
#include "RectTrackerEx.h"


CRectTrackerEx::CRectTrackerEx()
{
}


CRectTrackerEx::~CRectTrackerEx()
{
}
void CRectTrackerEx::Draw(CDC * pDC, CPen * pen)
{
	if ((m_nStyle & dottedLine) != 0 || (m_nStyle & solidLine) != 0)
	{
		VERIFY(pDC->SaveDC() != 0);//保存设备上下文的当前状态

		pDC->SetMapMode(MM_TEXT);
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0, 0);

		CRect rect = m_rect;
		rect.NormalizeRect();

		CPen *pOldPen = NULL;
		CBrush *pOldBrush = NULL;
		int nOldROP;

		pOldPen = (CPen*)pDC->SelectObject(pen);
		pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		nOldROP = pDC->SetROP2(R2_COPYPEN);

		rect.InflateRect(+1, +1);//增大矩形的宽和高
		pDC->Rectangle(rect.left, rect.top, rect.right, rect.bottom);
		pDC->SetROP2(nOldROP);

		if ((m_nStyle & (resizeInside | resizeOutside)) != 0)
		{
			UINT mask = GetHandleMask();
			for (int i = 0; i < 8; ++i)
			{
				if (mask & (1 << i))
				{
					GetHandleRect((TrackerHit)i, &rect);
					//手柄
					LOGPEN logpen;
					pen->GetLogPen(&logpen);
					pDC->FillSolidRect(rect, logpen.lopnColor);
				}
			}
		}

		//还原画笔
		pDC->SelectObject(pOldPen);
		//还原画刷
		pDC->SelectObject(pOldBrush);
	}
	else
	{
		CRectTracker::Draw(pDC);
	}
}
