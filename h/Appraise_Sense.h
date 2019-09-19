/******************************************************************************
 *File Name	     :	atoalgo_sense.h
 *Copyright	     :	Zhuzhou CRRC Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/08/12 
 *Description    :	atoalgo_sense H file.
 *Modification history:
 *REV1.0.0    Tangwei     2019/08/12  File Create 
 ******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef _ATOALGO_SENSE_H_
#define _ATOALGO_SENSE_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/Appraise_Data_Analyze.h"
//#include "../math/atoalgo_math_calculate.h"
//#include "../sense/atoalgo_sense_signal.h"
/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/

#define LINECALCLNUMS				(200U)			/*�µ������ܼ������*/

#define GRAVIT_ACCELERATION         (9.81F)   		/*�������ٶ�*/

#define SENSE_POINT_MAX_NUM			(50U)			/*��ǵ�������*/
#define SENSE_CHGPNT_MAX_NUM		(200U)			/*��ǵ�������*/

#define NEUTRAL_POINT_MAX_NUM       (10U)			/*�����ǵ�������*/
#define BRAKETEST_POINT_MAX_NUM     (5U)			/*��ͨ�����ǵ�������*/
#define STOPBEFNEU_POINT_MAX_NUM    (5U)			/*����ǰͣ����������*/
#define STOPBEHNEU_POINT_MAX_NUM    (5U)			/*�����ͣ����������*/
#define PASSMARKSTOP_POINT_MAX_NUM  (20U)			/*����ͣ����������*/

#define SENSE_SLAVELOCO_MAX_NUM     (3U)            /*�ӿػ������������*/
#define TARGETLINE_MAX_NUM          (20U)           /*Ŀ�����ߵ��������*/

#define LOCO_UNITTRAIN_CHNGTIME     (5U)            /*����/��Ԫ�г�����ת��ʱ��*/
#define HEAVYTRAIN_CHNGTIME         (10U)           /*���/�����г�����ת��ʱ��*/

/*UINT���͵ĳ�ʼ��ֵ*/
#define c_UintInitValue            (0U)
/*INT���͵ĳ�ʼ��ֵ*/
#define c_IntInitValue             (0L)
/*��������ǣ�����������ı�ֵ(Ԥ��100)*/
#define c_TracResiRatio            (130U)

/*2019-1-16 ������TangWei����ǵ�������*/
#define	BADGE_POINT_MAX_NUM 			(30U)
#define	RAILLINE_BADGEPOINT_MAX_NUM		(30U)

/*���µ�ʹ�ò���*/
#define ALGO_SENSE_DIFFVALUE		(3.0F)			/*���ڸ�ֵ��Ϊ����*/
#define ALGO_SENSE_JUDGE_NUM		(10U)			/*����JUDGE_NUM+2��ֵ����DIFF_VALUE��Ϊ����*/
/*��������ʹ�ò���*/
#define SPD_STOP_POINT_PRE_DIS		(150U)			/*ͣ��������ǰ����,��λm*/
#define SPD_DOWN_POINT_PRE_DIS		(100U)			/*���ٽ�����ǰ����,��λm*/
#define SPD_UP_POINT_DELY_DIS		(100U)			/*���ٽ�����ǰ����,��λm*/
#define LKJ_SPD_CHG_MAX_NUM			(20U)			/*�������߱仯�������ֵ*/
/*�������ϵ��*/
#define ALGO_SENSE_CURVE_PARA		(600U)			
/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
/*�г����鶨��*/
typedef enum TAG_ConsistType
{
	e_OnlyLoco    	  = 0x10,                  /*������*/
	e_OneTrian   	  = 0x11,                  /*С��*/
	e_OneOneTrain     = 0x22,                  /*1+1*/
	e_TwoZeroTrain    = 0x33,                  /*2+0*/
	e_TwoOneTrain     = 0x44,                  /*2+1*/
	e_ThreeZeroTrain  = 0x55,                  /*3+0*/
	e_TwoTwoTrain     = 0x66                   /*2+2*/
}E_MODEL_CONSISTTYPE;

/*��������*/
typedef enum TAG_VehicleType
{
	e_CNONE    	  = 0x00,                  /*0x00��XX*/
	e_C64    	  = 0x11,                  /*0x11��C64*/
	e_C70   	  = 0x22,                  /*0x22��C70*/
	e_C80   	  = 0x33                   /*0x33��C80*/
}E_MODEL_VEHICLETYPE;

/*��β����*/
typedef enum TAG_EOTType
{
	e_CtrlEOT    	  = 0xA5,                  /*��β����:0xA5���ɿ���β*/
	e_NomlEOT   	  = 0x5A                   /*0x5A����ͨ��β*/
}E_MODEL_EOTTYPE;
#if 1
/*���ٱ仯��ʶ*/
typedef enum TAG_SpdChngType
{
	e_NormalSpdPt     = 0x00,                                           /*LKJ�����ޱ仯��*/
	e_SpdRiseStartPt  = 0x11,                                           /*LKJ�����������*/
	e_SpdRiseEndPt    = 0x22,                                           /*LKJ���������յ�*/
	e_SpdDeclStartPt  = 0x33,                                           /*LKJ�����½����*/
	e_SpdDeclEndPt    = 0x44,                                           /*LKJ�����½��յ�*/
    /*2019.01.04������YipingYang���������������㡢�½���ķ����ʶ*/
	e_SpdRisePt       = 0x55,                                           /*LKJ����������*/
	e_SpdDeclPt       = 0x66                                            /*LKJ�����½���*/
}E_SENSE_SPDCHNGTYPE;

/*2019-1-15 ������TangWei����ǵ�����ö��*/
typedef enum TAG_BadgeType
{
	e_SpdUpPnt			 = 0x01,   				/*���ٱ�ǵ�*/
	e_SpdDwPnt			 = 0x02,   				/*���ٱ�ǵ�*/
	e_NuetralPnt		 = 0x03,   				/*�����ǵ�*/
	e_BrkTestPnt		 = 0x04,   				/*��ͨ�����ǵ�*/
	e_NormalStopPnt	 	 = 0x05,   				/*����ͣ����ǵ�*/
	e_OutSideStopPnt	 = 0x06,   				/*����ͣ����ǵ�*/
	e_FrontNutrlStopPnt  = 0x07,   				/*����ǰͣ����ǵ�*/
	e_BehindNutrlStopPnt = 0x08,   				/*�����ͣ����ǵ�*/
	e_BigUpRampNuetralPnt  = 0x09,   			/*�����µ�������*/
	e_BigDwRampPnt		   = 0x0A,				/*����������ʼ��ǵ�*/
	e_MinLimitPnt          = 0x0B               /*�źŻ��������*/
}E_BADGETYPE;
#endif
/*�������α�ʶ*/
typedef enum TAG_E_SpecialAreaCode
{
  e_NuetralArea       = 0x88U,        /*��������*/
  e_SandArea          = 0x89U,        /*��ɳ����*/
  e_NoStopArea        = 0x8AU,        /*��ֹͣ������*/
  e_ConstructionArea  = 0x8BU,        /*ʩ������*/
  e_FloodArea         = 0x8CU,        /*��Ѵ�ض�*/  
  e_BrkTestArea       = 0x8DU,        /*��ͨ����*/
  e_BehNuetralArea    = 0x78U,        /*�����ͣ����*/
  e_BefNuetralArea    = 0x79U,        /*����ǰͣ����*/
  e_MinLimitArea      = 0x7AU,        /*�źŻ��������*/
  e_OutsideArea       = 0x7BU,        /*����ͣ����*/
  e_SpeSpeed          = 0x7CU,        /*�����ٶ�����*/
  e_SideTraNoSignal   = 0x7DU         /*���ߵ��������*/
}E_SENSE_SPECIALAREACODE;

