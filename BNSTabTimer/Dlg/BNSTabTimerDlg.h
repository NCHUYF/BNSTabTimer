#pragma once
#include "../Base/BaseSingleton.h"

// CBNSTabTimerDlg 对话框
class CBNSTabTimerDlg : public CDialogEx, public BaseSingleton<CBNSTabTimerDlg>
{
	enum TimerState
	{
		eGreen,
		eYellow,
		eRed,
	};

	friend class BaseSingleton<CBNSTabTimerDlg>;
private:
	CBNSTabTimerDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 构造
public:
// 对话框数据
	enum { IDD = IDD_BNSTABTIMER_DIALOG };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void SetGreen() {
		_textColor = RGB(0, 255, 0);
		_bgColor = RGB(0, 200, 0);
		_content.SetWindowTextW(L"tab");
		_state = TimerState::eGreen;
		_content.RedrawWindow();
		RedrawWindow();
	}
	void SetYellow() {
		_textColor = RGB(255, 255, 0);
		_bgColor = RGB(255, 200, 0);
		_state = TimerState::eYellow;
		_content.RedrawWindow();
		RedrawWindow();
	}
	void SetRed() {
		_textColor = RGB(255, 255, 0);
		_bgColor = RGB(200, 0, 0);
		_state = TimerState::eRed;
		_content.RedrawWindow();
		RedrawWindow();
	}
	void Reset();
	void Start();
	void Pause();
// 实现
protected:
	DECLARE_MESSAGE_MAP()
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
protected:
	void UpdateTime();
private:
	CStatic _content;
	COLORREF _textColor;
	COLORREF _bgColor;
	bool _bStart;
	int _timer;
	CFont font;
	TimerState _state;
};
