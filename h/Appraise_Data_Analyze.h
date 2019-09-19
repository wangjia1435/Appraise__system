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
#ifndef    ACS_APPRAISE_DATA_ANALYZE
#define	   ACS_APPRAISE_DATA_ANALYZE

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/Appraise_BasicFunction.h"
#include "../h/GL_Basic_Type_Definition.h"
#include<stdio.h>
/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/


#define ALGO_TARGET_LINE_NUM			(300U)								/*Ŀ������������ݸ���*/
#define ALGO_STATION_MAX_NUM            (3U)								/*վ������Ϣ������*/
#define ALGO_SEMAPHORE_MAX_NUM			(50U)								/*�źŻ�����*/
#define ALGO_LIMITSPEED_MAX_NUM			(100U)								/*������Ϣ������*/
#define ALGO_GRADIENT_MAX_NUM			(300U)								/*�µ���Ϣ������*/
#define ALGO_RADIUS_MAX_NUM				(100U)								/*�����Ϣ������*/
#define ALGO_TUNNEL_MAX_NUM				(30U)								/*�����Ϣ������*/
#define ALGO_BLOCK_MAX_NUM 				(10U)			    			    /*������Ϣ������*/
#define ALGO_DRIVER_CTL_DATA_NUM		(850U)								/*˾����ʻ�ο����ݸ���*/
#define ALGO_TIME_TABLE_NUM				(4U)								/*���������г�����ʱ�ָ���*/
#define ALGO_SIDE_TRACK_NUM				(20U)								/*���߹ɵ����ݸ���*/
#define ALGO_SPECIAL_ZONEDATA_NUM		(100U)								/*�����������ݸ���*/
#define ALGO_RECORD_BYTENUM				(384U)								/*���㷨ģ���¼�ֽ���*/
#define ALGO_DEBUG_BYTENUM				(512U)								/*���㷨ģ������ֽ���*/
#define ALGO_LIMIT_SPEED_NUM_MAX        (740U)								/*�������ߣ��������ߣ��������*/
/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
 /*�㷨����״̬���*/
typedef struct TAG_Algo_RunStatus
{
	UINT8				 AlgoVersion[4];										/*�汾   |A|B|C|D|,����1.0.0.1*/
 																				/*     |-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|*/
	
	UINT32               AlgoAutoQuitReqCode;                                  /*�㷨�����˳�ԭ��
			                                                                     bit0:���ؿ�ת�����˳�
	                                                                             bit1:�ٶ��쳣�����˳�
	                                                                             bit2:ѹ��������
	                                                                             bit3:--
	                                                                             bit4:������ʧ
	                                                                             bit5:--
	                                                                             bit6:��β����
	                                                                             bit7:ͨ��ģʽ���뽵��ģʽ
	                                                                             bit8:���Ʊ�������
	                                                                             bit9:�����ƶ��쳣
	                                                                             bit10ǣ�������޷�����
	                                                                             bit11���Ʒ����޷�����
	                                                                             bit12��ͨ����ʧ��
	                                                                             bit13�𳵺���
	                                                                             bit14�����ٹ滮����(����ʾ��Ϣ)
	                                                                             */
	UINT32               AlgoAutoForbidCode;                                   /* �˹���ʻ�л����Զ���ʻʱ�򣬿��Ʋ������Զ���ʻԭ��
																				 bit0: �г��Ǵ���ǣ���Ͷ��й���;
	                                                                             bit1��LKJ�ٶȺ�TCMS�ٶȲ������Χ��;
	                                                                             bit2��ʵ���ٶȸ��ڹ滮�ٶ�3km/h;
	                                                                             bit3���г����������������ڣ�
	                                                                             bit4���г��ڹ�������״̬���޹������У����޶�����ʧ��ѹ�������ϡ���β���ϵ�;
	                                                                             bit5��ͨ��ģʽ���뽵��ģʽ���г��Դ����˶�״̬����ʱ���������Զ���ʻ
	                                                                             bit6���㷨�ж����ϣ�������У���쳣
	                                                                             bit7���޷��滮, ����ʱ�����̫��
	                                                                             */   
}S_ALGO_RUNSTATUS;
 
 /*�㷨�������ָ��*/