/** LKJ����ģʽ */
typedef enum TAG_E_Algo_LKJ_CtrlMode {
  e_Standby      =0x00,														/** ���� */
  e_EntExitDepot =0x02,													    /** ����� */
  e_Shunt        =0x03,														/** ���� */
  e_Degrade      =0x04,														/** ���� */
  e_General      =0x05,														/** ͨ�� */
  e_Visual       =0x06,														/** Ŀ���г� */
  e_RemoteLKJ    =0x07,													    /** �Ǳ��� */
  e_NoAdvance    =0x08,													    /** �޷�ð */
  e_Other        =0x09														/** ������ATP��� */
} E_ALGO_LKJ_CtrlMode;

/** �źŻ����� */
typedef enum TAG_E_Algo_SignalType {
  e_RvSignal                   =0x01,								        /** �ӳ���·�ź� */
  e_EnterSignal                =0x02,								        /** ��վ�źŻ� */
  e_RvDeSignal                 =0x03,								        /** �ӷ�����·�źŻ� */
  e_DepartSiganl               =0x04,								        /** ������·�źŻ� */
  e_ExitSignal                 =0x05,								        /** ��վ�źŻ� */
  e_PassedSignal               =0x06,								        /** ͨ���źŻ� */
  e_PermitSignal               =0x07,								        /** �����źŻ� */
  e_ApproachSignal             =0x08,								        /** �ӽ��źŻ� */
  e_AdvancedSignal             =0x09,								        /** Ԥ���źŻ� */
  e_SplittedSignal             =0x0A,								        /** �ָ��źŻ� */
  e_LineLocationPassedSignal   =0x0B,								        /** ��·��ͨ���źŻ� */
  e_WaistSwitchSignal          =0x0C,								        /** �����źŻ� */
  e_LabelSignal                =0x28								        /** �źű�־���źŻ� */
} E_ALGO_SignalType;

/** LKJ15�����ź� */
typedef enum TAG_E_Algo_LocoSignal_15 {
  e_L3         =0x01,														/** ��3�� */
  e_L2         =0x02,														/** ��2�� */
  e_L          =0x03,														/** �̵� */
  e_LU         =0x04,														/** �̻Ƶ� */
  e_LU2        =0x05, 														/** �̻�2�� */
  e_U          =0x06,														/** �Ƶ� */
  e_U2S        =0x07,														/** ��2���� */
  e_U2         =0x08,														/** ��2�� */
  e_L6         =0x09,														/** ��6�� */
  e_UUS        =0x0A,												        /** ˫������ */
  e_UU         =0x0B,														/** ˫�Ƶ� */
  e_HB         =0x0C,													    /** ������� */
  e_HU         =0x0D,														/** ��Ƶ� */
  e_H          =0x0E,														/** ����� */
  e_L4         =0x0F,														/** ��4�� */
  e_L5         =0x10,														/** ��5�� */
  e_257Hz      =0x11,														/** 25.7Hz */
  e_279Hz      =0x12,														/** 27.9Hz */
  e_NoSignal_H =0x13,													    /** ����H�� */
  e_NoSignal_B =0x14,												        /** ����׵� */
  e_U3         =0x15														/** ��3�� */
} E_ALGO_LocoSignal;

/*2019.01.04������TangWei�����µ�ṹ��*/
typedef struct TAG_ChangeRampPoint
{
	UINT8  ChangeRampPointNum;							/*���µ�����*/
	UINT32 ChangeRampPointDis[SENSE_CHGPNT_MAX_NUM];	/*���µ����飬��λm���೵ͷ����*/
	
	/*2019.04.12������TangWei�����µ�����*/
	REAL32 ChangeRampPointAveRamp[SENSE_CHGPNT_MAX_NUM];	/*���µ��¶�ֵ �����㷶ΧΪ�೵ͷ0��ChangeRampPointDis[ChangeRampPointNum-1]��
															(ChangeRampPointAveRamp[0]Ϊ����λ�õ�����Ϊ0�ı��µ���ε�ƽ��ֵ��
			  						  	  	  	  	  	  	 ChangeRampPointAveRamp[1]Ϊ���µ���������Ϊ0������Ϊ1��ε�ƽ��ֵ���Դ�����)*/
	
} S_CHANGERAMPPOINT;

/*20190305������zxm�������µ����ݽṹ*/
typedef struct TAG_LongRampInf
{
	E_SysBool IsExistLongRamp;							/*�Ƿ���ڳ����µ���e_TRUEΪ���ڣ�e_FALSEΪ������*/
	E_SysBool IsAccessInRamp;							/*�Ƿ��ڳ����µ���,e_TRUEΪ�ڳ����µ��У�e_FALSEΪ����*/
	UINT16    PosFromLoco;								/*�����µ���ʼλ�ã����복ͷ*/
	UINT16    PosEndFromLoco;							/*�����µ�����λ�ã����복ͷ*/
	INT16     RampValue;								/*�����µ�ƽ��ֵ*/
	UINT8     RampType;									/*�µ����ͣ�0Ϊ�������£�1λ��������*/
}S_LONGRAMPINF;

/**2019.01.04������TangWei����·���ݴ�����*/
typedef struct TAG_RaillineCalc
{
	REAL32 RailAddRes[LINECALCLNUMS];					/*��·��λ������������λ1=1N/KN*��
														      ��������Ϊ50���복ͷ85m��Ϊ RailAddRes[1]*/
	S_CHANGERAMPPOINT ChangeRampPointStr;				/*���µ�ṹ��*/
	S_LONGRAMPINF	  longRamp;						    /*�����µ�*/
} S_RAILLINECALC_RESULT;


/*2019-1-28ɾ��TAG_StopPoint��TAG_SpeedDownPoint��TAG_SpeedUpPoint��ΰ*/



/*������������Ϣ*/
typedef struct TAG_NeutralInfo
{
	UINT16	    MininumSpeed;			/*������������ٶ�*/
	UINT16	    Neutral_BgnPntDis;		/*�������ο�ʼ���0��λ�ã���λm*/
	UINT16	    ZoneLength;		        /*�������γ��ȣ���λm*/
} S_NEUTRAL_INFO;

