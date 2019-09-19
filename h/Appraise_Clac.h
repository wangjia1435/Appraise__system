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
	UINT16     Velocity;					/*速度*/
	UINT32	   Time;						/*时间*/
	UINT32	   Distance2RelativeZero;		/*相对0点距离*/
	UINT32	   AbsoluteDiStance;		    /*绝对距离*/
	UINT16	   Level;						/*级位*/
	UINT16     RunningStatus;				/*工况*/
	E_SysBool  Nuetral;						/*分相*/
	E_SysBool  BrakeTest;					/*贯通试验*/
	UINT8	   SignalType_E;				/*信号机类型*/
	
}S_APPRAISE_PARA;

typedef struct TAG_SafetyCalcResult
{
	// UINT16 	AppraiseTotalGrade; 		/*驾驶评价总分*/
	 UINT32 	Safety;				 		/*安全性*/
	 UINT16     OverAccNum;					/*加速度过大次数*/
	 UINT16		OverAccAccNum;				/*加加速度过大次数*/
	 UINT16		OverTrnCplrFrcNum;			/*车钩力过大次数*/
	 UINT16     OverSpdNum;					/*速度过大次数*/
	 UINT16		BreakDownNum;				/*故障触发次数*/
	//REAL32	QratioP;					/*脱轨系数,一般小于1.0，特殊情况下1.2*/
	//REAL32	pratioP;					/*减载率，设计速度<160km/h限值0.65,>160km/h为0.8*/
	//REAL32	MaxHforce;					/*最大横向力限值(15+3p0)KN*/
		
	 
} S_SAFETYCALCRESULT;

 typedef struct TAG_StartUpTimeDate
{
	UINT8		StartUpNum;						/*起车次数*/

	UINT32		StartUp_v0[STARUP_NUM_MAX];		/*起车前时间戳，1=1s*/
	UINT32		StartUp_v5[STARUP_NUM_MAX];		/*速度为5km/h时间戳，1=1s*/
	UINT32		StartUp_Time[STARUP_NUM_MAX];	/*起车用时，1=1s*/

	UINT32		StartUp_d0[STARUP_NUM_MAX];		/*起车前绝对位移*/
	UINT32		StartUp_d5[STARUP_NUM_MAX];		/*速度为5km/h绝对位移*/
 	REAL32		StartUp_Ramp[STARUP_NUM_MAX];	/*起车段加算坡道千分数，1=千分之一*/

	E_SysBool	StartUp_Key;					/*e_TRUE表示正在起车过程,e_FALSE表示不在起车过程中*/
} S_STARTUPTIMEDATE;

 typedef struct TAG_SpeedStopTimeDate
{
	UINT8		SpdStopNum;						/*停车次数*/

	UINT32		SpdStop_vX[STARUP_NUM_MAX];		/*预备停车时（v=（？*待定*？）km/h）时间戳，1=1s*/
	UINT32		SpdStop_v0[STARUP_NUM_MAX];		/*停车时（v=0km/h）时间戳，1=1s*/
	UINT32		SpdStop_Time[STARUP_NUM_MAX];	/*停车用时，1=1s*/
	REAL32		SpdStop_Ramp[STARUP_NUM_MAX];	/*停车段加算坡道千分数，1=千分之一*/

	E_SysBool	SpdStop_Key;					/*e_TRUE表示正在停车减速过程,e_FALSE表示不在停车减速过程中*/
} S_SPEEDSTOPTIMEDATE;


  typedef struct TAG_NeturlSpdDnDate
{
	UINT8		NeturlPassNum;						/*通过分相次数*/

	UINT32		Neturl_vBefore[NETURL_NUM_MAX];		/*分相前速度*/
	UINT32		Neturl_vBehind[NETURL_NUM_MAX];		/*分相后速度*/
	UINT32		Neturl_Time[NETURL_NUM_MAX];		/*分相前后速度差*/
	REAL32		Neturl_Ramp[NETURL_NUM_MAX];		/*分相段平均坡道*/

	E_SysBool	Neturl_Key;					/*e_TRUE表示正在分相过程,e_FALSE表示不在分相过程中*/
} S_NETURLSPDDOWNDATE;

 typedef struct TAG_EfficiencyCalcResult
{
	//UINT16 	AppraiseTotalGrade; 		/*驾驶评价总分*/
	UINT32		Efficiency;		    		/*效率性*/
	REAL32		StationAveSpd;				/*站内平均速度*/
	REAL32		IntrvlRngAveSpd;			/*区间平均速度*/
	REAL32		RunAveSpdAll;				/*不考虑停车的平均速度*/	
	REAL32		StationAveTime;				/*站内平均时间*/
	REAL32		IntrvlRngAveTime;			/*区间平均时间*/
	REAL32		StartUpTime;				/*平均起车用时*/
	S_STARTUPTIMEDATE  StartUpDate;			/*起车时间数据*/
	REAL32		SpdStopTime;				/*停车用时*/
	S_SPEEDSTOPTIMEDATE	SpdStopDate;		/*停车时间数据*/
	REAL32		NeturlSpdDwSize;			/*过分相降幅*/
	S_NETURLSPDDOWNDATE	NeturlSpdDwDate;	/*过分相降幅数据*/
	REAL32      OnTimeRate;					/*准点率*/
	 
} S_EFFICIENCYCALCRESULT;

  typedef struct TAG_StatusDate
{
	UINT32		ForceLvl;				/*级位*/
	UINT32		Status;					/*工况*/
} S_STATUS_DATE;

 typedef struct TAG_SteadyCalcResult
{

	//UINT32 		Steady;				 		/*平稳性*/
	UINT32		LvlChgNum;					/*级位变化次数*/
	UINT32		StatChgNum;					/*工况变化*/
	UINT32		AirBrkNum;					/*空气制动次数*/
	REAL32      AirBrkRate;					/*空气制动频率*/
	S_STATUS_DATE   StatusDate;				/*工况状态数据*/

	UINT32		BigRpUnload;				/*上坡段退流*/
	REAL32		NeturlImpulsion;			/*过分相冲动*/
	REAL32      BrkCooperate;				/*空电配合*/
	REAL32		RpChgHandle;				/*变坡点处理*/
	REAL32		SpdDnAveSpd;				/*减速段平均加速度*/
	REAL32		SpdUpAveSpd;				/*加速段平均加速度*/
	UINT16		OverAveSpdNum;				/*变速段平均加速度超标次数*/
	//REAL32	P_Acc;						/*横向振动加速度*/
	//REAL32	Q_Acc;						/*垂向振动加速度*/
} S_STEADYCALCRESULT;
 typedef struct TAG_RationlityCalcResult
{

	 UINT16 	Rationlity;			 		/*合理性*/
	 UINT16     StopDistance;				/*停车距离*/
	 REAL32     StartUpProcess;				/*起车过程*/
	 REAL32     StopProcess;				/*停车过程*/
	 REAL32     ElecBrkRationality;			/*电制动合理性*/
	 REAL32     AirBrkRationality;			/*空气制动合理性*/
	 REAL32		BrkTestStatus;				/*贯通试验状态*/
	 REAL32		PassNtrlStus;				/*过分相状态*/

	 
} S_RATIONLITYCALCRESULT;

 typedef struct TAG_EnergyEfficiencyResult
{

	 UINT16 	EnergyEfficiency;		 	/*能耗*/
	 UINT32		ConsumeElectrical;			/*耗电量*/
	 UINT32		ReElectrical;				/*再生电量*/
	 UINT32		IdlingDynNum;				/*空转滑行总周期数*/
	 REAL32		IdlingRate;					/*空转滑行率*/
	 UINT32		BrakeDynNum;				/*制动总周期数*/
	 REAL32		BrakeRate;					/*制动占比*/
	 
} S_ENERGYEFFICIENCYCALCRESULT;


 typedef struct TAG_IndicatorsCalcResult
 {
	
	 S_SAFETYCALCRESULT 				Safety;				 		/*安全性*/
	 S_EFFICIENCYCALCRESULT 			Efficiency;		    		/*效率性*/
	 S_STEADYCALCRESULT 				Steady;				 		/*平稳性*/
	 S_RATIONLITYCALCRESULT 			Rationlity;			 		/*合理性*/
	 S_ENERGYEFFICIENCYCALCRESULT 		EnergyEfficiency;		 	/*能耗*/
	 
 } S_INDICATORSCALCRESULT;

 typedef struct TAG_ControlQuality
{
	S_INDICATORSCALCRESULT IndicatorsCalcResult;
	REAL32   DataError;								/*数据错误*/
	REAL32   PlanError;								/*规划错误*/
	REAL32   StatusError;							/*工况不匹配*/
	UINT32	 RePlanNum;								/*非正常重新规划次数*/
	REAL32	 AveSpdDiff;							/*平均目标速度偏差*/
													/*速度偏差段状态信息*/
	REAL32   RePlanSpdDiff;							/*重新规划时速度偏差*/

} S_CONTROLQUALITY;

 typedef struct TAG_ControlRate
{
	UINT16	AutoInNum;					/*自动驾驶切入次数*/
	UINT16  ManulTakeNum;				/*人工接管次数*/
	UINT32	AutoRunTime;				/*自动驾驶时间*/
	UINT32	AutoRunDis;					/*自动驾驶路程*/
	UINT32	ManulRunTime;				/*人工驾驶时间*/
	UINT32	ManulRunDis;				/*人工驾驶路程*/
	REAL32  RunTimeRate;				/*驾驶时间控车率*/
	REAL32	RunDisRate;					/*驾驶路程控车率*/
	 
} S_CONTROLRATE;

