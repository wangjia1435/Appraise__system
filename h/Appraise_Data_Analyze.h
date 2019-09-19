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


#define ALGO_TARGET_LINE_NUM			(300U)								/*目标曲线输出数据个数*/
#define ALGO_STATION_MAX_NUM            (3U)								/*站中心信息最大个数*/
#define ALGO_SEMAPHORE_MAX_NUM			(50U)								/*信号机机组*/
#define ALGO_LIMITSPEED_MAX_NUM			(100U)								/*限速信息最大个数*/
#define ALGO_GRADIENT_MAX_NUM			(300U)								/*坡道信息最大个数*/
#define ALGO_RADIUS_MAX_NUM				(100U)								/*弯道信息最大个数*/
#define ALGO_TUNNEL_MAX_NUM				(30U)								/*隧道信息最大个数*/
#define ALGO_BLOCK_MAX_NUM 				(10U)			    			    /*闭塞信息最大个数*/
#define ALGO_DRIVER_CTL_DATA_NUM		(850U)								/*司机驾驶参考数据个数*/
#define ALGO_TIME_TABLE_NUM				(4U)								/*运行区间列车运行时分个数*/
#define ALGO_SIDE_TRACK_NUM				(20U)								/*侧线股道数据个数*/
#define ALGO_SPECIAL_ZONEDATA_NUM		(100U)								/*特殊区段数据个数*/
#define ALGO_RECORD_BYTENUM				(384U)								/*给算法模块记录字节数*/
#define ALGO_DEBUG_BYTENUM				(512U)								/*给算法模块调试字节数*/
#define ALGO_LIMIT_SPEED_NUM_MAX        (740U)								/*限速曲线（防护曲线）数组个数*/
/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
 /*算法运行状态输出*/
typedef struct TAG_Algo_RunStatus
{
	UINT8				 AlgoVersion[4];										/*版本   |A|B|C|D|,比如1.0.0.1*/
 																				/*     |-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|*/
	
	UINT32               AlgoAutoQuitReqCode;                                  /*算法申请退出原因：
			                                                                     bit0:严重空转申请退出
	                                                                             bit1:速度异常申请退出
	                                                                             bit2:压缩机故障
	                                                                             bit3:--
	                                                                             bit4:动力损失
	                                                                             bit5:--
	                                                                             bit6:列尾故障
	                                                                             bit7:通常模式进入降级模式
	                                                                             bit8:控制保护故障
	                                                                             bit9:空气制动异常
	                                                                             bit10牵引封锁无法消除
	                                                                             bit11电制封锁无法消除
	                                                                             bit12贯通试验失败
	                                                                             bit13起车后溜
	                                                                             bit14非零速规划警惕(仅提示信息)
	                                                                             */
	UINT32               AlgoAutoForbidCode;                                   /* 人工驾驶切换到自动驾驶时候，控制不允许自动驾驶原因：
																				 bit0: 列车非处于牵引和惰行工况;
	                                                                             bit1：LKJ速度和TCMS速度差不在允许范围内;
	                                                                             bit2：实际速度高于规划速度3km/h;
	                                                                             bit3：列车运行在特殊区段内；
	                                                                             bit4：列车在故障运行状态，无故障运行，如无动力丢失、压缩机故障、列尾故障等;
	                                                                             bit5：通常模式进入降级模式，列车仍处于运动状态运行时，不允许自动驾驶
	                                                                             bit6：算法判定故障，如数据校验异常
	                                                                             bit7：无法规划, 如起车时距分相太近
	                                                                             */   
}S_ALGO_RUNSTATUS;
 
 /*算法输出控制指令*/
