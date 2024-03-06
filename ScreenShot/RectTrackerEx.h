#pragma once
#include "afxext.h"
class CRectTrackerEx :
	public CRectTracker
{
public:
	CRectTrackerEx();
	~CRectTrackerEx();
	void CRectTrackerEx::Draw(CDC * pDC, CPen * pen);
};

