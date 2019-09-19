/******************************************************************************
 *File Name	     :	Appraise_Clac.h
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/07/01
 *Description    :	
 *Modification history:
 *REV1.0.0    Tangwei     2019/07/01    File Create 
******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef ACS_APPRAISE_CLAC_H_
#define	ACS_APPRAISE_CLAC_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/Appraise_BasicFunction.h"
//#include "Appraise_BasicFunction.h"
//#include "../AppraiseSyetem/Appraise_Sense.h"
/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/
#define		STARUP_NUM_MAX		(30U)
#define		NETURL_NUM_MAX		(50U)
/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
 typedef struct TAG_AppraisePara
{
	UINT16     Velocity;					/*�ٶ�*/
	UINT32	   Time;						/*ʱ��*/
	UINT32	   Distance2RelativeZero;		/*���0�����*/
	UINT32	   AbsoluteDiStance;		    /*���Ծ���*/
	UINT16	   Level;						/*��λ*/
	UINT16     RunningStatus;				/*����*/
	E_SysBool  Nuetral;						/*����*/
	E_SysBool  BrakeTest;					/*��ͨ����*/
	UINT8	   SignalType_E;				/*�źŻ�����*/
	
}S_APPRAISE_PARA;

typedef struct TAG_SafetyCalcResult
{
	// UINT16 	AppraiseTotalGrade; 		/*��ʻ�����ܷ�*/
	 UINT32 	Safety;				 		/*��ȫ��*/
	 UINT16     OverAccNum;					/*���ٶȹ������*/
	 UINT16		OverAccAccNum;				/*�Ӽ��ٶȹ������*/
	 UINT16		OverTrnCplrFrcNum;			/*�������������*/
	 UINT16     OverSpdNum;					/*�ٶȹ������*/
	 UINT16		BreakDownNum;				/*���ϴ�������*/
	//REAL32	QratioP;					/*�ѹ�ϵ��,һ��С��1.0�����������1.2*/
	//REAL32	pratioP;					/*�����ʣ�����ٶ�<160km/h��ֵ0.65,>160km/hΪ0.8*/
	//REAL32	MaxHforce;					/*����������ֵ(15+3p0)KN*/
		
	 
} S_SAFETYCALCRESULT;

 typedef struct TAG_StartUpTimeDate
{
	UINT8		StartUpNum;						/*�𳵴���*/

	UINT32		StartUp_v0[STARUP_NUM_MAX];		/*��ǰʱ�����1=1s*/
	UINT32		StartUp_v5[STARUP_NUM_MAX];		/*�ٶ�Ϊ5km/hʱ�����1=1s*/
	UINT32		StartUp_Time[STARUP_NUM_MAX];	/*����ʱ��1=1s*/

	UINT32		StartUp_d0[STARUP_NUM_MAX];		/*��ǰ����λ��*/
	UINT32		StartUp_d5[STARUP_NUM_MAX];		/*�ٶ�Ϊ5km/h����λ��*/
 	REAL32		StartUp_Ramp[STARUP_NUM_MAX];	/*�𳵶μ����µ�ǧ������1=ǧ��֮һ*/

	E_SysBool	StartUp_Key;					/*e_TRUE��ʾ�����𳵹���,e_FALSE��ʾ�����𳵹�����*/
} S_STARTUPTIMEDATE;

 typedef struct TAG_SpeedStopTimeDate
{
	UINT8		SpdStopNum;						/*ͣ������*/

	UINT32		SpdStop_vX[STARUP_NUM_MAX];		/*Ԥ��ͣ��ʱ��v=����*����*����km/h��ʱ�����1=1s*/
	UINT32		SpdStop_v0[STARUP_NUM_MAX];		/*ͣ��ʱ��v=0km/h��ʱ�����1=1s*/
	UINT32		SpdStop_Time[STARUP_NUM_MAX];	/*ͣ����ʱ��1=1s*/
	REAL32		SpdStop_Ramp[STARUP_NUM_MAX];	/*ͣ���μ����µ�ǧ������1=ǧ��֮һ*/

	E_SysBool	SpdStop_Key;					/*e_TRUE��ʾ����ͣ�����ٹ���,e_FALSE��ʾ����ͣ�����ٹ�����*/
} S_SPEEDSTOPTIMEDATE;


  typedef struct TAG_NeturlSpdDnDate
{
	UINT8		NeturlPassNum;						/*ͨ���������*/

	UINT32		Neturl_vBefore[NETURL_NUM_MAX];		/*����ǰ�ٶ�*/
	UINT32		Neturl_vBehind[NETURL_NUM_MAX];		/*������ٶ�*/
	UINT32		Neturl_Time[NETURL_NUM_MAX];		/*����ǰ���ٶȲ�*/
	REAL32		Neturl_Ramp[NETURL_NUM_MAX];		/*�����ƽ���µ�*/

	E_SysBool	Neturl_Key;					/*e_TRUE��ʾ���ڷ������,e_FALSE��ʾ���ڷ��������*/
} S_NETURLSPDDOWNDATE;

 typedef struct TAG_EfficiencyCalcResult
{
	//UINT16 	AppraiseTotalGrade; 		/*��ʻ�����ܷ�*/
	UINT32		Efficiency;		    		/*Ч����*/
	REAL32		StationAveSpd;				/*վ��ƽ���ٶ�*/
	REAL32		IntrvlRngAveSpd;			/*����ƽ���ٶ�*/
	REAL32		RunAveSpdAll;				/*������ͣ����ƽ���ٶ�*/	
	REAL32		StationAveTime;				/*վ��ƽ��ʱ��*/
	REAL32		IntrvlRngAveTime;			/*����ƽ��ʱ��*/
	REAL32		StartUpTime;				/*ƽ������ʱ*/
	S_STARTUPTIMEDATE  StartUpDate;			/*��ʱ������*/
	REAL32		SpdStopTime;				/*ͣ����ʱ*/
	S_SPEEDSTOPTIMEDATE	SpdStopDate;		/*ͣ��ʱ������*/
	REAL32		NeturlSpdDwSize;			/*�����ཱུ��*/
	S_NETURLSPDDOWNDATE	NeturlSpdDwDate;	/*�����ཱུ������*/
	REAL32      OnTimeRate;					/*׼����*/
	 
} S_EFFICIENCYCALCRESULT;

  typedef struct TAG_StatusDate
{
	UINT32		ForceLvl;				/*��λ*/
	UINT32		Status;					/*����*/
} S_STATUS_DATE;

 typedef struct TAG_SteadyCalcResult
{

	//UINT32 		Steady;				 		/*ƽ����*/
	UINT32		LvlChgNum;					/*��λ�仯����*/
	UINT32		StatChgNum;					/*�����仯*/
	UINT32		AirBrkNum;					/*�����ƶ�����*/
	REAL32      AirBrkRate;					/*�����ƶ�Ƶ��*/
	S_STATUS_DATE   StatusDate;				/*����״̬����*/

	UINT32		BigRpUnload;				/*���¶�����*/
	REAL32		NeturlImpulsion;			/*������嶯*/
	REAL32      BrkCooperate;				/*�յ����*/
	REAL32		RpChgHandle;				/*���µ㴦��*/
	REAL32		SpdDnAveSpd;				/*���ٶ�ƽ�����ٶ�*/
	REAL32		SpdUpAveSpd;				/*���ٶ�ƽ�����ٶ�*/
	UINT16		OverAveSpdNum;				/*���ٶ�ƽ�����ٶȳ������*/
	//REAL32	P_Acc;						/*�����񶯼��ٶ�*/
	//REAL32	Q_Acc;						/*�����񶯼��ٶ�*/
} S_STEADYCALCRESULT;
 typedef struct TAG_RationlityCalcResult
{

	 UINT16 	Rationlity;			 		/*������*/
	 UINT16     StopDistance;				/*ͣ������*/
	 REAL32     StartUpProcess;				/*�𳵹���*/
	 REAL32     StopProcess;				/*ͣ������*/
	 REAL32     ElecBrkRationality;			/*���ƶ�������*/
	 REAL32     AirBrkRationality;			/*�����ƶ�������*/
	 REAL32		BrkTestStatus;				/*��ͨ����״̬*/
	 REAL32		PassNtrlStus;				/*������״̬*/

	 
} S_RATIONLITYCALCRESULT;

 typedef struct TAG_EnergyEfficiencyResult
{

	 UINT16 	EnergyEfficiency;		 	/*�ܺ�*/
	 UINT32		ConsumeElectrical;			/*�ĵ���*/
	 UINT32		ReElectrical;				/*��������*/
	 UINT32		IdlingDynNum;				/*��ת������������*/
	 REAL32		IdlingRate;					/*��ת������*/
	 UINT32		BrakeDynNum;				/*�ƶ���������*/
	 REAL32		BrakeRate;					/*�ƶ�ռ��*/
	 
} S_ENERGYEFFICIENCYCALCRESULT;


 typedef struct TAG_IndicatorsCalcResult
 {
	
	 S_SAFETYCALCRESULT 				Safety;				 		/*��ȫ��*/
	 S_EFFICIENCYCALCRESULT 			Efficiency;		    		/*Ч����*/
	 S_STEADYCALCRESULT 				Steady;				 		/*ƽ����*/
	 S_RATIONLITYCALCRESULT 			Rationlity;			 		/*������*/
	 S_ENERGYEFFICIENCYCALCRESULT 		EnergyEfficiency;		 	/*�ܺ�*/
	 
 } S_INDICATORSCALCRESULT;

 typedef struct TAG_ControlQuality
{
	S_INDICATORSCALCRESULT IndicatorsCalcResult;
	REAL32   DataError;								/*���ݴ���*/
	REAL32   PlanError;								/*�滮����*/
	REAL32   StatusError;							/*������ƥ��*/
	UINT32	 RePlanNum;								/*���������¹滮����*/
	REAL32	 AveSpdDiff;							/*ƽ��Ŀ���ٶ�ƫ��*/
													/*�ٶ�ƫ���״̬��Ϣ*/
	REAL32   RePlanSpdDiff;							/*���¹滮ʱ�ٶ�ƫ��*/

} S_CONTROLQUALITY;

 typedef struct TAG_ControlRate
{
	UINT16	AutoInNum;					/*�Զ���ʻ�������*/
	UINT16  ManulTakeNum;				/*�˹��ӹܴ���*/
	UINT32	AutoRunTime;				/*�Զ���ʻʱ��*/
	UINT32	AutoRunDis;					/*�Զ���ʻ·��*/
	UINT32	ManulRunTime;				/*�˹���ʻʱ��*/
	UINT32	ManulRunDis;				/*�˹���ʻ·��*/
	REAL32  RunTimeRate;				/*��ʻʱ��س���*/
	REAL32	RunDisRate;					/*��ʻ·�̿س���*/
	 
} S_CONTROLRATE;