typedef struct TAG_Algo_OutputCtlData
{
	UINT8	RunningStatus;                								    /*�������壺 0x01-����,0x02-ǣ��,0x03-���ƶ�,0x04-�����ƶ�,0x05-�յ����ƶ�*/
	UINT8  	BrakeCMD;         										        /*bit0:��բʩ�����bit1����բ�������bit2 Сբ�ƶ����bit3 Сբ��������*/
	UINT8  	RunningModeFlag;			    								/*bit0,�ɽ����Զ���ʻ��bit1���˳����룻bit2���г̳�ʼ������0��������1��������bit3����ʼ�����   */
	UINT8   CtlCmd;                               							/*bit0-��ɰ��bit1-��ѹ����ǿ�ã�bit2-ͣ��ʩ�ӣ�bit3-ͣ�Ż��⣻bit4-��ѯβ����ѹ��bit5-׼����բ */
	UINT8   CtlMode;														/*Bit0���ϵ�ģʽ����  Bit1���㵥ģʽ����, Bit2:����ģʽ����  Bit3~Bit7 Ԥ��*/
	UINT8   NeutralCmd;														/*bit0-����Ԥ�棻bit1-����ǿ�ϣ����Զ��������źţ���bit2-����ͨ����bit3-�����ද��ж�أ�*/	
	UINT8   BrakeTestSta;												    /*bit0-��ʼ��բ��bit1-��բ��ɣ�*/
	UINT8   IsoMotorCmd;													/*bit0-I�ܵ��1����,bit1-I�ܵ��2����,bit2-II�ܵ��1����,bit3-II�ܵ��2����*/
	INT16	DrivingFSetValue;			   									/*ǣ���������ٷֱȣ�ǣ��Ϊ��������Ϊ��,1=0.1%,-1000~+1000*/
	UINT16	ABHTargetValue;										    		/*��բ��ѹ��*/
	UINT16	IBHTargetValue;	                      							/*СբĿ��ֵ*/
	UINT32  RunningTime;    												/*��ǰ����������ʱ��-��*/
	UINT32  RemainTime;     												/*��ǰ����ʣ��ʱ��-��*/
}S_ALGO_OUTPUT_CTLDATA;


/* �㷨�滮�������*/
typedef struct TAG_AlgoOutputTargetLine
{
	UINT32 UpDataLife;                                    					/*�滮���߸��±�ʶ,����һ�Σ�ֵ��1*/
	UINT16 ValidNum;    													/*�����Ч����*/	
	UINT16 PressureDecrement[ALGO_TARGET_LINE_NUM];    						/*��ѹ��-Kpa*/
	UINT8  RunningStatus[ALGO_TARGET_LINE_NUM];    					  		/*����  0x01�����У�0x02��ǣ����0x03�����ƶ���0x04�������ƶ���0x05���յ����ƶ�*/	
	UINT16 TragetPosition[ALGO_TARGET_LINE_NUM];  							/*��滮ʱ��0�����Ծ���*/
	UINT16 TragetV[ALGO_TARGET_LINE_NUM];  									/*Ŀ���ٶ�*/
	UINT16 TragetF[ALGO_TARGET_LINE_NUM];   								/*Ŀ�꼶λ*/
}S_ALGO_OUTPUT_TARGETLINE;

/* �㷨��¼�������*/
typedef struct TAG_AlgoOutputRecord
{
	UINT8  ValidNum;                                      					/*��¼��Ч�ֽڸ���*/
	UINT8  AlgoRecord[ALGO_RECORD_BYTENUM];    								/*��¼����*/
	UINT8  AlgoDebug[ALGO_DEBUG_BYTENUM];									/*��������*/
}S_ALGO_OUTPUT_RECORD;

/* �㷨���롪��˾�����ݲο�����*/
typedef struct TAG_AlgoTargetLineRef
{
	UINT16	ValidNum;   												/*��Ч����*/
	UINT16	Distance[ALGO_DRIVER_CTL_DATA_NUM];  						/*����0�����Ծ���*/
	UINT16  Speed[ALGO_DRIVER_CTL_DATA_NUM];   							/*�ٶ�*/
	INT16   Force[ALGO_DRIVER_CTL_DATA_NUM];    						/*��Ϊǣ����/��Ϊ���ƶ���*/
	UINT16  PressureDecrement[ALGO_DRIVER_CTL_DATA_NUM];				/*��ѹ��*/
	UINT8   RunningStatus[ALGO_DRIVER_CTL_DATA_NUM];  					/*������ 0x01-����,0x02-ǣ��,0x03-���ƶ�,0x04-�����ƶ�,0x05-�յ����ƶ�*/
	UINT8   Scene[ALGO_DRIVER_CTL_DATA_NUM];    						/*����   1-������2-�������£�3-�������£�4-���࣬5-�𳵣�6-ͣ����7-��ͨ����*/
}S_ALGO_TARGETLINE_REF;


