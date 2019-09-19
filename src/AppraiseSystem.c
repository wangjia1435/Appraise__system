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
//#include "../AppraiseSyetem/GL_Basic_Type_Definition.h"
#include "../h/Appraise_Data_Analyze.h"
#include "../h/AppraiseSystem.h"
//#include "../AppraiseSyetem/Appraise_Clac_Grade.h"

#if 1
//#include <winsock2.h>

//#include ""
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../h/Appraise_network.h"
//#include <netinet/in.h>
//#include <sys/socket.h>
//#include <dirent.h>
//#include <signal.h>
//#include <malloc.h>
//#include <sys/stat.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//#include <custFtpd_api.h>
//#include <custFtpClnt_api.h>
//#include <ocs_trdp_api.h>
#endif

/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/

/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
 /******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/
UINT32 g_cycleTIme = 0;

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/
/******************************************************************************
 *Name    : ACS_DriveAppraise_InitPro
 *Function: 函数初始化
 *Para    :// S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02     create
******************************************************************************/
E_SysBool  ACS_DriveAppraise_InitPro(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade,
									S_KERNEL_SENSEDATA* pSenseData,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt)
{
	
	Comn_F_MemSet((void *)(pA2AInputPara),
					          0,sizeof(S_ATO2ACS_INPUTPARA));
	Comn_F_MemSet((void *)(pAllFeedBackGrade),
					          0,sizeof(S_ALL_FEEDBACK_GRADE));

	Comn_F_MemSet((void *)pSenseData,
					          0,sizeof(S_KERNEL_SENSEDATA));
	Comn_F_MemSet((void *)pAtIndClcRslt,
					          0,sizeof(S_AUTOINDICATORSCALCRESULT));
	//printf("/%d %d %d",Buffer[0][0],Buffer[0][1],Buffer[0][2]);

	return e_TRUE;

}
/******************************************************************************
 *Name    : ACS_UDP_RecvData
 *Function: 数据接收
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/24      create
******************************************************************************/
E_SysBool  ACS_UDP_RecvData(UINT8 buffer[][1400])
{
#if 0
	int recvSocket;
	struct sockaddr_in recvAddr;
	int localPort = 5000;
	int result = 0;
	//int buffer[8][1400];
	UINT8 i=0;
    struct sockaddr_in  tempSockAddr;
    //unsigned int addrLen = sizeof(tempSockAddr);
    unsigned int addrLen = sizeof(recvAddr);
    
    recvSocket = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&recvAddr, 0,sizeof(struct sockaddr_in));
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_addr.s_addr = inet_addr("192.168.50.105");
	recvAddr.sin_port = htons(localPort);
	bind(recvSocket, (struct sockaddr*)&recvAddr, sizeof(struct sockaddr_in));
	memset(buffer[0], 0, sizeof(buffer[0]));
	for(i=0;i<8;i++)
	{
		recvfrom(recvSocket, buffer[i], sizeof(buffer[i]), 0, 
					(struct sockaddr *)&recvAddr, (&addrLen));
	}
#endif
	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_Data_ATO2ACS_Analyze
 *Function: 解析ATO发过来的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/03/14      create
