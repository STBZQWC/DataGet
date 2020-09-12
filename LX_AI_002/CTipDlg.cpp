// CTipDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LX_AI_002.h"
#include "CTipDlg.h"
#include "afxdialogex.h"


// CTipDlg 对话框

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_StopGetData, pParent)
{

}

CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_Msg_StopGetData, m_stopGdata);
}

BOOL CTipDlg::PreTranslateMessage(MSG * pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN: //屏蔽回车键
			return TRUE;
		case VK_ESCAPE: //屏蔽ESC键
			return TRUE;
		case VK_SPACE: //屏蔽ESC键
			return TRUE;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
	return 0;
}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_Msg_StopGetData, &CTipDlg::OnBnClickedButtonMsgStopgetdata)
END_MESSAGE_MAP()


// CTipDlg 消息处理程序


int CTipDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	
	return 0;
}



void CTipDlg::OnBnClickedButtonMsgStopgetdata()
{
	// TODO: 在此添加控件通知处理程序
	if (!USB5621A_AI_ReleaseTask(hDevice))
	{
		printf("AI_ReleaseTask Error\n");
		getch();
	}

	// 第八步 释放设备对象
	if (!USB5621A_DEV_Release(hDevice))
	{
		printf("DEV_Release Error\n");
		getch();
	}

	OnOK();
}


BOOL CTipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	GetDlgItem(IDC_BUTTON_Msg_StopGetData)->PostMessageW(WM_KILLFOCUS,0,0);
	return FALSE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
