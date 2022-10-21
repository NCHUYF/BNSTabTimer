
// BNSTabTimerDlg.cpp: 实现文件
//

#include "pch.h"
#include "../Resource.h"
#include "SettingDlg.h"
#include "afxdialogex.h"
#include "../Utility/LayoutUtility.h"
#include "../Model/GlobalData.h"

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD, _btnAdd);
	DDX_Control(pDX, IDC_SUB, _btnSub);
	DDX_Control(pDX, IDC_CONTENT, _textContent);
}

void CSettingDlg::UpdateUI()
{
	CString str;
	str.Format(L"%d", _valCache);
	_textContent.SetWindowText(str);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_SUB, &CSettingDlg::OnBnClickedSub)
	ON_BN_CLICKED(IDC_ADD, &CSettingDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序

BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	_valCache = GlobalData::tabDelay;
	UpdateUI();

	LayoutUtility::SetControl(this, LayoutUtility::ANCHOR_CENTER);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSettingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSettingDlg::OnPaint()
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
HCURSOR CSettingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSettingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 拖拽效果
	__super::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}


#define IDC_STARTSETTING 1060
#define IDC_CLOSE 2060
void CSettingDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	tagPOINT lpoint;
	::GetCursorPos(&lpoint);//得到鼠标位置
	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, IDC_STARTSETTING, L"设置");
	menu.AppendMenu(MF_STRING, IDC_CLOSE, L"关闭");
	//确定弹出式菜单的位置
	SetForegroundWindow();
	UINT nCmd = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, lpoint.x, lpoint.y, this);
	if (nCmd == IDC_STARTSETTING)
	{
		MessageBox(L"IDC_STARTSETTING");
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

void CSettingDlg::OnBnClickedSub()
{
	_valCache = max(0, _valCache - 1);
	UpdateUI();
}


void CSettingDlg::OnBnClickedAdd()
{
	_valCache = min(1000, _valCache + 1);
	UpdateUI();
}


void CSettingDlg::OnOK()
{
	GlobalData::tabDelay = _valCache;
	CDialogEx::OnOK();
}
