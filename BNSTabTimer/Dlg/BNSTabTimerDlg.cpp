
// BNSTabTimerDlg.cpp: 实现文件
//

#include "pch.h"
#include "../framework.h"
#include "../BNSTabTimer.h"
#include "BNSTabTimerDlg.h"
#include "afxdialogex.h"
#include "../Utility/LayoutUtility.h"
#include "SettingDlg.h"
#include "../Model/GlobalData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_TIMER 1
#define WM_MOUSEBUTTONDOWN WM_USER+777

BEGIN_MESSAGE_MAP(CBNSTabTimerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_HOTKEY()
	ON_MESSAGE(WM_MOUSEBUTTONDOWN, OnMouseButtonDown)
END_MESSAGE_MAP()

// 鼠标钩子
HHOOK glHook = NULL;
LRESULT CALLBACK MouseProc(int nCode, WPARAM msg, LPARAM lparam)
{
	if (msg == WM_XBUTTONUP)
	{
		auto glWnd = CBNSTabTimerDlg::Instance();
		if (glWnd && IsWindow(glWnd->GetSafeHwnd()))
		{
			PMOUSEHOOKSTRUCT mh = (PMOUSEHOOKSTRUCT)lparam;
			POINT pt;
			pt.x = mh->pt.x;
			pt.y = mh->pt.y;
			glWnd->PostMessage(WM_MOUSEBUTTONDOWN, msg, (LPARAM)nCode);
		}
	}
	return CallNextHookEx(glHook, nCode, msg, lparam);
}

LRESULT CBNSTabTimerDlg::OnMouseButtonDown(WPARAM wParam, LPARAM lParam)
{
	if (!IsWindowVisible())return 0;
	Reset();
	Start();
	return 0;
}

CBNSTabTimerDlg::CBNSTabTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	_bStart = false;
	_state = TimerState::eGreen;
}

void CBNSTabTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CBNSTabTimerDlg::Reset()
{
	KillTimer(ID_TIMER);
	_bStart = false;
	_timer = GlobalData::tabDelay;
	SetGreen();
	UpdateTime();
}

void CBNSTabTimerDlg::Start()
{
	KillTimer(ID_TIMER);
	SetTimer(ID_TIMER, 1000, NULL);
	SetRed();
	_bStart = true;
	UpdateTime();
}

void CBNSTabTimerDlg::Pause()
{
	KillTimer(ID_TIMER);
	_bStart = false;
}

BOOL CBNSTabTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
		::SetLayeredWindowAttributes(GetSafeHwnd(), 0, 222, LWA_ALPHA);
		ModifyStyleEx(WS_EX_TRANSPARENT, 0, SWP_FRAMECHANGED);
	}

	// 内容
	{
		CRect rcContent = rcClient;
		_content.Create(L"60", WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rcContent, this, IDC_CONTENT);
		_content.ShowWindow(SW_SHOW);
		_content.SetFont(&font);//设置字体
	}

	// 注册鼠标钩子
	{
		glHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);
	}

	// 初始化
	Reset();

	// TODO: 在此添加额外的初始化代码
	LayoutUtility::SetControl(this, LayoutUtility::ANCHOR_RIGHTTOP);

	// 注册热键
	//RegisterHotKey(m_hWnd, 1001, 0, 'E');

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBNSTabTimerDlg::OnDestroy()
{
	// 释放鼠标钩子
	{
		if (glHook)
			UnhookWindowsHookEx(glHook);
	}

	Reset();

	// 注销热键
	//UnregisterHotKey(m_hWnd, 1001);

	font.DeleteObject();
	__super::OnDestroy();
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
	CDialogEx::OnPaint();
}

void CBNSTabTimerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 拖拽效果
	__super::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}


#define IDC_STARTSETTING 1060
#define IDC_ABOUT 1070
#define IDC_CLOSE 2060
void CBNSTabTimerDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	tagPOINT lpoint;
	::GetCursorPos(&lpoint);//得到鼠标位置
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, IDC_STARTSETTING, L"设置");
	menu.AppendMenu(MF_STRING, IDC_ABOUT, L"帮助");
	menu.AppendMenu(MF_STRING, IDC_CLOSE, L"关闭");
	//确定弹出式菜单的位置
	SetForegroundWindow();
	UINT nCmd = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, lpoint.x, lpoint.y, this);
	if (nCmd == IDC_STARTSETTING)
	{
		CSettingDlg dlg(this);
		dlg.DoModal();
	}
	else if (nCmd == IDC_ABOUT)
	{
		::MessageBox(::GetActiveWindow(), L"按下鼠标侧键触发", L"帮助", MB_OK | MB_ICONINFORMATION);
	}
	else if (nCmd == IDC_CLOSE)
	{
		DestroyWindow();
	}
	//资源回收
	HMENU hmenu = menu.Detach();
	menu.DestroyMenu();
	__super::OnRButtonUp(nFlags, point);
}

BOOL CBNSTabTimerDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);        //取得窗体窗户区区域
	CRgn myrgn1, myrgn2;
	myrgn1.CreateRoundRectRgn(0, 0, rect.Width(), rect.Height(), 10, 10);//圆角的窗体区域
	CBrush frameBrush, titlebrush, bgbrush;
	bgbrush.CreateSolidBrush(_bgColor);//主窗体背景色画刷
	frameBrush.CreateSolidBrush(RGB(200, 200, 200));
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	pDC->FillRgn(&myrgn1, &bgbrush);
	pDC->FrameRgn(&myrgn1, &frameBrush, 1, 1);
	pDC->SetBkMode(TRANSPARENT);

	return true;
}


HBRUSH CBNSTabTimerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_CONTENT)
	{
		pDC->SetTextColor(_textColor);
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CBNSTabTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMER && _bStart)
	{
		_timer = max(0, _timer - 1);
		UpdateTime();
	}
	__super::OnTimer(nIDEvent);
}

void CBNSTabTimerDlg::UpdateTime()
{
	if (!_bStart)return;

	CString str;
	str.Format(L"%d", _timer);
	_content.SetWindowText(str);
	CRect rc;
	_content.GetWindowRect(&rc);
	ScreenToClient(&rc);
	InvalidateRect(rc);
	UpdateWindow();  //一定要加这一句

	if (_state == eGreen)
	{
		if (_timer > 5)
			SetRed();
		else if (_timer > 0)
			SetYellow();
	}
	else if (_state == eYellow)
	{
		if (_timer == 0)
		{
			SetGreen();
			Reset();
		}
	}
	else if (_state == eRed)
	{
		if (_timer == 5)
			SetYellow();
	}
}

void CBNSTabTimerDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	//if (nHotKeyId == 1001)
	//{
	//	if (GetAsyncKeyState('R') & 0x8000)
	//	{
	//		Reset();
	//		Start();
	//	}
	//}

	__super::OnHotKey(nHotKeyId, nKey1, nKey2);
}


BOOL CBNSTabTimerDlg::PreTranslateMessage(MSG* pMsg)
{
	return __super::PreTranslateMessage(pMsg);
}
