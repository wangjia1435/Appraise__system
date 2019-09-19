/******************************************************************************
 *File Name	     :	Appraise_Clac_Grade.h
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/08/19
 *Description    :	
 *Modification history:
 *REV1.0.0    Tangwei     2019/07/01    File Create 
******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef ACS_APPRAISE_CLAC_GRADE_H_
#define	ACS_APPRAISE_CLAC_GRADE_H_

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

/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
typedef struct TAG_SafetyGrade
{
	 UINT8 		Grd_Safety;				 		/*分数—安全性总分*/
	 
	 UINT8		Grd_OverAccNum;					/*分数—加速度过大次数*/
	 UINT8		Grd_OverAccAccNum;				/*分数—加加速度过大次数*/
	 UINT8		Grd_OverTrnCplrFrcNum;			/*分数—车钩力过大次数*/
	 UINT8      Grd_OverSpdNum;					/*分数—速度过大次数*/
	 UINT8		Grd_BreakDownNum;				/*分数—故障触发次数*/
	//UINT8		Grd_QratioP;					/*分数—脱轨系数,一般小于1.0，特殊情况下1.2*/
	//UINT8		Grd_pratioP;					/*分数—减载率，设计速度<160km/h限值0.65,>160km/h为0.8*/
	//UINT8		Grd_MaxHforce;					/*分数—最大横向力限值(15+3p0)KN*/
		
	 
} S_SAFETY_GRADE;

 typedef struct TAG_EfficiencyGrade
{
	UINT8		Grd_Efficiency;		    		/*效率总分*/
	
	UINT8		Grd_StationAveSpd;				/*分数—站内平均速度*/
	UINT8		Grd_IntrvlRngAveSpd;			/*分数—区间平均速度*/
	UINT8		Grd_StationAveTime;				/*分数—站内平均时间*/
	UINT8		Grd_IntrvlRngAveTime;			/*分数—区间平均时间*/
	UINT8		Grd_StartUpTime;				/*分数—起车用时*/
	UINT8		Grd_SpdStopTime;				/*分数—停车用时*/
	UINT8		Grd_NeturlSpdDnSize;			/*分数—过分相降幅*/
	UINT8		Grd_OnTimeRate;					/*分数—准点率*/
	 
} S_EFFICIENCY_GRADE;

 typedef struct TAG_SteadyGrade
{

	UINT8 		Grd_Steady;				 		/*平稳性总分*/
	
	UINT8		Grd_LvlChgNum;					/*分数—级位变化次数*/
	UINT8		Grd_StatChgNum;					/*分数—工况变化*/
	UINT8		Grd_AirBrkNum;					/*分数—空气制动次数*/
	UINT8       Grd_AirBrkRate;					/*分数—空气制动频率*/
	UINT8		Grd_BigRpUnload;				/*分数—上坡段退流*/
	UINT8		Grd_NeturlImpulsion;			/*分数—过分相冲动*/
	UINT8       Grd_BrkCooperate;				/*分数—空电配合*/
	UINT8		Grd_RpChgHandle;				/*分数—变坡点处理*/
	UINT8		Grd_SpdDnAveSpd;				/*分数—减速段平均加速度*/
	UINT8		Grd_SpdUpAveSpd;				/*分数—加速段平均加速度*/
	UINT8		Grd_OverAveSpdNum;				/*分数—变速段平均加速度超标次数*/
	//REAL32	Grd_P_Acc;						/*分数—横向振动加速度*/
	//REAL32	Grd_Q_Acc;						/*分数—垂向振动加速度*/
} S_STEADY_GRADE;
 typedef struct TAG_RationlityGrade
{

	UINT8		Grd_Rationlity;			 		/*合理性总分*/
	
	UINT8		Grd_StopDistance;				/*分数—停车距离*/
	UINT8		Grd_StartUpProcess;				/*分数—起车过程*/
	UINT8		Grd_StopProcess;				/*分数—停车过程*/
	UINT8		Grd_ElecBrkRationality;			/*分数—电制动合理性*/
	UINT8		Grd_AirBrkRationality;			/*分数—空气制动合理性*/
	UINT8		Grd_BrkTestStatus;				/*分数—贯通试验状态*/
	UINT8		Grd_PassNtrlStus;				/*分数—过分相状态*/

	 
} S_RATIONLITY_GRADE;

 typedef struct TAG_EnergyEfficiencyGrade
{

	UINT8		Grd_EnergyEfficiency;			/*能耗总分*/
	
	UINT8		Grd_EnergyConsun;				/*分数—耗电量*/
	UINT8		Grd_ReviveEnergy;				/*分数—再生电量*/
	UINT8		Grd_IdlingRate;					/*分数—空转滑行率*/
	UINT8		Grd_BakeRate;					/*分数—制动占比*/
	
} S_ENERGYEFFICIENCY_GRADE;


 typedef struct TAG_IndicatorsGrade
 {
	 UINT8							Grd_DriveGrade;					/*驾驶评价总分*/
	 
	 S_SAFETY_GRADE 				Grd_Safety;				 		/*分数—安全性*/
	 S_EFFICIENCY_GRADE 			Grd_Efficiency;		    		/*分数—效率性*/
	 S_STEADY_GRADE 				Grd_Steady;				 		/*分数—平稳性*/
	 S_RATIONLITY_GRADE 			Grd_Rationlity;			 		/*分数—合理性*/
	 S_ENERGYEFFICIENCY_GRADE 		Grd_EnergyEfficiency;		 	/*分数—能耗*/
	 
 } S_INDICATORS_GRADE;

 typedef struct TAG_ControlQualityGrade
{
	S_INDICATORS_GRADE Grd_IndicatorsGrade;					/*驾驶评价各项点分*/
	
	UINT8		Grd_DataError;								/*分数—数据错误*/
	UINT8		Grd_PlanError;								/*分数—规划错误*/
	UINT8		Grd_StatusError;							/*分数—工况不匹配*/
	UINT8		Grd_RePlanNum;								/*分数—非正常重新规划次数*/
	UINT8		Grd_AveSpdDiff;								/*分数—平均目标速度偏差*/
	UINT8   	Grd_RePlanSpdDiff;							/*分数—重新规划时速度偏差*/

} S_CONTROLQUALITY_GRADE;

 typedef struct TAG_ControlRateGrade
{
	 UINT8		 Grd_AutoInNum;					/*分数—自动驾驶切入次数*/
	 UINT8		 Grd_ManulTakeNum;				/*分数—人工接管次数*/
	 UINT8		 Grd_AutoRunTime;				/*分数—自动驾驶时间*/
	 UINT8		 Grd_AutoRunDis;				/*分数—自动驾驶路程*/
	 UINT8		 Grd_ManulRunTime;				/*分数—人工驾驶时间*/
	 UINT8		 Grd_ManulRunDis;				/*分数—人工驾驶路程*/
	 UINT8  	 Grd_RunTimeRate;				/*分数—驾驶时间控车率*/
	 UINT8		 Grd_RunDisRate;				/*分数—驾驶路程控车率*/
	 
} S_CONTROLRATE_GRADE;

 typedef struct TAG_AutoIndicatorsGrade
{
	S_CONTROLQUALITY_GRADE					Grd_AtCntrlQlty;				 /*控车质量*/	
	S_CONTROLRATE_GRADE						Grd_AtCntrlRate;				 /*控车率*/
	 
} S_ALL_FEEDBACK_GRADE;