/*--�㷨���롪��������Ϣ--------------------------*/
typedef struct TAG_LimitSpeedCurve{
  UINT8   RsSpdType;														/*�������� */
  UINT16  RsSpd;															/*���� */
  UINT16  RsSpdLength;														/*���ٳ��� */ 
  UINT16  RelativeDist;														/*����0��λ����Ծ��� ��λ���� */
}S_LIMITSPEEDCURVE;
typedef struct TAG_Input_LimitSpeedCurve
{
	UINT16 LimitSpeedValidNum;												/*������Ч����*/  
	S_LIMITSPEEDCURVE LIMITSPEED[ALGO_LIMITSPEED_MAX_NUM];					/*��������*/
}S_INPUT_LimitSpeedCurve;

/*--�㷨���롪���µ���Ϣ----------------------*/
typedef struct TAG_Ramp
{
  INT16  Grade;																/*�¶�ǧ�ֱȣ�����Ϊ�����ֱ���0.1 */
  UINT16 GradeLength;														/*�µ����ȣ���Χ��0��65535,��λ���� */ 
  UINT16 GradeRelatDist;													/*����0��λ����Ծ��� ��λ���� */ 
}S_Ramp;

typedef struct TAG_Input_Ramp
{
  UINT16 RampValidNum;                                  					/*�µ���Ч����*/  
  S_Ramp Ramps[ALGO_GRADIENT_MAX_NUM];										/*�µ�����*/  
}S_INPUT_RAMP;

/*--�㷨���롪�������Ϣ----------------------*/
typedef struct TAG_Curve
{
  INT16   Radius;															/*D15=1������ D15=0�����䣬D14��D0������뾶*/
  UINT16  CurveLenth;														/*������ȣ���Χ��0��65535,��λ���� */
  UINT16  CurveRelatDist;													/*����0��λ����Ծ��� ��λ���� */ 
}S_CURVE;
typedef struct TAG_Input_Curve
{
  UINT16  CurveValidNum;													/*�����Ч����*/  
  S_CURVE Curves[ALGO_RADIUS_MAX_NUM];										/*�������*/
}S_INPUT_CURVE;

/*--�㷨���롪�������Ϣ----------------------*/
typedef struct TAG_Tunnel
{
  UINT16  TunnelLenth;														/*������ȣ���Χ��0��65535,��λ���� */
  UINT16  TunnelRelatDist;													/* ����0��λ����Ծ��� ��λ���� */ 
}S_TUNNEL;
typedef struct TAG_Input_Tunnel
{
  UINT16   TunnelValidNum;                                				    /*�����Ч����*/  
  S_TUNNEL Tunnel[ALGO_TUNNEL_MAX_NUM];                      				/*�������*/    
}S_INPUT_TUNNEL;


/** �㷨���롪վ����λ�� */
typedef struct TAG_StationInfo
{
  //UINT16										RouteNo;				    /** LKJ2000���ݽ�·�� */
  UINT32										StationNo;					/** LKJ2000��վ�� */
  UINT16										RelativeDist;				/** վ����λ����Ծ��룬��Χ��0��10000,��λ���� */
} S_STATIONINFO;

typedef struct TAG_Input_StaionInfo 
{
  UINT8											StationNum;				/** վ�������� */
  S_STATIONINFO				StationInfo[ALGO_STATION_MAX_NUM];
} S_INPUT_STATIONINFO;

/** �㷨����-�źŻ���Ϣ */
typedef struct TAG_LocoSignal {
  UINT8								SignalType_E;				/** �źŻ����� */
  UINT8								SignalNoHead[6];		    /** ����ַ�ͷ */
  UINT8								backup[2];		    		/** Ԥ��*/
  UINT16							SignalNo;				    /** �źŻ����, ��ΧΪ1��655350 */
  UINT16 							RelativeDist;			    /** �źŻ�λ����Ծ��룬��Χ��0��10000,��λ���� */
} S_LOCOSIGNAL;

typedef struct TAG_Input_SignalInfo {
  UINT8								SignalNum;				    /** �źŻ���������Χ0-50 */
  S_LOCOSIGNAL						SignalInfo[16];//SignalInfo[ALGO_SEMAPHORE_MAX_NUM];
} S_INPUT_SIGNALINFO;

