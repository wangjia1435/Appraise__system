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
#define CHANGERAMPPOINTNUMS (100U)				
#define LONGRAMP_MIN		(69)
#define LONGRAMP_AVR		(105)
/******************************************************************************
*    Static Variable Define Section
******************************************************************************/
/*�����������λ�ö���ȫ�ֱ���-zxm-20181225*/
UINT16 G_PlanStart_LocoRelPos	= 0;
/******************************************************************************
*    Function Define Section
******************************************************************************/

/******************************************************************************
*    Function Define Section
******************************************************************************/
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcCurveAvgValue
 *Function: ���������������
 *Para    : 
 *Return  : ����������ƽ�����ֵ
 *NOTE    : V1.0.0  tw 		 2018/12/10			create
 *NOTE    : V1.0.1  zxm		 2018/12/25			modify
 *NOTE    : V1.0.2  tw 		 2019/03/13			recreate
******************************************************************************/
E_SysBool  Atoalgo_Sense_CalcCurveAvgValue(const S_TRAINSTATUSDATA*			const pTrainStatusData,
										   const S_ALGO_STRATEGYCTRLDATA*	const pAlgoStrategyCtrlData,
						   	   	    	   const S_FORWARDRLDATA* 			const pForwardRailLineData, 
						   	   	    	   	   	 REAL32*						  AvgCurve)
{
	UINT16 Num					= 0U;
	UINT32 temp 				= 0U;
	INT16  TempNum				= 0U;
	UINT16 ArrayIndex			= 0U;
	UINT16 CurveValidNum		= 0U;
	UINT16 Index				= 0U;
	UINT16 AvgIndex				= 0U;
	UINT16 TailRelativePositionTemp = 0U;
	REAL32 CurveArray[300U];
	REAL32 AvgCurveTemp[LINECALCLNUMS];
	/*����*/
	UINT16 SingleLocoPos	    = 0U;
	
	SingleLocoPos 				= G_PlanStart_LocoRelPos;
	TailRelativePositionTemp	= G_PlanStart_LocoRelPos;
	/*�����Ч����*/
	CurveValidNum				= pForwardRailLineData->FWCurves.CurveValidNum;
#if 0
	printf("CAV:%f,%d \n",CurveAvgValue,CurveValidNum);

#endif
	Comn_F_MemSet((void *)AvgCurve,
						          0,LINECALCLNUMS*sizeof(REAL32));
	
	Comn_F_MemSet((void *)AvgCurveTemp,
						          0,LINECALCLNUMS*sizeof(REAL32));
	
	Comn_F_MemSet((void *)CurveArray,
						          0,300U*sizeof(REAL32));	

	if(0 == CurveValidNum)
	{
		return e_FALSE;
	}

	if(CurveValidNum > ALGO_RADIUS_MAX_NUM)
	{		
		CurveValidNum = ALGO_RADIUS_MAX_NUM;
	}
	
	if(G_PlanStart_LocoRelPos < pTrainStatusData->TrainConsistData.TrainActualLength)
	{
		TempNum = (pTrainStatusData->TrainConsistData.TrainActualLength - \
				G_PlanStart_LocoRelPos)/pAlgoStrategyCtrlData->PlanCalcStep;
		TailRelativePositionTemp = 0;
	}
	else
	{
		TailRelativePositionTemp = G_PlanStart_LocoRelPos - pTrainStatusData->TrainConsistData.TrainActualLength;
	}
	
	Num = pTrainStatusData->TrainConsistData.TrainActualLength/pAlgoStrategyCtrlData->PlanCalcStep;
	
	if(Num == 0U)
	{
		/*�����������*/
		for(Index = 1 ; Index < CurveValidNum; Index++)
		{
			
			if(SingleLocoPos < pForwardRailLineData->FWCurves.Curves[0].CurveRelatDist)
			{
				while(SingleLocoPos < pForwardRailLineData->FWCurves.Curves[0].CurveRelatDist)
				{
					AvgCurveTemp[ArrayIndex] = 0.0F;
					if(ArrayIndex == 0)
					{
						//printf("k%.1f %d %d\n",AvgCurveTemp[ArrayIndex],pForwardRailLineData->FWCurves.Curves[Index].CurveRelatDist,G_PlanStart_LocoRelPos);
					}
					ArrayIndex++;
					SingleLocoPos += pAlgoStrategyCtrlData->PlanCalcStep;
					if(ArrayIndex >= 200U )
					{
						Comn_F_MemCpy(AvgCurve,AvgCurveTemp,sizeof(AvgCurveTemp),LINECALCLNUMS*sizeof(REAL32));
						return e_TRUE;
					}
					
				}
				continue;
			}
			while(SingleLocoPos < pForwardRailLineData->FWCurves.Curves[Index].CurveRelatDist)
			{
				if((SingleLocoPos <= (pForwardRailLineData->FWCurves.Curves[Index-1U].CurveRelatDist + \
					pForwardRailLineData->FWCurves.Curves[Index-1U].CurveLenth)) && 
					 (SingleLocoPos >= pForwardRailLineData->FWCurves.Curves[Index-1U].CurveRelatDist))
				{
					
					AvgCurveTemp[ArrayIndex]	= (REAL32)ALGO_SENSE_CURVE_PARA/((pForwardRailLineData->FWCurves.Curves[Index-1U].Radius) & 0x7fff);
					if(ArrayIndex == 0)
					{
						#if 0
						printf("k%.1f %d %d %d\n",AvgCurveTemp[ArrayIndex],
								pForwardRailLineData->FWCurves.Curves[Index].CurveRelatDist,
								pForwardRailLineData->FWCurves.Curves[Index].CurveLenth,
								G_PlanStart_LocoRelPos);
						#endif
					}
				}
				else if((SingleLocoPos >= (pForwardRailLineData->FWCurves.Curves[Index-1U].CurveRelatDist + \
						 pForwardRailLineData->FWCurves.Curves[Index-1U].CurveLenth)) && 
						   (SingleLocoPos < pForwardRailLineData->FWCurves.Curves[Index].CurveRelatDist))
				{
				
					AvgCurveTemp[ArrayIndex]	= 0.0F;

				}
				ArrayIndex++;
				/*��ǰ�ƶ�һ����������*/
				SingleLocoPos += pAlgoStrategyCtrlData->PlanCalcStep;

				if(ArrayIndex >= 200U )
				{
					Comn_F_MemCpy(AvgCurve,AvgCurveTemp,sizeof(AvgCurveTemp),LINECALCLNUMS*sizeof(REAL32));
					return e_TRUE;
				}
			}
			
		}
	}
	
	
	for(Index = 0 ; Index < CurveValidNum; Index++)
	{		
		if(TempNum > 0)
		{
			while(TempNum > 0)
			{	

				CurveArray[ArrayIndex] = 0.0F;
				ArrayIndex++;
				TempNum--;
			}
		}
		if(TailRelativePositionTemp < pForwardRailLineData->FWCurves.Curves[0].CurveRelatDist)
		{
			while(TailRelativePositionTemp < pForwardRailLineData->FWCurves.Curves[0].CurveRelatDist)
			{
				CurveArray[ArrayIndex] = 0.0F;
				ArrayIndex++;
				TailRelativePositionTemp += pAlgoStrategyCtrlData->PlanCalcStep;
			}
			continue;
		}

		while(TailRelativePositionTemp < pForwardRailLineData->FWCurves.Curves[Index].CurveRelatDist)
		{
			if((TailRelativePositionTemp <= (pForwardRailLineData->FWCurves.Curves[Index-1U].CurveRelatDist + \
				pForwardRailLineData->FWCurves.Curves[Index-1U].CurveLenth)) && 
				 (TailRelativePositionTemp >= pForwardRailLineData->FWCurves.Curves[Index-1U].CurveRelatDist))
			{
				
				CurveArray[ArrayIndex]	= (REAL32)ALGO_SENSE_CURVE_PARA/((pForwardRailLineData->FWCurves.Curves[Index-1U].Radius) & 0x7fff);
				
			}
			else if((TailRelativePositionTemp >= (pForwardRailLineData->FWCurves.Curves[Index-1U].CurveRelatDist + \
					 pForwardRailLineData->FWCurves.Curves[Index-1U].CurveLenth)) && 
					   (TailRelativePositionTemp < pForwardRailLineData->FWCurves.Curves[Index].CurveRelatDist))
			{
			
				CurveArray[ArrayIndex]	= 0.0F;

			}
			ArrayIndex++;
			/*��ǰ�ƶ�һ����������*/
			TailRelativePositionTemp += pAlgoStrategyCtrlData->PlanCalcStep;

			if(ArrayIndex >= 300U )
			{
				break;
			}
		}
		if(ArrayIndex >= 300U)
		{
			break;
		}

	}
	
	for(Index = 0;Index < Num;Index++)
	{
		AvgCurveTemp[0] += CurveArray[Index];
	}
	AvgCurveTemp[0] = AvgCurveTemp[0]/(REAL32)Num;
	for(Index = 1 ; Index < LINECALCLNUMS ; Index++)
	{
		AvgCurveTemp[Index] = AvgCurveTemp[Index-1] + (CurveArray[Index-1 + Num]- CurveArray[Index-1])/(REAL32)Num; 
		if(AvgCurveTemp[Index]<0.0001F&&AvgCurveTemp[Index]>(-0.0001F))
		{
			AvgCurveTemp[Index] = 0.0F;
		}
		if(Index > LINECALCLNUMS)
		{
			break;
		}
	}

	Comn_F_MemCpy(AvgCurve,AvgCurveTemp,sizeof(AvgCurveTemp),LINECALCLNUMS*sizeof(REAL32));
	
	return e_TRUE;
	
}
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcRampInitAvgValue
 *Function: �������µ���ʼֵ
 *Para    : 
 *Return  : ƽ���µ�ֵ
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.0  tw	 	 2018/12/09			modified
 *NOTE    : V1.0.0  zxm 	 2018/12/21			modified