#if 0
typedef struct TAG_AutoDriveFeedbackGrade
{
	 UINT16 	AutoTotalGrade; 			/*自动驾驶总分*/
	 UINT32 	DriveGrade;					/*驾驶评价总分*/
	 UINT32 	ControlGrade;		 		/*控制质量总分*/
	 UINT32 	AutoDriveRataGrade;			/*空车率总分*/
	 
} S_AUTODRIVE_FEEDBACK_GRADE;

typedef struct TAG_DriveFeedbackGrade
{
	 UINT16 	Grd_AppraiseTotal; 		 /*驾驶评价总分*/
	 UINT32 	Grd_Safety;				 /*安全性总分*/
	 UINT32 	Grd_Efficiency;		     /*效率性总分*/
	 UINT32 	Grd_Steady;				 /*平稳性总分*/
	 UINT16 	Grd_Rationlity;			 /*合理性总分*/
	 UINT16 	Grd_EnergyEfficiency;	 /*能耗总分*/

	
	 UINT32 	SafetyGrade;				 /*安全性项点分*/
	 UINT32 	EfficiencyGrade;		     /*效率性项点分*/
	 UINT32 	SteadyGrade;				 /*平稳性项点分*/
	 UINT16 	RationlityGrade;			 /*合理性项点分*/
	 UINT16 	EnergyEfficiencyGrade;		 /*能耗项点分*/


	 
} S_DRIVE_FEEDBACK_GRADE;



typedef struct TAG_All_FeedbackGrade
{
	S_AUTODRIVE_FEEDBACK_GRADE  AutoDriveGrade;			/*自动驾驶评价*/
	S_DRIVE_FEEDBACK_GRADE			DriveGrade;			/*驾驶评价*/
	
	
} S_ALL_FEEDBACK_GRADE;
#endif 



 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/

#endif
