#pragma once
#include "../Base/BaseSingleton.h"

// CSettingDlg 对话框
class CSettingDlg : public CDialogEx
{
public:
	CSettingDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_SETTING_DLG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void UpdateUI();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSub();
	afx_msg void OnBnClickedAdd();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
private:
	CStatic _content;
	CButton _btnAdd;
	CButton _btnSub;
	CStatic _textContent;
	int _valCache;
};
