
// ScreenShotDlg.h : 头文件
//

#pragma once


// CScreenShotDlg 对话框
class CScreenShotDlg : public CDialogEx
{
// 构造
public:
	CScreenShotDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCREENSHOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NOTIFYICONDATA m_nid; //托盘
	afx_msg void OnBnClickedBtnClose();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedBtnShot();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);//托盘自定义消息
	afx_msg void OnDestroy();
	ATOM nShowHotId;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	//开机自启动
	void AutoRun();
};
