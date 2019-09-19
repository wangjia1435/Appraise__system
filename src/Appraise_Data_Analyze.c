/******************************************************************************
 *File Name	     :	ACS_AppraiseSystem.h
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/07/01
 *Description    :	
 *Modification history:
 *REV1.0.0    Tangwei     2019/07/01    File Create 
******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
//#ifndef ACS_APPRAISE_SYSTEM_H_
//#define	ACS_APPRAISE_SYSTEM_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/Appraise_Data_Analyze.h"
#include "../h/Appraise_BasicFunction.h"

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

/******************************************************************************
 *Name    : ACS_Data_pipe0_Analyze
 *Function: 解析管道0的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe0_Analyze(UINT8* Pipe0,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{

	UINT16 PipeIndex = 0;
/*条件判断*/
#if 0
	UINT16 i=0;
	for(i=0;i<1400;i++)
printf("%d ",Pipe0[i]);
#endif




	PipeIndex = 35;
/*数据解析*/
	/*机车命令及状态-CCU+BCU*/
	pA2AInputPara->DynaData.LocoDynCMDandStatus.ATOFlag					
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.RunningStatus 			
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.FltStatus				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.SingalStatus			
				= Pipe0[PipeIndex];

	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.LocoStatus				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.DmiCmd					
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.FastRunTime				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.SlowRunTime				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BrakeTestFlag			
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BackOffFlag				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BigBrakePosition		
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.SmallBrakePosition		
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.MotorIsoStatus			
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BCUBrakeHandleType		
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BCUPressureType			
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TrainTailType			
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TrainLoadType			
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.VehicleType				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.ConsistType				
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.ClosedVehicleNums		
				= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.SleepLocoNums			
				= Pipe0[PipeIndex];//55
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.SlowRunMaxSpeed			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BrkShoePresPHT			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.PressureDecrement		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.ABHExTargetACK			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.IBHExTargetACK			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.PressureTotalVal		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.BrakeCylinder			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.EqualReservoir			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.RateOfFlow				
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TrainTailValue			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.PriVolt					
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TcmsSpeed				
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.Force					
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TrcFmax					
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.EBrFmax					
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TrcPowerLostPercent		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.EBrkPowerLostPercent	
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.Position				
		 	= Comn_F_GetUINT32(Pipe0[PipeIndex],
							   Pipe0[PipeIndex+1],
							   Pipe0[PipeIndex+2],
							   Pipe0[PipeIndex+3]);
	
	PipeIndex = PipeIndex + 4;
	pA2AInputPara->DynaData.LocoDynCMDandStatus.TravlledDistance		
			= Comn_F_GetUINT32(Pipe0[PipeIndex],
							   Pipe0[PipeIndex+1],
							   Pipe0[PipeIndex+2],
							   Pipe0[PipeIndex+3]);
	/*LKJ动态控制数据*/
	//pA2AInputPara->DynaData.LKJDynamicCtlData.Singal = &Pipe[117];
	PipeIndex = 117;
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.LKJMode 		= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.ResByte 		= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.TrainType 	= Pipe0[PipeIndex]; //120
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.TrainPipe 		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.TrainWeight 		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.TrainLength 		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.VehicleNum 		
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.LocoType 			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.WheelDiameter 	
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.LkjSpeed			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.HeavyCar 			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.EmptyCar 			
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.NextSigRelaDist 	
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->DynaData.LKJDynamicCtlData.CurrentSideLine = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.NextSideLine 	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.CurrentBranch	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.LKJDynamicCtlData.NextBranch 	  = Pipe0[PipeIndex]; //144
	
	/*过分相信号*/
	PipeIndex = 156;
	pA2AInputPara->DynaData.NeutralSignal.NeutralForetellFlag = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.NeutralSignal.NeutralForceFlag 	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.NeutralSignal.NeutralPassFlag 	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->DynaData.NeutralSignal.LocoInNeutral 	  = Pipe0[PipeIndex];
	
	
	/*控制指令*///160
	PipeIndex = 160;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningStatus   = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.BrakeCMD 		  = Pipe0[PipeIndex];	
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningModeFlag = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.CtlCmd		  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.CtlMode		  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.NeutralCmd	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.BrakeTestSta	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.IsoMotorCmd	  = Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.DrivingFSetValue= Pipe0[PipeIndex];
	
	PipeIndex = PipeIndex + 1;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.ABHTargetValue	
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.IBHTargetValue	
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex = PipeIndex + 2;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.RunningTime		
			 = Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);
	
		PipeIndex = PipeIndex + 4;
	pA2AInputPara->CtrlData.AlgoOutputCtlData.RemainTime	
		 	= Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);
	
		
		/* 规划曲线*//*??????????????????*/
	PipeIndex =180;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.UpDataLife
			= Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);
	
	PipeIndex += 4;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.ValidNum 
			= Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex += 2;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.PressureDecrement[0] 
	        = Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	PipeIndex += 2;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.RunningStatus[0] = Pipe0[PipeIndex];
	
	PipeIndex += 1;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetPosition[0]
	        = Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);

	PipeIndex += 2;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetV[0]
	        = Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);

	PipeIndex += 2;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetF[0]
		    = Comn_F_GetUINT16(Pipe0[PipeIndex],Pipe0[PipeIndex+1]);
	
	/*算法软件版本未添加*/
	
	/*算法运行状态输出*/
	PipeIndex = 199;
	pA2AInputPara->CtrlData.AlgoOutputStaData.AlgoAutoQuitReqCode 
			= Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);
	
	PipeIndex = PipeIndex + 4;
	pA2AInputPara->CtrlData.AlgoOutputStaData.AlgoAutoForbidCode  
			= Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);
	

	/*耗电量*/
	PipeIndex = 594;
	pA2AInputPara->SpecialData.LocoElectrical.ConsumeElectrical = 
			Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);
	
	PipeIndex = PipeIndex + 4;
	pA2AInputPara->SpecialData.LocoElectrical.ReElectrical	= 
			Comn_F_GetUINT32(Pipe0[PipeIndex],
								Pipe0[PipeIndex+1],
								Pipe0[PipeIndex+2],
								Pipe0[PipeIndex+3]);		
	
	return e_TRUE;
	
}
/******************************************************************************
 *Name    : ACS_Data_pipe1_Analyze
 *Function: 解析管道1的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe1_Analyze(UINT8* Pipe1,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	UINT16 PipeIndex = 0;
	UINT16 LimSpdCrvIndex = 0;
	
	/*动态防护曲线*/
	PipeIndex += 16;
	for(LimSpdCrvIndex = 0; LimSpdCrvIndex < ALGO_LIMIT_SPEED_NUM_MAX; LimSpdCrvIndex++)
	{
		pA2AInputPara->DynaData.LkjProjectCurve.LimitSpeed[LimSpdCrvIndex] = Pipe1[PipeIndex];
		PipeIndex += 1;
	}
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_Data_pipe2_Analyze
 *Function: 解析管道2的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe2_Analyze(UINT8* Pipe2,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	UINT16 PipeIndex = 0;
	UINT16 VaildNum  = 0;
	UINT16 Index 	 = 0;
	
	/*规划曲线输出-规划点工况,速度,相对距离*/
	PipeIndex =16;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.ValidNum 
			= Comn_F_GetUINT16(Pipe2[PipeIndex],Pipe2[PipeIndex+1]);
	VaildNum = pA2AInputPara->CtrlData.AlgoOutputTargetLine.ValidNum; 
	
	PipeIndex += 2;
	for(Index = 0; Index < 300 ; Index++)
	{
		if(Index<VaildNum)
		{
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.RunningStatus[Index] = 
					(Pipe2[PipeIndex]&0xe0)>>5;
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetV[0] = 
					Comn_F_GetUINT16(Pipe2[PipeIndex],Pipe2[PipeIndex+1])&0x1fff;
		}
		else
		{
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.RunningStatus[Index] = 0;
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetV[0] = 0;
		}
		PipeIndex += 2;	
	}
	
	for(Index = 0; Index < 300; Index++ )
	{
		if(Index<VaildNum)
		{
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetPosition[Index] = 
					Comn_F_GetUINT16(Pipe2[PipeIndex],Pipe2[PipeIndex+1]);

		}
		else
		{

			pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetPosition[Index] = 0;
		}
		PipeIndex += 2;	
	}

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_Data_pipe3_Analyze
 *Function: 解析管道3的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe3_Analyze(UINT8 *Pipe3,
		  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	UINT16 PipeIndex = 0;
	UINT16 VaildNum  = 0;
	UINT16 Index 	 = 0;
	
	/*规划曲线输出-规划点工况和速度*/
	PipeIndex =16;
	pA2AInputPara->CtrlData.AlgoOutputTargetLine.ValidNum 
			= Comn_F_GetUINT16(Pipe3[PipeIndex],Pipe3[PipeIndex+1]);
	VaildNum = pA2AInputPara->CtrlData.AlgoOutputTargetLine.ValidNum; 
	
	PipeIndex += 2;
	for(Index = 0; Index < 300 ; Index++)
	{
		if(Index<VaildNum)
		{
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.PressureDecrement[Index] = 
					Comn_F_GetUINT16(Pipe3[PipeIndex],Pipe3[PipeIndex+1]);
		}
		else
		{
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.PressureDecrement[Index] = 0;
		}
		PipeIndex += 2;	
	}
	
	for(Index = 0; Index < 300 ; Index++)
	{
		if(Index<VaildNum)
		{
			pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetPosition[Index] = 
					Comn_F_GetUINT16(Pipe3[PipeIndex],Pipe3[PipeIndex+1]);

		}
		else
		{

			pA2AInputPara->CtrlData.AlgoOutputTargetLine.TragetPosition[Index] = 0;
		}
		PipeIndex += 2;	
	}
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_Data_pipe4_Analyze
 *Function: 解析管道4的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe4_Analyze(UINT8 *Pipe4,
  	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	UINT16 PipeIndex = 0;
	UINT16 VaildNum  = 0;
	UINT16 Index 	 = 0;

	PipeIndex = 16;
	pA2AInputPara->BasicData.ForwardRailLineData.FWRamps.RampValidNum = 
			Comn_F_GetUINT16(Pipe4[PipeIndex],Pipe4[PipeIndex+1]);
	
	PipeIndex +=2;
	for(Index = 0; Index < 100; Index++)
	{
		pA2AInputPara->BasicData.ForwardRailLineData.FWRamps.Ramps[Index].Grade = Pipe4[PipeIndex];
		PipeIndex +=2;
		pA2AInputPara->BasicData.ForwardRailLineData.FWRamps.Ramps[Index].GradeLength = Pipe4[PipeIndex];
		PipeIndex +=2;
		pA2AInputPara->BasicData.ForwardRailLineData.FWRamps.Ramps[Index].GradeRelatDist = Pipe4[PipeIndex];
		PipeIndex +=2;
	}
	
	pA2AInputPara->BasicData.ForwardRailLineData.FWCurves.CurveValidNum =
			Comn_F_GetUINT16(Pipe4[PipeIndex],Pipe4[PipeIndex+1]);
	
	PipeIndex +=2;
	for(Index = 0; Index < 50 ; Index++)
	{
		pA2AInputPara->BasicData.ForwardRailLineData.FWCurves.Curves[Index].Radius = Pipe4[PipeIndex];
		PipeIndex +=2;
		pA2AInputPara->BasicData.ForwardRailLineData.FWCurves.Curves[Index].CurveLenth = Pipe4[PipeIndex];
		PipeIndex +=2;
		pA2AInputPara->BasicData.ForwardRailLineData.FWCurves.Curves[Index].CurveRelatDist = Pipe4[PipeIndex];
		PipeIndex +=2;
	}
		
	
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_Data_pipe5_Analyze
 *Function: 解析管道5的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe5_Analyze(UINT8 *Pipe5,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_Data_pipe6_Analyze
 *Function: 解析管道6的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe6_Analyze(UINT8 *Pipe6,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	UINT16 PipeIndex = 0;
	UINT16 VaildNum  = 0;
	UINT16 Index 	 = 0;
	/*按lkj15解析*/
	PipeIndex = 23; 
	pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalNum = Pipe6[PipeIndex];
	
	PipeIndex += 1;
	/*1*/
	pA2AInputPara->BasicData.ForwardRailLineData.FWStationInfo.StationInfo[0].StationNo = 
			Comn_F_GetUINT32(Pipe6[PipeIndex],
								Pipe6[PipeIndex+1],
								Pipe6[PipeIndex+2],
								Pipe6[PipeIndex+3]);
	PipeIndex += 4;
	
	pA2AInputPara->BasicData.ForwardRailLineData.FWStationInfo.StationInfo[0].RelativeDist =
			Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
	PipeIndex += 2;
	/*2*/
	pA2AInputPara->BasicData.ForwardRailLineData.FWStationInfo.StationInfo[1].StationNo = 
			Comn_F_GetUINT32(Pipe6[PipeIndex],
								Pipe6[PipeIndex+1],
								Pipe6[PipeIndex+2],
								Pipe6[PipeIndex+3]);
	PipeIndex += 4;
	
	pA2AInputPara->BasicData.ForwardRailLineData.FWStationInfo.StationInfo[1].RelativeDist =
			Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
	PipeIndex += 2;
	/*3*/
	pA2AInputPara->BasicData.ForwardRailLineData.FWStationInfo.StationInfo[2].StationNo = 
			Comn_F_GetUINT32(Pipe6[PipeIndex],
								Pipe6[PipeIndex+1],
								Pipe6[PipeIndex+2],
								Pipe6[PipeIndex+3]);
	PipeIndex += 4;
	
	pA2AInputPara->BasicData.ForwardRailLineData.FWStationInfo.StationInfo[2].RelativeDist =
			Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalNum = Pipe6[PipeIndex];
	PipeIndex += 1;
	VaildNum = pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalNum;
	for(Index = 0 ; Index < 16; Index++)
	{
		if(Index < VaildNum)
		{
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalType_E = Pipe6[PipeIndex];
						
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[0] = Pipe6[PipeIndex];
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[1] = Pipe6[PipeIndex];
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[2] = Pipe6[PipeIndex];
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[3] = Pipe6[PipeIndex];
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[4] = Pipe6[PipeIndex];
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[5] = Pipe6[PipeIndex];
			PipeIndex += 1;								
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNo = 
							Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
			PipeIndex += 2;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].RelativeDist = 
							Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
			PipeIndex += 2;
		}
		else
		{
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalType_E = 0;
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[0] = 0;
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[1] = 0;
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[2] = 0;
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[3] = 0;
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[4] = 0;
			PipeIndex += 1;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNoHead[5] = 0;
			PipeIndex += 1;								
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].SignalNo = 0;

			PipeIndex += 2;
			pA2AInputPara->BasicData.ForwardRailLineData.FWSignalInfo.SignalInfo[Index].RelativeDist = 0;
			PipeIndex += 2;
		}
	
	}
	
#if 0	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.ForwardRailLineData.FWRamps.Ramps[Index] = Pipe6[PipeIndex];
		PipeIndex +=2;
	}
#endif
	pA2AInputPara->BasicData.ForwardRailLineData.FWTunnels.TunnelValidNum =
			Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
	PipeIndex +=2;
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.ForwardRailLineData.FWTunnels.Tunnel[Index].TunnelLenth = 
				Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
		PipeIndex +=2;
		pA2AInputPara->BasicData.ForwardRailLineData.FWTunnels.Tunnel[Index].TunnelRelatDist = 
				Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
		PipeIndex +=2;
	}
			
	pA2AInputPara->BasicData.ForwardRailLineData.FWBlocksInfo.Num = Pipe6[PipeIndex];
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.ForwardRailLineData.FWBlocksInfo.BlockInfo[Index].BlockFlag = 
				Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
		PipeIndex +=2;
		
		pA2AInputPara->BasicData.ForwardRailLineData.FWBlocksInfo.BlockInfo[Index].BlockRelatDist = 
				Comn_F_GetUINT16(Pipe6[PipeIndex],Pipe6[PipeIndex+1]);
		
		PipeIndex +=2;
		pA2AInputPara->BasicData.ForwardRailLineData.FWBlocksInfo.BlockInfo[Index].BlockLength =
				Comn_F_GetUINT32(Pipe6[PipeIndex],
									Pipe6[PipeIndex+1],
									Pipe6[PipeIndex+2],
									Pipe6[PipeIndex+3]);
		PipeIndex +=4;
	}
	
	/*参考曲线未解析*/
	return e_TRUE; 
}
/******************************************************************************
 *Name    : ACS_Data_pipe7_Analyze
 *Function: 解析管道7的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe7_Analyze(UINT8 *Pipe7,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	UINT16 PipeIndex = 0;
	UINT16 VaildNum  = 0;
	UINT16 Index 	 = 0;

	PipeIndex = 23;
	pA2AInputPara->BasicData.TrainTimeTable.ValidNum = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeHour[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeHour[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeHour[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeHour[3] = Pipe7[PipeIndex];
	PipeIndex += 1;

	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeMin[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeMin[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeMin[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeMin[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeSec[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeSec[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeSec[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.AddOnTimeSec[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeHour[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeHour[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeHour[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeHour[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeMin[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeMin[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeMin[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeMin[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeSec[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeSec[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeSec[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalTimeSec[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeHour[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeHour[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeHour[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeHour[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeMin[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeMin[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeMin[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeMin[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeSec[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeSec[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeSec[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ArrivedTimeSec[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeHour[0] = Pipe7[PipeIndex];
	PipeIndex += 1;	
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeHour[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeHour[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeHour[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeMin[0] = Pipe7[PipeIndex];
	PipeIndex += 1;	
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeMin[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeMin[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeMin[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeSec[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeSec[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeSec[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.StartTimeSec[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeHour[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeHour[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeHour[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeHour[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeMin[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeMin[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeMin[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeMin[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeSec[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeSec[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeSec[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.SuspendTimeSec[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
/*	
	pA2AInputPara->BasicData.TrainTimeTable.ResBytes[0] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ResBytes[1] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ResBytes[2] = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	pA2AInputPara->BasicData.TrainTimeTable.ResBytes[3] = Pipe7[PipeIndex];
	PipeIndex += 1;
*/	
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalASpeed[0] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalASpeed[1] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalASpeed[2] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalASpeed[3] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalCourse[0] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalCourse[1] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalCourse[2] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.IntervalCourse[3] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationRouteNo[0] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationRouteNo[1] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationRouteNo[2] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationRouteNo[3] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationSN[0] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationSN[1] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationSN[2] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.CurStationSN[3] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationRouteNo[0] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationRouteNo[1] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;	
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationRouteNo[2] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationRouteNo[3] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationSN[0] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationSN[1] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationSN[2] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	pA2AInputPara->BasicData.TrainTimeTable.NextStationSN[3] = 
			Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
	PipeIndex += 2;
	
	if(PipeIndex != 132)
	{
		printf("Err_p7");
	}
	PipeIndex +=3;
	
	pA2AInputPara->BasicData.SpecialZoneData.ValidNum = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.SpecialZoneData.SpecialAreaCode[Index]= Pipe7[PipeIndex];
		PipeIndex +=1;	
	}
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.SpecialZoneData.Mark[Index]= Pipe7[PipeIndex];
		PipeIndex +=1;	
	}
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.SpecialZoneData.Relative_Distance[Index] = 
				Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
		PipeIndex +=2;
	}
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.SpecialZoneData.MininumSpeed[Index] = 
				Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
		PipeIndex +=2;
	}	
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.SpecialZoneData.ZoneLength[Index] = 
				Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
		PipeIndex +=2;
	}
	
	for(Index = 0; Index < 30 ; Index++)
	{
		pA2AInputPara->BasicData.SpecialZoneData.Res[Index] = 
				Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
		PipeIndex +=2;
	}
	
	if(PipeIndex != 496)
	{
		printf("Err_p7_01");
	}
	PipeIndex += 3;
	
	pA2AInputPara->BasicData.SideTrackInfo.ValidNum = Pipe7[PipeIndex];
	PipeIndex += 1;
	
	for(Index = 0; Index < 50 ; Index++)
	{
		pA2AInputPara->BasicData.SideTrackInfo.SideTrackSN[Index] = Pipe7[PipeIndex];
		PipeIndex += 1;
	}
	
	for(Index = 0; Index < 50 ; Index++)
	{
		pA2AInputPara->BasicData.SideTrackInfo.Res[Index] = Pipe7[PipeIndex];
		PipeIndex += 1;
	
	}
	
	for(Index = 0; Index < 50 ; Index++)
	{
		pA2AInputPara->BasicData.SideTrackInfo.ValidTrackLength[Index] = 
				Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
		PipeIndex += 2;
	}
	
	for(Index = 0; Index < 50 ; Index++)
	{
		pA2AInputPara->BasicData.SideTrackInfo.StopLocToFSignal[Index] = 
				Comn_F_GetUINT16(Pipe7[PipeIndex],Pipe7[PipeIndex+1]);
		PipeIndex += 2;
	}
	/*时间戳*/
	PipeIndex = 809;
	pA2AInputPara->SpecialData.TimeDate.Year_TimeDate.Year    = Pipe7[PipeIndex];
	PipeIndex += 1;

	pA2AInputPara->SpecialData.TimeDate.Year_TimeDate.Month   = Pipe7[PipeIndex];
	PipeIndex += 1;

	pA2AInputPara->SpecialData.TimeDate.Year_TimeDate.Day     = Pipe7[PipeIndex];
	PipeIndex += 1;

	pA2AInputPara->SpecialData.TimeDate.Year_TimeDate.Hour    = Pipe7[PipeIndex];
	PipeIndex += 1;

	pA2AInputPara->SpecialData.TimeDate.Year_TimeDate.Minutes = Pipe7[PipeIndex];
	PipeIndex += 1;

	pA2AInputPara->SpecialData.TimeDate.Year_TimeDate.Second  = Pipe7[PipeIndex];
	PipeIndex += 1;

		/*时间戳计算*/
	Comn_F_Date2Stamp(&(pA2AInputPara->SpecialData.TimeDate.Year_TimeDate)
					,&(pA2AInputPara->SpecialData.TimeDate.SecondTime));


	return e_TRUE;
}