/** ������Ϣ */
typedef struct TAG_BlockInfoSet {
  UINT16 							 BlockFlag;					            /** ������־��0���Զ�������1�����Զ����� */
  UINT16							 BlockRelatDist;			            /** �������λ����Ծ��룬��Χ��0��10000����λ���� */
  UINT32							 BlockLength;			                /** �������ȣ���Χ��0��65535,��λ���� */
} S_BlockInfoSet;
/** ������Ϣ�� */
typedef struct TAG_Input_BlockInfoSet{
  UINT8								 Num;					                /** �������������ݷ�Χ��0��10 */
  S_BlockInfoSet				     BlockInfo[ALGO_BLOCK_MAX_NUM];		    /** ���λ����Ծ��룬��Χ��0��10000,��λ���� */
} S_INPUT_BLOCKINFOSET;


/*�㷨���롪��������·���ݽṹ��*/
typedef struct TAG_ForwardRLData
{
  S_INPUT_STATIONINFO				 FWStationInfo;							/*վ������Ϣ*/
  S_INPUT_SIGNALINFO				 FWSignalInfo;							/*�źŻ�*/
  S_INPUT_LimitSpeedCurve  			 FWLimitSpeed;                 			/*����*/
  S_INPUT_RAMP  					 FWRamps;								/*�¶�*/
  S_INPUT_CURVE  					 FWCurves;								/*���*/
  S_INPUT_TUNNEL  				     FWTunnels;                    			/*���*/
  S_INPUT_BLOCKINFOSET               FWBlocksInfo;							/*����*/
}S_FORWARDRLDATA;


/*�㷨���롪���г�����ʱ�����ݽṹ��*/
typedef struct TAG_TrainTimeTable
{
	UINT8  ValidNum;   						                        		/*��Ч����*/
	UINT8  AddOnTimeHour[ALGO_TIME_TABLE_NUM];                 				/*����ʱ��-ʱ*/
	UINT8  AddOnTimeMin[ALGO_TIME_TABLE_NUM];                  				/*����ʱ��-��*/
	UINT8  AddOnTimeSec[ALGO_TIME_TABLE_NUM];                  				/*����ʱ��-��*/
	UINT8  IntervalTimeHour[ALGO_TIME_TABLE_NUM];              				/*��������ʱ��-ʱ*/
	UINT8  IntervalTimeMin[ALGO_TIME_TABLE_NUM];               				/*��������ʱ��-��*/
	UINT8  IntervalTimeSec[ALGO_TIME_TABLE_NUM];               				/*��������ʱ��-��*/
	UINT8  ArrivedTimeHour[ALGO_TIME_TABLE_NUM];               				/*����ʱ��-ʱ*/
	UINT8  ArrivedTimeMin[ALGO_TIME_TABLE_NUM];                				/*����ʱ��-��*/
	UINT8  ArrivedTimeSec[ALGO_TIME_TABLE_NUM];                				/*����ʱ��-��*/
	UINT8  StartTimeHour[ALGO_TIME_TABLE_NUM];                 				/*����ʱ��-ʱ*/
	UINT8  StartTimeMin[ALGO_TIME_TABLE_NUM];                  				/*����ʱ��-��*/
	UINT8  StartTimeSec[ALGO_TIME_TABLE_NUM];                 				/*����ʱ��-��*/
	UINT8  SuspendTimeHour[ALGO_TIME_TABLE_NUM];               				/*վͣʱ��-ʱ*/
	UINT8  SuspendTimeMin[ALGO_TIME_TABLE_NUM];                				/*վͣʱ��-��*/
	UINT8  SuspendTimeSec[ALGO_TIME_TABLE_NUM];                				/*վͣʱ��-��*/
	UINT8  ResBytes[ALGO_TIME_TABLE_NUM];               			  		/*Ԥ���ֽ�*/
	UINT16 IntervalASpeed[ALGO_TIME_TABLE_NUM];         			  		/*����ƽ���ٶ�*/
	UINT16 IntervalCourse[ALGO_TIME_TABLE_NUM];                			    /*�������*/
	UINT16 CurStationRouteNo[ALGO_TIME_TABLE_NUM];	  						/*��ǰ��վ��·��*/				 
	UINT16 CurStationSN[ALGO_TIME_TABLE_NUM];								/*��ǰ��վ��վ��*/	
	UINT16 NextStationRouteNo[ALGO_TIME_TABLE_NUM];							/*��һ��վ��·��*/				 
	UINT16 NextStationSN[ALGO_TIME_TABLE_NUM];								/*��һ��վ��վ��*/
}S_TRAINTIMETABLE;

