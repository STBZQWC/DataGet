//All_x.cpp:�������Զ�����������ļ�

#include"stdafx.h"
USB5621A_AI_PARAM AIParam;
U32 nReadSampsPerChan = 1024, pSampsPerChanRead = 0;
F64 fTimeout = 10.0; // 10���ӳ�ʱ
U32 pAvailSampsPerChan = 0;
HANDLE hDevice = INVALID_HANDLE_VALUE;			//���������Ϊ���ݲɼ����ṩ�ڴ�ռ�
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
int i_getdata = 0;		//�ɼ�����ѭ������
int i_inf_No = 0;		//�������
BOOL i_inf_stopgetinf = 0;		//�ɼ����
int i_inf_tf = 0;		//���ݸ�������
int count_ax=0;
float v0 = 0;
float vt = 0;
int state_listcombo=0;
float Fliter_V = 0.1;
float buff_t=0;