#if 0
 typedef struct TAG_DriveFeedbackGrade
{
	 UINT16 	AppraiseTotalGrade; 		 /*驾驶评价总分*/
	 UINT32 	SafetyGrade;				 /*安全性总分*/
	 UINT32 	EfficiencyGrade;		     /*效率性总分*/
	 UINT32 	SteadyGrade;				 /*平稳性总分*/
	 UINT16 	RationlityGrade;			 /*合理性总分*/
	 UINT16 	EnergyEfficiencyGrade;		 /*能耗总分*/
	 
} S_DRIVE_FEEDBACK_GRADE;


typedef struct TAG_AutoDriveFeedbackGrade
{
	 UINT16 	AutoTotalGrade; 			/*自动驾驶总分*/
	 UINT32 	DriveGrade;					/*驾驶评价总分*/
	 UINT32 	ControlGrade;		 		/*控制质量总分*/
	 UINT32 	AutoDriveRataGrade;			/*空车率总分*/
	 
} S_AUTODRIVE_FEEDBACK_GRADE;



 typedef struct TAG_All_FeedbackGrade
{
	S_AUTODRIVE_FEEDBACK_GRADE  AutoDriveGrade;			/*自动驾驶评价*/
	S_DRIVE_FEEDBACK_GRADE			DriveGrade;			/*驾驶评价*/
	
	
} S_ALL_FEEDBACK_GRADE;

