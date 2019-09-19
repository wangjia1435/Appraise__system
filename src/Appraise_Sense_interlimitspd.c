/******************************************************************************
 *File Name	     :	Appraise_Sense_interlimitspd.c
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/08/13
 *Description    :	
 *Modification history:
 *REV1.0.0    Tangwei     2019/08/13    File Create 
******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
//#ifndef 
//#define	
/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/

#include "../h/AppraiseSystem.h"
#include "../h/Appraise_Sense.h"

/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/
#define MIN_IDENTIFY_NUM               (8U)    /*��Сʶ�����*/
#define PRESERVING_SPD_0               (5U)    /*�����ٶ������ٵĲ�ֵ0,>60ʹ��*/
#define PRESERVING_SPD_1               (3U)    /*�����ٶ������ٵĲ�ֵ1,<60ʹ��*/
#define PRESERVING_SPDCHNG_VALUE       (60U)   /*�����ٶ������ٲ�ֵת������ٶ�*/
#define INTER2PROJECT_SPDVALUE         (10U)   /*�ڲ������ٶȺϲ������������ٶȵ��ٶ�ֵ*/
#define MIN_IDENTIFY_DIS               (1500U)  /*���ٵ�&���ٵ�֮�����С����m*/
#define MAX_IDENTIFY_DIS               (3000U) /*�Ӽ����յ������������������*/
#define ACS_LIMIT_SPEED_NUM_MAX        (740U)	/*�������ߣ��������ߣ��������*/
/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/

/******************************************************************************
 *Name      : Atoalgo_Sense_CurPtLkjSpd2InterSpd
 *Function  : ����ǰ���LKJ�ٶ�ת��Ϊ�ڲ������ٶ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn 
 *Return    : UINT16 ��Ӧ���ڲ������ٶȣ�1=1km/h)
 *Note		: V1.0.0       YipingYang    2019/01/18   Create
 *Note		: V1.0.1       YipingYang    2019/01/19   Modify
 *Note		: V1.0.2       YipingYang    2019/01/21   Modify
 ******************************************************************************/
UINT16 Atoalgo_Sense_CurPtLkjSpd2InterSpd(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
										  const S_KERNEL_SENSEDATA* const pSenseDataIn,
		   	   	   	   	   	   	   	   	   	    				const UINT16 curIndexIn)
{
	UINT16 t_Spd  			= 0U;
	UINT16 t_Temp 			= 0U;
   	UINT16 t_PresSpd    	= 0U;  /*������ٶȵĲ�ֵ*/
	UINT16 t_PreServeSpd_0 	= 0U;
	UINT16 t_PreServeSpd_1	= 0U;

	if((ptrNULL == pProjectCurveIn)||(curIndexIn > ALGO_LIMIT_SPEED_NUM_MAX - 1U))
	{
		return 0U;
	}
	
	t_PreServeSpd_0 = PRESERVING_SPD_0;
	t_PreServeSpd_1 = PRESERVING_SPD_1;
	
	if(e_OnlyLoco == pSenseDataIn->TrainStatusData.TrainConsistData.ConsistType)
	{
		t_PreServeSpd_0 = PRESERVING_SPD_1;
	}
	 /*��������0���ǵ�������1*/
	t_Temp = (UINT16)((t_PreServeSpd_0 > (t_PreServeSpd_1 + 1U))? \
			(t_PreServeSpd_0 - (t_PreServeSpd_1 + 1U)) : 0U);

	
	if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= PRESERVING_SPDCHNG_VALUE)     /*�ٶ��Ƿ����60*/
	{
		t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PreServeSpd_0)?\
				(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PreServeSpd_0) : 0U;
	}
	else if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= ((PRESERVING_SPDCHNG_VALUE > t_Temp*2U)?\
			(PRESERVING_SPDCHNG_VALUE - t_Temp*2U):0U))						/*�ٶ��Ƿ���ڵ���58*/
	{
		/*58��59����������-4*/
		t_PresSpd = (PRESERVING_SPDCHNG_VALUE - pProjectCurveIn->LimitSpeed[curIndexIn]/10U)/2 +\
					(PRESERVING_SPDCHNG_VALUE - pProjectCurveIn->LimitSpeed[curIndexIn]/10U)%2;
		t_PresSpd = (t_PreServeSpd_0 > t_PresSpd)?(t_PreServeSpd_0 - t_PresSpd):0U;
		t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PresSpd)?\
				(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PresSpd) : 0U;
		
	}
	else if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= INTER2PROJECT_SPDVALUE)   /*�ٶ��Ƿ����10*/
	{
		t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PreServeSpd_1)?\
				(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PreServeSpd_1) : 0U;
	}
	else																			/*�ٶ�С��10*/
	{
		t_Temp = t_PreServeSpd_1 - 1U;
		if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= ((INTER2PROJECT_SPDVALUE > t_Temp*2U)?\
		    (INTER2PROJECT_SPDVALUE - t_Temp*2U):0U))								/*�ٶ��Ƿ����8*/
		{
			t_PresSpd = (INTER2PROJECT_SPDVALUE - pProjectCurveIn->LimitSpeed[curIndexIn]/10U)/2 +\
						(INTER2PROJECT_SPDVALUE - pProjectCurveIn->LimitSpeed[curIndexIn]/10U)%2;
			t_PresSpd = (t_PreServeSpd_1 > t_PresSpd)?(t_PreServeSpd_1 - t_PresSpd):0U;
			t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PresSpd)?\
					(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PresSpd) : 0U;
		}
		else
		{
			t_Spd = pProjectCurveIn->LimitSpeed[curIndexIn]/10U;
		}
	}
	return t_Spd;
}
/******************************************************************************
 *Name      : 
 *Function  : �����ڲ����������ٶ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
 *Para      :		S_KERNEL_SENSEDATA* const pSenseDataIn
 *Return    :��������e_TRUE �쳣����e_FALSE
 *Note		: V1.0.0       Tangwei    2019/08/12   Create
 ******************************************************************************/
E_SysBool LkjSpd2InterSpd(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
								S_KERNEL_SENSEDATA* const pSenseDataIn)
{
	UINT16 Index = 0;

	if((ptrNULL == pProjectCurveIn)||(ptrNULL == pSenseDataIn))
	{
		return e_FALSE;
	}
	

	for(Index = 0;Index < ACS_LIMIT_SPEED_NUM_MAX; Index++)
	{
		pSenseDataIn->InterProjectInfo.InterProjectCurve.LimitSpeed[Index] = \
		Atoalgo_Sense_CurPtLkjSpd2InterSpd(pProjectCurveIn,pSenseDataIn,Index);
	}
	return e_TRUE;
}