#if 0
 typedef struct TAG_DriveFeedbackGrade
{
	 UINT16 	AppraiseTotalGrade; 		 /*��ʻ�����ܷ�*/
	 UINT32 	SafetyGrade;				 /*��ȫ���ܷ�*/
	 UINT32 	EfficiencyGrade;		     /*Ч�����ܷ�*/
	 UINT32 	SteadyGrade;				 /*ƽ�����ܷ�*/
	 UINT16 	RationlityGrade;			 /*�������ܷ�*/
	 UINT16 	EnergyEfficiencyGrade;		 /*�ܺ��ܷ�*/
	 
} S_DRIVE_FEEDBACK_GRADE;


typedef struct TAG_AutoDriveFeedbackGrade
{
	 UINT16 	AutoTotalGrade; 			/*�Զ���ʻ�ܷ�*/
	 UINT32 	DriveGrade;					/*��ʻ�����ܷ�*/
	 UINT32 	ControlGrade;		 		/*���������ܷ�*/
	 UINT32 	AutoDriveRataGrade;			/*�ճ����ܷ�*/
	 
} S_AUTODRIVE_FEEDBACK_GRADE;



 typedef struct TAG_All_FeedbackGrade
{
	S_AUTODRIVE_FEEDBACK_GRADE  AutoDriveGrade;			/*�Զ���ʻ����*/
	S_DRIVE_FEEDBACK_GRADE			DriveGrade;			/*��ʻ����*/
	
	
} S_ALL_FEEDBACK_GRADE;

