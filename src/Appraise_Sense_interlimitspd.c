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
#define MIN_IDENTIFY_NUM               (8U)    /*最小识别点数*/
#define PRESERVING_SPD_0               (5U)    /*防护速度与限速的差值0,>60使用*/
#define PRESERVING_SPD_1               (3U)    /*防护速度与限速的差值1,<60使用*/
#define PRESERVING_SPDCHNG_VALUE       (60U)   /*防护速度与限速差值转换点的速度*/
#define INTER2PROJECT_SPDVALUE         (10U)   /*内部防护速度合并到防护曲线速度的速度值*/
#define MIN_IDENTIFY_DIS               (1500U)  /*加速点&减速点之间的最小距离m*/
#define MAX_IDENTIFY_DIS               (3000U) /*从减速终点检索加速起点的最大距离*/
#define ACS_LIMIT_SPEED_NUM_MAX        (740U)	/*限速曲线（防护曲线）数组个数*/
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
 *Function  : 将当前点的LKJ速度转换为内部防护速度
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn 
 *Return    : UINT16 对应的内部防护速度（1=1km/h)
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
   	UINT16 t_PresSpd    	= 0U;  /*与防护速度的差值*/
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
	 /*单机等于0，非单机等于1*/
	t_Temp = (UINT16)((t_PreServeSpd_0 > (t_PreServeSpd_1 + 1U))? \
			(t_PreServeSpd_0 - (t_PreServeSpd_1 + 1U)) : 0U);

	
	if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= PRESERVING_SPDCHNG_VALUE)     /*速度是否大于60*/
	{
		t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PreServeSpd_0)?\
				(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PreServeSpd_0) : 0U;
	}
	else if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= ((PRESERVING_SPDCHNG_VALUE > t_Temp*2U)?\
			(PRESERVING_SPDCHNG_VALUE - t_Temp*2U):0U))						/*速度是否大于等于58*/
	{
		/*58和59，防护曲线-4*/
		t_PresSpd = (PRESERVING_SPDCHNG_VALUE - pProjectCurveIn->LimitSpeed[curIndexIn]/10U)/2 +\
					(PRESERVING_SPDCHNG_VALUE - pProjectCurveIn->LimitSpeed[curIndexIn]/10U)%2;
		t_PresSpd = (t_PreServeSpd_0 > t_PresSpd)?(t_PreServeSpd_0 - t_PresSpd):0U;
		t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PresSpd)?\
				(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PresSpd) : 0U;
		
	}
	else if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= INTER2PROJECT_SPDVALUE)   /*速度是否大于10*/
	{
		t_Spd = (pProjectCurveIn->LimitSpeed[curIndexIn]/10U > t_PreServeSpd_1)?\
				(pProjectCurveIn->LimitSpeed[curIndexIn]/10U - t_PreServeSpd_1) : 0U;
	}
	else																			/*速度小于10*/
	{
		t_Temp = t_PreServeSpd_1 - 1U;
		if(pProjectCurveIn->LimitSpeed[curIndexIn]/10U >= ((INTER2PROJECT_SPDVALUE > t_Temp*2U)?\
		    (INTER2PROJECT_SPDVALUE - t_Temp*2U):0U))								/*速度是否大于8*/
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
 *Function  : 计算内部防护曲线速度
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
 *Para      :		S_KERNEL_SENSEDATA* const pSenseDataIn
 *Return    :正常返回e_TRUE 异常返回e_FALSE
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
