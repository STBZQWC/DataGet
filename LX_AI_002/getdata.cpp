// getdata.cpp: 实现文件
//

#include "stdafx.h"
#include "LX_AI_002.h"
#include "getdata.h"
#include "afxdialogex.h"


// getdata 对话框

IMPLEMENT_DYNAMIC(getdata, CDialogEx)

getdata::getdata(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LX_AI_002_DIALOG, pParent)
{

}

getdata::~getdata()
{
}

void getdata::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(getdata, CDialogEx)
END_MESSAGE_MAP()


// getdata 消息处理程序
