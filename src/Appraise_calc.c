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
 *Function: ����ָ�������ʼ��
 *Para    :// S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/25     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseResult_InitPro()
{
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_DriveAppraise_InitPro
 *Function: ������ʼ��
 *Para    :// S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02     create
******************************************************************************/
E_SysBool  ACS_DriveAppraise_InitPro()
{
	return e_TRUE;
}
#endif
/******************************************************************************
 *Name    : ACS_DriveAppraiseClac_M
 *Function: ��ʻ����ָ�����(��ȫ��Ч�ʣ�ƽ�ȣ������ܺ�)
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_M(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*��ȫ*/
	if(e_FALSE == ACS_SafeParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*Ч��*/
	if(e_FALSE == ACS_EfficiencyParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*ƽ��*/
	if(e_FALSE == ACS_EnrgEficParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*����*/
	if(e_FALSE == ACS_RationlityParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*�ܺ�*/
	if(e_FALSE == ACS_SteadyParaClac(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}


	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_DriveAppraiseClac_A
 *Function: �Զ���ʻ����ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_DriveAppraiseClac_A(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*������������*/
	if(e_FALSE == ACS_CntrlQltyPrClc(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	/*��ʻ����ָ�����*/
	if(e_FALSE == ACS_DriveAppraiseClac_M(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}
	
	/*�س��ʼ���*/
	if(e_FALSE == ACS_CntrlRtPrClc(pA2AInputPara,pAtIndClcRslt,pSenseData))
	{
		return e_FALSE;
	}

	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_SafeParaClac
 *Function: ��ȫ��ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SafeParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	UINT32 DisIndex = 0;


	DisIndex = (pA2AInputPara->DynaData.LocoDynCMDandStatus.Position)/10;

	/*���ٶȹ����������*/


	/*�Ӽ��ٶȹ����������*/


	/*�ٶȹ��ߴ�������*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.TcmsSpeed/10 > 
		pSenseData->InterProjectInfo.InterProjectCurve.LimitSpeed[DisIndex])
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Safety.OverSpdNum +=1;
	}

	/*���ϴ�������*/
	if(pA2AInputPara->CtrlData.AlgoOutputStaData.AlgoAutoQuitReqCode !=0x00000000)
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Safety.BreakDownNum +=1;
	}

	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_EfficiencyParaClac
 *Function: Ч��ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EfficiencyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	UINT8 StartUp_Index = 0;
	
	/*������ͣ����ƽ���ٶ�*/
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Efficiency.RunAveSpdAll =  
					(REAL32)pA2AInputPara->DynaData.LocoDynCMDandStatus.TravlledDistance/
					(REAL32)pA2AInputPara->SpecialData.TimeDate.SecondTime;	
	/*����ͣ����ƽ���ٶ�*/


	/*�����źŵƵļ�Ȩƽ���ٶ�*/


	/*����ʱ*/
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
	/*ͣ����ʱ*/

	/*�������ٶȽ���*/

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_SteadyParaClac
 *Function: ƽ����ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_SteadyParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*�����仯*/
	if(pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus != 
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.Status)
	{	
		/*����ת������*/
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatChgNum += 1U;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.Status =
				pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus;

		/*�����ƶ�����*/
		if((pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus = 0x04)||
			(pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus = 0x05))
		{
			pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.AirBrkNum += 1U;
		}
	}

	/*��λ�仯����*/
	if(pA2AInputPara->CtrlData.AlgoOutputCtlData.DrivingFSetValue != 
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.ForceLvl)/*�˴�ֻ�жϰٷֱȱ仯�Ƿ���ȷ��*/
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.LvlChgNum += 1U;
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.Steady.StatusDate.ForceLvl =
				pA2AInputPara->CtrlData.AlgoOutputCtlData.DrivingFSetValue;
	}


	/*�����ƶ�Ƶ��*/


	/*���¶�����*/


	/*���ٶ�����*/


	/*������嶯*/


	/*�յ����*/


	/*���µ㴦��*/


	/*ƽ�����ٶ�*/


	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_RationlityParaClac
 *Function: ������ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
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
 *Function: �ܺ�ָ�����
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_EnrgEficParaClac(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{
	/*�ĵ���*/
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.ConsumeElectrical =
		pA2AInputPara->SpecialData.LocoElectrical.ConsumeElectrical;

	/*��������*/
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.ReElectrical =
		pA2AInputPara->SpecialData.LocoElectrical.ReElectrical;

	/*��ת������*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.FltStatus == 0x01)
	{
		pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.IdlingDynNum +=1;
	}
	pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.IdlingRate =
		(REAL32)pAtIndClcRslt->AutoControlQuality.IndicatorsCalcResult.EnergyEfficiency.IdlingDynNum/
		(REAL32)pA2AInputPara->SpecialData.DynDate.Total_Dyn_Num;
#if 0
	/*�ƶ�ռ��*/
	if(pA2AInputPara->DynaData.LocoDynCMDandStatus.)
	{
	
	}
#endif
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_CntrlQltyPrClc()
 *Function: ������������
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
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
 *Function: �س��ʼ���
 *Para    :
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/16     create
******************************************************************************/
E_SysBool  ACS_CntrlRtPrClc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_KERNEL_SENSEDATA*   pSenseData)
{

	return e_TRUE;
}
#endif