/*�㷨���롪��������������*/
typedef struct TAG_SpecialZoneData{
	UINT8  ValidNum;   						                        	    /*��Ч����*/
	UINT8  SpecialAreaCode[ALGO_SPECIAL_ZONEDATA_NUM];         				/*�������δ���*/
	UINT8  Mark[ALGO_SPECIAL_ZONEDATA_NUM];	                  				/*��־*/		
	UINT16 Relative_Distance[ALGO_SPECIAL_ZONEDATA_NUM];					/*��0�����*/ 
	UINT16 MininumSpeed[ALGO_SPECIAL_ZONEDATA_NUM];           				/*�������*/
 	UINT16 ZoneLength[ALGO_SPECIAL_ZONEDATA_NUM];              				/*���γ���*/
	UINT16 Res[ALGO_SPECIAL_ZONEDATA_NUM];                	    			/*Ԥ��*/
}S_SPECIALZONEDATA;

/*�㷨���롪�����߹ɵ�������Ϣ*/
typedef struct TAG_SideTrackData{
	UINT8  ValidNum;   						                        		/*��Ч����*/
	UINT8  SideTrackSN[50];//[ALGO_SIDE_TRACK_NUM];            				/*���߹����*/
	UINT8  Res[50];//[ALGO_SIDE_TRACK_NUM];                           		/*Ԥ��*/
	UINT16 ValidTrackLength[50];//[ALGO_SIDE_TRACK_NUM];	      			/*������Ч����*/				 
	UINT16 StopLocToFSignal[50];//[ALGO_SIDE_TRACK_NUM];       				/*ͣ��λ�þ���ǰ���źŻ�����*/	
}S_SIDETRACKDATA;

/*�㷨���롪���������״̬-CCU+BCU*/
typedef struct TAG_LocoDynCmdAndStatus
{
	UINT8   ATOFlag;                                       					/*���������ź�	bit0-�Զ���ʻ����,bit1-�Զ���ʻ���� ,bit2-�Զ�������bit3-ATO�س���bit4-���ؽӹܱ�������*/
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
	UINT8   SingalStatus;                               					/*�ź��쳣״̬�ֽڣ�
	                                                                          Bit0���ź��쳣-�źŻ�ǰ����20km/h
	                                                                          Bit1��--
	                                                                          Bit2��-- 
	                                                                          Bit3��-- 
	                                                                          Bit4��-- 
	                                                                          Bit5��-- 
	                                                                          Bit6��--  
	                                                                          Bit7 ��-*/
	UINT8   LocoStatus;														/*����״̬�ֽڣ�Bit0�����ϱպ�״̬ Bit1���յ����ϸ��� Bit2���ͷ��ƶ�ʩ��״̬ Bit3�������ƶ�ʩ��״̬ 
	                                                                          Bit4��ͣ���ƶ�����״̬��1=���⣩Bit5:ǣ������ Bit6:���Ʒ���*/
	UINT8   DmiCmd;															/*�˻��������Bit0���ϵ�ģʽ  Bit1���㵥ģʽ, Bit2:����ģʽ Bit3: ��ͨ  bit4:�Զ�ģʽ���˹�����   Bit5~Bit7 Ԥ��*/
	UINT8   FastRunTime;													/*����ʱ�䣨min��-˾������*/
	UINT8   SlowRunTime;													/*����ʱ�䣨min��-˾������*/
	UINT8	BrakeTestFlag;												    /*��բ��־��0xA5-����բ���˶�״̬�½����Զ���ʻ�㷨�ж��Ƿ���й�ͨ����*/
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
	UINT8   BCUBrakeHandleType;                            					/*բ����*/
	UINT8   BCUPressureType;                              	 				/*��ѹ����*/
	UINT8   TrainTailType;                                 					/*��β����*/
	UINT8   TrainLoadType;                                 					/*��������*/
	UINT8   VehicleType;                                   					/*��������*/
	UINT8   ConsistType;                                   					/*����ģʽ*/
	UINT8   ClosedVehicleNums;                                   			/*���ų�����*/
	UINT8   SleepLocoNums;													/*���һ�������*/
	UINT16  SlowRunMaxSpeed;												/*�����������*/
	UINT16  BrkShoePresPHT;													/*ÿ�ٶ�բ��ѹ��*/
	UINT16  PressureDecrement;                      						/*��ǰ��ѹ����Kpa��*/
	UINT16  ABHExTargetACK;													/*�г���Ŀ��ֵ��ѹ���趨����*/
	UINT16  IBHExTargetACK;													/*�ƶ���Ŀ��ֵ�趨����*/
	UINT16  PressureTotalVal;                       						/*��ǰ�ܷ��ѹ��*/	
	UINT16  BrakeCylinder;						   							/*��ǰ�ƶ���ѹ��*/	
	UINT16  EqualReservoir; 						   						/*��ǰ������*/	
	UINT16  RateOfFlow;                             						/*�������*/	
	UINT16  TrainTailValue;                         						/*β����ѹ*/	
	UINT16  PriVolt;														/*����ԭ�ߵ�ѹ��V��0-38000v*/
	UINT16  TcmsSpeed;														/*��ǰTCMS�ٶȣ�1=0.01km/h*/
	UINT16  Force;          							   					/*��ǰʵ��ǣ��/���ƶ� 1=0.1KN*/
	UINT16  TrcFmax;                                   						/*��ǰ�������ǣ����*/	
	UINT16  EBrFmax;                                   						/*��ǰ���������ƶ���*/	
	UINT16  TrcPowerLostPercent;                                   			/*ǣ����������ʧ�ٷֱ�1=0.1%*/	
	UINT16  EBrkPowerLostPercent;                                   		/*������������ʧ�ٷֱ�1=0.1%*/	
	UINT32  Position;   							   						/*������Ծ���-��Ի�����·����ʱ����0���λ�þ���*/
	UINT32  TravlledDistance;                       						/*����λ�ƣ��ۼ�λ��,��λ���� */
}S_LOCO_DYNCMDANDSTATUS;

