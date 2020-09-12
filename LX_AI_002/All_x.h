//All_x.h:程序中自定义变量头文件（声明文件）

#pragma once
//#include   <vector>
using namespace std;
extern USB5621A_AI_PARAM AIParam;
extern U32 nReadSampsPerChan , pSampsPerChanRead ;
extern F64 fTimeout ; // 10秒钟超时
extern U32 pAvailSampsPerChan;
extern HANDLE hDevice;
extern F64 fAnlgArray[4096];

class ResultOfExp		//实验数据结果
{
public:
	CString Exp_V;
	CString Exp_A;
	CString Exp_X;
	CString XXX;
};
extern TCHAR pFolderPath[200];
extern unsigned int m_count;
extern float output;
extern CString infOfexp[10][256];
extern int infOfexp_No;			//实验序号（先遍历，然后选中）

extern CString choose_exp;		//选择实验分组
extern int i_p_exp;


extern int i_getdata;		//采集数据循环因子
extern int i_inf_No;		//数据组别
extern BOOL i_inf_stopgetinf;		//采集标记
extern int i_inf_tf;		//数据个数计数
extern int count_ax;
extern float v0;
extern float vt;
extern int state_listcombo;
extern float Fliter_V;
extern float buff_t;