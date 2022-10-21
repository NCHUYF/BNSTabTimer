#pragma once
#include "Base/BaseSingleton.h"

// CBNSTabTimerDlg 对话框
class CBNSTabTimerDlg : public CDialogEx, public BaseSingleton<CBNSTabTimerDlg>
{
	friend class BaseSingleton<CBNSTabTimerDlg>;
private:
	CBNSTabTimerDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 构造
public:
// 对话框数据
	enum { IDD = IDD_BNSTABTIMER_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CStatic _content;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