/*�㷨���롪��LKJ��������*/
typedef struct TAG_LkjProtectCurve
{	
	UINT16  LimitSpeed[ALGO_LIMIT_SPEED_NUM_MAX];            				/*������������*/
}S_LKJ_PROJECTCURVE;

/*�㷨���롪��LKJ��̬��������*/
typedef struct TAG_LKJDynCtlData
{
	UINT8 	Singal;          									   			/*�����ź�*/
	UINT8 	LKJMode;														/*���״̬*/
	UINT8   ResByte;														/*Ԥ���ֽ�*/
	UINT8   TrainType;                                 	  					/*�г�����*/
	UINT16  TrainPipe;														/*�г���*/	
	UINT16  TrainWeight;													/*�г�����*/
	UINT16  TrainLength;													/*�г��Ƴ�*/
	UINT16  VehicleNum;														/*��������*/
	UINT16  LocoType;														/*��������*/
	UINT16  WheelDiameter;													/*�����־�*/	
	UINT16  LkjSpeed;        							   					/*��ǰLKJ�ٶ�*/
	/*�����㷨�ӿ�����-20180711-likai*/
	UINT16 	HeavyCar;													    /*�س�����*/
	UINT16 	EmptyCar;				  									    /*�ճ�����*/
	UINT16  NextSigRelaDist;				  							    /*��������һ�źŻ��ľ���*/
	UINT8  	CurrentSideLine;			                                    /*����������*/
	UINT8  	NextSideLine;				                                    /*�·�������*/
	
	/*���ӱ�����֧�� ���·���֧�ߺ�*/
	UINT8  	CurrentBranch;			        								/*������֧�� */
	UINT8  	NextBranch;				        								/*�·���֧�� */
}S_LKJ_DYNAMICCTLDATA;


/*�㷨���롪���������ź�*/
typedef struct TAG_NeutralSignal
{
	UINT8 NeutralForetellFlag;   											/*����Ԥ���ź�*/
	UINT8 NeutralForceFlag;                                   				/*����ǿ���ź�*/
	UINT8 NeutralPassFlag;                                   				/*����ͨ���ź�*/
	UINT8 LocoInNeutral;													/*���ڹ�����*/
}S_NEUTRALSIGNAL;


/*�������ģ��ĵ���*/
typedef struct TAG_LocoElectrical
{
	UINT32 ConsumeElectrical;   											/*�������ĵĵ���*/
	UINT32 ReElectrical;                         	          				/*���������ĵ���*/

}S_LOCOELECTRICAL;