******************************************************************************/
E_SysBool  ACS_Data_ATO2ACS_Analyze(UINT8 Buffer[][1400],
									S_ATO2ACS_INPUTPARA* pA2AInputPara)
{
	/*数据解析，管道0~7*/
	ACS_Data_pipe0_Analyze(Buffer[0],pA2AInputPara);
	ACS_Data_pipe1_Analyze(Buffer[1],pA2AInputPara);
	ACS_Data_pipe2_Analyze(Buffer[2],pA2AInputPara);
	ACS_Data_pipe3_Analyze(Buffer[3],pA2AInputPara);
	ACS_Data_pipe4_Analyze(Buffer[4],pA2AInputPara);
	ACS_Data_pipe5_Analyze(Buffer[5],pA2AInputPara);
	ACS_Data_pipe6_Analyze(Buffer[6],pA2AInputPara);
	ACS_Data_pipe7_Analyze(Buffer[7],pA2AInputPara);
	
	/*数据接收总周期数*/
	pA2AInputPara->SpecialData.DynDate.Total_Dyn_Num +=1;

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_DataSense
 *Function: 数据感知与规则库识别
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/25      create
******************************************************************************/
E_SysBool  ACS_DataSense(const S_ATO2ACS_INPUTPARA*  const pA2AInputPara,
						 S_KERNEL_SENSEDATA*  const pSenseDataIn)
{

	/*内部防护曲线计算*/
	if(e_FALSE == LkjSpd2InterSpd(&(pA2AInputPara->DynaData.LkjProjectCurve),pSenseDataIn))
	{
		return e_FALSE;
	}


	/*获取机车参数数据*/
	if(e_FALSE == Atoalgo_Sense_LocolData(&(pA2AInputPara->DynaData),
							&(pA2AInputPara->BasicData.ForwardRailLineData),
							pSenseDataIn))
	{
		return e_FALSE;
	}


	/*获取机车辆数数据*/
	if(e_FALSE == Atoalgo_Sense_TrainData(&(pA2AInputPara->DynaData),
							&(pA2AInputPara->BasicData.ForwardRailLineData),
							pSenseDataIn))
	{
		return e_FALSE;
	}
	

	/*获取机车LKJ信号相关数据*/
	if(e_FALSE == Atoalgo_Sense_LocoSignal(&(pA2AInputPara->DynaData),
						   &(pSenseDataIn->LocoSignalData)));
	{
		return e_FALSE;
	}
	
	/*步长，车长计算*/
	if(e_FALSE == Atoalgo_Plan_StrategyCalc(pSenseDataIn,
							  &(pSenseDataIn->AlgoStrategyCtrlData)))
	{
		return e_FALSE;
	}


	/*坡道加算*/
	if(e_FALSE == Atoalgo_Sense_RailLineClac(&(pA2AInputPara->BasicData.ForwardRailLineData),pSenseDataIn))
	{
		return e_FALSE;
	}
	
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_ParaCalc
 *Function: 指标计算
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/24      create
******************************************************************************/
E_SysBool  ACS_ParaCalc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
						S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
						S_KERNEL_SENSEDATA*   pSenseData)
						//S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade)
{
	//
	ACS_DriveAppraiseClac_A(pA2AInputPara,pAtIndClcRslt,pSenseData);
	
	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_CalcResultStoreAndRead
 *Function: 计算结果存取
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/24      create
******************************************************************************/
E_SysBool  ACS_CalcResultStoreAndRead(S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade)
{

	return e_TRUE;
}
/******************************************************************************
 *Name    : ACS_DriveAppraise
 *Function: 评分
 *Para    : S_PLAN_OUTPUTDATA* con[]st pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/14      create
******************************************************************************/
E_SysBool  ACS_DriveAppraise(S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
							 S_ALL_FEEDBACK_GRADE* pFeedBackGradeOut)
{
#if 0
	if()
	{
	Auto_DriveAppraise();
	}
	else
	{
	Manul_DriveAppraise();
	}
#endif
	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_Data_Feedback
 *Function: 数据反馈
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02      create
******************************************************************************/
E_SysBool  ACS_Data_Feedback2ATO(S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade)
{
	return e_TRUE;
}

/******************************************************************************
 *Name    : ACS_DriveAppraise_Main
 *Function: 主函数
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02      create
******************************************************************************/
E_SysBool  ACS_DriveAppraise_Main(int a)
{
	S_ATO2ACS_INPUTPARA  pA2AInputPara;
	S_ALL_FEEDBACK_GRADE pAllFeedBackGrade;
	S_KERNEL_SENSEDATA   pSenseData;
	S_AUTOINDICATORSCALCRESULT pAtIndClcRslt;

	UINT8 buffer[1400];
	UINT32 rcvLen = 0;
	UINT32 rcvSocketFd = 0;
	struct sockaddr_in myAddr = { 0, };
	struct sockaddr_in rcvAddr = { 0, };
	printf("enter appraise system\n");

	/* socket初始化*/
	if (e_FALSE == Net_SocketInit("172.20.10.2", 5000, &rcvSocketFd, &myAddr))
	{
		return e_FALSE;
	}

	/*数据初始化*/
	if(e_FALSE == ACS_DriveAppraise_InitPro(&pA2AInputPara,&pAllFeedBackGrade,&pSenseData,&pAtIndClcRslt))
	{
		return e_FALSE;
	}

	while(1)
	{
		printf("g_cycle_time=%d\n", g_cycleTIme++);
		sleep(1);
		/*数据接收*/
		if (e_FALSE == Net_SocketRcv(rcvSocketFd, &rcvAddr, buffer, &rcvLen))
		//if(e_FALSE == ACS_UDP_RecvData(Buffer))
		{
			//return e_FALSE;
			//continue;
		}

		/*解析ATO发过来的数据*/
		if(e_FALSE == ACS_Data_ATO2ACS_Analyze(Get_RecvPipeBuffer(),&pA2AInputPara))
		{
			//return e_FALSE;
			//continue;
		}

		/*数据感知与规则库识别*/
		if(e_FALSE == ACS_DataSense(&pA2AInputPara,&pSenseData))
		{
			//return e_FALSE;
			//continue;
		}
		 
		/*各项指标计算*/
		if(e_FALSE == ACS_ParaCalc(&pA2AInputPara,&pAtIndClcRslt,&pSenseData))
		{
			//return e_FALSE;
			//continue;
		}

		/*指标数据存取*/
		if(e_FALSE == ACS_CalcResultStoreAndRead(&pAtIndClcRslt,&pAllFeedBackGrade))
		{
			//return e_FALSE;
			//continue;
		}

		/*评分计算*/
		if(e_FALSE == ACS_DriveAppraise(&pAtIndClcRslt,&pAllFeedBackGrade))
		{
			//return e_FALSE;
			//continue;
		}

		/*驾驶评价反馈*/
		if(e_FALSE == ACS_Data_Feedback2ATO(&pAllFeedBackGrade))
		{
			//return e_FALSE;
			//continue;
		}
		
	}
	return e_TRUE;
}

int main()
{
	ACS_DriveAppraise_Main(0);
	return 0;
}


