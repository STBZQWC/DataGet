
// LX_AI_002Dlg.h: 头文件
//

#pragma once
//#include "CTipDlg.h"

// CLXAI002Dlg 对话框
class CLXAI002Dlg : public CDialogEx
{
// 构造
public:
	void ClearAllSeries(void);
	CLXAI002Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LX_AI_002_DIALOG };
#endif
	//CTipDlg *stopgetData;
	~CLXAI002Dlg();
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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int InitListCombo();
	//LPITEMIDLIST GetIDListFromPath(CString strPathName);

	afx_msg void OnBnClickedButtonStartgetdata();

	afx_msg void OnBnClickedButtonPicTv();
	// 图片输出控件
	CTChart m_PicOut;
	afx_msg void OnBnClickedButtonSavepicture();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void GifDataVT();
	//void GifDataVT();
	afx_msg void OnBnClickedButtonstopgetdata();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonStatistic();
	afx_msg void OnBnClickedButtonOutdata();
	// 实验数据捕捉信息
	CListCtrl m_InfOfExp;
	// 选择捕捉列表内的实验数据
	CComboBox m_chooseexp;
	// 统计窗口最大值
	CString sta_max;
	// 统计窗口最小值
	CString sta_min;
	// 数据展示平均值
	CString sta_ave;
	afx_msg void OnBnClickedButtonshowvt();
	afx_msg void OnBnClickedButtonPicat();
	afx_msg void OnBnClickedButtonPicxt();
	afx_msg void OnEnChangeEditstaave();
	// 反向最大值（-）
	CString sta_max_fu;
	afx_msg void OnEnChangeEditstamaxfu();
	afx_msg void OnEnChangeEditstamax();
	afx_msg void OnEnChangeEditstamin();
	// 实验数据用表
	CTChart m_pic_exp;
public:
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	
	POINT old;
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ReSize(UINT nID, int x, int y);
	CRect rect_des;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonstartdong();
};
