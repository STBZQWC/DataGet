
// LX_AI_002Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "LX_AI_002.h"
#include "LX_AI_002Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ResultOfExp roe[1024];		//采集数据数组（5.11始只用v）

vector<vector<float> >iof_a_V(1);
vector<vector<float> >iof_a_T(1);
vector<float>iof_a_A(256);
vector<float>iof_a_X(256);
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CLXAI002Dlg 对话框

void CLXAI002Dlg::ClearAllSeries(void)
{
	for (long i = 0; i <m_PicOut.get_SeriesCount(); i++)
	{
		((CSeries)m_PicOut.Series(i)).Clear();
	}
	if (i_p_exp==1)
	{
		for (long i = 0; i < m_pic_exp.get_SeriesCount(); i++)
		{
			((CSeries)m_pic_exp.Series(i)).Clear();
		}
	}
	return;
}

CLXAI002Dlg::CLXAI002Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LX_AI_002_DIALOG, pParent)
	, sta_max(_T(""))
	, sta_min(_T(""))
	, sta_ave(_T(""))
	, sta_max_fu(_T(""))
	//m_pic_exp(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//stopgetData = NULL;
}

void CLXAI002Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON_StopOutData, m_button_stop);
	DDX_Control(pDX, IDC_TCHART_PicOut, m_PicOut);
	DDX_Control(pDX, IDC_LIST_InfOfExp, m_InfOfExp);
	DDX_Control(pDX, IDC_COMBO_exp, m_chooseexp);
	DDX_Text(pDX, IDC_EDIT_sta_max, sta_max);
	DDX_Text(pDX, IDC_EDIT_sta_min, sta_min);
	DDX_Text(pDX, IDC_EDIT_sta_ave, sta_ave);
	DDX_Text(pDX, IDC_EDIT_sta_max_fu, sta_max_fu);
	DDX_Control(pDX, IDC_TCHART1, m_pic_exp);
}

CLXAI002Dlg::~CLXAI002Dlg()
{
	/*if (stopgetData != NULL) {

		delete stopgetData;

		stopgetData = NULL;

	}*/
}

BEGIN_MESSAGE_MAP(CLXAI002Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_StartGetData, &CLXAI002Dlg::OnBnClickedButtonStartgetdata)
	//ON_BN_CLICKED(IDC_BUTTON_StopOutData, &CLXAI002Dlg::OnBnClickedButtonStopoutdata)
//	ON_BN_KILLFOCUS(IDC_BUTTON_StartGetData, &CLXAI002Dlg::OnBnKillfocusButtonStartgetdata)
//ON_BN_DOUBLECLICKED(IDC_BUTTON_Pic_TV, &CLXAI002Dlg::OnBnDoubleclickedButtonPicTv)
	ON_BN_CLICKED(IDC_BUTTON_Pic_TV, &CLXAI002Dlg::OnBnClickedButtonPicTv)
	ON_BN_CLICKED(IDC_BUTTON_SavePicture, &CLXAI002Dlg::OnBnClickedButtonSavepicture)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_stopGetData, &CLXAI002Dlg::OnBnClickedButtonstopgetdata)
	ON_WM_CLOSE()
	//ON_BN_CLICKED(IDC_BUTTON_Statistic, &CLXAI002Dlg::OnBnClickedButtonStatistic)
	ON_BN_CLICKED(IDC_BUTTON_OutData, &CLXAI002Dlg::OnBnClickedButtonOutdata)
	ON_BN_CLICKED(IDC_BUTTON_show_vt, &CLXAI002Dlg::OnBnClickedButtonshowvt)
	ON_BN_CLICKED(IDC_BUTTON_Pic_at, &CLXAI002Dlg::OnBnClickedButtonPicat)
	ON_BN_CLICKED(IDC_BUTTON_Pic_xt, &CLXAI002Dlg::OnBnClickedButtonPicxt)
	ON_EN_CHANGE(IDC_EDIT_sta_ave, &CLXAI002Dlg::OnEnChangeEditstaave)
	ON_EN_CHANGE(IDC_EDIT_sta_max_fu, &CLXAI002Dlg::OnEnChangeEditstamaxfu)
	ON_EN_CHANGE(IDC_EDIT_sta_max, &CLXAI002Dlg::OnEnChangeEditstamax)
	ON_EN_CHANGE(IDC_EDIT_sta_min, &CLXAI002Dlg::OnEnChangeEditstamin)
//	ON_WM_SIZE()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON_start_dong, &CLXAI002Dlg::OnBnClickedButtonstartdong)
END_MESSAGE_MAP()

// CLXAI002Dlg 消息处理程序