typedef struct TAG_NeutralPoint
{
	E_BADGETYPE      BadgeType;
	UINT16	         NeutralNum;		/*�������θ���*/
	S_NEUTRAL_INFO	 NeutralInfo[NEUTRAL_POINT_MAX_NUM];		
} S_NEUTRAL_POINT;

/*��ͨ��������Ϣ*/
typedef struct TAG_BrakeTestInfo
{
	UINT8      Mark;                    /*��־*/
	UINT16	   MininumSpeed;			/*��ͨ��������ٶ�*/
	UINT16	   BrakeTest_BgnPntDis;	    /*��ͨ���鿪ʼ���0��λ�ã���λm*/
	UINT16	   ZoneLength;	            /*��ͨ���鳤�ȣ���λm*/
	UINT8      DoBrakeTestFlag;         /*������բ��־,1:������բ*/
} S_BRAKETEST_INFO;

typedef struct TAG_BrakeTestPoint
{
	E_BADGETYPE       BadgeType;
	UINT16	          BrakeTestNum;		/*��ͨ�������*/
	S_BRAKETEST_INFO  BrakeTest_Info[BRAKETEST_POINT_MAX_NUM];	
} S_BRAKETEST_POINT;

/*����ǰͣ��������Ϣ*/
typedef struct TAG_STOPBEFNEUInfo
{
	UINT8      Mark;                    /*��־*/
	UINT16	   StopBefNeu_BgnPntDis;	/*����ǰͣ�����0��λ�ã���λm*/
	UINT16	   StopFlag;	            /*1���Ƶ�ͣ��*/
} S_STOPBEFNEU_INFO;

typedef struct TAG_StopBefNeuPoint
{
	E_BADGETYPE        BadgeType;
	UINT16	           StopBefNeuNum;		/*����ǰͣ�������*/
	S_STOPBEFNEU_INFO  StopBefNeu_Info[STOPBEFNEU_POINT_MAX_NUM];	
} S_STOPBEFNEU_POINT;

/*�����ͣ������Ϣ*/
typedef struct TAG_StopBehNeuPoint
{
	E_BADGETYPE BadgeType;
	UINT16	   StopBehNeuNum;		/*�����ͣ�������*/
	UINT16     StopBehNeuRelaDist[STOPBEHNEU_POINT_MAX_NUM];	
} S_STOPBEHNEU_POINT;

/*����ǰ/��ͣ�����0�����*/
typedef struct TAG_StopNeuRelaDist
{
	
	UINT32		 StopBeh_NeuRelaDist[RAILLINE_BADGEPOINT_MAX_NUM];				/*�����ͣ�����0��λ�ã���λm*/
	UINT32		 StopBef_NeuRelaDist[RAILLINE_BADGEPOINT_MAX_NUM]; 				/*����ǰͣ�����0��λ�ã���λm*/	
	
} S_STOP_NEU_RELA_DIST;

/*����ͣ������Ϣ*/
typedef struct TAG_PassMarkStopInfo
{
	E_BADGETYPE BadgeType;
	UINT8  SideTrackSN;            					/*���߹����*/
	UINT16 ValidTrackLength;	      				/*������Ч����*/				 
	UINT16 StopLocToFSignal;       					/*ͣ��λ�þ���ǰ���źŻ�����*/		
} S_PASSMARKSTOP_INFO;

typedef struct TAG_PassMarkStopPoint
{
	E_BADGETYPE BadgeType;
	UINT16	             PassMarkStopNum;		    /*����ͣ�������*/
	S_PASSMARKSTOP_INFO  PassMarkStop_Info[PASSMARKSTOP_POINT_MAX_NUM];	
} S_PASSMARKSTOP_POINT;
#if 0
/*�������߱�ǵ�__�滮����ʶ����-��ΰ*/
typedef struct TAG_SpdLimitBadgePoint
{
//	S_STOP_POINT 			StopPoint;			/*ͣ����*/
//	S_SPEED_DOWN_POINT		SpdDwPnt;			/*�޶��½���*/
//	S_SPEED_UP_POINT		SpdUpPnt;			/*����������*/
} S_BADGEPOINT,S_SPDLIMIT_BADGEPOINT;
#endif
/*��·��Ϣ���_�滮����ʶ����-������
 * �������ٱ�ǵ㣺
 * �ٶ���������RelDistance���������λ�ã�MinSpeed����������ٶȣ�MaxSpeed�������յ��ٶ�
 * �ٶ��½�����RelDistance���½��յ�λ�ã�MinSpeed���½��յ��ٶȣ�MaxSpeed���½�����ٶ�*/
typedef struct TAG_RailLineInfoBadgePoint{
	UINT8  		 ValidNum;   						                            /*��Ч����*/
	/*2019.01.23 YipingYang��������������Ա*/
	UINT8        NormalStopPntIndex;                                            /*����ͣ���������ֵ,
																				��������ͣ����ʱ��Ч*/
	E_SysBool    ExistNormalStopPnt;                                            /*��������ͣ����Ϊe_TRUE*/
	E_BADGETYPE  BadgeType[RAILLINE_BADGEPOINT_MAX_NUM];         			    /*��·�������*/
	UINT16 		 RelDistance[RAILLINE_BADGEPOINT_MAX_NUM];				        /*��0�����*/ 
	UINT16 		 MinSpeed[RAILLINE_BADGEPOINT_MAX_NUM];           			    /*�������*/
	UINT16 		 MaxSpeed[RAILLINE_BADGEPOINT_MAX_NUM];           			    /*�������*/
 	UINT16 		 ZoneLength[RAILLINE_BADGEPOINT_MAX_NUM];              			/*���γ���*/
	UINT16       Res[RAILLINE_BADGEPOINT_MAX_NUM];                	    		/*Ԥ��*/
}S_RAILLINEINFO_BADGEPOINT;


#if 0
/*��·��Ϣ���_�滮����ʶ����-������*/
typedef struct TAG_RailLineBadgePoint
{	
	S_NEUTRAL_POINT         NeutralPnt;                                /*������*/
	S_BRAKETEST_POINT       BrakeTestPnt;                              /*��ͨ��*/
	S_STOPBEFNEU_POINT      StopBefNeuPnt;                             /*����ǰͣ����*/
	S_STOPBEHNEU_POINT      StopBehNeuPnt;                             /*�����ͣ����*/
	S_PASSMARKSTOP_POINT    PassMarkStopPnt;                           /*����ͣ��λ�þ���ǰ���źŻ�*/
}S_RAILLINE_BADGEPOINT;
#endif
typedef struct TAG_BadgePointSetIndex
{	
	E_BADGETYPE BadgePointType;	/*��ǵ�����*/
	//sUINT16		BadgePointDistance[BADGE_POINT_MAX_NUM];/*��ǵ�೵ͷ���룬��λm*/
	UINT8		Index;			/*��ǵ���Ϣ����������*/
}S_BADGEPOINT_SETINDEX;