typedef struct TAG_Algo_OutputCtlData
{
	UINT8	RunningStatus;                								    /*工况定义： 0x01-惰行,0x02-牵引,0x03-电制动,0x04-空气制动,0x05-空电混合制动*/
	UINT8  	BrakeCMD;         										        /*bit0:大闸施加命令，bit1：大闸缓解命令，bit2 小闸制动命令，bit3 小闸缓解命令*/
	UINT8  	RunningModeFlag;			    								/*bit0,可进入自动驾驶；bit1，退出申请；bit2，行程初始化允许（0，不允许；1，允许）；bit3，初始化完成   */
	UINT8   CtlCmd;                               							/*bit0-撒砂；bit1-主压缩机强泵；bit2-停放施加；bit3-停放缓解；bit4-查询尾部风压；bit5-准备试闸 */
	UINT8   CtlMode;														/*Bit0：赶点模式运行  Bit1：点单模式运行, Bit2:慢行模式运行  Bit3~Bit7 预留*/
	UINT8   NeutralCmd;														/*bit0-分相预告；bit1-分相强断（半自动过分相信号）；bit2-分相通过；bit3-过分相动力卸载；*/	
	UINT8   BrakeTestSta;												    /*bit0-开始试闸；bit1-试闸完成；*/
	UINT8   IsoMotorCmd;													/*bit0-I架电机1隔离,bit1-I架电机2隔离,bit2-II架电机1隔离,bit3-II架电机2隔离*/
	INT16	DrivingFSetValue;			   									/*牵引电制力百分比，牵引为正，电制为负,1=0.1%,-1000~+1000*/
	UINT16	ABHTargetValue;										    		/*大闸减压量*/
	UINT16	IBHTargetValue;	                      							/*小闸目标值*/
	UINT32  RunningTime;    												/*当前区间已运行时间-秒*/
	UINT32  RemainTime;     												/*当前区间剩下时间-秒*/
}S_ALGO_OUTPUT_CTLDATA;


/* 算法规划曲线输出*/
typedef struct TAG_AlgoOutputTargetLine
{
	UINT32 UpDataLife;                                    					/*规划曲线更新标识,更新一次，值加1*/
	UINT16 ValidNum;    													/*输出有效个数*/	
	UINT16 PressureDecrement[ALGO_TARGET_LINE_NUM];    						/*减压量-Kpa*/
	UINT8  RunningStatus[ALGO_TARGET_LINE_NUM];    					  		/*工况  0x01，惰行；0x02，牵引；0x03，电制动；0x04，空气制动；0x05，空电混合制动*/	
	UINT16 TragetPosition[ALGO_TARGET_LINE_NUM];  							/*距规划时刻0点的相对距离*/
	UINT16 TragetV[ALGO_TARGET_LINE_NUM];  									/*目标速度*/
	UINT16 TragetF[ALGO_TARGET_LINE_NUM];   								/*目标级位*/
}S_ALGO_OUTPUT_TARGETLINE;

/* 算法记录数据输出*/
typedef struct TAG_AlgoOutputRecord
{
	UINT8  ValidNum;                                      					/*记录有效字节个数*/
	UINT8  AlgoRecord[ALGO_RECORD_BYTENUM];    								/*记录数据*/
	UINT8  AlgoDebug[ALGO_DEBUG_BYTENUM];									/*调试数据*/
}S_ALGO_OUTPUT_RECORD;

/* 算法输入——司机操纵参考数据*/
typedef struct TAG_AlgoTargetLineRef
{
	UINT16	ValidNum;   												/*有效个数*/
	UINT16	Distance[ALGO_DRIVER_CTL_DATA_NUM];  						/*距离0点的相对距离*/
	UINT16  Speed[ALGO_DRIVER_CTL_DATA_NUM];   							/*速度*/
	INT16   Force[ALGO_DRIVER_CTL_DATA_NUM];    						/*正为牵引力/负为电制动力*/
	UINT16  PressureDecrement[ALGO_DRIVER_CTL_DATA_NUM];				/*减压量*/
	UINT8   RunningStatus[ALGO_DRIVER_CTL_DATA_NUM];  					/*工况： 0x01-惰行,0x02-牵引,0x03-电制动,0x04-空气制动,0x05-空电混合制动*/
	UINT8   Scene[ALGO_DRIVER_CTL_DATA_NUM];    						/*场景   1-其他，2-长大下坡，3-长大上坡，4-分相，5-起车，6-停车，7-贯通试验*/
}S_ALGO_TARGETLINE_REF;


/*--算法输入——限速信息--------------------------*/
typedef struct TAG_LimitSpeedCurve{
  UINT8   RsSpdType;														/*限速类型 */
  UINT16  RsSpd;															/*限速 */
  UINT16  RsSpdLength;														/*限速长度 */ 
  UINT16  RelativeDist;														/*距离0点位置相对距离 单位：米 */
}S_LIMITSPEEDCURVE;
typedef struct TAG_Input_LimitSpeedCurve
{
	UINT16 LimitSpeedValidNum;												/*限速有效个数*/  
	S_LIMITSPEEDCURVE LIMITSPEED[ALGO_LIMITSPEED_MAX_NUM];					/*限速数组*/
}S_INPUT_LimitSpeedCurve;