BOOL CLXAI002Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_pic_exp.ShowWindow(false);
	//此处代码
	
	GetClientRect(&rect_des);     //取客户区大小  
	/*old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	CRect rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);
	cy = rt.bottom;
	MoveWindow(0, 0, cx, cy);*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLXAI002Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLXAI002Dlg::OnPaint()
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
HCURSOR CLXAI002Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CLXAI002Dlg::PreTranslateMessage(MSG * pMsg)
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
	//return 0;
}


int CLXAI002Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	
}

int CLXAI002Dlg::InitListCombo()
{
	//CRect rect;
	
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小 
	m_InfOfExp.GetClientRect(&rect);
	if (state_listcombo != 0)
	{
		m_InfOfExp.DeleteAllItems();
		return 1;
	}
	m_InfOfExp.SetExtendedStyle(m_InfOfExp.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//插入列
	m_InfOfExp.InsertColumn(0, _T("序号"), LVCFMT_CENTER, (rect.Width() / 5) * 1.5, 1);
	m_InfOfExp.InsertColumn(1, _T("电压平均值/V"), LVCFMT_CENTER, (rect.Width() / 5) * 3, 2);
	state_listcombo = 1;
	return 1;
	//int aaa = save_exp[0].size();
}

//LPITEMIDLIST CLXAI002Dlg::GetIDListFromPath(CString strPathName)		//其中包含选定文件夹代码，可移植到Self_Function.h
//{
//	if (TRUE == strPathName.IsEmpty())
//		return NULL;
//
//	LPSHELLFOLDER pDesktopFolder = NULL;		//IShellFolder
//	HRESULT hr = SHGetDesktopFolder(&pDesktopFolder);		//long
//	if (FAILED(hr))		//hr<0
//	{
//		return NULL;
//	}
//	// 得到文件路径对应的ItemIDList
//	LPITEMIDLIST pItemIDList = NULL;		//ITEMIDLIST
//	LPWSTR  pPathName = strPathName.GetBuffer(strPathName.GetLength());		//wchar获取strpathname指针，对变量内容进行修改
//	hr = pDesktopFolder->ParseDisplayName(NULL, NULL, pPathName, NULL, &pItemIDList, NULL);
//	pDesktopFolder->Release();
//	if (hr != S_OK)
//	{
//		return NULL;
//	}
//
//	return pItemIDList;
//}

float Cal_vtoa(float v)		//计算加速度函数
{
	float v_total;		//公式分子
	float c_in;		//电荷量
	float a;		//加速度
	v_total = v * 10 * 1000;		//公式见放大器说明书
	c_in = v_total / 2;
	a = c_in / 10.35;
	return a;
}


float Cal_atox(float a, float t)		//计算加速度函数
{
	float x;
	if (count_ax==0)		//第一个点
	{
		v0 = a * buff_t*0.001;		//算出速度
		x = 0.5*a*buff_t*buff_t*0.000001;
		count_ax++;
		buff_t += 0.016;
		return x*1000;
	}
	vt = v0 + a * buff_t*0.001;		//算出末速度
	x = v0 * buff_t*0.001 + 0.5*a*buff_t*buff_t*0.000001;		//位移
	v0 = vt;		//前一点的vt就是后一点的v0
	buff_t += 0.016;
	return x*1000;
}


void CLXAI002Dlg::OnEnChangeEditstaave()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(false);
	// TODO:  在此添加控件通知处理程序代码
}

void CLXAI002Dlg::OnBnClickedButtonStartgetdata()
{
	// TODO: 在此添加控件通知处理程序代码
	m_PicOut.ShowWindow(true);
	m_pic_exp.ShowWindow(false);
	// 第一步 创建设备对象
	hDevice = USB5621A_DEV_Create(0, 0);		//驱动手册中的创建对象函数，用于建立连接
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		//getlasterror();
		MessageBox(_T("DEV_Create Error!请检查设备连通性！"));
		exit(0);
		//return 0;
	}

	memset(&AIParam, 0, sizeof(USB5621A_AI_PARAM));

	AIParam.nSampChanCount = 4;
	for (int nChannel = 0; nChannel < USB5621A_AI_MAX_CHANNELS; nChannel++)
	{
		AIParam.CHParam[nChannel].nChannel = nChannel;
		AIParam.CHParam[nChannel].nSampleGain = USB5621A_AI_SAMPGAIN_1MULT;
		AIParam.CHParam[nChannel].nRefGround = USB5621A_AI_REFGND_RSE;
		AIParam.CHParam[nChannel].nReserved0 = 0;
		AIParam.CHParam[nChannel].nReserved1 = 0;
		AIParam.CHParam[nChannel].nReserved2 = 0;
	}
	AIParam.nChanScanMode = USB5621A_AI_CHAN_SCANMODE_CONTINUOUS;
	AIParam.nGroupLoops = 1;
	AIParam.nGroupInterval = 1;
	AIParam.nSampleSignal = USB5621A_AI_SAMPSIGNAL_AI;
	AIParam.nSampleRange = USB5621A_AI_SAMPRANGE_N10_P10V;

	// 时钟参数
	AIParam.nSampleMode = USB5621A_AI_SAMPMODE_CONTINUOUS;
	AIParam.nSampsPerChan = 1024;
	AIParam.fSampleRate = 62500.0;
	AIParam.nClockSource = USB5621A_AI_CLKSRC_LOCAL;
	AIParam.bClockOutput = FALSE;

	// 开始触发参数
	AIParam.bDTriggerEn = TRUE;
	AIParam.nDTriggerDir = USB5621A_AI_TRIGDIR_FALLING;
	AIParam.bATriggerEn = TRUE;
	AIParam.nATriggerDir = USB5621A_AI_TRIGDIR_FALLING;
	AIParam.fTriggerLevel = 0.0;
	AIParam.nTriggerSens = 5;
	AIParam.nDelaySamps = 0;

	// 其他参数
	AIParam.nReserved1 = 0;
	AIParam.nReserved2 = 0;
	AIParam.nReserved3 = 0;

	if (!USB5621A_AI_VerifyParam(hDevice, &AIParam))
	{
		printf("参数有错，已被调整为合法值，请注意查看日志文件USB5621A.log, 按任意键继续...\n");
		getch();
	}

	//return 0;
		// 第二步 初始化AI采集任务
	if (!USB5621A_AI_InitTask(hDevice, &AIParam, NULL))		//将上述各参数输入到采集卡中
	{
		printf("AI_InitTask Error\n");
		getch();
	}

	// 第三步 开始AI采集任务
	if (!USB5621A_AI_StartTask(hDevice))		//启动AI(模拟量输入)采集程序
	{
		printf("AI_StartTask Error\n");
		getch();
	}
		// 第四步 发送软件触发事件(硬件外触发时不需要)
	if (!USB5621A_AI_SendSoftTrig(hDevice))		//给一个下降沿触发，使其开始采集数据
	{
		printf("AI_SendSoftTrig Error\n");
		getch();
	}
	//StopGetDataWindows();
	//while (1)
	for (int i = 0; i < 1024; i++)
	{
		double tp = i * 0.016;
		roe[i].XXX.Format(_T("%f"),tp);
	}
	MessageBox(_T("初始化成功，请单击图像区域开始记录数据！"));
}


void CLXAI002Dlg::OnBnClickedButtonPicTv()		//开始采集功能
{
	//Teechart定义环节
	//CSeries TV_Series = (CSeries)m_PicOut.Series(0);
	if (output==0.2)
	{
		Fliter_V = 0.1;
	}
	MessageBox(_T("切换采集模式时，请务必先点击“停止采集”再进行切换！！！"));
	m_PicOut.ShowWindow(true);
	m_pic_exp.ShowWindow(false);
	iof_a_T.resize(1);
	iof_a_V.resize(1);
	iof_a_T[0].resize(1);
	iof_a_V[0].resize(1);
	iof_a_T[0].assign(1, 0);
	iof_a_V[0].assign(1, 0);
	CTitles TV_Titles = m_PicOut.get_Header();
	CLegend TV_legend = (CLegend)m_PicOut.get_Legend();
	//CAxes TV_axes = (CAxes)m_PicOut.Series(0);
	InitListCombo();
	ClearAllSeries();
	TV_legend.put_LegendStyle(2);
	TV_Titles.put_Caption(_T("双摆振动V-T(电压-时间)图象"));
	output = 0.1;
	//TV_axes.get_Right.put_Visible(true);
	SetTimer(0, 25, NULL);		//利用定时器定时刷新，获取数据并绘制到图像上
}


void CLXAI002Dlg::OnBnClickedButtonSavepicture()
{
	// TODO: 在此添加控件通知处理程序代码
	CString title;
	CTitles A_title = m_pic_exp.get_Header();
	CExport res = (CExport)m_pic_exp.get_Export();
	title = A_title.get_Caption();
	CString strPrjPath(_T("D:\my Docs"));

	BROWSEINFO sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	//sInfo.pidlRoot = GetIDListFromPath(strPrjPath);
	sInfo.lpszTitle = _T("请选择一个文件夹：");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	//TCHAR pFolderPath[200]; //获得选定文件的目录      已经在对应.h声明
	::SHGetPathFromIDList(lpidlBrowse, pFolderPath);//pxxxxx里面有文件名
	res.SaveToBitmapFile((CString)pFolderPath + _T("\\") + title + _T(".jpg"), 1);		//图片存储语句
	AfxMessageBox(_T("保存成功！请前往选定目录查看！"));
}


void CLXAI002Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//int i_getdata;
	if (0 == nIDEvent)
	{
		++m_count;
		//DWORD start_time = GetTickCount();
		GifDataVT();
		//DWORD end_time = GetTickCount();
		//++m_count;
		//--m_count;

	}
	CDialogEx::OnTimer(nIDEvent);
}

void CLXAI002Dlg::GifDataVT()
{
	//vector<vector<float> >save_exp(1);
	CSeries gif = (CSeries)m_PicOut.Series(0);
	ClearAllSeries();
	
	USB5621A_AI_ReadAnalog(hDevice, fAnlgArray, nReadSampsPerChan, &pSampsPerChanRead, &pAvailSampsPerChan, fTimeout);		//采集卡数据获取
	for ( i_getdata = 0; i_getdata<1024; i_getdata++)
	{
		F64 f_total = fAnlgArray[i_getdata * 4 + 0] + fAnlgArray[i_getdata * 4 + 1] + fAnlgArray[i_getdata * 4 + 2] + fAnlgArray[i_getdata * 4 + 3];
		f_total = f_total / (F64)8;
		if (abs(f_total) >= Fliter_V&&i_inf_stopgetinf!=1&&(f_total-(fAnlgArray[(i_getdata+1) * 4 + 0] + fAnlgArray[(i_getdata + 1) * 4 + 1] + fAnlgArray[(i_getdata + 1) * 4 + 2] + fAnlgArray[(i_getdata + 1) * 4 + 3]))>0.01)
		{
			i_inf_tf = 256;
			i_inf_stopgetinf = 1;
			if (i_inf_No!=0)
			{
				iof_a_T.resize(i_inf_No + 1);
				iof_a_V.resize(i_inf_No + 1);
			}
		}
		if (i_inf_tf!=0)
		{
			iof_a_V[i_inf_No].push_back(f_total);
			iof_a_T[i_inf_No].push_back(_ttof(roe[i_getdata].XXX));
			i_inf_tf--;
		}
		if (i_inf_tf==0&&i_inf_stopgetinf==1)
		{
			i_inf_No++;
			i_inf_stopgetinf = 0;
		}
	
		roe[i_getdata].Exp_V.Format(_T("%f"), f_total);
		gif.AddXY(i_getdata,_ttof(roe[i_getdata].Exp_V), roe[i_getdata].XXX,0);		//将数据点绘制在Teechart控件上
	}
}

void CLXAI002Dlg::OnBnClickedButtonstopgetdata()
{
	// TODO: 在此添加控件通知处理程序代码
	//0.停止测量进程（定时器）
	KillTimer(0);
	if (Fliter_V==0.2)
	{
		output = 0.2;
	}
	//1.求取平均值，显示在表格中
	CRect rect;
	int i_y = 0; int i_x = 0;
	F64 buff_total = 0; F64 buff_ave = 0; F64 buff_v=0;
	CString buff_00; CString buff_01;
	infOfexp_No = iof_a_V.size();
		//储存实验数据数量
	for (i_y=0;i_y<infOfexp_No;i_y++)
	{
		for ( i_x = 0; i_x < 256; i_x++)
		{
			//ioe_a[i_y].iof_a_V[i_x].Format(_T("%f"), buff_v);
			buff_v=iof_a_V[i_y][i_x];
			buff_total += buff_v;
		}
		buff_ave = buff_total / (F64)256;
		//m_InfOfExp.InsertColumn(1, _T("电压平均值"), LVCFMT_CENTER, (rect.Width() / 5) * 3, 2);
		buff_00.Format(_T("%d"), i_y + 1);
		buff_01.Format(_T("%f"),buff_ave);
		//m_InfOfExp.SetItemText(i_y + 1, 0,buff_00);
		m_InfOfExp.GetClientRect(&rect);
		m_InfOfExp.InsertItem(i_y + 1, buff_00);
		m_InfOfExp.SetItemText((i_y), 1, buff_01);
		m_chooseexp.AddString(buff_00);
		//m_InfOfExp.InsertColumn(i_y + 1, 1, buff_01);
		buff_total = 0; buff_ave = 0; buff_v = 0;
	}
	m_chooseexp.InsertString(0,_T("请选择序号"));
	m_chooseexp.SetCurSel(0);
	i_p_exp = 1;
	MessageBox(_T("已停止采集！"));
}


void CLXAI002Dlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	USB5621A_AI_ReleaseTask(hDevice);
	USB5621A_DEV_Release(hDevice);
	CDialogEx::OnClose();
}


void CLXAI002Dlg::OnBnClickedButtonOutdata()
{
	//0.针对统计是否完成进行的统计
	float num_x = iof_a_X[0];
	float num_a = iof_a_A[0];
	if (num_a == 0 && num_x == 0)
	{
	if (MessageBox(_T("加速度&位移数据未统计完成！需要统计请单击是，然后单击图像生成进行计算，单击否则只生成电压数据"), NULL, MB_YESNO) == IDYES)
	{
		return;
	}
	}
	else if (num_x==0&&num_a!=0)
	{
		if (MessageBox(_T("位移数据未统计完成！需要统计请单击是，然后单击x-t图像生成进行计算，单击否则位移数据为0"), NULL, MB_YESNO) == IDYES)
		{
			return;
		}
	}
	else if (num_a == 0 && num_x != 0)
	{
		if (MessageBox(_T("加速度数据未统计完成！需要统计请单击是，然后单击a-t图像生成进行计算，单击否则加速度数据为0"), NULL, MB_YESNO) == IDYES)
		{
			return;
		}
	}
	//进行生成
	m_chooseexp.GetWindowText(choose_exp);
	infOfexp_No = _wtoi(choose_exp) - 1;

	CApplication App;  //创建应用程序实例
	CWorkbooks Books;  //工作簿，多个Excel文件
	CWorkbook Book;    //单个工作簿
	CWorksheets sheets;//多个sheet页面
	CWorksheet sheet;  //单个sheet页面
	CRange range;      //操作单元格
	CBorder border;
	CString str;
	CString strPrjPath(_T("D:\my Docs"));
	CFileDialog FileDialog(FALSE, _T("xlsx"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Excel工作簿(*.xlsx)|*.xlsx|所有文件(*.*)"), this);
	if (FileDialog.DoModal() != IDOK)
	{
		return;
	}
	CString strExcelFile = FileDialog.GetPathName();  //选择保存路径名称

	if (::PathFileExists(strExcelFile))
		DeleteFile(strExcelFile);
	COleVariant
		covTrue((short)TRUE),
		covFalse((short)FALSE),
		covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//LPDISPATCH lpdisp = NULL;
	//GetDlgItemText(IDOK, str);
	//1.创建Excel实例
	if (!App.CreateDispatch(_T("Excel.Application"), NULL))
	{
		AfxMessageBox(_T("创建Excel实例失败"));
		exit(-1);
	}
	else
	{
		AfxMessageBox(_T("创建成功，文件保存在所选取目录下~"));
	}
	App.put_Visible(TRUE);  //打开Excel
	App.put_UserControl(FALSE);
	//2. 得到workbooks容器
	Books.AttachDispatch(App.get_Workbooks());
	Book.AttachDispatch(Books.Add(covOptional));
	sheets.AttachDispatch(Book.get_Worksheets());
	sheet.AttachDispatch(sheets.get_Item(COleVariant((short)1)));   //获取sheet1
	sheet.put_Name(_T("实验数据"));     //设置sheet1名字
	//3. 加载要合并的单元格
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("E1"))), TRUE);
	range.Merge(COleVariant((long)0));


	//4. 设置表格内容
	range.AttachDispatch(sheet.get_Cells(), TRUE);               //加载所有单元格
	range.put_Item(COleVariant((long)1), COleVariant((long)1), COleVariant( _T("双摆提速钻具实验数据表")));
	range.put_Item(COleVariant((long)2), COleVariant((long)1), COleVariant(_T("序号")));
	range.put_Item(COleVariant((long)2), COleVariant((long)2), COleVariant(_T("时间/ms")));
	range.put_Item(COleVariant((long)2), COleVariant((long)3), COleVariant(_T("电压/v")));
	range.put_Item(COleVariant((long)2), COleVariant((long)4), COleVariant(_T("加速度/(mm/ms2)")));
	range.put_Item(COleVariant((long)2), COleVariant((long)5), COleVariant(_T("位移/mm")));
	range.AttachDispatch(sheet.get_UsedRange());//加载已使用的单元格
	range.put_WrapText(COleVariant((long)1));   //设置文本自动换行


	//5.设置对齐方式
	//水平对齐：默认 1 居中 -4108， 左= -4131，右=-4152
	//垂直对齐：默认 2 居中 -4108， 左= -4160，右=-4107
	range.put_VerticalAlignment(COleVariant((long)-4108));
	range.put_HorizontalAlignment(COleVariant((long)-4108));

	//6.设置字体颜色
	CFont0 ft;
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("E1"))), TRUE);
	ft.AttachDispatch(range.get_Font());
	ft.put_Name(COleVariant(_T("黑体")));
	ft.put_Bold(COleVariant((long)1));
	ft.put_ColorIndex(COleVariant((long)1));    //颜色    
	ft.put_Size(COleVariant((long)18));         //大小
	Book.SaveCopyAs(COleVariant(strExcelFile)); //保存

	//7.设置边框
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("E258"))), TRUE);
	border.AttachDispatch(range.get_Borders());
	border.put_ColorIndex(COleVariant((long)1));
	Book.SaveCopyAs(COleVariant(strExcelFile));

	//8.设置行高&列宽
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("E1"))), TRUE);
	range.put_RowHeight(COleVariant((short)27));
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A258"))), TRUE);
	range.put_ColumnWidth(COleVariant((short)5));
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("B1")), COleVariant(_T("B258"))), TRUE);
	range.put_ColumnWidth(COleVariant((short)8));
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("C1")), COleVariant(_T("C258"))), TRUE);
	range.put_ColumnWidth(COleVariant((short)14));
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("D1")), COleVariant(_T("D258"))), TRUE);
	range.put_ColumnWidth(COleVariant((short)14));
	range.AttachDispatch(sheet.get_Range(COleVariant(_T("E1")), COleVariant(_T("E258"))), TRUE);
	range.put_ColumnWidth(COleVariant((short)14));
	Book.SaveCopyAs(COleVariant(strExcelFile));


	////9.设置单元格格式
	//range.AttachDispatch(sheet.get_Range(COleVariant(_T("A3")), COleVariant(_T("E2050"))), TRUE);
	//range.put_NumberFormat(COleVariant((long)0));
	//Book.SaveCopyAs(COleVariant(strExcelFile));

	//10.数据导入
	/*int need_x = 0;
	int need_a = 0;
	if (need_a != 0)
	{
		iof_a_A.insert(iof_a_A.end(), need_a, 0);
	}
	if (need_x != 0)
	{
		iof_a_A.insert(iof_a_A.end(), need_a, 0);
	}*/

	for ( int i = 0; i < 256; i++)		
	{
		range.AttachDispatch(sheet.get_Cells(), TRUE);
		CString buff_excel_T;
		CString buff_excel_V;
		CString buff_excel_A;
		CString buff_excel_X;
		buff_excel_T.Format(_T("%f"), iof_a_T[infOfexp_No][i]);
		buff_excel_V.Format(_T("%f"), iof_a_V[infOfexp_No][i]);
		buff_excel_A.Format(_T("%f"), iof_a_A[i]);
		buff_excel_X.Format(_T("%f"), iof_a_X[i]);
		range.put_Item(COleVariant((long)i + 3), COleVariant((long)1), COleVariant((long)i+1));
		range.put_Item(COleVariant((long)i + 3), COleVariant((long)2), COleVariant(buff_excel_T));
		range.put_Item(COleVariant((long)i + 3), COleVariant((long)3), COleVariant(buff_excel_V));
		range.put_Item(COleVariant((long)i + 3), COleVariant((long)4), COleVariant(buff_excel_A));
		range.put_Item(COleVariant((long)i + 3), COleVariant((long)5), COleVariant(buff_excel_X));
		//Book.SaveCopyAs(COleVariant(strExcelFile));
	}
	Book.SaveCopyAs(COleVariant(strExcelFile));

	//11.保存&释放资源

	Book.put_Saved(TRUE);
	Books.Close();
	App.Quit();
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	Book.ReleaseDispatch();
	Books.ReleaseDispatch();
	App.ReleaseDispatch();
}