#endif
 typedef struct TAG_AutoIndicatorsCalcResult
{
	S_CONTROLQUALITY					AutoControlQuality;				 /*�س�����*/	
	S_CONTROLRATE						AutoControlRate;				 /*�س���*/

	 
} S_AUTOINDICATORSCALCRESULT;

 typedef struct TAG_RecordData
{

	UINT32     AccumulateWeight;		/*�ۼ�����*/
	/*...*/
	/*�ٶ�ƫ���״̬��Ϣ*/
} S_RECORDDATA;




 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/
 /******************************************************************************
 *Name    : ACS_DriveAppraiseClac_M
 *Function: ��ʻ����ָ�����(��ȫ��Ч�ʣ�ƽ�ȣ������ܺ�)
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_M(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_DriveAppraiseClac_A
 *Function: �Զ���ʻ����ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_A(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);

/******************************************************************************
 *Name    : ACS_SafeParaClac
 *Function: ��ȫ��ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SafeParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_EfficiencyParaClac
 *Function: Ч��ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EfficiencyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_SteadyParaClac
 *Function: ƽ����ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SteadyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_RationlityParaClac
 *Function: ������ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_RationlityParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_EnrgEficPraClac()
 *Function: �ܺ�ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EnrgEficParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_CntrlQltyPrClc()
 *Function: ������������
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlQltyPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_CntrlRtPrClc()
 *Function: �س��ʼ���
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlRtPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
#endif
