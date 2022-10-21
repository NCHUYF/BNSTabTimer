
// BNSTabTimerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BNSTabTimer.h"
#include "BNSTabTimerDlg.h"
#include "afxdialogex.h"
#include "Utility/LayoutUtility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CBNSTabTimerDlg::CBNSTabTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBNSTabTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBNSTabTimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CBNSTabTimerDlg 消息处理程序

BOOL CBNSTabTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	static CFont font;
	font.DeleteObject();
	font.CreatePointFont(280, _T("微软雅黑"));

	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left += 5;
	rcClient.right -= 5;
	rcClient.top += 5;
	rcClient.bottom -= 5;

	// 窗口置顶
	{
		::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_DRAWFRAME);
	}

	// 窗口透明
	{
		SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
		::SetLayeredWindowAttributes(GetSafeHwnd(), 0, 128, LWA_ALPHA);
		ModifyStyleEx(WS_EX_TRANSPARENT, 0, SWP_FRAMECHANGED);
	}

	// 内容
	{
		CRect rcContent = rcClient;
		_content.Create(L"60", WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rcContent, this, IDC_CONTENT);
		_content.ShowWindow(SW_SHOW);
		_content.SetFont(&font);//设置字体
	}

	// TODO: 在此添加额外的初始化代码
	LayoutUtility::SetControl(this, LayoutUtility::ANCHOR_RIGHTTOP);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBNSTabTimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBNSTabTimerDlg::OnPaint()
{
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
HCURSOR CBNSTabTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBNSTabTimerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 拖拽效果
	__super::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}