void CLXAI002Dlg::OnBnClickedButtonshowvt()
{
	//0.获取选择组号
	m_chooseexp.GetWindowText(choose_exp);
	infOfexp_No = _wtoi(choose_exp)-1;
	m_PicOut.ShowWindow(false);	
	m_pic_exp.ShowWindow(true); // 隐藏控件（实验用控件）
	//由于直接采集的就是电压，这里省去数据处理过程
	//1.开始图像输出
	CSeries Showvt = (CSeries)m_pic_exp.Series(0);
	//CSeries Showvt_x= (CSeries)m_PicOut.Series(1);
	CLegend Showvt_legend = (CLegend)m_pic_exp.get_Legend();
	CTitles Showvt_titles = (CTitles)m_pic_exp.get_Header();
	//CSeries(m_PicOut.Series(1)).put_Active(FALSE);
	//InfOfExp_all showvt_iofe_all;
	CString buff_time;
	ClearAllSeries();
	Showvt_legend.put_LegendStyle(2);
	Showvt_titles.put_Caption(_T("双摆振动V-T(电压-时间)图象"));
	for (int i_showvt = 0; i_showvt < 256; i_showvt++)
	{
		buff_time.Format(_T("%f"), iof_a_T[infOfexp_No][i_showvt]);
		//Showvt.AddXY(i_showvt, _ttof(ioe_a[infOfexp_No].iof_a_V[i_showvt]), ioe_a[infOfexp_No].iof_a_T[i_showvt], 0);
		Showvt.AddXY(i_showvt, iof_a_V[infOfexp_No][i_showvt],buff_time, 0);
		
	}
	//Showvt.AddArray(256,iof_a_V[infOfexp_No],)
	//2.开始数值计算
	int showvt_average_x;
	F64 showvt_average_buff_v=0;
	F64 showvt_average_buff_total = 0;
	F64 showvt_average_buff_ave = 0;
	for (showvt_average_x = 0; showvt_average_x < 256; showvt_average_x++)		//平均值计算
	{
		//ioe_a[i_y].iof_a_V[i_x].Format(_T("%f"), buff_v);
		showvt_average_buff_v = iof_a_V[infOfexp_No][showvt_average_x];
		showvt_average_buff_total += showvt_average_buff_v;		//累加
	}
	showvt_average_buff_ave = showvt_average_buff_total / (F64)256;		//平均值计算
	sta_ave.Format(_T("%f"),showvt_average_buff_ave);
	HWND h = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_ave);
	::SetWindowText(h, sta_ave);
	//sort(iof_a_V[infOfexp_No].begin(), iof_a_V[infOfexp_No].end());
	//最最值获取
	vector<float>iof_a_V_mm(256);
	partial_sort_copy(iof_a_V[infOfexp_No].begin(), iof_a_V[infOfexp_No].end(), iof_a_V_mm.begin(), iof_a_V_mm.end());		//排序语句
	if (iof_a_V_mm[0]>0)
	{
		sta_max.Format(_T("%f"),iof_a_V_mm[255]);
		sta_max_fu = _T("----");
		sta_min.Format(_T("%f"), iof_a_V_mm[0]);
	}
	else if (iof_a_V_mm[255] < 0)
	{
		sta_max_fu.Format(_T("%f"), iof_a_V_mm[255]);
		sta_max= _T("----");
		sta_min.Format(_T("%f"), iof_a_V_mm[0]);
	}
	else
	{
		sta_max_fu.Format(_T("%f"), iof_a_V_mm[0]);
		sta_min = _T("0");
		sta_max.Format(_T("%f"), iof_a_V_mm[255]);
	}
	HWND h1 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_max_fu);
	::SetWindowText(h1, sta_max_fu);
	
	HWND h2 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_max);
	::SetWindowText(h2, sta_max);

	HWND h3 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_min);
	::SetWindowText(h3, sta_min);

}


