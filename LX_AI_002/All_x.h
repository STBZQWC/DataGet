//All_x.h:�������Զ������ͷ�ļ��������ļ���

#pragma once
//#include   <vector>
using namespace std;
extern USB5621A_AI_PARAM AIParam;
extern U32 nReadSampsPerChan , pSampsPerChanRead ;
extern F64 fTimeout ; // 10���ӳ�ʱ
extern U32 pAvailSampsPerChan;
extern HANDLE hDevice;
extern F64 fAnlgArray[4096];

class ResultOfExp		//ʵ�����ݽ��
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
extern int infOfexp_No;			//ʵ����ţ��ȱ�����Ȼ��ѡ�У�

extern CString choose_exp;		//ѡ��ʵ�����
extern int i_p_exp;


extern int i_getdata;		//�ɼ�����ѭ������
extern int i_inf_No;		//�������
extern BOOL i_inf_stopgetinf;		//�ɼ����
extern int i_inf_tf;		//���ݸ�������
extern int count_ax;
extern float v0;
extern float vt;
extern int state_listcombo;
extern float Fliter_V;
extern float buff_t;