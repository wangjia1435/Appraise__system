/******************************************************************************
 *File Name	     :	atoalgo_sense_railline.c
 *Copyright	     :	Zhuzhou CRRC Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2018/11/21
 *Description    :	��·���ݸ�֪ �µ�����...
 *Modification history:
 *REV1.0.0    litiebing      2018/11/21    file create

 ******************************************************************************/
/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/Appraise_Sense.h"
#include "../h/Appraise_BasicFunction.h"

/******************************************************************************
*    Global Variable Define Section
******************************************************************************/

/******************************************************************************
*    Local Macro Define Section
******************************************************************************/

/******************************************************************************
*    Local Struct    Define Section
******************************************************************************/

/******************************************************************************
*    Local Prototype Declare Section
******************************************************************************/

/******************************************************************************
*    Static Variable Define Section
******************************************************************************/

/******************************************************************************
*    Function Define Section
******************************************************************************/

/******************************************************************************
*    Function Define Section
******************************************************************************/

/******************************************************************************
 *Name    : Atoalgo_Math_CalcTrainLength
 *Function: �Գ���ȡ��,��45-51�Գ���ȡ�࣬������С���ֵ
 *Para    : 
 *Return  : ���ؼ����µ�����
 *NOTE    : V1.0.0  	zxm 		 2018/12/25		
******************************************************************************/
UINT16  Atoalgo_Math_CalcTrainLength(UINT16 TrainLength)
{
	UINT16 TrainLengthRslt 	= 0;
	UINT16 Index 			= 0;
	UINT16 Rslt[7];
	UINT16 i				= 0;
	UINT16 Min = 0;
	UINT16 MinIndex = 0;

	for(Index = 45;Index <= 51&&i<7;Index++)
	{
		Rslt[i] = TrainLength%Index;
		i++;
	}
	Min = Rslt[0];
	for(i = 0; i < 7; i++)
	{

		if(Min >= Rslt[i])
		{
			Min = Rslt[i];
			MinIndex = i;
		}
	}
	return MinIndex + 45;
}
/******************************************************************************
*Name    : Atoalgo_Plan_StrategyCalc
*Function: �滮���Լ��㣬�粽������
*Para    : void
*Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
*NOTE    : V1.0.0  zxm 	 2019/1/10      ��������
******************************************************************************/
E_SysBool Atoalgo_Plan_StrategyCalc(S_KERNEL_SENSEDATA* 		const 	pKernelSenseData,
									S_ALGO_STRATEGYCTRLDATA*    const   pAlgoStrategyCtrlData)
{
	UINT16 TrainLengthTemp	= 0U;
	
	/*��������*/
	TrainLengthTemp 		= pKernelSenseData->TrainStatusData.TrainConsistData.TrainActualLength;
	pAlgoStrategyCtrlData->PlanCalcStep	= Atoalgo_Math_CalcTrainLength(TrainLengthTemp);
	pKernelSenseData->TrainStatusData.TrainConsistData.TrainActualLength = \
			(TrainLengthTemp/(pAlgoStrategyCtrlData->PlanCalcStep))*(pAlgoStrategyCtrlData->PlanCalcStep);
	return e_TRUE;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_LocoSignal
 *Function: ��ȡ�����ź��������
 *Para    : const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData,
 *Para    :       S_LOCOSIGNAL_DATA*    const pLocoSignal                       
 *Return  : 
 *NOTE    : V1.0.0  Chenjiahui			 2019/01/14		 create
******************************************************************************/
E_SysBool Atoalgo_Sense_LocoSignal(const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData,
		                                 S_LOCOSIGNAL_DATA*    const pLocoSignal)
{
	if((ptrNULL == pAlgoInputDynData) || (ptrNULL == pLocoSignal))
	{
		return e_FALSE;	
	}
	
	pLocoSignal->SingalStatus    = pAlgoInputDynData->LocoDynCMDandStatus.SingalStatus;
	pLocoSignal->Singal          = pAlgoInputDynData->LKJDynamicCtlData.Singal;
	pLocoSignal->LKJMode         = pAlgoInputDynData->LKJDynamicCtlData.LKJMode;
	pLocoSignal->CurrentSideLine = pAlgoInputDynData->LKJDynamicCtlData.CurrentSideLine;
	pLocoSignal->NextSideLine    = pAlgoInputDynData->LKJDynamicCtlData.NextSideLine;
	pLocoSignal->CurrentBranch   = pAlgoInputDynData->LKJDynamicCtlData.CurrentBranch;
	pLocoSignal->NextBranch      = pAlgoInputDynData->LKJDynamicCtlData.NextBranch;

	return e_TRUE;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcTotalLocosWgt
 *Function: �����ܻ�����������������
 *Para    :                          
 *Return  : 
 *NOTE    : V1.0.0  zhouww 	 2018/08/04      create
 *NOTE    : V1.0.1  zxm		 2019/02/26      modify
******************************************************************************/
UINT16 Atoalgo_Sense_CalcTotalLocosWgt(S_TRAINSTATUSDATA* const pTrainStatusData)
{
	UINT16 m_LocoTotalWgt 		= 0U;
	UINT16 m_LocoNums			= 0U;
	
	/*�����������*/
	if((pTrainStatusData->TrainConsistData.ConsistType == e_OneOneTrain) || \
	   (pTrainStatusData->TrainConsistData.ConsistType == e_TwoZeroTrain))
	{
		m_LocoTotalWgt += 2*200U;
		m_LocoNums 		= 2U;
	}
	else if((pTrainStatusData->TrainConsistData.ConsistType == e_TwoOneTrain) ||\
			(pTrainStatusData->TrainConsistData.ConsistType == e_ThreeZeroTrain))
	{
		m_LocoTotalWgt += 3*200U;
		m_LocoNums 		= 3U;
	}
	else if(pTrainStatusData->TrainConsistData.ConsistType == e_TwoTwoTrain)
	{
		m_LocoTotalWgt += 4*200U;
		m_LocoNums 		= 4U;
	}
	else
	{
		m_LocoTotalWgt += 200U;
		m_LocoNums 		= 1U;
	}
	
	m_LocoTotalWgt += pTrainStatusData->TrainConsistData.SleepLocoNums * 200U;
	pTrainStatusData->TrainConsistData.LocoNums = m_LocoNums + pTrainStatusData->TrainConsistData.SleepLocoNums;
	return m_LocoTotalWgt;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_TrainData
 *Function: ��ȡ���������������
 *Para    : const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,
 *Para    : const S_FORWARDRLDATA* 			const ForwardRailLineData,
 *Para    : S_KERNEL_SENSEDATA* 			const pKernelSenseData					       	                      
 *Return  : 
 *NOTE    : V1.0.0  zxm			 2019/01/11 	 create
******************************************************************************/
E_SysBool Atoalgo_Sense_TrainData(const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,
								  const S_FORWARDRLDATA* 		const ForwardRailLineData,
								       	S_KERNEL_SENSEDATA*     const pKernelSenseData)
{
	if((ptrNULL==pAlgoInputDynData)||(ptrNULL==ForwardRailLineData)||\
	   (ptrNULL==pKernelSenseData))
	{
		return e_FALSE;
	}
	
	/*�г��������ݴ���*/
	pKernelSenseData->TrainStatusData.TrainConsistData.BrkShoePresPHT       = \
			pAlgoInputDynData->LocoDynCMDandStatus.BrkShoePresPHT;
	pKernelSenseData->TrainStatusData.TrainConsistData.ClosedVehicleNums    = \
			pAlgoInputDynData->LocoDynCMDandStatus.ClosedVehicleNums;
	
	/*�޸��г������߼�����ʹ��DMI�������ݣ���ʹ��LKJ����-zhouww 2019-04-06*/
#if 0
	pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType       	= \
			pAlgoInputDynData->LocoDynCMDandStatus.ConsistType;
#endif
	switch (pAlgoInputDynData->LocoDynCMDandStatus.ConsistType)
	{
		case e_OneTrian :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_OneTrian;
			break;
		case e_OneOneTrain :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_OneOneTrain;
			break;
		case e_TwoZeroTrain :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_TwoZeroTrain;
			break;
		case e_TwoOneTrain :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_TwoOneTrain;
			break;
		case e_ThreeZeroTrain :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_ThreeZeroTrain;
			break;
		case e_TwoTwoTrain :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_TwoTwoTrain;
			break;
		default :
			pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_OnlyLoco;
			break;
	}	
	if(pAlgoInputDynData->LKJDynamicCtlData.TrainWeight == 0U)
	{
		pKernelSenseData->TrainStatusData.TrainConsistData.ConsistType  = e_OnlyLoco;
	}
	
	pKernelSenseData->TrainStatusData.TrainConsistData.SleepLocoNums        = \
			pAlgoInputDynData->LocoDynCMDandStatus.SleepLocoNums;
	pKernelSenseData->TrainStatusData.TrainConsistData.TrainLength          = \
			pAlgoInputDynData->LKJDynamicCtlData.TrainLength;
	pKernelSenseData->TrainStatusData.TrainConsistData.TrainType            = \
				pAlgoInputDynData->LKJDynamicCtlData.TrainType;
	pKernelSenseData->TrainStatusData.TrainConsistData.VehicleWeight        = \
			pAlgoInputDynData->LKJDynamicCtlData.TrainWeight;
	pKernelSenseData->TrainStatusData.TrainConsistData.LocosWeight        = \
			Atoalgo_Sense_CalcTotalLocosWgt(&(pKernelSenseData->TrainStatusData));
	pKernelSenseData->TrainStatusData.TrainConsistData.TrainWeight			= \
			pKernelSenseData->TrainStatusData.TrainConsistData.LocosWeight + \
			pAlgoInputDynData->LKJDynamicCtlData.TrainWeight;
	pKernelSenseData->TrainStatusData.TrainConsistData.TrainActualLength	= \
			(UINT16)((pKernelSenseData->TrainStatusData.TrainConsistData.TrainLength)*(1.1F)) + \
			(pKernelSenseData->TrainStatusData.TrainConsistData.LocoNums)*36;	/*����������������������������*/
	/*����״̬���ݴ���*/
	pKernelSenseData->TrainStatusData.VehiclesStatusData.BCUBrakeHandleType = \
			pAlgoInputDynData->LocoDynCMDandStatus.BCUBrakeHandleType;
	pKernelSenseData->TrainStatusData.VehiclesStatusData.BCUPressureType 	= \
			pAlgoInputDynData->LocoDynCMDandStatus.BCUPressureType;
	pKernelSenseData->TrainStatusData.VehiclesStatusData.TrainLoadType      = \
			pAlgoInputDynData->LocoDynCMDandStatus.TrainLoadType;
	pKernelSenseData->TrainStatusData.VehiclesStatusData.VehicleType       	= \
			pAlgoInputDynData->LocoDynCMDandStatus.VehicleType;
	/*�г���λ���ݴ���*/		
	pKernelSenseData->TrainLocateData.Position 								= \
			pAlgoInputDynData->LocoDynCMDandStatus.Position;
	pKernelSenseData->TrainLocateData.TravlledDistance 						= \
			pAlgoInputDynData->LocoDynCMDandStatus.TravlledDistance;
	pKernelSenseData->TrainLocateData.NextSigRelaDist 						= \
			pAlgoInputDynData->LKJDynamicCtlData.NextSigRelaDist;

	pKernelSenseData->TrainStatusData.TrainConsistData.VehicleNum			= \
			pAlgoInputDynData->LKJDynamicCtlData.VehicleNum;
	pKernelSenseData->TrainStatusData.TrainConsistData.HeavyCar				= \
			pAlgoInputDynData->LKJDynamicCtlData.HeavyCar;
	pKernelSenseData->TrainStatusData.TrainConsistData.EmptyCar				= \
			pAlgoInputDynData->LKJDynamicCtlData.EmptyCar;
	/*��β������ݴ���*/
	pKernelSenseData->TrainStatusData.EotStatusData.TrainTailType           = \
			pAlgoInputDynData->LocoDynCMDandStatus.TrainTailType;
	pKernelSenseData->TrainStatusData.EotStatusData.TrainTailValue          = \
			pAlgoInputDynData->LocoDynCMDandStatus.TrainTailValue;
#if 1
	pKernelSenseData->TrainStatusData.VehiclesStatusData.BCUPressureType	= 0xA5;
#endif
	return e_TRUE;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_LocolData
 *Function: ��ȡ���������������
 *Para    : const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,
 *Para    : const S_FORWARDRLDATA* 		const ForwardRailLineData,
 *Para    : S_KERNEL_SENSEDATA* 	const pKernelSenseData					       	                      
 *Return  : 
 *NOTE    : V1.0.0  zxm			 2019/01/11 	 create
******************************************************************************/
E_SysBool Atoalgo_Sense_LocolData(const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,
		  	  	  	  	  	 	  const S_FORWARDRLDATA* 		const ForwardRailLineData,
		  	  	  	  	  	       	    S_KERNEL_SENSEDATA*     const pKernelSenseData)
{
	UINT8 CurrRunningStatus = 0;
	if((ptrNULL==pAlgoInputDynData)||(ptrNULL==ForwardRailLineData)||\
	   (ptrNULL==pKernelSenseData))
	{
		return e_FALSE;
	}
	/*�������״̬����*/

	pKernelSenseData->TrainStatusData.LocosStatusData.ABHExTargetACK        = \
			pAlgoInputDynData->LocoDynCMDandStatus.ABHExTargetACK;
	pKernelSenseData->TrainStatusData.LocosStatusData.BackOffFlag           = \
			pAlgoInputDynData->LocoDynCMDandStatus.BackOffFlag;
	pKernelSenseData->TrainStatusData.LocosStatusData.BigBrakePosition      = \
			pAlgoInputDynData->LocoDynCMDandStatus.BigBrakePosition;
	pKernelSenseData->TrainStatusData.LocosStatusData.BrakeCylinder      	= \
			pAlgoInputDynData->LocoDynCMDandStatus.BrakeCylinder;
	pKernelSenseData->TrainStatusData.LocosStatusData.EBrFmax      			= \
			pAlgoInputDynData->LocoDynCMDandStatus.EBrFmax;
	pKernelSenseData->TrainStatusData.LocosStatusData.EBrkPowerLostPercent  = \
			pAlgoInputDynData->LocoDynCMDandStatus.EBrkPowerLostPercent;
	pKernelSenseData->TrainStatusData.LocosStatusData.EqualReservoir        = \
			pAlgoInputDynData->LocoDynCMDandStatus.EqualReservoir;
	pKernelSenseData->TrainStatusData.LocosStatusData.FltStatus      		= \
			pAlgoInputDynData->LocoDynCMDandStatus.FltStatus;
	pKernelSenseData->TrainStatusData.LocosStatusData.Force      			= \
			pAlgoInputDynData->LocoDynCMDandStatus.Force;
	pKernelSenseData->TrainStatusData.LocosStatusData.IBHExTargetACK     	= \
			pAlgoInputDynData->LocoDynCMDandStatus.IBHExTargetACK;
	pKernelSenseData->TrainStatusData.LocosStatusData.LocoStatus            = \
			pAlgoInputDynData->LocoDynCMDandStatus.LocoStatus;
	pKernelSenseData->TrainStatusData.LocosStatusData.LocoType              = \
			pAlgoInputDynData->LKJDynamicCtlData.LocoType;
	pKernelSenseData->TrainStatusData.LocosStatusData.MotorIsoStatus      	= \
			pAlgoInputDynData->LocoDynCMDandStatus.MotorIsoStatus;
	pKernelSenseData->TrainStatusData.LocosStatusData.PressureDecrement     = \
			pAlgoInputDynData->LocoDynCMDandStatus.PressureDecrement;
	pKernelSenseData->TrainStatusData.LocosStatusData.PressureTotalVal      = \
			pAlgoInputDynData->LocoDynCMDandStatus.PressureTotalVal;
	pKernelSenseData->TrainStatusData.LocosStatusData.PriVolt      			= \
			pAlgoInputDynData->LocoDynCMDandStatus.PriVolt;
	pKernelSenseData->TrainStatusData.LocosStatusData.RateOfFlow      		= \
			pAlgoInputDynData->LocoDynCMDandStatus.RateOfFlow;
	pKernelSenseData->TrainStatusData.LocosStatusData.SmallBrakePosition    = \
			pAlgoInputDynData->LocoDynCMDandStatus.SmallBrakePosition;
	pKernelSenseData->TrainStatusData.LocosStatusData.TcmsSpeed      		= \
			pAlgoInputDynData->LocoDynCMDandStatus.TcmsSpeed;
	pKernelSenseData->TrainStatusData.LocosStatusData.TrcFmax      			= \
			pAlgoInputDynData->LocoDynCMDandStatus.TrcFmax;
	pKernelSenseData->TrainStatusData.LocosStatusData.TrcPowerLostPercent   = \
			pAlgoInputDynData->LocoDynCMDandStatus.TrcPowerLostPercent;

	pKernelSenseData->TrainStatusData.LocosStatusData.WheelDiameter			= \
			pAlgoInputDynData->LKJDynamicCtlData.WheelDiameter;
	pKernelSenseData->TrainStatusData.LocosStatusData.LkjSpeed				= \
			pAlgoInputDynData->LKJDynamicCtlData.LkjSpeed;
#if 1	
	/*2019.02.28��zhubaolin,��ӣ������ж���Ҫ���㹤��������������*/

	//Atoalgo_Sense_TrainRuningCoastProc(pAlgoInputDynData, pKernelSenseData);

#endif
	return e_TRUE;
}