void CLXAI002Dlg::OnBnClickedButtonPicat()
{
	m_PicOut.ShowWindow(false);
	m_pic_exp.ShowWindow(true);
	m_chooseexp.GetWindowText(choose_exp);
	infOfexp_No = _wtoi(choose_exp) - 1;
	//1.定义变量
	CSeries Showat = (CSeries)m_pic_exp.Series(0);
	CLegend Showat_legend= (CLegend)m_pic_exp.get_Legend();
	CTitles Showat_titles = (CTitles)m_pic_exp.get_Header();
	CString buff_time_at;
	ClearAllSeries();
	Showat_legend.put_LegendStyle(2);
	Showat_titles.put_Caption(_T("双摆振动A-T(加速度-时间)图象(m/s2)"));
	//2.计算加速度环节
	//a=cal_vtoa(v);
	transform(iof_a_V[infOfexp_No].begin(), iof_a_V[infOfexp_No].end(), iof_a_A.begin(), Cal_vtoa);
	for (int i_showat = 0; i_showat < 256; i_showat++)
	{
		buff_time_at.Format(_T("%f"), iof_a_T[infOfexp_No][i_showat]);
		//Showvt.AddXY(i_showvt, _ttof(ioe_a[infOfexp_No].iof_a_V[i_showvt]), ioe_a[infOfexp_No].iof_a_T[i_showvt], 0);
		Showat.AddXY(i_showat, iof_a_A[i_showat], buff_time_at, 0);
	}
	//4.最最计算环节
	int showat_average_x;
	F64 showat_average_buff_a = 0;
	F64 showat_average_buff_total = 0;
	F64 showat_average_buff_ave = 0;
	for (showat_average_x = 0; showat_average_x < 256; showat_average_x++)		//平均值计算
	{
		//ioe_a[i_y].iof_a_V[i_x].Format(_T("%f"), buff_v);
		showat_average_buff_a = iof_a_X[showat_average_x];
		showat_average_buff_total += showat_average_buff_a;
	}
	showat_average_buff_ave = showat_average_buff_total / (F64)256;
	sta_ave.Format(_T("%f"), showat_average_buff_ave);
	HWND h_showat_1 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_ave);
	::SetWindowText(h_showat_1, sta_ave);
	//sort(iof_a_V[infOfexp_No].begin(), iof_a_V[infOfexp_No].end());
	//最最值获取
	vector<float>iof_a_A_mm(256);
	partial_sort_copy(iof_a_A.begin(), iof_a_A.end(), iof_a_A_mm.begin(), iof_a_A_mm.end());		//排序语句
	if (iof_a_A_mm[0] > 0)
	{
		sta_max.Format(_T("%f"), iof_a_A_mm[255]);
		sta_max_fu = _T("----");
		sta_min.Format(_T("%f"), iof_a_A_mm[0]);
	}
	else if (iof_a_A_mm[255] < 0)
	{
		sta_max_fu.Format(_T("%f"), iof_a_A_mm[255]);
		sta_max = _T("----");
		sta_min.Format(_T("%f"), iof_a_A_mm[0]);
	}
	else
	{
		sta_max_fu.Format(_T("%f"), iof_a_A_mm[0]);
		sta_min = _T("0");
		sta_max.Format(_T("%f"), iof_a_A_mm[255]);
	}
	HWND h_showat_2 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_max_fu);
	::SetWindowText(h_showat_2, sta_max_fu);

	HWND h_showat_3 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_max);
	::SetWindowText(h_showat_3, sta_max);

	HWND h_showat_4 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_min);
	::SetWindowText(h_showat_4, sta_min);
}


