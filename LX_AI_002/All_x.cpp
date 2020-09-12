//All_x.cpp:程序中自定义变量定义文件

#include"stdafx.h"
USB5621A_AI_PARAM AIParam;
U32 nReadSampsPerChan = 1024, pSampsPerChanRead = 0;
F64 fTimeout = 10.0; // 10秒钟超时
U32 pAvailSampsPerChan = 0;
HANDLE hDevice = INVALID_HANDLE_VALUE;			//创建句柄，为数据采集卡提供内存空间
F64 fAnlgArray[4096];
unsigned int m_count;
TCHAR pFolderPath[200];
float output;
CString infOfexp[10][256];
int infOfexp_No=0;
CString choose_exp;
int i_p_exp=0;
//
//vector<vector<float> >save_exp(1);
int i_getdata = 0;		//采集数据循环因子
int i_inf_No = 0;		//数据组别
BOOL i_inf_stopgetinf = 0;		//采集标记
int i_inf_tf = 0;		//数据个数计数
int count_ax=0;
float v0 = 0;
float vt = 0;
int state_listcombo=0;
float Fliter_V = 0.1;
float buff_t=0;