/*--算法输入——坡道信息----------------------*/
typedef struct TAG_Ramp
{
  INT16  Grade;																/*坡度千分比，上坡为正，分辨率0.1 */
  UINT16 GradeLength;														/*坡道长度，范围：0～65535,单位：米 */ 
  UINT16 GradeRelatDist;													/*距离0点位置相对距离 单位：米 */ 
}S_Ramp;

typedef struct TAG_Input_Ramp
{
  UINT16 RampValidNum;                                  					/*坡道有效个数*/  
  S_Ramp Ramps[ALGO_GRADIENT_MAX_NUM];										/*坡道数组*/  
}S_INPUT_RAMP;

/*--算法输入——弯道信息----------------------*/
typedef struct TAG_Curve
{
  INT16   Radius;															/*D15=1：左弯 D15=0：右弯，D14～D0：弯道半径*/
  UINT16  CurveLenth;														/*弯道长度，范围：0～65535,单位：米 */
  UINT16  CurveRelatDist;													/*距离0点位置相对距离 单位：米 */ 
}S_CURVE;
typedef struct TAG_Input_Curve
{
  UINT16  CurveValidNum;													/*弯道有效个数*/  
  S_CURVE Curves[ALGO_RADIUS_MAX_NUM];										/*弯道数组*/
}S_INPUT_CURVE;

/*--算法输入——隧道信息----------------------*/
typedef struct TAG_Tunnel
{
  UINT16  TunnelLenth;														/*隧道长度，范围：0～65535,单位：米 */
  UINT16  TunnelRelatDist;													/* 距离0点位置相对距离 单位：米 */ 
}S_TUNNEL;
typedef struct TAG_Input_Tunnel
{
  UINT16   TunnelValidNum;                                				    /*隧道有效个数*/  
  S_TUNNEL Tunnel[ALGO_TUNNEL_MAX_NUM];                      				/*隧道数组*/    
}S_INPUT_TUNNEL;


/** 算法输入—站中心位置 */
typedef struct TAG_StationInfo
{
  //UINT16										RouteNo;				    /** LKJ2000数据交路号 */
  UINT32										StationNo;					/** LKJ2000车站号 */
  UINT16										RelativeDist;				/** 站中心位置相对距离，范围：0～10000,单位：米 */
} S_STATIONINFO;

typedef struct TAG_Input_StaionInfo 
{
  UINT8											StationNum;				/** 站中心数量 */
  S_STATIONINFO				StationInfo[ALGO_STATION_MAX_NUM];
} S_INPUT_STATIONINFO;

/** 算法输入-信号机信息 */
typedef struct TAG_LocoSignal {
  UINT8								SignalType_E;				/** 信号机类型 */
  UINT8								SignalNoHead[6];		    /** 编号字符头 */
  UINT8								backup[2];		    		/** 预留*/
  UINT16							SignalNo;				    /** 信号机编号, 范围为1～655350 */
  UINT16 							RelativeDist;			    /** 信号机位置相对距离，范围：0～10000,单位：米 */
} S_LOCOSIGNAL;

typedef struct TAG_Input_SignalInfo {
  UINT8								SignalNum;				    /** 信号机数量，范围0-50 */
  S_LOCOSIGNAL						SignalInfo[16];//SignalInfo[ALGO_SEMAPHORE_MAX_NUM];
} S_INPUT_SIGNALINFO;

/** 闭塞信息 */
typedef struct TAG_BlockInfoSet {
  UINT16 							 BlockFlag;					            /** 闭塞标志：0：自动闭塞；1：半自动闭塞 */
  UINT16							 BlockRelatDist;			            /** 闭塞起点位置相对距离，范围：0～10000，单位：米 */
  UINT32							 BlockLength;			                /** 闭塞长度，范围：0～65535,单位：米 */
} S_BlockInfoSet;
/** 闭塞信息组 */
typedef struct TAG_Input_BlockInfoSet{
  UINT8								 Num;					                /** 闭塞数量，数据范围：0～10 */
  S_BlockInfoSet				     BlockInfo[ALGO_BLOCK_MAX_NUM];		    /** 起点位置相对距离，范围：0～10000,单位：米 */
} S_INPUT_BLOCKINFOSET;