void CLXAI002Dlg::OnBnClickedButtonPicxt()
{
	m_PicOut.ShowWindow(false);
	m_pic_exp.ShowWindow(true);
	m_chooseexp.GetWindowText(choose_exp);
	infOfexp_No = _wtoi(choose_exp) - 1;
	CSeries Showxt = (CSeries)m_pic_exp.Series(0);
	CLegend Showxt_legend = (CLegend)m_pic_exp.get_Legend();
	CTitles Showxt_titles = (CTitles)m_pic_exp.get_Header();
	CString buff_time_xt;
	ClearAllSeries();
	Showxt_legend.put_LegendStyle(2);
	Showxt_titles.put_Caption(_T("双摆振动X-T(加速度-时间)图象(mm)"));
	//2.计算加速度环节
	transform(iof_a_A.begin(), iof_a_A.end(),iof_a_T[infOfexp_No].begin(),iof_a_X.begin(), Cal_atox);
	for (int i_showxt = 0; i_showxt < 256; i_showxt++)
	{
		buff_time_xt.Format(_T("%f"), iof_a_T[infOfexp_No][i_showxt]);
		//Showvt.AddXY(i_showvt, _ttof(ioe_a[infOfexp_No].iof_a_V[i_showvt]), ioe_a[infOfexp_No].iof_a_T[i_showvt], 0);
		Showxt.AddXY(i_showxt, iof_a_X[i_showxt], buff_time_xt, 0);
	}
	//4.最最计算环节
	int showat_average_x;
	F64 showat_average_buff_a = 0;
	F64 showat_average_buff_total = 0;
	F64 showat_average_buff_ave = 0;
	for (showat_average_x = 0; showat_average_x < 256; showat_average_x++)		//平均值计算
	{
		//ioe_a[i_y].iof_a_V[i_x].Format(_T("%f"), buff_v);
		showat_average_buff_a = iof_a_A[showat_average_x];
		showat_average_buff_total += showat_average_buff_a;
	}
	showat_average_buff_ave = showat_average_buff_total / (F64)256;
	sta_ave.Format(_T("%f"), showat_average_buff_ave);
	HWND h_showxt_1 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_ave);
	::SetWindowText(h_showxt_1, sta_ave);
	//sort(iof_a_V[infOfexp_No].begin(), iof_a_V[infOfexp_No].end());
	//最最值获取
	vector<float>iof_a_X_mm(256);
	partial_sort_copy(iof_a_X.begin(), iof_a_X.end(), iof_a_X_mm.begin(), iof_a_X_mm.end());		//排序语句
	if (iof_a_X_mm[0] > 0)
	{
		sta_max.Format(_T("%f"), iof_a_X_mm[255]);
		sta_max_fu = _T("----");
		sta_min.Format(_T("%f"), iof_a_X_mm[0]);
	}
	else if (iof_a_X_mm[255] < 0)
	{
		sta_max_fu.Format(_T("%f"), iof_a_X_mm[255]);
		sta_max = _T("----");
		sta_min.Format(_T("%f"), iof_a_X_mm[0]);
	}
	else
	{
		sta_max_fu.Format(_T("%f"), iof_a_X_mm[0]);
		sta_min = _T("0");
		sta_max.Format(_T("%f"), iof_a_X_mm[255]);
	}
	HWND h_showxt_2 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_max_fu);
	::SetWindowText(h_showxt_2, sta_max_fu);

	HWND h_showxt_3 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_max);
	::SetWindowText(h_showxt_3, sta_max);

	HWND h_showxt_4 = ::GetDlgItem(this->m_hWnd, IDC_EDIT_sta_min);
	::SetWindowText(h_showxt_4, sta_min);
	count_ax = 0;
}