/*2019-1-15 ������TangWei����ǵ�����*/
typedef struct TAG_All_BadgePoint
{	
	UINT8		BadgePointVaildNum;						/*��ǵ��ܸ���*/
	//E_BADGETYPE BadgePointType[BADGE_POINT_MAX_NUM];	/*��ǵ�����*/
	//UINT16		BadgePointDistance[BADGE_POINT_MAX_NUM];/*��ǵ�೵ͷ���룬��λm*/
	//UINT8		Index[BADGE_POINT_MAX_NUM];				/*��ǵ���Ϣ����������*/
	S_BADGEPOINT_SETINDEX BadgePointSetIndex[BADGE_POINT_MAX_NUM];
	S_RAILLINEINFO_BADGEPOINT *pRailLineBadgePointInfo;				
//	S_SPDLIMIT_BADGEPOINT *pSpdLimitBadgePointInfo;
}S_ALL_BADGEPOINT;



/*��֪����-�������״̬����-������*/
typedef struct TAG_LocosStatusData
{
	UINT8   RunningStatus;                                 					/*ʵ�ʹ����� Bit0:ʵ�ʹ���-ǣ��,Bit1:ʵ�ʹ���-���ƶ�*/
	UINT8   FltStatus;                               						/*����״̬�ֽڣ�
	                                                                          Bit0����ת/���� 
	                                                                          Bit1�������Խ��� 
	                                                                          Bit2�������Է�����  
	                                                                          Bit3������װ�ù��� 
	                                                                          Bit4��ѹ�������� 
	                                                                          Bit5��LKJ���� 
	                                                                          Bit6����β����  
	                                                                          Bit7 ��������ʧ*/

	UINT8   LocoStatus;														/*����״̬�ֽڣ�Bit0�����ϱպ�״̬ Bit1���յ����ϸ��� Bit2���ͷ��ƶ�ʩ��״̬ Bit3�������ƶ�ʩ��״̬ 
	                                                                          Bit4��ͣ���ƶ�����״̬��1=���⣩Bit5:ǣ������ Bit6:���Ʒ���*/
	UINT8   BackOffFlag;                                   					/*�����־:0xA5-����*/
	UINT8   BigBrakePosition;                              					/*��բλ��-Bit0����ת Bit1����С�ƶ� Bit2�������ƶ� Bit3��ȫ�ƶ� Bit4������ Bit5������Bit6�������ƶ� Bit7��Ԥ��*/
	UINT8   SmallBrakePosition;                            					/*Сբλ��-Bit0����ת Bit1���ƶ���  Bit2��ȫ�ƶ� Bit3���������� Bit4��Ԥ��	*/
	UINT8   MotorIsoStatus;													/*Bit0�����ڳ�I�ܵ��1����
																			  Bit1�����ڳ�I�ܵ��2����
																			  Bit2�����ڳ�II�ܵ��1����
																			  Bit3�����ڳ�II�ܵ��2����
																			  Bit4�����ڳ�I�ܵ��1����
																			  Bit5�����ڳ�I�ܵ��2����
																			  Bit6�����ڳ�II�ܵ��1����
																			  Bit7�����ڳ�II�ܵ��2����
																			*/
	UINT16  PressureDecrement;                      						/*��ǰ��ѹ����Kpa��*/
	UINT16  ABHExTargetACK;													/*�г���Ŀ��ֵ��ѹ���趨����*/
	UINT16  IBHExTargetACK;													/*�ƶ���Ŀ��ֵ�趨����*/
	UINT16  PressureTotalVal;                       						/*��ǰ�ܷ��ѹ��*/	
	UINT16  BrakeCylinder;						   							/*��ǰ�ƶ���ѹ��*/	
	UINT16  EqualReservoir; 						   						/*��ǰ������*/	
	UINT16  RateOfFlow;                             						/*�������*/	
	UINT16  PriVolt;														/*����ԭ�ߵ�ѹ��V��0-38000v*/
	UINT16  TcmsSpeed;														/*��ǰTCMS�ٶȣ�1=0.01km/h*/
	UINT16  Force;          							   					/*��ǰʵ��ǣ��/���ƶ� 1=0.1KN*/
	UINT16  TrcFmax;                                   						/*��ǰ�������ǣ����*/	
	UINT16  EBrFmax;                                   						/*��ǰ���������ƶ���*/	
	UINT16  TrcPowerLostPercent;                                   			/*ǣ����������ʧ�ٷֱ�1=0.1%*/	
	UINT16  EBrkPowerLostPercent;                                   		/*������������ʧ�ٷֱ�1=0.1%*/
	/*2019.01.09������YipingYang*/
	UINT16  LocoType;                                                       /*�������ͱ���*/
	UINT16  BrkInitSpeed;                                                   /*�ƶ����ٶȣ�1=0.01km/h*/
	/*2019.01.11������zxm*/
	UINT16  WheelDiameter;													/*�����־�*/	
	UINT16  LkjSpeed;        							   					/*��ǰLKJ�ٶ�*/
	/*2019.03.04,liuyexuan,���������ٶȼ���*/
	UINT16  PreSpdCount;													/*�����ٶȱ仯���õ�������*/
	UINT16  BaseSpd;														/*��3����ǰ�ٶ���Ϊ������ٶȵĻ�׼�ٶ�*/
	UINT16  OrgiSpd;													    /*������ǰ���ٶ�ֵ*/
	UINT16	PreSpd;															/*һ������֮ǰ���ٶ�ֵ*/
	REAL32  SpdChg;															/*�������ڵ��ٶȱ仯��ֵ*/
	REAL32	Acceleration;													/*����ó��ļ��ٶ�ֵ*/
}S_LOCOS_STATUSDATA;


/*��֪����-�������״̬����-������*/
typedef struct TAG_VehiclesStatusData
{
	UINT8   BCUBrakeHandleType;                            					/*բ����*/
	UINT8   BCUPressureType;                              	 				/*��ѹ����*/
	UINT8   TrainLoadType;                                 					/*��������*/
	UINT8   VehicleType;                                   					/*��������*/
}S_VEHICLES_STATUSDATA;

/*��֪����-��β���״̬����-������*/
typedef struct TAG_EotStatusData
{	
	UINT8   TrainTailType;                                 				/*��β����*/
	UINT16  TrainTailValue;                         					/*β����ѹ*/	
}S_EOT_STATUSDATA;