******************************************************************************/
REAL32 Atoalgo_Sense_CalcRampInitAvgValue(const S_TRAINSTATUSDATA* 			const pTrainStatusData,
						   	   	   	   	  const S_FORWARDRLDATA* 			const pForwardRailLineData,
						   	   	   	   	  	    E_SysBool*				    const Degrade2Normal)
{
	UINT16 RampValidNums 			= 0;
	INT16  Index					= 0;
	INT16  IndexTempTail			= 0;
	UINT16 distanceTail				= 0;
	REAL32 rampTempTail				= 0;
	INT16  IndexTempHead			= 0;
	UINT16 distanceHead				= 0;
	REAL32 rampTempHead				= 0;
	REAL32 LocolRampLength			= 0.0F;
	REAL32 AverRampValue			= 0.0F;
	*Degrade2Normal = e_FALSE;
	
	if((pTrainStatusData == ptrNULL) || (pForwardRailLineData == ptrNULL))
	{
		return 0;
	}
	
	/*�µ���Ч����*/
	RampValidNums 			= pForwardRailLineData->FWRamps.RampValidNum;
	
	if(RampValidNums <= 0)
	{
		return 0;
	}
	
	/*���ҳ�β���ڵ��µ�*/
	for(Index = 0;Index < RampValidNums;Index++)
	{
		if(G_PlanStart_LocoRelPos < (pTrainStatusData->TrainConsistData.TrainActualLength))
		{
			IndexTempTail	= 0;
			rampTempTail	= (REAL32)pForwardRailLineData->FWRamps.Ramps[IndexTempTail].Grade/(10.0F);
			distanceTail 	= (pTrainStatusData->TrainConsistData.TrainActualLength) - G_PlanStart_LocoRelPos;
			break;	
		}
		
		if(G_PlanStart_LocoRelPos >= (pTrainStatusData->TrainConsistData.TrainActualLength))
		{
			if((G_PlanStart_LocoRelPos - (pTrainStatusData->TrainConsistData.TrainActualLength)) <= \
					pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist)
			{
				IndexTempTail	= Index - 1;
				rampTempTail	= (REAL32)pForwardRailLineData->FWRamps.Ramps[IndexTempTail].Grade/(10.0F);
				distanceTail 	= pForwardRailLineData->FWRamps.Ramps[IndexTempTail+1].GradeRelatDist - 
						          (G_PlanStart_LocoRelPos - (pTrainStatusData->TrainConsistData.TrainActualLength));
				break;
			}
		}
	}

	/*���ҳ�ͷ���ڵ��µ�*/
	for(Index = IndexTempTail;Index < RampValidNums;Index++)
	{
		if(G_PlanStart_LocoRelPos <= pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist)
		{
			IndexTempHead 	= Index - 1;
			rampTempHead    = (REAL32)pForwardRailLineData->FWRamps.Ramps[IndexTempHead].Grade/(10.0F);
			if(G_PlanStart_LocoRelPos >= pForwardRailLineData->FWRamps.Ramps[IndexTempHead].GradeRelatDist)
			{
				distanceHead = G_PlanStart_LocoRelPos - pForwardRailLineData->FWRamps.Ramps[IndexTempHead].GradeRelatDist;
			}
			
			break;
		}
	}

	/*��������ͨ��ʱ�����ʼ�µ�ֵȡ��ͷ�����¶�ֵ*/
	if((IndexTempHead == 0)&&
	   (G_PlanStart_LocoRelPos ==  pForwardRailLineData->FWRamps.Ramps[1].GradeRelatDist))
	{
		AverRampValue = ((REAL32)pForwardRailLineData->FWRamps.Ramps[1].Grade)/(10.0F);
		*Degrade2Normal = e_TRUE;
		return AverRampValue;
	}
	
	if(IndexTempHead == IndexTempTail)
	{
		AverRampValue = (REAL32)pForwardRailLineData->FWRamps.Ramps[IndexTempHead].Grade/(10.0F);
		return AverRampValue;
	}
	else
	{
		/*�������µ���Ȩƽ��ֵ*/
		for(Index = IndexTempTail+1;Index <= IndexTempHead-1;Index++)
		{
			LocolRampLength = LocolRampLength + ((REAL32)pForwardRailLineData->FWRamps.Ramps[Index].Grade) /\
							  (REAL32)(pTrainStatusData->TrainConsistData.TrainActualLength)* \
							  ((REAL32)pForwardRailLineData->FWRamps.Ramps[Index].GradeLength)/(10.0F) ;

		}
		/*������ƽ���µ�*/
		AverRampValue 		= LocolRampLength + (rampTempTail*((REAL32)distanceTail) + rampTempHead*((REAL32)distanceHead)) / \
						    ((REAL32)(pTrainStatusData->TrainConsistData.TrainActualLength));	
		return AverRampValue;
	}
}

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcRampAvgValue
 *Function: ���㶨��ƽ���µ���50��Ϊһ������
 *Para    : 
 *Return  : ƽ���µ�ֵ
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.1  tw 		 2018/12/09			modified
 *NOTE    : V1.0.2  tw 		 2019/03/07			modified
