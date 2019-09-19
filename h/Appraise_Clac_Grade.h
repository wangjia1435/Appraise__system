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
	 UINT8 		Grd_Safety;				 		/*��������ȫ���ܷ�*/
	 
	 UINT8		Grd_OverAccNum;					/*���������ٶȹ������*/
	 UINT8		Grd_OverAccAccNum;				/*�������Ӽ��ٶȹ������*/
	 UINT8		Grd_OverTrnCplrFrcNum;			/*�������������������*/
	 UINT8      Grd_OverSpdNum;					/*�������ٶȹ������*/
	 UINT8		Grd_BreakDownNum;				/*���������ϴ�������*/
	//UINT8		Grd_QratioP;					/*�������ѹ�ϵ��,һ��С��1.0�����������1.2*/
	//UINT8		Grd_pratioP;					/*�����������ʣ�����ٶ�<160km/h��ֵ0.65,>160km/hΪ0.8*/
	//UINT8		Grd_MaxHforce;					/*����������������ֵ(15+3p0)KN*/
		
	 
} S_SAFETY_GRADE;

 typedef struct TAG_EfficiencyGrade
{
	UINT8		Grd_Efficiency;		    		/*Ч���ܷ�*/
	
	UINT8		Grd_StationAveSpd;				/*������վ��ƽ���ٶ�*/
	UINT8		Grd_IntrvlRngAveSpd;			/*����������ƽ���ٶ�*/
	UINT8		Grd_StationAveTime;				/*������վ��ƽ��ʱ��*/
	UINT8		Grd_IntrvlRngAveTime;			/*����������ƽ��ʱ��*/
	UINT8		Grd_StartUpTime;				/*����������ʱ*/
	UINT8		Grd_SpdStopTime;				/*������ͣ����ʱ*/
	UINT8		Grd_NeturlSpdDnSize;			/*�����������ཱུ��*/
	UINT8		Grd_OnTimeRate;					/*������׼����*/
	 
} S_EFFICIENCY_GRADE;

 typedef struct TAG_SteadyGrade
{

	UINT8 		Grd_Steady;				 		/*ƽ�����ܷ�*/
	
	UINT8		Grd_LvlChgNum;					/*��������λ�仯����*/
	UINT8		Grd_StatChgNum;					/*�����������仯*/
	UINT8		Grd_AirBrkNum;					/*�����������ƶ�����*/
	UINT8       Grd_AirBrkRate;					/*�����������ƶ�Ƶ��*/
	UINT8		Grd_BigRpUnload;				/*���������¶�����*/
	UINT8		Grd_NeturlImpulsion;			/*������������嶯*/
	UINT8       Grd_BrkCooperate;				/*�������յ����*/
	UINT8		Grd_RpChgHandle;				/*���������µ㴦��*/
	UINT8		Grd_SpdDnAveSpd;				/*���������ٶ�ƽ�����ٶ�*/
	UINT8		Grd_SpdUpAveSpd;				/*���������ٶ�ƽ�����ٶ�*/
	UINT8		Grd_OverAveSpdNum;				/*���������ٶ�ƽ�����ٶȳ������*/
	//REAL32	Grd_P_Acc;						/*�����������񶯼��ٶ�*/
	//REAL32	Grd_Q_Acc;						/*�����������񶯼��ٶ�*/
} S_STEADY_GRADE;
 typedef struct TAG_RationlityGrade
{

	UINT8		Grd_Rationlity;			 		/*�������ܷ�*/
	
	UINT8		Grd_StopDistance;				/*������ͣ������*/
	UINT8		Grd_StartUpProcess;				/*�������𳵹���*/
	UINT8		Grd_StopProcess;				/*������ͣ������*/
	UINT8		Grd_ElecBrkRationality;			/*���������ƶ�������*/
	UINT8		Grd_AirBrkRationality;			/*�����������ƶ�������*/
	UINT8		Grd_BrkTestStatus;				/*��������ͨ����״̬*/
	UINT8		Grd_PassNtrlStus;				/*������������״̬*/

	 
} S_RATIONLITY_GRADE;

 typedef struct TAG_EnergyEfficiencyGrade
{

	UINT8		Grd_EnergyEfficiency;			/*�ܺ��ܷ�*/
	
	UINT8		Grd_EnergyConsun;				/*�������ĵ���*/
	UINT8		Grd_ReviveEnergy;				/*��������������*/
	UINT8		Grd_IdlingRate;					/*��������ת������*/
	UINT8		Grd_BakeRate;					/*�������ƶ�ռ��*/
	
} S_ENERGYEFFICIENCY_GRADE;


 typedef struct TAG_IndicatorsGrade
 {
	 UINT8							Grd_DriveGrade;					/*��ʻ�����ܷ�*/
	 
	 S_SAFETY_GRADE 				Grd_Safety;				 		/*��������ȫ��*/
	 S_EFFICIENCY_GRADE 			Grd_Efficiency;		    		/*������Ч����*/
	 S_STEADY_GRADE 				Grd_Steady;				 		/*������ƽ����*/
	 S_RATIONLITY_GRADE 			Grd_Rationlity;			 		/*������������*/
	 S_ENERGYEFFICIENCY_GRADE 		Grd_EnergyEfficiency;		 	/*�������ܺ�*/
	 
 } S_INDICATORS_GRADE;

 typedef struct TAG_ControlQualityGrade
{
	S_INDICATORS_GRADE Grd_IndicatorsGrade;					/*��ʻ���۸�����*/
	
	UINT8		Grd_DataError;								/*���������ݴ���*/
	UINT8		Grd_PlanError;								/*�������滮����*/
	UINT8		Grd_StatusError;							/*������������ƥ��*/
	UINT8		Grd_RePlanNum;								/*���������������¹滮����*/
	UINT8		Grd_AveSpdDiff;								/*������ƽ��Ŀ���ٶ�ƫ��*/
	UINT8   	Grd_RePlanSpdDiff;							/*���������¹滮ʱ�ٶ�ƫ��*/

} S_CONTROLQUALITY_GRADE;

 typedef struct TAG_ControlRateGrade
{
	 UINT8		 Grd_AutoInNum;					/*�������Զ���ʻ�������*/
	 UINT8		 Grd_ManulTakeNum;				/*�������˹��ӹܴ���*/
	 UINT8		 Grd_AutoRunTime;				/*�������Զ���ʻʱ��*/
	 UINT8		 Grd_AutoRunDis;				/*�������Զ���ʻ·��*/
	 UINT8		 Grd_ManulRunTime;				/*�������˹���ʻʱ��*/
	 UINT8		 Grd_ManulRunDis;				/*�������˹���ʻ·��*/
	 UINT8  	 Grd_RunTimeRate;				/*��������ʻʱ��س���*/
	 UINT8		 Grd_RunDisRate;				/*��������ʻ·�̿س���*/
	 
} S_CONTROLRATE_GRADE;

 typedef struct TAG_AutoIndicatorsGrade
{
	S_CONTROLQUALITY_GRADE					Grd_AtCntrlQlty;				 /*�س�����*/	
	S_CONTROLRATE_GRADE						Grd_AtCntrlRate;				 /*�س���*/
	 
} S_ALL_FEEDBACK_GRADE;


