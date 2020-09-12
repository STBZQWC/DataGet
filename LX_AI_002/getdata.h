#pragma once


// getdata 对话框

class getdata : public CDialogEx
{
	DECLARE_DYNAMIC(getdata)

public:
	getdata(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~getdata();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LX_AI_002_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
