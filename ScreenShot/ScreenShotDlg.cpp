
// ScreenShotDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenShot.h"
#include "ScreenShotDlg.h"
#include "afxdialogex.h"
#include "Show.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_SHOWTASK WM_USER+1
// CScreenShotDlg �Ի���



CScreenShotDlg::CScreenShotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenShotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenShotDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CScreenShotDlg::OnBnClickedBtnClose)
	ON_WM_NCACTIVATE()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BTN_SHOT, &CScreenShotDlg::OnBnClickedBtnShot)
	ON_MESSAGE(UM_SHOWTASK, &CScreenShotDlg::OnShowTask)
	ON_WM_DESTROY()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CScreenShotDlg ��Ϣ�������

BOOL CScreenShotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_nid.uCallbackMessage = UM_SHOWTASK;//�Զ�����Ϣ
	m_nid.hIcon = m_hIcon;
	wcscpy(m_nid.szTip, _T("��ͼ"));
	Shell_NotifyIcon(NIM_ADD,&m_nid);

	//����ΨһID,���ַ�������ԭ���б��У�����Ψһ��ʶ��
	nShowHotId = GlobalAddAtom(_T("SHOT_HOTKEY"));
		//�����ȼ�
	if (IDCANCEL == RegisterHotKey(m_hWnd, nShowHotId, MOD_ALT | MOD_WIN, 'X'))
	{
		MessageBox(L"ALT+WIN+X��ϵͳ�ȼ���ͻ");
		EndDialog(IDOK);
	}
	//���ÿ���������
	AutoRun();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScreenShotDlg::OnPaint()
{
	//���ش���
	ShowWindow(SW_HIDE);
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScreenShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenShotDlg::OnBnClickedBtnClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//EndDialog(IDOK);
	ShowWindow(SW_HIDE);
}


BOOL CScreenShotDlg::OnNcActivate(BOOL bActive)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CDialogEx::OnNcActivate(bActive);
}


LRESULT CScreenShotDlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT result = CDialogEx::OnNcHitTest(point);
	if (result == HTCLIENT)
	{
		result = HTCAPTION;
	}
	return result;
}

//��Ļ��ͼ
void CScreenShotDlg::OnBnClickedBtnShot()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*
	//		ԭ��
		1����ͼ��һ˲���ͼ�񱣴�
		2��������һ������
		3���Ѵ����Ĵ��ڱ߿򡣱�������ȥ����ֻʣ�¿ͻ���
		4���������ڴ�С��������Ļ
		5����ͼ�������һ˲���ͼ����Ƶ�������
		6��ѡȡһ������
		7������ͼ��
	*/

	//���ر�����
	ShowWindow(SW_HIDE);


	//1����ͼ��һ˲���ͼ�񱣴�

	CShow dlg;
	if (IDCANCEL == dlg.DoModal())
	{
		this->ShowWindow(SW_SHOW);
	}


}
LRESULT CScreenShotDlg:: OnShowTask(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDBLCLK:	//���˫��
		ShowWindow(SW_SHOW);
		break;
	case WM_RBUTTONUP://�Ҽ�����
	{
						  CPoint point;
						  GetCursorPos(&point);
						  CMenu menu;
						  menu.CreatePopupMenu();
						  menu.AppendMenu(MF_STRING, IDCANCEL, _T("�ر�"));
						  //�����˵�
						  menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
						  break;
	}
		
	}
	return 0;
}

void CScreenShotDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	//��������
	Shell_NotifyIcon(NIM_DELETE,&m_nid);
	//�����ȼ�
	UnregisterHotKey(m_hWnd, nShowHotId);
	//�Ƴ�ԭ��
	GlobalDeleteAtom(nShowHotId);
}

//WM_HOTKEY
void CScreenShotDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nHotKeyId == nShowHotId)
	{
		OnBnClickedBtnShot();
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//����������
void CScreenShotDlg::AutoRun()
{
	//��ȡexe·��
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);
	
	//��ע���
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY,&hKey))
	{  
		return;
	}
	//д������
	RegSetValueEx(hKey, L"shot", 0, REG_SZ, (const BYTE*)szExePath,MAX_PATH);
	//�ر�ע���
	RegCloseKey(hKey); 
}