#if 0
typedef struct TAG_AutoDriveFeedbackGrade
{
	 UINT16 	AutoTotalGrade; 			/*�Զ���ʻ�ܷ�*/
	 UINT32 	DriveGrade;					/*��ʻ�����ܷ�*/
	 UINT32 	ControlGrade;		 		/*���������ܷ�*/
	 UINT32 	AutoDriveRataGrade;			/*�ճ����ܷ�*/
	 
} S_AUTODRIVE_FEEDBACK_GRADE;

typedef struct TAG_DriveFeedbackGrade
{
	 UINT16 	Grd_AppraiseTotal; 		 /*��ʻ�����ܷ�*/
	 UINT32 	Grd_Safety;				 /*��ȫ���ܷ�*/
	 UINT32 	Grd_Efficiency;		     /*Ч�����ܷ�*/
	 UINT32 	Grd_Steady;				 /*ƽ�����ܷ�*/
	 UINT16 	Grd_Rationlity;			 /*�������ܷ�*/
	 UINT16 	Grd_EnergyEfficiency;	 /*�ܺ��ܷ�*/

	
	 UINT32 	SafetyGrade;				 /*��ȫ������*/
	 UINT32 	EfficiencyGrade;		     /*Ч��������*/
	 UINT32 	SteadyGrade;				 /*ƽ��������*/
	 UINT16 	RationlityGrade;			 /*����������*/
	 UINT16 	EnergyEfficiencyGrade;		 /*�ܺ�����*/


	 
} S_DRIVE_FEEDBACK_GRADE;



typedef struct TAG_All_FeedbackGrade
{
	S_AUTODRIVE_FEEDBACK_GRADE  AutoDriveGrade;			/*�Զ���ʻ����*/
	S_DRIVE_FEEDBACK_GRADE			DriveGrade;			/*��ʻ����*/
	
	
} S_ALL_FEEDBACK_GRADE;
#endif 



 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/

#endif