/** ATOʱ����Ϣ */
typedef struct TAG_AcsTimeDate 
{
	S_ATO_DATETIME	  Year_TimeDate;
	UINT32			  SecondTime;
} S_ACS_TIME_DATE;

typedef struct TAG_DynDate
{
	UINT32			  Total_Dyn_Num;
} S_DYN_DATE;


/*��������*/
typedef struct TAG_SpecialData
{
	S_LOCOELECTRICAL  LocoElectrical;
	S_ACS_TIME_DATE	  TimeDate;	
	S_DYN_DATE		  DynDate;
}S_ACS_SPECIALDATA;


/*���(Para1)������̬�������������ݴ��*/
typedef struct TAG_AlgoInputDynData
{
	S_LOCO_DYNCMDANDSTATUS LocoDynCMDandStatus;           					/*�������״̬*/
	S_LKJ_PROJECTCURVE     LkjProjectCurve;              	 				/*LKJ��̬��������*/
	S_LKJ_DYNAMICCTLDATA   LKJDynamicCtlData;			  					/*LKJ��̬��������*/
	S_NEUTRALSIGNAL        NeutralSignal;                 					/*�������ź�*/
}S_ALGO_INPUT_DYNDATA,S_ACS_DYNDATA;

/*���(Para2)�������������������ݴ��*/
typedef struct TAG_AlgoInputBasicData
{ 
  UINT32 				 UpDataLife;                                    	/*���ݸ��±�ʶ,����һ�Σ�ֵ��1*/
  S_FORWARDRLDATA 		 ForwardRailLineData;        						/*ǰ��������·����*/
  S_ALGO_TARGETLINE_REF  TargetLineRef;                		 				/*Ŀ�����߲ο�����-˾����ʻ����*/
  S_TRAINTIMETABLE       TrainTimeTable;                					/*�г�����ʱ�ֱ�*/
  S_SPECIALZONEDATA      SpecialZoneData;              	 					/*������������*/
  S_SIDETRACKDATA        SideTrackInfo;                 					/*���߹ɵ�����*/
}S_ALGO_INPUT_BASICDATA,S_ACS_BASICDATA;

/*�㷨������(Para3)*/
typedef struct TAG_AlgoOutputCtlData
{ 
	S_ALGO_RUNSTATUS          AlgoOutputStaData;							/*�㷨����״̬���*/		  
	S_ALGO_OUTPUT_CTLDATA 	  AlgoOutputCtlData;          					/*�㷨�������*/
	S_ALGO_OUTPUT_TARGETLINE  AlgoOutputTargetLine;       					/*Ŀ���������*/
	S_ALGO_OUTPUT_RECORD      AlgoOutputRecord;           					/*�㷨�����¼�ֽ�*/
}S_ALGO_OUTPUT_CTRLDATA,S_ACS_CTRLDATA;

/*���*/
typedef struct TAG_AcsData
{ 
	S_ACS_DYNDATA  	   DynaData;
	S_ACS_BASICDATA	   BasicData;
	S_ACS_CTRLDATA     CtrlData;
	S_ACS_SPECIALDATA  SpecialData;
}S_ATO2ACS_INPUTPARA;


/******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/

/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/

/******************************************************************************
*    Multi-Include-Prevent End Section
******************************************************************************/

/******************************************************************************
 *Name    : ACS_Data_pipe0_Analyze
 *Function: �����ܵ�0������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe0_Analyze(UINT8* Pipe0,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe1_Analyze
 *Function: �����ܵ�1������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe1_Analyze(UINT8* Pipe1,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe2_Analyze
 *Function: �����ܵ�2������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe2_Analyze(UINT8* Pipe2,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe3_Analyze
 *Function: �����ܵ�3������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe3_Analyze(UINT8 *Pipe3,
		  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe4_Analyze
 *Function: �����ܵ�4������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe4_Analyze(UINT8 *Pipe4,
  	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe5_Analyze
 *Function: �����ܵ�5������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe5_Analyze(UINT8 *Pipe5,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe6_Analyze
 *Function: �����ܵ�6������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe6_Analyze(UINT8 *Pipe6,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe7_Analyze
 *Function: �����ܵ�7������
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : ��ʼ��״̬����������e_TRUE �쳣����e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe7_Analyze(UINT8 *Pipe7,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
#endif
