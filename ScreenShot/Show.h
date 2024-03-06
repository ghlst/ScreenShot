#pragma once


// CShow �Ի���
#include "RectTrackerEx.h"
class CShow : public CDialogEx
{
	DECLARE_DYNAMIC(CShow)

public:
	CShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShow();

// �Ի�������
	enum { IDD = IDD_SHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	int m_nScreenWidth;
	int m_nScreenHeight; 
	CDC m_memDC;
	CRectTrackerEx m_tracker;//��Ƥ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void DoubleBuffur(CDC* pDc);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
