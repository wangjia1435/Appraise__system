/******************************************************************************
 *File Name	     :	ACS_Appraise_calc.c
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/07/01
 *Description    :	
 *Modification history:
 *REV1.0.0    Tangwei     2019/07/25    File Create 
******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef   ACS_APPRAISE_CALC_H_
#define	  ACS_APPRAISE_CALC_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/AppraiseSystem.h"
//#include ""


/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/

/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/
#if 0
/******************************************************************************
 *Name    : ACS_DriveAppraiseResult_InitPro
 *Function: 各项指标分数初始化
 *Para    :// S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/25     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseResult_InitPro()
{
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_DriveAppraise_InitPro
 *Function: 函数初始化
 *Para    :// S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02     create
******************************************************************************/
E_SysBool  ACS_DriveAppraise_InitPro()
{
	return e_TRUE;
}
#endif
/******************************************************************************
 *Name    : ACS_DriveAppraiseClac_M
 *Function: 驾驶评价指标计算(安全，效率，平稳，合理，能耗)
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_M(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*安全*/
	if(e_FALSE == ACS_SafeParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*效率*/
	if(e_FALSE == ACS_EfficiencyParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*平稳*/
	if(e_FALSE == ACS_EnrgEficParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*合理*/
	if(e_FALSE == ACS_RationlityParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*能耗*/
	if(e_FALSE == ACS_SteadyParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}


	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_DriveAppraiseClac_A
 *Function: 自动驾驶评价指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_A(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*控制质量计算*/
	if(e_FALSE == ACS_CntrlQltyPrClc(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*驾驶评价指标计算*/
	if(e_FALSE == ACS_DriveAppraiseClac_M(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}
	
	/*控车率计算*/
	if(e_FALSE == ACS_CntrlRtPrClc(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_SafeParaClac
 *Function: 安全性指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SafeParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	UINT32 DisIndex = 0;


	DisIndex = (pA2AInputPara->DynaData.LocoDynCMDandStatus.Position)/10;

	/*加速度过大次数计算*/


	/*加加速度过大次数计算*/


	/*速度过高次数计算*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.TcmsSpeed/10 > 
		pSenseData->InterProjectInfo.InterProjectCurve.LimitSpeed[DisIndex])
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Safety.OverSpdNum +=1;
	}

	/*故障次数计算*/
	if(pA2AInputPara->CtrlData.AlgoOutputStaData.AlgoAutoQuitReqCode !=0x00000000)
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Safety.BreakDownNum +=1;
	}

	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_EfficiencyParaClac
 *Function: 效率指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EfficiencyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	UINT8 StartUp_Index = 0;
	
	/*不考虑停车的平均速度*/
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.RunAveSpdAll =  
					(REAL32)pA2AInputPara->DynaData.LocoDynCMDandStatus.TravlledDistance/
					(REAL32)pA2AInputPara->SpecialData.TimeDate.SecondTime;	
	/*考虑停车的平均速度*/


	/*考虑信号灯的加权平均速度*/


	/*起车用时*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.TcmsSpeed <= 5)
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_v0[StartUp_Index] = 
			pA2AInputPara->SpecialData.TimeDate.SecondTime;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_Key = e_TRUE;
		/*RAMP CLAC*/
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_Ramp[StartUp_Index] =
		Atoalgo_Sense_RampValueClac(&(pSenseData->AlgoStrategyCtrlData),
													pSenseData->RaillineCalcResult.RailAddRes,
													(REAL32)pA2AInputPara->DynaData.LocoDynCMDandStatus.Position);

	}
		if((pA2AInputPara->DynaData.LocoDynCMDandStatus.TcmsSpeed >= 5*100)&&
			(pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_Key == e_TRUE))
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_v5[StartUp_Index] = 
			pA2AInputPara->SpecialData.TimeDate.SecondTime;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_Key = e_FALSE;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_Time[StartUp_Index] =
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_v5[StartUp_Index] -
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUp_v0[StartUp_Index];
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.StartUpDate.StartUpNum +=1;
		StartUp_Index += 1;
	}
	/*停车用时*/

	/*过分相速度降幅*/

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_SteadyParaClac
 *Function: 平稳性指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SteadyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*工况变化*/
	if(pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus != 
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.Status)
	{	
		/*工况转换次数*/
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatChgNum += 1U;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.Status =
				pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus;

		/*空气制动次数*/
		if((pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus = 0x04)||
			(pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus = 0x05))
		{
			pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.AirBrkNum += 1U;
		}
	}

	/*级位变化次数*/
	if(pA2AInputPara->CtrlData.AlgoOutputCtlData.DrivingFSetValue != 
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.ForceLvl)/*此处只判断百分比变化是否正确？*/
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.LvlChgNum += 1U;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.ForceLvl =
				pA2AInputPara->CtrlData.AlgoOutputCtlData.DrivingFSetValue;
	}


	/*空气制动频率*/


	/*上坡段退流*/


	/*加速段退流*/


	/*过分相冲动*/


	/*空电配合*/


	/*变坡点处理*/


	/*平均加速度*/


	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_RationlityParaClac
 *Function: 合理性指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_RationlityParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_EnrgEficPraClac()
 *Function: 能耗指标计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EnrgEficParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*耗电量*/
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.ConsumeElectrical =
		pA2AInputPara->SpecialData.LocoElectrical.ConsumeElectrical;

	/*再生电量*/
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.ReElectrical =
		pA2AInputPara->SpecialData.LocoElectrical.ReElectrical;

	/*空转滑行率*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.FltStatus == 0x01)
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.IdlingDynNum +=1;
	}
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.IdlingRate =
		(REAL32)pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.IdlingDynNum/
		(REAL32)pA2AInputPara->SpecialData.DynDate.Total_Dyn_Num;
#if 0
	/*制动占比*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.)
	{
	
	}
#endif
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_CntrlQltyPrClc()
 *Function: 控制质量计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlQltyPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_CntrlRtPrClc()
 *Function: 控车率计算
 *Para    :
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlRtPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{

	return e_TRUE;
}
#endif