/*��֪����-�����ź��������-������*/
typedef struct TAG_LocoSignalData
{
	UINT8   SingalStatus;                               				/*�ź��쳣״̬�ֽڣ�
																		  Bit0���ź��쳣-�źŻ�ǰ����20km/h
																		  Bit1��--
																		  Bit2��-- 
																		  Bit3��-- 
																		  Bit4��-- 
																		  Bit5��-- 
																		  Bit6��--  
																		  Bit7 ��-*/
	UINT8 	Singal;          									   		/*�����ź�*/
	UINT8 	LKJMode;													/*���״̬*/
	UINT8  	CurrentSideLine;			                                /*����������*/
	UINT8  	NextSideLine;				                                /*�·�������*/
	/*���ӱ�����֧�� ���·���֧�ߺ�*/
	UINT8  	CurrentBranch;			        							/*������֧�� */
	UINT8  	NextBranch;				        							/*�·���֧�� */

}S_LOCOSIGNAL_DATA;

/*��֪����-�г�������Ϣ-������*/
typedef struct TAG_TrainConsistData
{
	E_MODEL_CONSISTTYPE   ConsistType;                                  /*����ģʽ*/
	UINT8   ClosedVehicleNums;                                   		/*���ų�����*/
	UINT8   SleepLocoNums;												/*���һ�������*/
	UINT16  BrkShoePresPHT;												/*ÿ�ٶ�բ��ѹ��*/
	/*2019/03/26��TangWei����*/
	REAL32  ConvertBrakeRate;											/*�г������ƶ���*/
	/*2019/01/09��YipingYang����*/
	UINT8   TrainType;                                                  /*�г�����*/
	UINT16  TrainLength;                                                /*�г��Ƴ�*/
	UINT16	TrainActualLength;											/*�г��ܳ�(��������+��������)*/
	UINT16  LocosWeight;                                                /*��������*/
	UINT16  VehicleWeight;                                              /*�������أ�LKJ��������أ�*/
	UINT16  TrainWeight;												/*�г����أ������ӳ�����*/
	UINT16  LoadWeight;												    /*�г�����*/
	/*�¼�-zxm-2019-1-11*/
	UINT16  VehicleNum;				 									/*��������*/
	UINT16 	HeavyCar;													/*�س�����*/
	UINT16 	EmptyCar;				  									/*�ճ�����*/
	UINT16  LocoNums;													/*��������������������+���һ�������*/
}S_TRAINCONSIST_DATA;

/*��֪����-�������״̬����-������*/
typedef struct TAG_TrainStatusData{
	S_LOCOS_STATUSDATA 	   LocosStatusData;                            /*����״̬����*/
	S_VEHICLES_STATUSDATA  VehiclesStatusData;                         /*����״̬����*/
	S_EOT_STATUSDATA	   EotStatusData;							   /*��β״̬����*/
	S_TRAINCONSIST_DATA    TrainConsistData;                           /*�г���������*/ 
}S_TRAINSTATUSDATA;

/*��֪����-�г���λ����-������*/
typedef struct TAG_TrainLocateData
{	
	UINT32                  Position;   							   /*������Ծ���-��Ի�����·����ʱ����0���λ�þ���*/
	UINT32                  TravlledDistance;                          /*����λ�ƣ��ۼ�λ��,��λ���� */
	UINT16                  NextSigRelaDist;				  		   /*��������һ�źŻ��ľ���*/
	UINT16                  PassSigRelaDist;				  		   /*������Խ���źŻ��ľ���*/
	UINT32                  NextStationRelaDist;                       /*��������һվ�ľ���*/
	UINT32                  PassStationRelaDist;                       /*����Խ����һ��վ����*/
	S_NEUTRAL_POINT         NeutralPnt;                                /*����������*/
	S_BRAKETEST_POINT       BrakeTestPnt;                              /*��ͨ������*/
	S_STOPBEFNEU_POINT      StopBefNeuPnt;                             /*����ǰͣ�������*/
	S_STOPBEHNEU_POINT      StopBehNeuPnt;                             /*�����ͣ�������*/
	S_PASSMARKSTOP_POINT    PassMarkStopPnt;                           /*����ͣ��λ�þ���ǰ���źŻ�����*/
	
	/*����ǰ��ͣ���㣬2019.04.23������Tangwei*/
	S_STOP_NEU_RELA_DIST	StopNeuRelaDist;	
	
}S_TRAIN_LOCATEDATA;

/*��֪����-�㷨����ģʽ��������-������*/
typedef struct TAG_AlgoModeCtrlData
{	
	UINT8   ATOFlag;                                       					/*���������ź�	bit0-�Զ���ʻ����,bit1-�Զ���ʻ���� ,bit2-�Զ�������bit3-ATO�س���bit4-���ؽӹܱ�������*/
	UINT8   DmiCmd;															/*�˻��������Bit0���ϵ�ģʽ  Bit1���㵥ģʽ, Bit2:����ģʽ Bit3: ��ͨ  bit4:�Զ�ģʽ���˹�����   Bit5~Bit7 Ԥ��*/
	UINT8   FastRunTime;													/*����ʱ�䣨min��-˾������*/
	UINT8   SlowRunTime;													/*����ʱ�䣨min��-˾������*/
}S_ALGO_MODECTRLDATA;
typedef struct TAG_AlgoStrategyCtrlData
{
	UINT16  PlanCalcStep;												/*���㲽��*/
	UINT8	TriggerNum;													/*�����滮ֵ*/
	/*2019.03.02 YipingYang�������滮����*/
	UINT16  MaxPlanLen; 												/*���滮����m*/
	E_SysBool IsNeedBkTest;												/*�Ƿ���Ҫ��բ��trueΪ��բ��falseΪ����բ*/
}S_ALGO_STRATEGYCTRLDATA;

/*���ٱ仯�������飬2019.01.04�޸Ķ��壬YipingYang*/
typedef struct TAG_InterProjectInfo
{
	E_SENSE_SPDCHNGTYPE SpdChngType[ALGO_LIMIT_SPEED_NUM_MAX];
	S_LKJ_PROJECTCURVE InterProjectCurve;
}S_INTERPROJECT_INFO;

