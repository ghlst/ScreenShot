// Show.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenShot.h"
#include "Show.h"
#include "afxdialogex.h"


// CShow �Ի���

IMPLEMENT_DYNAMIC(CShow, CDialogEx)

CShow::CShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShow::IDD, pParent)
{
	//��ȡ��Ļ�Ŀ�͸�
	m_nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	m_nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	//��ȡ����dc
	CDC* pDesktop =  GetDesktopWindow()->GetDC();
	//����һ�ż���λͼ
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDesktop, m_nScreenWidth, m_nScreenHeight);

	//�����ڴ�DC��

	m_memDC.CreateCompatibleDC(pDesktop);
	m_memDC.SelectObject(&bmp);
	m_memDC.BitBlt(0, 0, m_nScreenWidth, m_nScreenHeight, pDesktop, 0, 0, SRCCOPY);
}

CShow::~CShow()
{
}

void CShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShow, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CShow ��Ϣ�������


void CShow::OnPaint()

{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	/*CRect rect;
	GetClientRect(&rect);*/

	//˫����
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, m_nScreenWidth, m_nScreenHeight);
	memDC.SelectObject(&bmp);
	DoubleBuffur(&memDC);
	dc.BitBlt(0, 0, m_nScreenWidth, m_nScreenHeight, &memDC, 0, 0, SRCCOPY);
	Invalidate(FALSE);
	
}

void CShow::DoubleBuffur(CDC* pDc)
{
	pDc->BitBlt(0, 0, m_nScreenWidth, m_nScreenHeight, &m_memDC, 0, 0, SRCCOPY);

	//������Ƥ��
	CPen pen(PS_SOLID, 3, RGB(0,169,255));
	m_tracker.Draw(pDc,&pen);

	
	//���ƷŴ�
	//��ȡ�������
	POINT pos;
	GetCursorPos(&pos);
	CRect rect;
	pDc->Rectangle(pos.x + 5 - 1, pos.y + 30 - 1, pos.x + 5 + 100 + 1, pos.y + 30 + 100 + 1);
	//������ͼ 
	pDc->SetStretchBltMode(HALFTONE);
	pDc->StretchBlt(pos.x + 5, pos.y + 30, 100, 100, &m_memDC, pos.x - 25, pos.y - 25, 50, 50, SRCCOPY);
	//����������
	CPen b(PS_SOLID,1,RGB(3, 131, 253));
	CPen * pOld = pDc->SelectObject(&b);
	pDc->MoveTo(pos.x + 5 - 1, pos.y + 30 - 1 + 51);//��͸�һ��102
	pDc->LineTo(pos.x + 5 + 100 + 1, pos.y + 30 - 1 + 51);
	pDc->MoveTo(pos.x + 5 - 1 + 51, pos.y + 30 - 1);
	pDc->LineTo(pos.x + 5 - 1 + 51, pos.y + 30 - 1 + 102);
	pDc->SelectObject(pOld);
	//���������ʾ��Ϣ
	CFont font;
	font.CreatePointFont(100,L"����");
	CFont * pOldFont = pDc->SelectObject(&font);
	pDc->FillSolidRect(pos.x + 5 - 1, pos.y + 30 - 1 + 102, 102, 30, RGB(20, 20, 20));
	CString str;
	str.Format(L"%d x %d",m_tracker.m_rect.Width(),m_tracker.m_rect.Height());
	pDc->SetBkMode(TRANSPARENT);
	pDc->SetTextColor(RGB(255, 255, 255));
	pDc->TextOut(pos.x + 5 - 1 + 2, pos.y + 30 - 1 + 102 + 2, str);
	pDc->SelectObject(pOldFont);
}

BOOL CShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowPos(&wndTopMost,0,0,m_nScreenWidth,m_nScreenHeight,SWP_SHOWWINDOW);
	m_tracker.m_nHandleSize = 5;
	m_tracker.m_nStyle = CRectTracker::solidLine | CRectTracker::resizeOutside;
	m_tracker.m_rect.SetRect(0, 0, 0, 0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CShow::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//û�е���
	if (m_tracker.HitTest(point) == CRectTracker::hitNothing)
	{
		m_tracker.TrackRubberBand(this, point, TRUE);
		m_tracker.m_rect.NormalizeRect();
	}
	else
	{
		m_tracker.Track(this,point,TRUE);
		m_tracker.m_rect.NormalizeRect();
	}
	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CShow::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

//˫����ͼ
void CShow::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_tracker.m_rect.PtInRect(point))
	{
		//��ͼ
		//����һ��ͼƬ
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(&m_memDC,m_tracker.m_rect.Width(),m_tracker.m_rect.Height());
		//�����ڴ�DC
		CDC  tempDC;
		tempDC.CreateCompatibleDC(&m_memDC);
		tempDC.SelectObject(&bmp);
		//����ͼ��
		tempDC.BitBlt(0, 0, m_tracker.m_rect.Width(), m_tracker.m_rect.Height(), &m_memDC, m_tracker.m_rect.left, m_tracker.m_rect.top, SRCCOPY);

		//����ͼ��
		//�ļ���
		srand((UINT)time(NULL));
		CTime time = CTime::GetCurrentTime();	
		CString str;
		str.Format(L"D:/user/Desktop/desktop/pictrue/shot/%s%d.png", time.Format(L"DK%Y%M%d%H%M%S"), rand() % 900 + 100);
		//str.Format(L"D:\\shot picture\\%s%d.png", time.Format(L"DK%Y%M%d%H%M%S"), rand() % 900 + 100);
		CImage image;
		image.Attach(bmp);
		image.Save(str);
		image.Detach();
		//���õ����а�
		OpenClipboard();
		EmptyClipboard();
		SetClipboardData(CF_BITMAP,bmp);
		CloseClipboard();
		//�رնԻ���
		EndDialog(IDCANCEL);

	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CShow::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Invalidate(FALSE);
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CShow::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint point;
	GetCursorPos(&point);
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_tracker.HitTest(point) == CRectTracker::hitNothing)
	{
		//����ͼ��
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZEALL);
		SetCursor(hCursor);
		return TRUE;
	}
	else if (m_tracker.HitTest(point) == CRectTracker::hitTopLeft)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZENWSE);
		SetCursor(hCursor);
		return TRUE;
	}
	else if (m_tracker.HitTest(point) == CRectTracker::hitTop)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZENS);
		SetCursor(hCursor);
		return TRUE;
	}
	else if (m_tracker.HitTest(point) == CRectTracker::hitBottom)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZENS);
		SetCursor(hCursor);
		return TRUE;
	}
	else if (m_tracker.HitTest(point) == CRectTracker::hitBottomRight)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZENWSE);
		SetCursor(hCursor);
		return TRUE;
	}
	else if (m_tracker.HitTest(point) == CRectTracker::hitBottomLeft)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZENESW);
		SetCursor(hCursor);
		return TRUE;
	}
	else if (m_tracker.HitTest(point) == CRectTracker::hitTopRight)
	{
		HCURSOR hCursor = LoadCursor(NULL, IDC_SIZENESW);
		SetCursor(hCursor);
		return TRUE;
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
