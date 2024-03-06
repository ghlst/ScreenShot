
// ScreenShotDlg.h : ͷ�ļ�
//

#pragma once


// CScreenShotDlg �Ի���
class CScreenShotDlg : public CDialogEx
{
// ����
public:
	CScreenShotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENSHOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	NOTIFYICONDATA m_nid; //����
	afx_msg void OnBnClickedBtnClose();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedBtnShot();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);//�����Զ�����Ϣ
	afx_msg void OnDestroy();
	ATOM nShowHotId;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	//����������
	void AutoRun();
};