/*��֪���ݴ�������ݿ�*/
typedef struct TAG_KernelSenseData
{
	S_INTERPROJECT_INFO       InterProjectInfo;                         /*�ڲ�����������Ϣ*/
	S_RAILLINECALC_RESULT     RaillineCalcResult;						/*��·��Ϣ������*/
	/*2019_1_29ɾ��S_BADGEPOINT����ΰ*/
	S_RAILLINEINFO_BADGEPOINT RailLineBadgePointData;					/*��ǵ�����*/
	S_TRAINSTATUSDATA         TrainStatusData;							/*�г�״̬����*/
	S_LOCOSIGNAL_DATA         LocoSignalData;			  				/*�����ź�������ݣ�LKJ��*/
	S_TRAIN_LOCATEDATA        TrainLocateData;                           /*�г���λ����*/
	S_ALGO_MODECTRLDATA       AlgoModeCtrlData;							/*�㷨ģʽ��������*/
	S_ALGO_STRATEGYCTRLDATA	  AlgoStrategyCtrlData;						/*�㷨��������*/
	    
	S_ALGO_INPUT_BASICDATA*  pAlgoInputBasicData;                       /*���������ɾ��---�챣��*/      
}S_KERNEL_SENSEDATA;
/*��¼�����ƶ�״̬*/
#if 1
typedef struct TAG_AirBrkStatus
{
	UINT16      LastPressureDec;       /*����ǰ���г���ѹ��*/
	E_SysBool   AirBrkStatus;
	E_SysBool   AirBrkReleaseStart;
	
}S_ALGO_AIRBRKSTATUS;
#endif
/******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/
 /******************************************************************************
 *Name    : Atoalgo_Math_CalcTrainLength
 *Function: �Գ���ȡ��,��45-51�Գ���ȡ�࣬������С���ֵ
 *Para    : 
 *Return  : ���ؼ����µ�����
 *NOTE    : V1.0.0  	zxm 		 2018/12/25		
******************************************************************************/
UINT16  Atoalgo_Math_CalcTrainLength(UINT16 TrainLength);
  /******************************************************************************
*Name    : Atoalgo_Plan_StrategyCalc
*Function: �滮���Լ��㣬�粽������
*Para    : void
*Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
*NOTE    : V1.0.0  zxm 	 2019/1/10      ��������
******************************************************************************/
E_SysBool Atoalgo_Plan_StrategyCalc(S_KERNEL_SENSEDATA* 		const 	pKernelSenseData,
									S_ALGO_STRATEGYCTRLDATA*    const   pAlgoStrategyCtrlData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcFinalSpd
 *Function: �����������ʼֵ
 *Para    : 
 *Return  : ��ƽ�����ֵ
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.0  tw 		 2018/12/10			modified
******************************************************************************/
REAL32 Atoalgo_Sense_CalcCurveInitAvgValue(const S_TRAINSTATUSDATA* 	const pTrainStatusData,
						   	   	    	   const S_FORWARDRLDATA* 		const pForwardRailLineData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcCurveAvgValue
 *Function: ���������������
 *Para    : 
 *Return  : ����������ƽ�����ֵ
 *NOTE    : V1.0.0  tw 		 2018/12/10			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_CalcCurveAvgValue(const S_TRAINSTATUSDATA*			const pTrainStatusData,
										   const S_ALGO_STRATEGYCTRLDATA*	const pAlgoStrategyCtrlData,
						   	   	    	   const S_FORWARDRLDATA* 			const pForwardRailLineData, 
						   	   	    	   	   	 REAL32*						  AvgCurve);
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
						   	   	   	   	  	    E_SysBool*				    const Degrade2Normal);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcRampAvgValue
 *Function: ���㶨��ƽ���µ���50��Ϊһ������
 *Para    : 
 *Return  : ƽ���µ�ֵ
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.0  tw 		 2018/12/09			modified
******************************************************************************/
E_SysBool Atoalgo_Sense_CalcRampAvgValue(const S_TRAINSTATUSDATA* 		const pTrainStatusData,
										 const S_ALGO_STRATEGYCTRLDATA*	const pAlgoStrategyCtrlData,
						   	   	   	  	 const S_FORWARDRLDATA* 		const pForwardRailLineData,
						   	   	   	  	 	   REAL32*						  AvgRamp);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcAddRes
 *Function: ������·��������
 *Para    : 
 *Return  : ��������
 *NOTE    : V1.0.0  tw 		 2018/12/10			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_CalcAddRes(const S_TRAINSTATUSDATA* 	const pTrainStatusData,
								    const S_FORWARDRLDATA* 		const pForwardRailLineData, 
								          S_KERNEL_SENSEDATA*	const pKernelSensedataIO,
								    	  REAL32* 					  InAvgRampTemp,
								    	  REAL32* 					  InAvgCurveTemp);
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcAddRes
 *Function: ������·�������������µ�
 *Para    : 
 *Return  : �����������飬���µ�����
 *NOTE    : V1.0.0  tw 		 2019/1/8			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_RailLineClac(const S_FORWARDRLDATA* 		const pForwardRailLineData, 
								 	      	S_KERNEL_SENSEDATA*		const pKernelSensedataIO);
/******************************************************************************
 *Name    : Atoalgo_Sense_RampValueClac
 *Function: ���µ��µ�����
 *Para    : ���µ�����
 *Return  : ������µ�ƽ���µ����� (ChangeRampPointAveRamp[0]Ϊ����λ�õ�����Ϊ0�ı��µ���ε�ƽ��ֵ
 *Return  						  ChangeRampPointAveRamp[1]Ϊ���µ���������Ϊ0������Ϊ1��ε�ƽ��ֵ���Դ�����)
 *NOTE    : V1.0.0		tw 		 2019/04/12			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_RampChangePointAveRamp(S_KERNEL_SENSEDATA*	const pKernelSensedataIO);
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
									  UINT16 PlanCalcStep);
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
									 UINT16* const pBeginIndexOut);
/******************************************************************************
 *Name    : Atoalgo_Sense_RampValueClac
 *Function: ��������λ�õĸ�������
 *Para    : �����������飬���λ��
 *Return  : �����������ֵ
 *NOTE    : V1.0.0		tw 		 2019/01/08			create
******************************************************************************/
REAL32  Atoalgo_Sense_RampValueClac(const S_ALGO_STRATEGYCTRLDATA* 	const pAlgoStategyCtrlData,
									const REAL32* 					const RailAddRes,
										  REAL32					const Distance);
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
		   	   	   	   	   	   	   	   	   	    				const UINT16 curIndexIn);
/******************************************************************************
 *Name      : 
 *Function  : �����ڲ����������ٶ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Return    : UINT16 ��Ӧ���ڲ������ٶȣ�1=1km/h)
 *Note		: V1.0.0       Tangwei    2019/08/12   Create
 ******************************************************************************/
E_SysBool LkjSpd2InterSpd(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
								S_KERNEL_SENSEDATA* const pSenseDataIn);
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
		  	  	  	  	  	       	    S_KERNEL_SENSEDATA*     const pKernelSenseData);
#endif
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
								       	S_KERNEL_SENSEDATA*     const pKernelSenseData);



/******************************************************************************
 *Name    : Atoalgo_Sense_LocoSignal
 *Function: ��ȡ�����ź��������
 *Para    : const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData,
          :       S_LOCOSIGNAL_DATA*    const pLocoSignal                       
 *Return  : 
 *NOTE    : V1.0.0  Chenjiahui			 2019/01/14		 create
******************************************************************************/
E_SysBool Atoalgo_Sense_LocoSignal(const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData,
		                                 S_LOCOSIGNAL_DATA*    const pLocoSignal);