/*算法输入——基础线路数据结构体*/
typedef struct TAG_ForwardRLData
{
  S_INPUT_STATIONINFO				 FWStationInfo;							/*站中心信息*/
  S_INPUT_SIGNALINFO				 FWSignalInfo;							/*信号机*/
  S_INPUT_LimitSpeedCurve  			 FWLimitSpeed;                 			/*限速*/
  S_INPUT_RAMP  					 FWRamps;								/*坡度*/
  S_INPUT_CURVE  					 FWCurves;								/*弯道*/
  S_INPUT_TUNNEL  				     FWTunnels;                    			/*隧道*/
  S_INPUT_BLOCKINFOSET               FWBlocksInfo;							/*闭塞*/
}S_FORWARDRLDATA;


/*算法输入——列车运行时分数据结构体*/
typedef struct TAG_TrainTimeTable
{
	UINT8  ValidNum;   						                        		/*有效个数*/
	UINT8  AddOnTimeHour[ALGO_TIME_TABLE_NUM];                 				/*附加时分-时*/
	UINT8  AddOnTimeMin[ALGO_TIME_TABLE_NUM];                  				/*附加时分-分*/
	UINT8  AddOnTimeSec[ALGO_TIME_TABLE_NUM];                  				/*附加时分-秒*/
	UINT8  IntervalTimeHour[ALGO_TIME_TABLE_NUM];              				/*区间运行时分-时*/
	UINT8  IntervalTimeMin[ALGO_TIME_TABLE_NUM];               				/*区间运行时分-分*/
	UINT8  IntervalTimeSec[ALGO_TIME_TABLE_NUM];               				/*区间运行时分-秒*/
	UINT8  ArrivedTimeHour[ALGO_TIME_TABLE_NUM];               				/*到达时刻-时*/
	UINT8  ArrivedTimeMin[ALGO_TIME_TABLE_NUM];                				/*到达时刻-分*/
	UINT8  ArrivedTimeSec[ALGO_TIME_TABLE_NUM];                				/*到达时刻-秒*/
	UINT8  StartTimeHour[ALGO_TIME_TABLE_NUM];                 				/*开车时刻-时*/
	UINT8  StartTimeMin[ALGO_TIME_TABLE_NUM];                  				/*开车时刻-分*/
	UINT8  StartTimeSec[ALGO_TIME_TABLE_NUM];                 				/*开车时刻-秒*/
	UINT8  SuspendTimeHour[ALGO_TIME_TABLE_NUM];               				/*站停时刻-时*/
	UINT8  SuspendTimeMin[ALGO_TIME_TABLE_NUM];                				/*站停时刻-分*/
	UINT8  SuspendTimeSec[ALGO_TIME_TABLE_NUM];                				/*站停时刻-秒*/
	UINT8  ResBytes[ALGO_TIME_TABLE_NUM];               			  		/*预留字节*/
	UINT16 IntervalASpeed[ALGO_TIME_TABLE_NUM];         			  		/*区间平均速度*/
	UINT16 IntervalCourse[ALGO_TIME_TABLE_NUM];                			    /*区间里程*/
	UINT16 CurStationRouteNo[ALGO_TIME_TABLE_NUM];	  						/*当前车站交路号*/				 
	UINT16 CurStationSN[ALGO_TIME_TABLE_NUM];								/*当前车站车站号*/	
	UINT16 NextStationRouteNo[ALGO_TIME_TABLE_NUM];							/*下一车站交路号*/				 
	UINT16 NextStationSN[ALGO_TIME_TABLE_NUM];								/*下一车站车站号*/
}S_TRAINTIMETABLE;

/*算法输入——特殊区段数据*/
typedef struct TAG_SpecialZoneData{
	UINT8  ValidNum;   						                        	    /*有效个数*/
	UINT8  SpecialAreaCode[ALGO_SPECIAL_ZONEDATA_NUM];         				/*特殊区段代码*/
	UINT8  Mark[ALGO_SPECIAL_ZONEDATA_NUM];	                  				/*标志*/		
	UINT16 Relative_Distance[ALGO_SPECIAL_ZONEDATA_NUM];					/*距0点距离*/ 
	UINT16 MininumSpeed[ALGO_SPECIAL_ZONEDATA_NUM];           				/*最低限速*/
 	UINT16 ZoneLength[ALGO_SPECIAL_ZONEDATA_NUM];              				/*区段长度*/
	UINT16 Res[ALGO_SPECIAL_ZONEDATA_NUM];                	    			/*预留*/
}S_SPECIALZONEDATA;

