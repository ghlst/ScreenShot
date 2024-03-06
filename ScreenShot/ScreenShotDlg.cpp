
// ScreenShotDlg.cpp : 实现文件
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
// CScreenShotDlg 对话框



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


// CScreenShotDlg 消息处理程序

BOOL CScreenShotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_nid.cbSize = sizeof(NOTIFYICONDATA);
	m_nid.hWnd = m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_nid.uCallbackMessage = UM_SHOWTASK;//自定义消息
	m_nid.hIcon = m_hIcon;
	wcscpy(m_nid.szTip, _T("截图"));
	Shell_NotifyIcon(NIM_ADD,&m_nid);

	//创建唯一ID,把字符串放在原子列表中，返回唯一标识符
	nShowHotId = GlobalAddAtom(_T("SHOT_HOTKEY"));
		//设置热键
	if (IDCANCEL == RegisterHotKey(m_hWnd, nShowHotId, MOD_ALT | MOD_WIN, 'X'))
	{
		MessageBox(L"ALT+WIN+X与系统热键冲突");
		EndDialog(IDOK);
	}
	//设置开机自启动
	AutoRun();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenShotDlg::OnPaint()
{
	//隐藏窗口
	ShowWindow(SW_HIDE);
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScreenShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenShotDlg::OnBnClickedBtnClose()
{
	// TODO:  在此添加控件通知处理程序代码
	//EndDialog(IDOK);
	ShowWindow(SW_HIDE);
}


BOOL CScreenShotDlg::OnNcActivate(BOOL bActive)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnNcActivate(bActive);
}


LRESULT CScreenShotDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LRESULT result = CDialogEx::OnNcHitTest(point);
	if (result == HTCLIENT)
	{
		result = HTCAPTION;
	}
	return result;
}

//屏幕截图
void CScreenShotDlg::OnBnClickedBtnShot()
{
	// TODO:  在此添加控件通知处理程序代码
	/*
	//		原理
		1：截图那一瞬间的图像保存
		2：创建了一个窗口
		3：把创建的窗口边框。标题栏等去掉，只剩下客户区
		4：调整窗口大小到整个屏幕
		5：截图保存的那一瞬间的图像绘制到窗口上
		6：选取一块区域
		7：保存图像
	*/

	//隐藏本窗口
	ShowWindow(SW_HIDE);


	//1：截图那一瞬间的图像保存

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
	case WM_LBUTTONDBLCLK:	//左键双击
		ShowWindow(SW_SHOW);
		break;
	case WM_RBUTTONUP://右键弹起
	{
						  CPoint point;
						  GetCursorPos(&point);
						  CMenu menu;
						  menu.CreatePopupMenu();
						  menu.AppendMenu(MF_STRING, IDCANCEL, _T("关闭"));
						  //弹出菜单
						  menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
						  break;
	}
		
	}
	return 0;
}

void CScreenShotDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	//销毁托盘
	Shell_NotifyIcon(NIM_DELETE,&m_nid);
	//销毁热键
	UnregisterHotKey(m_hWnd, nShowHotId);
	//移除原子
	GlobalDeleteAtom(nShowHotId);
}

//WM_HOTKEY
void CScreenShotDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nHotKeyId == nShowHotId)
	{
		OnBnClickedBtnShot();
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//开机自启动
void CScreenShotDlg::AutoRun()
{
	//获取exe路径
	TCHAR szExePath[MAX_PATH];
	GetModuleFileName(NULL, szExePath, MAX_PATH);
	
	//打开注册表
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS | KEY_WOW64_64KEY,&hKey))
	{  
		return;
	}
	//写入数据
	RegSetValueEx(hKey, L"shot", 0, REG_SZ, (const BYTE*)szExePath,MAX_PATH);
	//关闭注册表
	RegCloseKey(hKey); 
}