#if 0
/******************************************************************************
 *Name      : Atoalgo_Sense_RsSpdShutUpPointDist
 *Function  : ����������߱տڵ�ľ���
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurve      
 *Return    : UINT32
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
UINT32 Atoalgo_Sense_RsSpdShutUpPointDist(const S_LKJ_PROJECTCURVE* const pProjectCurveIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdRiseSegStartPoint
 *Function  : �ж��Ƿ�Ϊ��������������ʼ��
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool�����������������ʼ�㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdRiseSegStartPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                       const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdDeclinePoint
 *Function  : �ж��Ƿ�Ϊ�����½���ʼ��
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool������������½���ʼ�㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdDeclineSegStartPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                          const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdRiseSegEndPoint
 *Function  : �ж��Ƿ�Ϊ�������������յ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool����������������յ㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdRiseSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                     const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_ExistSpdRiseSegEndPoint
 *Function  : �ж���Сʶ��������Ƿ�����������������յ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn,   UINT16* riseSegEndIndexOut  
 *Return    : E_SysBool������������������յ㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/31   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_ExistSpdRiseSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                        const UINT16 curIndexIn,
		                                        UINT16* riseSegEndIndexOut);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdDeclineSegEndPoint
 *Function  : �ж��Ƿ�Ϊ�����½��յ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool������������½��յ㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdDeclineSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                        const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_ExistSpdDeclineSegEndPoint
 *Function  : �ж���Сʶ��������Ƿ���������½��յ�
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn,    UINT16* declineSegEndIndexOut 
 *Return    : E_SysBool��������������½��յ㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_ExistSpdDeclineSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                        const UINT16 curIndexIn,
		                                        UINT16* declineSegEndIndexOut);

/******************************************************************************
 *Name      : Atoalgo_Sense_CalcSpdChngRecognise
 *Function  : ���ݷ�������ʶ���ٶȱ仯
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurve
 *Para      ��S_KERNEL_SENSEDATA* const pSenseDataOut      
 *Return    : E_SysBool,�����ɹ�����e_TRUE������ʧ�ܷ���e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/14   Create
 *Note		��V1.0.1       YipingYang    2019/01/17   modify �޸��������
 ******************************************************************************/
E_SysBool Atoalgo_Sense_CalcSpdChngRecognise(const S_LKJ_PROJECTCURVE* 	const pProjectCurveIn,
		                                     	   S_KERNEL_SENSEDATA* 	const pSenseDataOut);

#if 1

/******************************************************************************
*Name    : Atoalgo_Sense_AutoModeData
*Function: �Զ���ʻ����ģʽ����
*Para    : const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData
*Para    : const S_FORWARDRLDATA* const ForwardRailLineData
*Para    : S_KERNEL_SENSEDATA* const pKernelSenseData
*Return  : E_SysBool����������e_TRUE �쳣����e_FALSE
*NOTE    : V1.0.0  zxm           2019/01/11     create
******************************************************************************/
E_SysBool Atoalgo_Sense_AutoModeData(const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,
								     const S_FORWARDRLDATA* 		const ForwardRailLineData,
								       	   S_KERNEL_SENSEDATA* 		const pKernelSenseData);

/******************************************************************************
*Name    : Atoalgo_Sense_AutoDriveAllowProc
*Function: �Զ���ʻ������
*Para    : const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData
*Para    : const S_FORWARDRLDATA* const ForwardRailLineData
*Para    : S_KERNEL_SENSEDATA* const pKernelSenseData
*Return  : E_SysBool����������e_TRUE �쳣����e_FALSE
*NOTE    : V1.0.0  zxm           2019/01/11     create
******************************************************************************/
E_SysBool Atoalgo_Sense_AutoDriveAllowProc(const S_ALGO_INPUT_DYNDATA* 		const pAlgoInputDynData,
								     	   const S_FORWARDRLDATA* 			const ForwardRailLineData,
								       	   	     S_KERNEL_SENSEDATA* 		const pKernelSenseData);


/******************************************************************************
 *Name      : Atoalgo_Sense_ExistSpdRiseSegStartPoint
 *Function  : �жϵ�ǰ������֮ǰ�Ƿ���������������
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn,    UINT16* riseSegStartIndexOut 
 *Return    : E_SysBool�������������������㷵��e_TRUE������Ϊe_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/18   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_ExistSpdRiseSegStartPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                          const UINT16 curIndexIn,
		                                          UINT16* riseSegStartIndexOut);

/******************************************************************************
 *Name      : Atoalgo_Sense_SpdDwSegEndPtComfirm
 *Function  : �����壬�ٶ��½��յ�ȷ��
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : S_KERNEL_SENSEDATA* const pSenseDataOut
 *Para      : const UINT16 spdDwEndIndexIn�������յ����� 
 *Return    : void
 *Note		: V1.0.0       YipingYang    2019/01/18   Create
 ******************************************************************************/