/*算法输入——侧线股道数据信息*/
typedef struct TAG_SideTrackData{
	UINT8  ValidNum;   						                        		/*有效个数*/
	UINT8  SideTrackSN[50];//[ALGO_SIDE_TRACK_NUM];            				/*侧线轨道号*/
	UINT8  Res[50];//[ALGO_SIDE_TRACK_NUM];                           		/*预留*/
	UINT16 ValidTrackLength[50];//[ALGO_SIDE_TRACK_NUM];	      			/*侧线有效长度*/				 
	UINT16 StopLocToFSignal[50];//[ALGO_SIDE_TRACK_NUM];       				/*停车位置距离前方信号机距离*/	
}S_SIDETRACKDATA;

/*算法输入——机车命令及状态-CCU+BCU*/
typedef struct TAG_LocoDynCmdAndStatus
{
	UINT8   ATOFlag;                                       					/*机车控制信号	bit0-自动驾驶允许,bit1-自动驾驶激活 ,bit2-自动发车，bit3-ATO控车，bit4-主控接管保护控制*/
	UINT8   RunningStatus;                                 					/*实际工况： Bit0:实际工况-牵引,Bit1:实际工况-电制动*/
	UINT8   FltStatus;                               						/*故障状态字节：
	                                                                          Bit0：空转/滑行 
	                                                                          Bit1：保护性降弓 
	                                                                          Bit2：保护性分主断  
	                                                                          Bit3：分相装置故障 
	                                                                          Bit4：压缩机故障 
	                                                                          Bit5：LKJ故障 
	                                                                          Bit6：列尾故障  
	                                                                          Bit7 ：动力损失*/
	UINT8   SingalStatus;                               					/*信号异常状态字节：
	                                                                          Bit0：信号异常-信号机前控速20km/h
	                                                                          Bit1：--
	                                                                          Bit2：-- 
	                                                                          Bit3：-- 
	                                                                          Bit4：-- 
	                                                                          Bit5：-- 
	                                                                          Bit6：--  
	                                                                          Bit7 ：-*/
	UINT8   LocoStatus;														/*机车状态字节：Bit0：主断闭合状态 Bit1：空电联合隔离 Bit2：惩罚制动施加状态 Bit3：紧急制动施加状态 
	                                                                          Bit4：停放制动缓解状态（1=缓解）Bit5:牵引封锁 Bit6:电制封锁*/
	UINT8   DmiCmd;															/*人机交互命令：Bit0：赶点模式  Bit1：点单模式, Bit2:慢行模式 Bit3: 贯通  bit4:自动模式下人工缓解   Bit5~Bit7 预留*/
	UINT8   FastRunTime;													/*快行时间（min）-司机设置*/
	UINT8   SlowRunTime;													/*慢行时间（min）-司机设置*/
	UINT8	BrakeTestFlag;												    /*试闸标志：0xA5-需试闸，运动状态下进入自动驾驶算法判断是否进行贯通试验*/
	UINT8   BackOffFlag;                                   					/*后溜标志:0xA5-后溜*/
	UINT8   BigBrakePosition;                              					/*大闸位置-Bit0：运转 Bit1：最小制动 Bit2：常用制动 Bit3：全制动 Bit4：抑制 Bit5：重联Bit6：紧急制动 Bit7：预留*/
	UINT8   SmallBrakePosition;                            					/*小闸位置-Bit0：运转 Bit1：制动区  Bit2：全制动 Bit3：单缓激活 Bit4：预留	*/
	UINT8   MotorIsoStatus;													/*Bit0：本节车I架电机1隔离
																			  Bit1：本节车I架电机2隔离
																			  Bit2：本节车II架电机1隔离
																			  Bit3：本节车II架电机2隔离
																			  Bit4：它节车I架电机1隔离
																			  Bit5：它节车I架电机2隔离
																			  Bit6：它节车II架电机1隔离
																			  Bit7：它节车II架电机2隔离
																			*/
	UINT8   BCUBrakeHandleType;                            					/*闸类型*/
	UINT8   BCUPressureType;                              	 				/*定压类型*/
	UINT8   TrainTailType;                                 					/*列尾类型*/
	UINT8   TrainLoadType;                                 					/*负载类型*/
	UINT8   VehicleType;                                   					/*车辆类型*/
	UINT8   ConsistType;                                   					/*编组模式*/
	UINT8   ClosedVehicleNums;                                   			/*关门车数量*/
	UINT8   SleepLocoNums;													/*附挂机车数量*/
	UINT16  SlowRunMaxSpeed;												/*慢行最高限速*/
	UINT16  BrkShoePresPHT;													/*每百吨闸瓦压力*/
	UINT16  PressureDecrement;                      						/*当前减压量（Kpa）*/
	UINT16  ABHExTargetACK;													/*列车管目标值减压量设定反馈*/
	UINT16  IBHExTargetACK;													/*制动缸目标值设定反馈*/
	UINT16  PressureTotalVal;                       						/*当前总风缸压力*/	
	UINT16  BrakeCylinder;						   							/*当前制动缸压力*/	
	UINT16  EqualReservoir; 						   						/*当前均衡风缸*/	
	UINT16  RateOfFlow;                             						/*充风流量*/	
	UINT16  TrainTailValue;                         						/*尾部风压*/	
	UINT16  PriVolt;														/*机车原边电压（V）0-38000v*/
	UINT16  TcmsSpeed;														/*当前TCMS速度，1=0.01km/h*/
	UINT16  Force;          							   					/*当前实际牵引/电制动 1=0.1KN*/
	UINT16  TrcFmax;                                   						/*当前可用最大牵引力*/	
	UINT16  EBrFmax;                                   						/*当前可用最大电制动力*/	
	UINT16  TrcPowerLostPercent;                                   			/*牵引力动力损失百分比1=0.1%*/	
	UINT16  EBrkPowerLostPercent;                                   		/*电制力动力损失百分比1=0.1%*/	
	UINT32  Position;   							   						/*机车相对距离-相对基础线路更新时机车0点的位置距离*/
	UINT32  TravlledDistance;                       						/*机车位移，累计位移,单位：米 */
}S_LOCO_DYNCMDANDSTATUS;