******************************************************************************/
E_SysBool Atoalgo_Sense_CalcRampAvgValue(const S_TRAINSTATUSDATA* 		const pTrainStatusData,
										 const S_ALGO_STRATEGYCTRLDATA*	const pAlgoStrategyCtrlData,
						   	   	   	  	 const S_FORWARDRLDATA* 		const pForwardRailLineData,
						   	   	   	  	 	   REAL32*						  AvgRamp)
{
	REAL32 RampAvgValue			= 0.0F;
	UINT16 RampValidNums 		= 0;
	UINT16 Index				= 0;
	REAL32 AvgRampTemp[LINECALCLNUMS];
	UINT16 TailRelativePositionTemp = 0;
	E_SysBool Degrade2Normal = e_FALSE;
	REAL32 RampArray[300];
	UINT16 ArrayIndex = 0;
	UINT16 Num = 0;
	UINT16 TempNum = 0;
	UINT32 SingleLocoPos	 = 0U;
	
	/*��ʼƽ���µ�ֵ*/
	SingleLocoPos = G_PlanStart_LocoRelPos;
	if(0 == pForwardRailLineData->FWRamps.RampValidNum)
	{
		return e_FALSE;
	}
	RampAvgValue = Atoalgo_Sense_CalcRampInitAvgValue(pTrainStatusData,
													  pForwardRailLineData,
													  &Degrade2Normal);
	if(G_PlanStart_LocoRelPos < pTrainStatusData->TrainConsistData.TrainActualLength)
	{
		TempNum = (pTrainStatusData->TrainConsistData.TrainActualLength - \
				   G_PlanStart_LocoRelPos)/pAlgoStrategyCtrlData->PlanCalcStep;
	}
	else
	{
		TailRelativePositionTemp = G_PlanStart_LocoRelPos - pTrainStatusData->TrainConsistData.TrainActualLength;
	}

	Num = pTrainStatusData->TrainConsistData.TrainActualLength/pAlgoStrategyCtrlData->PlanCalcStep;
	RampValidNums 		= pForwardRailLineData->FWRamps.RampValidNum;

	if(Num == 0U)
		{
		/*�����µ�����*/
			for(Index = 1 ; Index < RampValidNums; Index++)
			{
				

				while(SingleLocoPos < pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist)
				{

					AvgRampTemp[ArrayIndex]	= (REAL32)(pForwardRailLineData->FWRamps.Ramps[Index-1].Grade)/(10.0F);
					ArrayIndex++;
					/*��ǰ�ƶ�һ����������*/
					SingleLocoPos += pAlgoStrategyCtrlData->PlanCalcStep;

					if(ArrayIndex >= 200U )
					{
						Comn_F_MemCpy(AvgRamp,AvgRampTemp,sizeof(AvgRampTemp),sizeof(AvgRampTemp));
						return e_TRUE;
					}
				}
				
			}
		}
		
	for(Index = 0 ; Index < pForwardRailLineData->FWRamps.RampValidNum ; Index++)
	{
		/*��β�����0��֮ǰ�������0��֮ǰ������λ�ø�ֵ*/

		while(TempNum > 0)
		{

				RampArray[ArrayIndex] = RampAvgValue;
				ArrayIndex++;
				TempNum--;
				//TailRelativePositionTemp += pAlgoStrategyCtrlData->PlanCalcStep;
		}
	
		while((TailRelativePositionTemp) <	pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist)
		{
			/*��������ͨ��ʱ����λ���µ���ֵ*/
			if((e_TRUE == Degrade2Normal) && (ArrayIndex < Num))
			{
				RampArray[ArrayIndex] = RampAvgValue;
				ArrayIndex++;
	
			}
			else
			{
				RampArray[ArrayIndex] = (REAL32)(pForwardRailLineData->FWRamps.Ramps[Index-1].Grade)/(10.0F);
				ArrayIndex++;
			}
			TailRelativePositionTemp += pAlgoStrategyCtrlData->PlanCalcStep;
			if(ArrayIndex > (LINECALCLNUMS + Num))
			{
				break;
			}
		}
		if(ArrayIndex > (LINECALCLNUMS + Num))
		{
			break;
		}

	}
	AvgRampTemp[0] = RampAvgValue;
	for(Index = 1 ; Index < ArrayIndex -Num -1 ; Index++)
	{
		AvgRampTemp[Index] = AvgRampTemp[Index-1] + (RampArray[Index-1 + Num]- RampArray[Index-1])/(REAL32)Num; 
		if(Index > LINECALCLNUMS)
		{
			break;
		}
	}

	Comn_F_MemCpy(AvgRamp,AvgRampTemp,sizeof(AvgRampTemp),sizeof(AvgRampTemp));
	return e_TRUE;
}

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcAddRes
 *Function: ������·�������������µ�̽��
 *Para    : 
 *Return  : ������������������ �����µ��������
 *NOTE    : V1.0.0  tw 		 2018/12/10			create
 *NOTE    : V1.0.1  zxm		 2018/12/25			modify
 *NOTE    : V1.0.2  tw		 2018/12/26			modify