void Atoalgo_Sense_SpdDwSegEndPtComfirm(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
												   S_KERNEL_SENSEDATA* const pSenseDataOut,
		                                     const UINT16 spdDwEndIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_BadgePointRecognise
 *Function  : ʶ���г�ǰ�����εı�ǵ�
 *Para      : const S_SPECIALZONEDATA* const pSpecZoneData 
 *Para      : S_KERNEL_SENSEDATA* const pSenseData 
 *Return    : E_SysBool����������e_TRUE �쳣����e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/21   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_BadgePointRecognise(const S_SPECIALZONEDATA* const pSpecZoneData,
		   	   	   	   	   	   	   	   	   	    	S_KERNEL_SENSEDATA* const pSenseData);

/******************************************************************************
 *Name      : Atoalgo_Sense_FirstSpecAreaInfront
 *Function  : ̽���г�ǰ���ĵ�һ����������
 *Para      : const S_SPECIALZONEDATA* const pSpecZoneData 
            : const UINT32 LocoPosIn, UINT8* SpecAreaIndex 
 *Return    : E_SysBool������г�ǰ�����������η���e_TRUE����֮����e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/22   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_FirstSpecAreaInfront(const S_SPECIALZONEDATA* const pSpecZoneData,
		   	   	   	   	   	   	   	   	   	 const UINT32 LocoPosIn,
		   	   	   	   	   	   	   	   	   	 UINT8* SpecAreaIndex);


/******************************************************************************
 *Name    : Atoalgo_Sense_CalcTrainHeavyEmptyWgt
 *Function: �����г����س�����
 *Para    : 
 *Return  : 
 *NOTE    : V1.0.0  zhouww 	 2019/02/19      create
******************************************************************************/
void Atoalgo_Sense_CalcTrainHeavyEmptyWgt(const S_TRAINSTATUSDATA* const pTrainStatusData,
										  	      UINT32* 				   heavy,
										  	      UINT32* 				   empty);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcTotalLocosWgt
 *Function: �����ܻ�������
 *Para    :                          
 *Return  : 
 *NOTE    : V1.0.0  zhouww 	 2018/08/04      create
******************************************************************************/
UINT16 Atoalgo_Sense_CalcTotalLocosWgt(S_TRAINSTATUSDATA* const pTrainStatusData);

/******************************************************************************
 *Name    : Atoalgo_Sense_RailLineBasicData
 *Function: ���ⲿ�������·�������ݼ����֪����
 *Para    :                          
 *Return  : �����ɹ�����e_TRUE��ʧ�ܷ���e_FALSE
 *NOTE    : V1.0.0  YipingYang 	 2019/02/26      create
******************************************************************************/
E_SysBool Atoalgo_Sense_RailLineBasicData(S_ALGO_INPUT_BASICDATA*  pAlgoInputBasicData,
									 	  S_ALGO_INPUT_BASICDATA** pBasicDataOut);

/******************************************************************************
 *Name    : Atoalgo_Sense_SearchLongRamp
 *Function: ̽��ǰ���������»򳤴�����
 *Para    :                          
 *Return  : �����ɹ�����e_TRUE��ʧ�ܷ���e_FALSE
 *NOTE    : V1.0.0  zxm 	 2019/03/05      create
******************************************************************************/
E_SysBool Atoalgo_Sense_SearchLongRamp(const S_FORWARDRLDATA* 		const pForwardRailLineData,
											 S_KERNEL_SENSEDATA*	const pKernelSensedataIO);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcWorkStatusChngTime
 *Function: ���ݸ�֪���ݼ��㹤��ת��ʱ��
 *Para    : const S_KERNEL_SENSEDATA* const pSenseData                         
 *Return  : ����ת��ʱ�䣬������Ч�����ޱ���ģʽ����0U
 *NOTE    : V1.0.0  YipingYang 	 2019/02/28      create
******************************************************************************/
UINT8 Atoalgo_Sense_CalcWorkStatusChngTime(const S_KERNEL_SENSEDATA* const pSenseData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalAirBrkReleaseTime
 *Function: �����ƶ�����ʱ��
 *Para    : const S_TRAINSTATUSDATA* const pTrainStatusData
          : const UINT16 PressureDecrement
 *Return  : �����ƶ�����ʱ��(1=1ms)
 *NOTE    : V1.0.0  zhubaolin 		 2018/01/08     create
          : V1.0.1  YipingYang       2019/03/05     modify �޸ĺ����������
******************************************************************************/
UINT32 Atoalgo_Sense_CalAirBrkReleaseTime(const S_TRAINSTATUSDATA* const pTrainStatusData,
										  const UINT16 PressureDecrement);

/******************************************************************************
Name    : ATO_Sense_BPVentTime
*Function: �����г����ŷ�ʱ��
*Para    : const S_TRAINSTATUSDATA* const pTrainStatusData
         : const UINT16 PressureDecrement
*Return  : UINT32(1=1ms)
*NOTE    : V1.0.0     YipingYang    2019/03/04    Create
         : V1.0.1     YipingYang    2019/03/05    modify  �޸ĺ����������
******************************************************************************/
UINT32 ATO_Sense_BPVentTime(const S_TRAINSTATUSDATA* const pTrainStatusData,
						    const UINT16 PressureDecrement);

/******************************************************************************
 *Name    : Atoalgo_Sense_TrainRuningCoastProc
 *Function: �г����ж��й����������ж϶���ʵ������״ֵ̬Ϊ0���������Ϊ0������ͬʱ����Ÿ�֪Ϊ���й��������ݸ�������ơ�
 *Para    : 
 *Return  : ����ת������
 *NOTE    : V1.0.0  zhubaolin 		 2018/01/08     create
******************************************************************************/
E_SysBool Atoalgo_Sense_TrainRuningCoastProc(const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,\
											S_KERNEL_SENSEDATA* 		const pKernelSenseData);
/******************************************************************************
 *Name    : Atoalgo_Ctrl_JudgingAirBrk
 *Function: �����ƶ������ж�
 *Para    : 
 *Return  : ����ת������
 *NOTE    : V1.0.0  zhubaolin 		 2018/01/08     create
******************************************************************************/
E_SysBool Atoalgo_Sense_JudgingAirBrk(const S_KERNEL_SENSEDATA*     const pKernelSenseData);
/******************************************************************************
 *Name    : Atoalgo_Sense_AccCalc
 *Function: ����������ٶ�
 *Para    : 
 *Return  : ��
 *NOTE    : V1.0.0  	LiuYeXuan 		 2019/02/25		
******************************************************************************/
E_SysBool Atoalgo_Sense_AccCalc(S_KERNEL_SENSEDATA * const pKernelSenseData);

/******************************************************************************
 *Name    : Atoalgo_Sense_IsNeededBreakTest
 *Function: ��֪�Ƿ�Ҫ����ͨ����
 *Para    : const S_KERNEL_SENSEDATA* const pSenseData                         
 *Return  : e_TRUE:Ҫ����e_FALSE:����
 *NOTE    : V1.0.0  zxm 	 2019/04/02      create
******************************************************************************/
E_SysBool Atoalgo_Sense_IsNeededBreakTest(S_KERNEL_SENSEDATA* const pSenseData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcStopPntPosFromSignal
 *Function: ����ͣ�����ͣ���źŻ���λ��
 *Para    : const S_KERNEL_SENSEDATA* const pSenseData
          : UINT8* StopPntIndex��ͣ��������ֵ 
 *Return  : UINT32��ͣ����λ�ã���0�����
 *NOTE    : V1.0.1  zxm 	 2019/04/02         create 
******************************************************************************/
UINT16 Atoalgo_Sense_CalcStopPntPosFromSignal(S_KERNEL_SENSEDATA* const pSenseData,
											  UINT16                    Distance);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcStopPntPosFromSignal
 *Function: �������ǰͣ��������0���λ��
 *Para    : const S_SPECIALZONEDATA*   const pSpecZoneData,
 *Para    : S_KERNEL_SENSEDATA*  const pSenseData,
 *Para    : S_STOP_NEU_RELA_DIST* const pStopNeuRelaDist
 *Return  : �ɹ�����e_TRUE,ʧ�ܷ���e_FALSE
 *NOTE    : V1.0.1  TangWei 	 2019/04/19         create 
******************************************************************************/
E_SysBool Atoalgo_Sense_CalcStopBef_NeuRelaDist(const S_SPECIALZONEDATA*   const pSpecZoneData,
  	   	   	   	    							   S_KERNEL_SENSEDATA*  const pSenseData,
  	   	   	   	    							   S_STOP_NEU_RELA_DIST* const pStopNeuRelaDist);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcStopBef_NeuMinDist
 *Function: �������ǰͣ��������0���λ��
 *Para    : 
 *Return  :
 *NOTE    : V1.0.1  TangWei 	 2019/04/19         create 
******************************************************************************/
UINT16 Atoalgo_Sense_CalcStopBef_NeuMinDist(const S_SPECIALZONEDATA*   const pSpecZoneData,
  	   	   	   	    							  S_KERNEL_SENSEDATA*  const pKernelSenseDataIn,
  	   	   	   	    							  REAL32	Spd,	   UINT16	RelaDis);
#endif
#endif