/*算法输入——LKJ防护曲线*/
typedef struct TAG_LkjProtectCurve
{	
	UINT16  LimitSpeed[ALGO_LIMIT_SPEED_NUM_MAX];            				/*防护限速数组*/
}S_LKJ_PROJECTCURVE;

/*算法输入——LKJ动态控制数据*/
typedef struct TAG_LKJDynCtlData
{
	UINT8 	Singal;          									   			/*机车信号*/
	UINT8 	LKJMode;														/*监控状态*/
	UINT8   ResByte;														/*预留字节*/
	UINT8   TrainType;                                 	  					/*列车类型*/
	UINT16  TrainPipe;														/*列车管*/	
	UINT16  TrainWeight;													/*列车总重*/
	UINT16  TrainLength;													/*列车计长*/
	UINT16  VehicleNum;														/*车辆辆数*/
	UINT16  LocoType;														/*机车类型*/
	UINT16  WheelDiameter;													/*机车轮径*/	
	UINT16  LkjSpeed;        							   					/*当前LKJ速度*/
	/*新增算法接口数据-20180711-likai*/
	UINT16 	HeavyCar;													    /*重车数量*/
	UINT16 	EmptyCar;				  									    /*空车数量*/
	UINT16  NextSigRelaDist;				  							    /*机车到下一信号机的距离*/
	UINT8  	CurrentSideLine;			                                    /*本分区侧线*/
	UINT8  	NextSideLine;				                                    /*下分区侧线*/
	
	/*增加本分区支线 和下分区支线号*/
	UINT8  	CurrentBranch;			        								/*本分区支线 */
	UINT8  	NextBranch;				        								/*下分区支线 */
}S_LKJ_DYNAMICCTLDATA;


/*算法输入——过分相信号*/
typedef struct TAG_NeutralSignal
{
	UINT8 NeutralForetellFlag;   											/*分相预告信号*/
	UINT8 NeutralForceFlag;                                   				/*分相强断信号*/
	UINT8 NeutralPassFlag;                                   				/*分相通过信号*/
	UINT8 LocoInNeutral;													/*正在过分相*/
}S_NEUTRALSIGNAL;