******************************************************************************/
E_SysBool  Atoalgo_Sense_CalcAddRes(const S_TRAINSTATUSDATA* 	const pTrainStatusData,
								    const S_FORWARDRLDATA* 		const pForwardRailLineData, 
								          S_KERNEL_SENSEDATA*	const pKernelSensedataIO,
								    	  REAL32* 					  InAvgRampTemp,
								    	  REAL32* 					  InAvgCurveTemp)
{
	INT16  JudgeDiff		= 0U;			/*���µ��ж�ֵ��1Ϊ�¶����ӣ�-1Ϊ�¶ȼ�С��0ΪС����µ���ƽ�£��Ƿ�Ҫ��ö�����ͣ���*/
	UINT16 CurveValidNum	= 0U;			/*������Ч����*/
	UINT16 Index 			= 0U;
	REAL32 DiffTemp			= 0.0F;			/*�µ��仯��*/
	UINT16 IndexDiff		= 0U;
	UINT16 IndexSucces 		= 1U;            /*�ж�ǰ�󲽳����¶ȴ���������ֵ�ĸ���*/
	UINT16 IndexFail 		= 0U;			/*�ж�ǰ�󲽳����¶���������ֵ�ĸ���*/
	UINT8  IndexChagePoite	= 0U;			/*���µ���������*/
	INT16  ChangeTemp[LINECALCLNUMS];      	//�м��ж�����,����Ϊ1��С��Ϊ-1������Ϊ0
	UINT16 Num				= 0U;
	UINT32 i = 0;
	REAL32 RampDiffValue    = 0.0F;
	
	Comn_F_MemSet((void*)ChangeTemp,0x00,sizeof(ChangeTemp));
	
	ChangeTemp[0]			 = 0;

	Num = pTrainStatusData->TrainConsistData.TrainActualLength/pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep;
	if(Num < 2)
	{
		RampDiffValue = 1.0;
	}
	else
	{
		RampDiffValue = 3.0;
	}
	
	for(Index = 0 ; Index < LINECALCLNUMS ; Index++)
	{
		/*��·������������*/
		pKernelSensedataIO->RaillineCalcResult.RailAddRes[Index] = InAvgRampTemp[Index] + InAvgCurveTemp[Index];

		/*�����м��ж����飬�����ж��¶��Ƿ��ڱ仯��1��ʾ�µ�������-1��ʾ�¶��½���0��ʾ�¶ȱ仯����*/
		if(Index > 0)
		{
			DiffTemp = pKernelSensedataIO->RaillineCalcResult.RailAddRes[Index] - 
					pKernelSensedataIO->RaillineCalcResult.RailAddRes[Index-1];
		}	
		if(DiffTemp > ((REAL32)RampDiffValue*(pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep))/\
					  ((REAL32)(pTrainStatusData->TrainConsistData.TrainActualLength)))
		{
			ChangeTemp[Index] =  1;
		}
		if((DiffTemp <= ((REAL32)RampDiffValue*(pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep))/\
						((REAL32)(pTrainStatusData->TrainConsistData.TrainActualLength))) && 
		   (DiffTemp >= (-((REAL32)RampDiffValue*(pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep))/\
				   	      ((REAL32)(pTrainStatusData->TrainConsistData.TrainActualLength)))))
		{
			ChangeTemp[Index] =  0;
		}	
		if(DiffTemp < (-((REAL32)RampDiffValue*(pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep))/\
						((REAL32)(pTrainStatusData->TrainConsistData.TrainActualLength))))
		{
			ChangeTemp[Index] = -1;
		}
	}
	
	/*b���µ�̽��*/
	do
		{
		IndexSucces 		= 1;
		IndexFail 			= 0;
		
		if(ChangeTemp[IndexDiff] != JudgeDiff)
		{
			for(Index = 1; Index <= (Num/2+2);Index++)
			{
				if(ChangeTemp[IndexDiff+Index] == ChangeTemp[IndexDiff])
				{
					IndexSucces++;
				}
				else 	
				{
					IndexFail++;
				}
			
				if(IndexFail > IndexSucces)
				{
					break;
				}
			}
			
			if(IndexSucces >= Num/2)
			{
				JudgeDiff = ChangeTemp[IndexDiff];
				if((Num<5)&&(JudgeDiff==0))
				{
					continue;
				}
				else
				{
					pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointDis[IndexChagePoite] = \
											IndexDiff * (pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep);	
				}
				
				IndexChagePoite++;
				pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointNum = IndexChagePoite;
			}
			if(((IndexDiff * (pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep) + G_PlanStart_LocoRelPos) > \
				 pForwardRailLineData->FWRamps.Ramps[pForwardRailLineData->FWRamps.RampValidNum-1].GradeRelatDist) || \
				(IndexChagePoite > CHANGERAMPPOINTNUMS))
			{
				break;
			}
			
		}
		IndexDiff++;
	}while(IndexDiff < LINECALCLNUMS - ALGO_SENSE_JUDGE_NUM);
	return e_TRUE;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcAddRes
 *Function: ������·�������������µ�
 *Para    : 
 *Return  : �����������飬���µ�����
 *NOTE    : V1.0.0		tw 		 2019/01/08			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_RailLineClac(const S_FORWARDRLDATA* 		const pForwardRailLineData, 
								 	      	S_KERNEL_SENSEDATA*		const pKernelSensedataIO)
{
	REAL32 AvgRampTemp[LINECALCLNUMS];
	REAL32 AvgCurveTemp	[LINECALCLNUMS];
	UINT32 i = 0;
	
	if(pKernelSensedataIO->LocoSignalData.LKJMode == e_Degrade)
	{
		return e_FALSE;
	}
	
	G_PlanStart_LocoRelPos	 = (UINT16)pKernelSensedataIO->TrainLocateData.Position;
	//printf("Pos:%d   ",G_PlanStart_LocoRelPos);
	if(e_FALSE == Atoalgo_Sense_CalcRampAvgValue(&(pKernelSensedataIO->TrainStatusData),
												 &(pKernelSensedataIO->AlgoStrategyCtrlData),
												 pForwardRailLineData,
												 AvgRampTemp))
	{
		//printf("ASC1 ERROR.\n");
		return e_FALSE;
	}
#if 0
	for(i = 0; i < 20; i++)
	{
		//printf("%.1f ",AvgRampTemp[i]);
	}
	//printf("\n");
#endif	
	
	if(e_FALSE == Atoalgo_Sense_CalcCurveAvgValue(&(pKernelSensedataIO->TrainStatusData),
			 	 	 	 	 	 	 	 	 	  &(pKernelSensedataIO->AlgoStrategyCtrlData),
												  pForwardRailLineData,
												  AvgCurveTemp))
	{
		//printf("ASC2 ERROR.\n");
		return e_FALSE;
	}

#if 0
	for(i = 0; i < 10; i++)
	{
		printf("%.1f ",AvgCurveTemp[i]);
	}
	printf("\n");
#endif	
	
	if(e_FALSE == Atoalgo_Sense_CalcAddRes(&(pKernelSensedataIO->TrainStatusData),
										   pForwardRailLineData,
										   pKernelSensedataIO,
										   AvgRampTemp,
										   AvgCurveTemp))
	{
		//printf("ASC1 ERROR.\n");
		return e_FALSE;
	}
#if 0
	printf("line res:");
	for(i = 0; i < 40; i++)
	{
		printf("%.2f ",pKernelSensedataIO->RaillineCalcResult.RailAddRes[i]);
	}
	printf("\n");
#endif	
	if(e_FALSE == Atoalgo_Sense_RampChangePointAveRamp(pKernelSensedataIO))
	{
		return e_FALSE;
	}
	return  e_TRUE;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_RampValueClac
 *Function: ���µ��µ�����
 *Para    : ���µ�����
 *Return  : ������µ�ƽ���µ����� (ChangeRampPointAveRamp[0]Ϊ����λ�õ�����Ϊ0�ı��µ���ε�ƽ��ֵ
 *Return  						  ChangeRampPointAveRamp[1]Ϊ���µ���������Ϊ0������Ϊ1��ε�ƽ��ֵ���Դ�����)
 *NOTE    : V1.0.0		tw 		 2019/04/12			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_RampChangePointAveRamp(S_KERNEL_SENSEDATA*	const pKernelSensedataIO)
{

	UINT16 Index			= 0;
	UINT16 VaildNum	 		= 0;
	UINT16 AveRampIndex		= 0;
	UINT16 PlanCalcStep		= 0U;
	REAL32 RampAveValue 	= 0.0F;
	UINT32 BeginDistance	= 0U;
	UINT32 EndDistance		= 0U;
	REAL32 CRPAveRamp[SENSE_CHGPNT_MAX_NUM];
	
	Comn_F_MemSet((void *)CRPAveRamp,0.0,SENSE_CHGPNT_MAX_NUM*sizeof(REAL32));
	
	VaildNum = pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointNum;
	PlanCalcStep = pKernelSensedataIO->AlgoStrategyCtrlData.PlanCalcStep;
	
	for(Index = 0;Index < VaildNum;Index++)
	{
		if(Index == 0U)
		{
			BeginDistance = 0;
			EndDistance   = pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointDis[0];
		}else if(Index > 0U)
		{
			BeginDistance = pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointDis[Index-1];
			EndDistance   = pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointDis[Index];
		}
		if(EndDistance >= 10000)
		{
			break;
		}
		if(BeginDistance>EndDistance)
		{
			CRPAveRamp[AveRampIndex]= Atoalgo_Sense_RampValueClac(&(pKernelSensedataIO->AlgoStrategyCtrlData),
																	pKernelSensedataIO->RaillineCalcResult.RailAddRes,
																	(REAL32)BeginDistance);
			AveRampIndex++;
			
#if DEBUG_PRINT_ERROR
			printf("RCP_dis\n");
#endif
			continue;
		}
		
		CRPAveRamp[AveRampIndex]=Atoalgo_Sense_SectionRampAve(BeginDistance,EndDistance,&(pKernelSensedataIO->RaillineCalcResult),PlanCalcStep);
		AveRampIndex++;
		
		if(EndDistance >= pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointDis[VaildNum-1])
		{
			break;
		}

	}
	
	
	Comn_F_MemCpy(&(pKernelSensedataIO->RaillineCalcResult.ChangeRampPointStr.ChangeRampPointAveRamp),
					CRPAveRamp,
					SENSE_CHGPNT_MAX_NUM*sizeof(REAL32),
					SENSE_CHGPNT_MAX_NUM*sizeof(REAL32));
	return e_TRUE;
}

/******************************************************************************
 *Name    : Atoalgo_Sense_RampValueClac
 *Function: ��������λ�õĸ�������
 *Para    : �����������飬���λ��
 *Return  : �����������ֵ
 *NOTE    : V1.0.0		tw 		 2019/01/08			create
******************************************************************************/
REAL32  Atoalgo_Sense_RampValueClac(const S_ALGO_STRATEGYCTRLDATA* 	const pAlgoStategyCtrlData,
									const REAL32* 					const RailAddRes,
										  REAL32					const Distance)
{
	UINT32 uintDistance = 0;
	REAL32 RampValue 	= 0;
	
	uintDistance  = (UINT32)(Distance/(pAlgoStategyCtrlData->PlanCalcStep));
	RampValue	  = RailAddRes[uintDistance];
	return RampValue;
}

/******************************************************************************
 *Name    : Atoalgo_Sense_RailLineBasicData
 *Function: ���ⲿ�������·�������ݼ����֪����
 *Para    :                          
 *Return  : �����ɹ�����e_TRUE��ʧ�ܷ���e_FALSE
 *NOTE    : V1.0.0  YipingYang 	 2019/02/26      create
******************************************************************************/
E_SysBool Atoalgo_Sense_RailLineBasicData(S_ALGO_INPUT_BASICDATA*  pAlgoInputBasicData,
									 	  S_ALGO_INPUT_BASICDATA** pBasicDataOut)
{
	if((ptrNULL == pAlgoInputBasicData))
	{
		return e_FALSE;
	}
	
	*pBasicDataOut = pAlgoInputBasicData;
	return e_TRUE;
}
#if 0
/******************************************************************************
 *Name    : Atoalgo_Sense_SearchLongRamp
 *Function: ̽��ǰ���������»򳤴�����
 *Para    :                          
 *Return  : �����ɹ�����e_TRUE��ʧ�ܷ���e_FALSE
 *NOTE    : V1.0.0  zxm 	 2019/03/05      create
******************************************************************************/
E_SysBool Atoalgo_Sense_SearchLongRamp(const S_FORWARDRLDATA* 		const pForwardRailLineData,
											 S_KERNEL_SENSEDATA*	const pKernelSensedataIO)
{
	UINT16 Index 			    = 0;
	UINT16 Index2 				= 0;
	UINT16 Index3				= 0;
	UINT16 PosFromLoco 			= 0;
	UINT16 SectionRampLength	= 0;
	INT16  SectionRampValue     = 0;

	if(0 == pForwardRailLineData->FWRamps.RampValidNum)
	{
		return e_FALSE;
	}
	
	Comn_F_MemSet((void *)&(pKernelSensedataIO->RaillineCalcResult.longRamp),0,sizeof(S_LONGRAMPINF));
	for(Index = 0;Index < pForwardRailLineData->FWRamps.RampValidNum;Index++)
	{
		/*̽��ǰ����������*/
		if((pForwardRailLineData->FWRamps.Ramps[Index].Grade <= (INT16)(-LONGRAMP_AVR)) /*&& \
				(pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist >= G_PlanStart_LocoRelPos)*/)/**��������**/
		{
			for(Index2 = Index;Index2 < (pForwardRailLineData->FWRamps.RampValidNum - Index);Index2++)
			{
				SectionRampValue  += pForwardRailLineData->FWRamps.Ramps[Index2].Grade;
				SectionRampLength += pForwardRailLineData->FWRamps.Ramps[Index2].GradeLength;
				if((pForwardRailLineData->FWRamps.Ramps[Index2].Grade <= (INT16)(-LONGRAMP_MIN)) && \
						(pForwardRailLineData->FWRamps.Ramps[Index2].Grade > (INT16)(-LONGRAMP_AVR)) && \
						(SectionRampLength += pForwardRailLineData->FWRamps.Ramps[Index2].GradeLength >= 1000))/*??????*/
				{
					continue;
				}

				if(pForwardRailLineData->FWRamps.Ramps[Index2].Grade > (INT16)(-LONGRAMP_MIN))/*100m-11,6000m-8*/
				{	
					if((SectionRampLength >= 5000))
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco 	= \
								pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist - G_PlanStart_LocoRelPos;						
		
						if(0 <= pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco)/*ֻ�г�ͷ�պô��ڳ����µ���Ծ����ϲ��ܴ���*/
						{
							pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_TRUE;
						}
						else
						{
							pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_FALSE;
						}
						
						if(pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco > 6000)
						{
							pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_FALSE;
							return e_FALSE;
						}
						pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco  = \
								pForwardRailLineData->FWRamps.Ramps[Index2-1].GradeRelatDist + \
								pForwardRailLineData->FWRamps.Ramps[Index2-1].GradeLength - G_PlanStart_LocoRelPos;
						
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_TRUE;
						pKernelSensedataIO->RaillineCalcResult.longRamp.RampType		= 1;
						pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue		= -110;
#if 0								
						printf("DP1:%d,%d,%d,%d,%d,%d\n",Index,Index2,Index3,
																pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco,
																pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco,
																pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue);
#endif
						return e_TRUE;
					}
					else
					{
						SectionRampValue   = 0;
					    SectionRampLength  = 0;
						Comn_F_MemSet((void *)&(pKernelSensedataIO->RaillineCalcResult.longRamp),0,sizeof(S_LONGRAMPINF));
						break;
					}
					
				}
				
				if((SectionRampLength >= 5000) && ((SectionRampValue/(Index2-Index+1)) <= (INT16)(-LONGRAMP_AVR)))/*????????*/
				{
					for(Index3 = Index2+1;Index3 < pForwardRailLineData->FWRamps.RampValidNum - (Index2+1);Index3++)
					{
						if(pForwardRailLineData->FWRamps.Ramps[Index3].Grade <= (INT16)(-LONGRAMP_AVR))
						{
							SectionRampValue += pForwardRailLineData->FWRamps.Ramps[Index3].Grade;
							continue;
						}else
						{
							break;
						}
					}
					pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco 	= \
							pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist - G_PlanStart_LocoRelPos;						

					if(0 <= pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco)
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_TRUE;
					}
					else
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_FALSE;
					}
					
					if(pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco > 6000)
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_FALSE;
						return e_FALSE;
					}
					pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco  = \
							pForwardRailLineData->FWRamps.Ramps[Index3].GradeRelatDist + \
							pForwardRailLineData->FWRamps.Ramps[Index3].GradeLength - G_PlanStart_LocoRelPos;
					
					pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_TRUE;
					pKernelSensedataIO->RaillineCalcResult.longRamp.RampType		= 1;
					pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue		= -110;
#if 0
					printf("DP2:%d,%d,%d,%d,%d,%d\n",Index,Index2,Index3,
										pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco,
										pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco,
										pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue);
#endif
					return e_TRUE;
				}
			}
		}
		else
		{
			Comn_F_MemSet((void *)&(pKernelSensedataIO->RaillineCalcResult.longRamp),0,sizeof(S_LONGRAMPINF));
		}
		
		/*̽��ǰ����������*/
		if((pForwardRailLineData->FWRamps.Ramps[Index].Grade >= (INT16)LONGRAMP_AVR) && \
				(pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist >= G_PlanStart_LocoRelPos))
		{
			for(Index2 = Index;Index2 < (pForwardRailLineData->FWRamps.RampValidNum - Index);Index2++)
			{
				SectionRampValue  += pForwardRailLineData->FWRamps.Ramps[Index2].Grade;
				SectionRampLength += pForwardRailLineData->FWRamps.Ramps[Index2].GradeLength;
				if((pForwardRailLineData->FWRamps.Ramps[Index2].Grade >= (INT16)LONGRAMP_MIN) && \
						(pForwardRailLineData->FWRamps.Ramps[Index2].Grade < (INT16)LONGRAMP_AVR) && \
						(SectionRampLength += pForwardRailLineData->FWRamps.Ramps[Index2].GradeLength >= 1000))
				{
					continue;
				}

				
				if((pForwardRailLineData->FWRamps.Ramps[Index2].Grade <= (INT16)LONGRAMP_MIN))
				{
					if(SectionRampLength >= 5000)
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco 	= \
								pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist - G_PlanStart_LocoRelPos;						
		
						if(0 == pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco)
						{
							pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_TRUE;
						}
						else
						{
							pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_FALSE;
						}
						
						if(pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco > 6000)
						{
							pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_FALSE;
							return e_FALSE;
						}
						
						pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco  = \
								pForwardRailLineData->FWRamps.Ramps[Index2-1].GradeRelatDist + \
								pForwardRailLineData->FWRamps.Ramps[Index2-1].GradeLength - G_PlanStart_LocoRelPos;
						
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_TRUE;
						pKernelSensedataIO->RaillineCalcResult.longRamp.RampType		= 0;
						pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue		= 110;
#if 0
						printf("UP1:%d,%d,%d,%d,%d,%d\n",Index,Index2,Index3,
																pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco,
																pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco,
																pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue);
#endif
						return e_TRUE;
					}
					else
					{
						SectionRampValue   = 0;
						SectionRampLength  = 0;
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_FALSE;
						break;
					}

				}
				
				if((SectionRampLength >= 5000) && ((SectionRampValue/(Index2-Index)) >= (INT16)LONGRAMP_AVR))
				{
					for(Index3 = Index2 + 1;Index3 < (pForwardRailLineData->FWRamps.RampValidNum - (Index2 + 1));Index3++)
					{
						if(pForwardRailLineData->FWRamps.Ramps[Index3].Grade >= (INT16)LONGRAMP_AVR)
						{
							SectionRampValue += pForwardRailLineData->FWRamps.Ramps[Index3].Grade;
							continue;
						}else
						{
							break;
						}
					}
					pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco 	= \
							pForwardRailLineData->FWRamps.Ramps[Index].GradeRelatDist - G_PlanStart_LocoRelPos;						

					if(0 == pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco)
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_TRUE;
					}
					else
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsAccessInRamp = e_FALSE;
					}
					
					if(pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco > 6000)
					{
						pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_FALSE;
						return e_FALSE;
					}
					pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco  = \
							pForwardRailLineData->FWRamps.Ramps[Index3].GradeRelatDist + \
							pForwardRailLineData->FWRamps.Ramps[Index3].GradeLength - G_PlanStart_LocoRelPos;
					
					pKernelSensedataIO->RaillineCalcResult.longRamp.IsExistLongRamp	= e_TRUE;
					pKernelSensedataIO->RaillineCalcResult.longRamp.RampType		= 0;
					pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue		= 110;
