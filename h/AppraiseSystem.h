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
#ifndef ACS_APPRAISE_SYSTEM_H_
#define	ACS_APPRAISE_SYSTEM_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
//#include "AppraisePara.h"
//#include "Appraise_BasicFunction.h"
#include "../h/Appraise_Sense.h"
#include "../h/Appraise_Clac.h"
#include "../h/Appraise_Clac_Grade.h"
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
 *Name    : ACS_DriveAppraise_InitPro
 *Function: ������ʼ��
 *Para    :// S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02     create
******************************************************************************/
E_SysBool  ACS_DriveAppraise_InitPro(S_ATO2ACS_INPUTPARA* pA2AInputPara,
									S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade,
									S_KERNEL_SENSEDATA* pSenseData,
									S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									UINT8 Buffer[][1400]);
/******************************************************************************
 *Name    : ACS_UDP_RecvData
 *Function: ���ݽ���
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/24      create
******************************************************************************/
E_SysBool  ACS_UDP_RecvData(UINT8 buffer[][1400]);
/******************************************************************************
 *Name    : ACS_Data_ATO2ACS_Analyze
 *Function: ����ATO������������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/03/14      create
******************************************************************************/
E_SysBool  ACS_Data_ATO2ACS_Analyze(UINT8 Buffer[][1400],
									S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_DataSense
 *Function: ���ݸ�֪������ʶ��
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/25      create
******************************************************************************/
E_SysBool  ACS_DataSense(const S_ATO2ACS_INPUTPARA*  const pA2AInputPara,
						 S_KERNEL_SENSEDATA*  const pSenseDataIn);
/******************************************************************************
 *Name    : ACS_ParaCalc
 *Function: ָ�����
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/24      create
******************************************************************************/
E_SysBool  ACS_ParaCalc(S_ATO2ACS_INPUTPARA* pA2AInputPara,
						S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
						S_KERNEL_SENSEDATA*   pSenseData);
/******************************************************************************
 *Name    : ACS_CalcResultStoreAndRead
 *Function: ��������ȡ
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/24      create
******************************************************************************/
E_SysBool  ACS_CalcResultStoreAndRead(S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
									S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade);
/******************************************************************************
 *Name    : ACS_DriveAppraise
 *Function: ����
 *Para    : S_PLAN_OUTPUTDATA* con[]st pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/14      create
******************************************************************************/
E_SysBool  ACS_DriveAppraise(S_AUTOINDICATORSCALCRESULT* pAtIndClcRslt,
							 S_ALL_FEEDBACK_GRADE* pFeedBackGradeOut);

/******************************************************************************
 *Name    : ACS_Data_Feedback
 *Function: ���ݷ���
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02      create
******************************************************************************/
E_SysBool  ACS_Data_Feedback2ATO(S_ALL_FEEDBACK_GRADE* pAllFeedBackGrade);

/******************************************************************************
 *Name    : ACS_DriveAppraise_Main
 *Function: ������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/07/02      create
******************************************************************************/
E_SysBool  ACS_DriveAppraise_Main();
#endif