/*机车功耗；耗电量*/
typedef struct TAG_LocoElectrical
{
	UINT32 ConsumeElectrical;   											/*机车消耗的电量*/
	UINT32 ReElectrical;                         	          				/*机车再生的电量*/

}S_LOCOELECTRICAL;



/** ATO时间信息 */
typedef struct TAG_AcsTimeDate 
{
	S_ATO_DATETIME	  Year_TimeDate;
	UINT32			  SecondTime;
} S_ACS_TIME_DATE;

typedef struct TAG_DynDate
{
	UINT32			  Total_Dyn_Num;
} S_DYN_DATE;


/*特殊数据*/
typedef struct TAG_SpecialData
{
	S_LOCOELECTRICAL  LocoElectrical;
	S_ACS_TIME_DATE	  TimeDate;	
	S_DYN_DATE		  DynDate;
}S_ACS_SPECIALDATA;


/*组包(Para1)——动态周期性输入数据打包*/
typedef struct TAG_AlgoInputDynData
{
	S_LOCO_DYNCMDANDSTATUS LocoDynCMDandStatus;           					/*机车命令及状态*/
	S_LKJ_PROJECTCURVE     LkjProjectCurve;              	 				/*LKJ动态防护曲线*/
	S_LKJ_DYNAMICCTLDATA   LKJDynamicCtlData;			  					/*LKJ动态控制数据*/
	S_NEUTRALSIGNAL        NeutralSignal;                 					/*过分相信号*/
}S_ALGO_INPUT_DYNDATA,S_ACS_DYNDATA;

/*组包(Para2)——条件发送输入数据打包*/
typedef struct TAG_AlgoInputBasicData
{ 
  UINT32 				 UpDataLife;                                    	/*数据更新标识,更新一次，值加1*/
  S_FORWARDRLDATA 		 ForwardRailLineData;        						/*前方基础线路数据*/
  S_ALGO_TARGETLINE_REF  TargetLineRef;                		 				/*目标曲线参考数据-司机驾驶数据*/
  S_TRAINTIMETABLE       TrainTimeTable;                					/*列车运行时分表*/
  S_SPECIALZONEDATA      SpecialZoneData;              	 					/*特殊区段数据*/
  S_SIDETRACKDATA        SideTrackInfo;                 					/*侧线股道数据*/
}S_ALGO_INPUT_BASICDATA,S_ACS_BASICDATA;

/*算法输出组包(Para3)*/
typedef struct TAG_AlgoOutputCtlData
{ 
	S_ALGO_RUNSTATUS          AlgoOutputStaData;							/*算法运行状态输出*/		  
	S_ALGO_OUTPUT_CTLDATA 	  AlgoOutputCtlData;          					/*算法控制输出*/
	S_ALGO_OUTPUT_TARGETLINE  AlgoOutputTargetLine;       					/*目标曲线输出*/
	S_ALGO_OUTPUT_RECORD      AlgoOutputRecord;           					/*算法输出记录字节*/
}S_ALGO_OUTPUT_CTRLDATA,S_ACS_CTRLDATA;

/*组包*/
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
 *Function: 解析管道0的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe0_Analyze(UINT8* Pipe0,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe1_Analyze
 *Function: 解析管道1的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe1_Analyze(UINT8* Pipe1,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe2_Analyze
 *Function: 解析管道2的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe2_Analyze(UINT8* Pipe2,
								  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe3_Analyze
 *Function: 解析管道3的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe3_Analyze(UINT8 *Pipe3,
		  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe4_Analyze
 *Function: 解析管道4的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe4_Analyze(UINT8 *Pipe4,
  	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe5_Analyze
 *Function: 解析管道5的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe5_Analyze(UINT8 *Pipe5,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe6_Analyze
 *Function: 解析管道6的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe6_Analyze(UINT8 *Pipe6,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
/******************************************************************************
 *Name    : ACS_Data_pipe7_Analyze
 *Function: 解析管道7的数据
 *Para    : S_PLAN_OUTPUTDATA* const pPlanOutputData
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Tangwei 	 2019/08/05      create
******************************************************************************/
E_SysBool  ACS_Data_pipe7_Analyze(UINT8 *Pipe7,
	  	  	  	  	  	  	  	  S_ATO2ACS_INPUTPARA* pA2AInputPara);
#endif