#if 0
					printf("UP2:%d,%d,%d,%d,%d,%d\n",Index,Index2,Index3,
										pKernelSensedataIO->RaillineCalcResult.longRamp.PosFromLoco,
										pKernelSensedataIO->RaillineCalcResult.longRamp.PosEndFromLoco,
										pKernelSensedataIO->RaillineCalcResult.longRamp.RampValue);
#endif
					return e_TRUE;
				}
			}
		}
		else
		{
			Comn_F_MemSet((void *)&(pKernelSensedataIO->RaillineCalcResult.longRamp),0,sizeof(S_LONGRAMPINF));
		}
	}
	return e_FALSE;
}
#endif
/******************************************************************************
 *Name    : Atoalgo_Sense_SectionRampAve
 *Function: ����һ�ξ����ƽ����������
 *Para    : ����öγ�ʼλ�úͽ���λ�ã�1=1m,�೵ͷ���룩
 *Return  : ���ظö�ƽ����������ֵ��1=1��λ����
 *NOTE    : V1.0.0		tw 		 2019/02/22			create
******************************************************************************/
REAL32  Atoalgo_Sense_SectionRampAve( UINT32 BeginDistance,
									  UINT32 EndDistance,
									 const S_RAILLINECALC_RESULT* const  RaillineCalcResult,
									  UINT16 PlanCalcStep)
{
	UINT8 BeginIndex = 0;
	UINT8 EndIndex  = 0;
	UINT8 Index 	 = 0;
	REAL32 AveRampTemp = 0.0F;
	REAL32 AveRamp	   = 0.0F;
	BeginIndex = (UINT8)(BeginDistance/(UINT32)PlanCalcStep);
	EndIndex   = (UINT8)(EndDistance/(UINT32)PlanCalcStep);
	if(BeginIndex > EndIndex)
	{
		//printf("Err_SectionRampAve");
		return 0.0;
	}

	if(BeginIndex == EndIndex)
	{
		return RaillineCalcResult->RailAddRes[BeginIndex];
	}
	if(EndIndex > BeginIndex)
	{
		for(Index = BeginIndex;Index <= EndIndex;Index++)
		{
			AveRampTemp += RaillineCalcResult->RailAddRes[Index];
		}
		AveRamp = AveRampTemp/(EndIndex - BeginIndex +1);
	}
	
	return AveRamp;
}
/******************************************************************************
 *Name    : Atoalgo_Sense_SectionChangeRampPoint
 *Function: �ж������ڱ��µ���Ϣ
 *Para    : ������ʼλ���������λ�ã����µ�����
 *Return  : ��������ڱ��µ��������һ�����µ�����ֵ
 *NOTE    : V1.0.0		tw 		 2019/02/26			create
******************************************************************************/
UINT8  Atoalgo_Sense_SectionChangeRampPoint(const UINT32 BeginDistance,
									 const UINT32 EndDistance,
									 const S_CHANGERAMPPOINT* const pChangeRampPointStr,
									 UINT16* const pBeginIndexOut)
{
	UINT16 Index = 0U;
	UINT8 RpChgPntNum = 0U;
	UINT8 RpChgPntBgnIndex =0U;
	UINT8 RpChgPntEndIndex = 0U;
	
	if( pChangeRampPointStr->ChangeRampPointNum == 0)
	{
		RpChgPntNum = 0;
	}
	else
	{
		for(Index = 0;Index < pChangeRampPointStr->ChangeRampPointNum;Index++)
		{
			if(Index == (pChangeRampPointStr->ChangeRampPointNum-1))
			{
				RpChgPntEndIndex = (UINT8)Index;
				RpChgPntNum = Index+1;
				break;
			}
			
		
			if((EndDistance) < (pChangeRampPointStr->ChangeRampPointDis[Index]))
			{
				if(Index == 0)
				{
					RpChgPntNum = 0;
					break;
				}
				else 
				{
					RpChgPntEndIndex = Index-1;
					break;	
				}
			}
			if(BeginDistance < pChangeRampPointStr->ChangeRampPointDis[Index])
			{
				RpChgPntNum++;
			}
		}
		RpChgPntBgnIndex = (RpChgPntEndIndex+1) - RpChgPntNum;
		if(RpChgPntNum == 0U)
		{
			RpChgPntBgnIndex = 0U;
		}
		*pBeginIndexOut = RpChgPntBgnIndex;
	}
	return RpChgPntNum;
}