#endif
 typedef struct TAG_AutoIndicatorsCalcResult
{
	S_CONTROLQUALITY					AutoControlQuality;				 /*控车质量*/	
	S_CONTROLRATE						AutoControlRate;				 /*控车率*/

	 
} S_AUTOINDICATORSCALCRESULT;

 typedef struct TAG_RecordData
{

	UINT32     AccumulateWeight;		/*累计载重*/
	/*...*/
	/*速度偏差段状态信息*/
} S_RECORDDATA;




 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/
 /******************************************************************************
 *Name    : ACS_DriveAppraiseClac_M
 *Function: 驾驶评价指标计算(安全，效率，平稳，合理，能耗)
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_M(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_DriveAppraiseClac_A
 *Function: 自动驾驶评价指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_A(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);

/******************************************************************************
 *Name    : ACS_SafeParaClac
 *Function: 安全性指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SafeParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_EfficiencyParaClac
 *Function: 效率指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EfficiencyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_SteadyParaClac
 *Function: 平稳性指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SteadyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_RationlityParaClac
 *Function: 合理性指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_RationlityParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_EnrgEficPraClac()
 *Function: 能耗指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EnrgEficParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_CntrlQltyPrClc()
 *Function: 控制质量计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlQltyPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_CntrlRtPrClc()
 *Function: 控车率计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlRtPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData);
#endif