void CLXAI002Dlg::OnEnChangeEditstamaxfu()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(false);
	// TODO:  在此添加控件通知处理程序代码
}


void CLXAI002Dlg::OnEnChangeEditstamax()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(false);
	// TODO:  在此添加控件通知处理程序代码
}


void CLXAI002Dlg::OnEnChangeEditstamin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(false);
	// TODO:  在此添加控件通知处理程序代码
}
void CLXAI002Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType != SIZE_MINIMIZED) //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{


		ReSize(IDC_TCHART1, cx,cy);
		ReSize(IDC_TCHART_PicOut, cx, cy);
		ReSize(IDC_LIST_InfOfExp, cx, cy);
		ReSize(IDC_COMBO_exp, cx, cy);
		ReSize(IDC_EDIT_sta_max, cx, cy);
		ReSize(IDC_EDIT_sta_min, cx, cy);
		ReSize(IDC_EDIT_sta_ave, cx, cy);
		ReSize(IDC_EDIT_sta_max_fu, cx, cy);


	/*	DDX_Control(pDX, IDC_TCHART_PicOut, m_PicOut);
		DDX_Control(pDX, IDC_LIST_InfOfExp, m_InfOfExp);
		DDX_Control(pDX, IDC_COMBO_exp, m_chooseexp);
		DDX_Text(pDX, IDC_EDIT_sta_max, sta_max);
		DDX_Text(pDX, IDC_EDIT_sta_min, sta_min);
		DDX_Text(pDX, IDC_EDIT_sta_ave, sta_ave);
		DDX_Text(pDX, IDC_EDIT_sta_max_fu, sta_max_fu);
		DDX_Control(pDX, IDC_TCHART1, m_pic_exp);*/

		GetClientRect(&rect_des); //最后要更新对话框的大小，当做下一次变化的旧坐标


	}
}
void CLXAI002Dlg::ReSize(UINT nID, int x, int y)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL) //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{


		CRect rec;
		pWnd->GetWindowRect(&rec); //获取控件变化前的大小
		ScreenToClient(&rec); //将控件大小装换位在对话框中的区域坐标
		rec.left = rec.left*x / rect_des.Width(); //按照比例调整空间的新位置
		rec.top = rec.top*y / rect_des.Height();
		rec.bottom = rec.bottom*y / rect_des.Height();
		rec.right = rec.right*x / rect_des.Width();
		pWnd->MoveWindow(rec); //伸缩控件
	}
}
//void CLXAI002Dlg::OnSize(UINT nType, int cx, int cy)
//{
//	CDialogEx::OnSize(nType, cx, cy);
//
//	// TODO: 在此处添加消息处理程序代码
//	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
//	{
//		ReSize();
//	}
//
//}

void CLXAI002Dlg::OnBnClickedButtonstartdong()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox(_T("切换采集模式时，请务必先点击“停止采集”再进行切换！！！"));
	Fliter_V = 0.75;
	//output = 0.2;
	OnBnClickedButtonPicTv();
}
