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

#define LINECALCLNUMS				(200U)			/*坡道加算总计算个数*/

#define GRAVIT_ACCELERATION         (9.81F)   		/*重力加速度*/

#define SENSE_POINT_MAX_NUM			(50U)			/*标记点最大个数*/
#define SENSE_CHGPNT_MAX_NUM		(200U)			/*标记点最大个数*/

#define NEUTRAL_POINT_MAX_NUM       (10U)			/*分相标记点最大个数*/
#define BRAKETEST_POINT_MAX_NUM     (5U)			/*贯通试验标记点最大个数*/
#define STOPBEFNEU_POINT_MAX_NUM    (5U)			/*分相前停车点最大个数*/
#define STOPBEHNEU_POINT_MAX_NUM    (5U)			/*分相后停车点最大个数*/
#define PASSMARKSTOP_POINT_MAX_NUM  (20U)			/*过标停车点最大个数*/

#define SENSE_SLAVELOCO_MAX_NUM     (3U)            /*从控机车的最大数量*/
#define TARGETLINE_MAX_NUM          (20U)           /*目标曲线的最大数量*/

#define LOCO_UNITTRAIN_CHNGTIME     (5U)            /*单机/单元列车工况转换时间*/
#define HEAVYTRAIN_CHNGTIME         (10U)           /*组合/重载列车工况转换时间*/

/*UINT类型的初始化值*/
#define c_UintInitValue            (0U)
/*INT类型的初始化值*/
#define c_IntInitValue             (0L)
/*零速启动牵引力与阻力的比值(预乘100)*/
#define c_TracResiRatio            (130U)

/*2019-1-16 新增，TangWei，标记点最大个数*/
#define	BADGE_POINT_MAX_NUM 			(30U)
#define	RAILLINE_BADGEPOINT_MAX_NUM		(30U)

/*变坡点使用参数*/
#define ALGO_SENSE_DIFFVALUE		(3.0F)			/*大于该值视为变坡*/
#define ALGO_SENSE_JUDGE_NUM		(10U)			/*连续JUDGE_NUM+2个值大于DIFF_VALUE判为变坡*/
/*防护曲线使用参数*/
#define SPD_STOP_POINT_PRE_DIS		(150U)			/*停车结束点前移量,单位m*/
#define SPD_DOWN_POINT_PRE_DIS		(100U)			/*减速结束点前移量,单位m*/
#define SPD_UP_POINT_DELY_DIS		(100U)			/*减速结束点前移量,单位m*/
#define LKJ_SPD_CHG_MAX_NUM			(20U)			/*防护曲线变化数量最大值*/
/*弯道阻力系数*/
#define ALGO_SENSE_CURVE_PARA		(600U)			
/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
/*列车编组定义*/
typedef enum TAG_ConsistType
{
	e_OnlyLoco    	  = 0x10,                  /*单机车*/
	e_OneTrian   	  = 0x11,                  /*小列*/
	e_OneOneTrain     = 0x22,                  /*1+1*/
	e_TwoZeroTrain    = 0x33,                  /*2+0*/
	e_TwoOneTrain     = 0x44,                  /*2+1*/
	e_ThreeZeroTrain  = 0x55,                  /*3+0*/
	e_TwoTwoTrain     = 0x66                   /*2+2*/
}E_MODEL_CONSISTTYPE;

/*车辆定义*/
typedef enum TAG_VehicleType
{
	e_CNONE    	  = 0x00,                  /*0x00：XX*/
	e_C64    	  = 0x11,                  /*0x11：C64*/
	e_C70   	  = 0x22,                  /*0x22：C70*/
	e_C80   	  = 0x33                   /*0x33：C80*/
}E_MODEL_VEHICLETYPE;

/*列尾定义*/
typedef enum TAG_EOTType
{
	e_CtrlEOT    	  = 0xA5,                  /*列尾类型:0xA5：可控列尾*/
	e_NomlEOT   	  = 0x5A                   /*0x5A：普通列尾*/
}E_MODEL_EOTTYPE;
#if 1
/*限速变化标识*/
typedef enum TAG_SpdChngType
{
	e_NormalSpdPt     = 0x00,                                           /*LKJ限速无变化点*/
	e_SpdRiseStartPt  = 0x11,                                           /*LKJ限速升高起点*/
	e_SpdRiseEndPt    = 0x22,                                           /*LKJ限速升高终点*/
	e_SpdDeclStartPt  = 0x33,                                           /*LKJ限速下降起点*/
	e_SpdDeclEndPt    = 0x44,                                           /*LKJ限速下降终点*/
    /*2019.01.04新增，YipingYang，增加限速上升点、下降点的分类标识*/
	e_SpdRisePt       = 0x55,                                           /*LKJ限速上升点*/
	e_SpdDeclPt       = 0x66                                            /*LKJ限速下降点*/
}E_SENSE_SPDCHNGTYPE;

/*2019-1-15 新增，TangWei，标记点类型枚举*/
typedef enum TAG_BadgeType
{
	e_SpdUpPnt			 = 0x01,   				/*加速标记点*/
	e_SpdDwPnt			 = 0x02,   				/*减速标记点*/
	e_NuetralPnt		 = 0x03,   				/*分相标记点*/
	e_BrkTestPnt		 = 0x04,   				/*贯通试验标记点*/
	e_NormalStopPnt	 	 = 0x05,   				/*正常停车标记点*/
	e_OutSideStopPnt	 = 0x06,   				/*机外停车标记点*/
	e_FrontNutrlStopPnt  = 0x07,   				/*分相前停车标记点*/
	e_BehindNutrlStopPnt = 0x08,   				/*分相后停车标记点*/
	e_BigUpRampNuetralPnt  = 0x09,   			/*长大坡道过分相*/
	e_BigDwRampPnt		   = 0x0A,				/*长大下坡起始标记点*/
	e_MinLimitPnt          = 0x0B               /*信号机最低限速*/
}E_BADGETYPE;
#endif
/*特殊区段标识*/
typedef enum TAG_E_SpecialAreaCode
{
  e_NuetralArea       = 0x88U,        /*分相区段*/
  e_SandArea          = 0x89U,        /*撒沙区段*/
  e_NoStopArea        = 0x8AU,        /*禁止停车区段*/
  e_ConstructionArea  = 0x8BU,        /*施工区段*/
  e_FloodArea         = 0x8CU,        /*防汛地段*/  
  e_BrkTestArea       = 0x8DU,        /*贯通试验*/
  e_BehNuetralArea    = 0x78U,        /*分相后停车点*/
  e_BefNuetralArea    = 0x79U,        /*分相前停车点*/
  e_MinLimitArea      = 0x7AU,        /*信号机最低限速*/
  e_OutsideArea       = 0x7BU,        /*机外停车点*/
  e_SpeSpeed          = 0x7CU,        /*特殊速度区段*/
  e_SideTraNoSignal   = 0x7DU         /*侧线掉白收码点*/
}E_SENSE_SPECIALAREACODE;

/** LKJ工作模式 */
typedef enum TAG_E_Algo_LKJ_CtrlMode {
  e_Standby      =0x00,														/** 待机 */
  e_EntExitDepot =0x02,													    /** 出入段 */
  e_Shunt        =0x03,														/** 调车 */
  e_Degrade      =0x04,														/** 降级 */
  e_General      =0x05,														/** 通常 */
  e_Visual       =0x06,														/** 目视行车 */
  e_RemoteLKJ    =0x07,													    /** 非本务 */
  e_NoAdvance    =0x08,													    /** 无防冒 */
  e_Other        =0x09														/** 与其他ATP结合 */
} E_ALGO_LKJ_CtrlMode;

/** 信号机类型 */
typedef enum TAG_E_Algo_SignalType {
  e_RvSignal                   =0x01,								        /** 接车进路信号 */
  e_EnterSignal                =0x02,								        /** 进站信号机 */
  e_RvDeSignal                 =0x03,								        /** 接发车进路信号机 */
  e_DepartSiganl               =0x04,								        /** 发车进路信号机 */
  e_ExitSignal                 =0x05,								        /** 出站信号机 */
  e_PassedSignal               =0x06,								        /** 通过信号机 */
  e_PermitSignal               =0x07,								        /** 容许信号机 */
  e_ApproachSignal             =0x08,								        /** 接近信号机 */
  e_AdvancedSignal             =0x09,								        /** 预告信号机 */
  e_SplittedSignal             =0x0A,								        /** 分割信号机 */
  e_LineLocationPassedSignal   =0x0B,								        /** 线路所通过信号机 */
  e_WaistSwitchSignal          =0x0C,								        /** 腰岔信号机 */
  e_LabelSignal                =0x28								        /** 信号标志牌信号机 */
} E_ALGO_SignalType;

/** LKJ15机车信号 */
typedef enum TAG_E_Algo_LocoSignal_15 {
  e_L3         =0x01,														/** 绿3灯 */
  e_L2         =0x02,														/** 绿2灯 */
  e_L          =0x03,														/** 绿灯 */
  e_LU         =0x04,														/** 绿黄灯 */
  e_LU2        =0x05, 														/** 绿黄2灯 */
  e_U          =0x06,														/** 黄灯 */
  e_U2S        =0x07,														/** 黄2闪灯 */
  e_U2         =0x08,														/** 黄2灯 */
  e_L6         =0x09,														/** 绿6灯 */
  e_UUS        =0x0A,												        /** 双黄闪灯 */
  e_UU         =0x0B,														/** 双黄灯 */
  e_HB         =0x0C,													    /** 红黄闪灯 */
  e_HU         =0x0D,														/** 红黄灯 */
  e_H          =0x0E,														/** 单红灯 */
  e_L4         =0x0F,														/** 绿4灯 */
  e_L5         =0x10,														/** 绿5灯 */
  e_257Hz      =0x11,														/** 25.7Hz */
  e_279Hz      =0x12,														/** 27.9Hz */
  e_NoSignal_H =0x13,													    /** 无码H灯 */
  e_NoSignal_B =0x14,												        /** 无码白灯 */
  e_U3         =0x15														/** 黄3灯 */
} E_ALGO_LocoSignal;

/*2019.01.04新增，TangWei，变坡点结构体*/
typedef struct TAG_ChangeRampPoint
{
	UINT8  ChangeRampPointNum;							/*变坡点总数*/
	UINT32 ChangeRampPointDis[SENSE_CHGPNT_MAX_NUM];	/*变坡点数组，单位m，距车头距离*/
	
	/*2019.04.12新增，TangWei，变坡点属性*/
	REAL32 ChangeRampPointAveRamp[SENSE_CHGPNT_MAX_NUM];	/*变坡点坡度值 ，计算范围为距车头0到ChangeRampPointDis[ChangeRampPointNum-1]；
															(ChangeRampPointAveRamp[0]为机车位置到索引为0的变坡点这段的平均值；
			  						  	  	  	  	  	  	 ChangeRampPointAveRamp[1]为变坡点数组索引为0到索引为1这段的平均值，以此类推)*/
	
} S_CHANGERAMPPOINT;

/*20190305新增，zxm，长大坡道数据结构*/
typedef struct TAG_LongRampInf
{
	E_SysBool IsExistLongRamp;							/*是否存在长大坡道，e_TRUE为存在，e_FALSE为不存在*/
	E_SysBool IsAccessInRamp;							/*是否处于长大坡道中,e_TRUE为在长大坡道中，e_FALSE为不在*/
	UINT16    PosFromLoco;								/*长大坡道起始位置，距离车头*/
	UINT16    PosEndFromLoco;							/*长大坡道结束位置，距离车头*/
	INT16     RampValue;								/*长大坡道平均值*/
	UINT8     RampType;									/*坡道类型：0为长大下坡，1位长大上坡*/
}S_LONGRAMPINF;

/**2019.01.04新增，TangWei，线路数据处理结果*/
typedef struct TAG_RaillineCalc
{
	REAL32 RailAddRes[LINECALCLNUMS];					/*线路单位附加阻力，单位1=1N/KN*，
														      例：步长为50，离车头85m处为 RailAddRes[1]*/
	S_CHANGERAMPPOINT ChangeRampPointStr;				/*变坡点结构体*/
	S_LONGRAMPINF	  longRamp;						    /*长大坡道*/
} S_RAILLINECALC_RESULT;


/*2019-1-28删除TAG_StopPoint，TAG_SpeedDownPoint，TAG_SpeedUpPoint唐伟*/



/*分相区段组信息*/
typedef struct TAG_NeutralInfo
{
	UINT16	    MininumSpeed;			/*分相区段最低速度*/
	UINT16	    Neutral_BgnPntDis;		/*分相区段开始点距0点位置，单位m*/
	UINT16	    ZoneLength;		        /*分相区段长度，单位m*/
} S_NEUTRAL_INFO;

typedef struct TAG_NeutralPoint
{
	E_BADGETYPE      BadgeType;
	UINT16	         NeutralNum;		/*分相区段个数*/
	S_NEUTRAL_INFO	 NeutralInfo[NEUTRAL_POINT_MAX_NUM];		
} S_NEUTRAL_POINT;

/*贯通试验组信息*/
typedef struct TAG_BrakeTestInfo
{
	UINT8      Mark;                    /*标志*/
	UINT16	   MininumSpeed;			/*贯通试验最低速度*/
	UINT16	   BrakeTest_BgnPntDis;	    /*贯通试验开始点距0点位置，单位m*/
	UINT16	   ZoneLength;	            /*贯通试验长度，单位m*/
	UINT8      DoBrakeTestFlag;         /*定点试闸标志,1:定点试闸*/
} S_BRAKETEST_INFO;

typedef struct TAG_BrakeTestPoint
{
	E_BADGETYPE       BadgeType;
	UINT16	          BrakeTestNum;		/*贯通试验个数*/
	S_BRAKETEST_INFO  BrakeTest_Info[BRAKETEST_POINT_MAX_NUM];	
} S_BRAKETEST_POINT;

/*分相前停车点组信息*/
typedef struct TAG_STOPBEFNEUInfo
{
	UINT8      Mark;                    /*标志*/
	UINT16	   StopBefNeu_BgnPntDis;	/*分相前停车点距0点位置，单位m*/
	UINT16	   StopFlag;	            /*1：黄灯停车*/
} S_STOPBEFNEU_INFO;

typedef struct TAG_StopBefNeuPoint
{
	E_BADGETYPE        BadgeType;
	UINT16	           StopBefNeuNum;		/*分相前停车点个数*/
	S_STOPBEFNEU_INFO  StopBefNeu_Info[STOPBEFNEU_POINT_MAX_NUM];	
} S_STOPBEFNEU_POINT;

/*分相后停车点信息*/
typedef struct TAG_StopBehNeuPoint
{
	E_BADGETYPE BadgeType;
	UINT16	   StopBehNeuNum;		/*分相后停车点个数*/
	UINT16     StopBehNeuRelaDist[STOPBEHNEU_POINT_MAX_NUM];	
} S_STOPBEHNEU_POINT;

/*分相前/后停车点距0点距离*/
typedef struct TAG_StopNeuRelaDist
{
	
	UINT32		 StopBeh_NeuRelaDist[RAILLINE_BADGEPOINT_MAX_NUM];				/*分相后停车点距0点位置，单位m*/
	UINT32		 StopBef_NeuRelaDist[RAILLINE_BADGEPOINT_MAX_NUM]; 				/*分相前停车点距0点位置，单位m*/	
	
} S_STOP_NEU_RELA_DIST;

/*过标停车点信息*/
typedef struct TAG_PassMarkStopInfo
{
	E_BADGETYPE BadgeType;
	UINT8  SideTrackSN;            					/*侧线轨道号*/
	UINT16 ValidTrackLength;	      				/*侧线有效长度*/				 
	UINT16 StopLocToFSignal;       					/*停车位置距离前方信号机距离*/		
} S_PASSMARKSTOP_INFO;

typedef struct TAG_PassMarkStopPoint
{
	E_BADGETYPE BadgeType;
	UINT16	             PassMarkStopNum;		    /*过标停车点个数*/
	S_PASSMARKSTOP_INFO  PassMarkStop_Info[PASSMARKSTOP_POINT_MAX_NUM];	
} S_PASSMARKSTOP_POINT;
#if 0
/*限速曲线标记点__规划场景识别用-唐伟*/
typedef struct TAG_SpdLimitBadgePoint
{
//	S_STOP_POINT 			StopPoint;			/*停车点*/
//	S_SPEED_DOWN_POINT		SpdDwPnt;			/*限度下降点*/
//	S_SPEED_UP_POINT		SpdUpPnt;			/*限速上升点*/
} S_BADGEPOINT,S_SPDLIMIT_BADGEPOINT;
#endif
/*线路信息标记_规划场景识别用-李铁兵
 * 对于限速标记点：
 * 速度上升区段RelDistance填上升起点位置，MinSpeed填上升起点速度，MaxSpeed填上升终点速度
 * 速度下降区段RelDistance填下降终点位置，MinSpeed填下降终点速度，MaxSpeed填下降起点速度*/
typedef struct TAG_RailLineInfoBadgePoint{
	UINT8  		 ValidNum;   						                            /*有效个数*/
	/*2019.01.23 YipingYang增加下面两个成员*/
	UINT8        NormalStopPntIndex;                                            /*正常停车点的索引值,
																				存在正常停车点时有效*/
	E_SysBool    ExistNormalStopPnt;                                            /*存在正常停车点为e_TRUE*/
	E_BADGETYPE  BadgeType[RAILLINE_BADGEPOINT_MAX_NUM];         			    /*线路标记类型*/
	UINT16 		 RelDistance[RAILLINE_BADGEPOINT_MAX_NUM];				        /*距0点距离*/ 
	UINT16 		 MinSpeed[RAILLINE_BADGEPOINT_MAX_NUM];           			    /*最低限速*/
	UINT16 		 MaxSpeed[RAILLINE_BADGEPOINT_MAX_NUM];           			    /*最高限速*/
 	UINT16 		 ZoneLength[RAILLINE_BADGEPOINT_MAX_NUM];              			/*区段长度*/
	UINT16       Res[RAILLINE_BADGEPOINT_MAX_NUM];                	    		/*预留*/
}S_RAILLINEINFO_BADGEPOINT;


#if 0
/*线路信息标记_规划场景识别用-李铁兵*/
typedef struct TAG_RailLineBadgePoint
{	
	S_NEUTRAL_POINT         NeutralPnt;                                /*分相区*/
	S_BRAKETEST_POINT       BrakeTestPnt;                              /*贯通区*/
	S_STOPBEFNEU_POINT      StopBefNeuPnt;                             /*分相前停车点*/
	S_STOPBEHNEU_POINT      StopBehNeuPnt;                             /*分相后停车点*/
	S_PASSMARKSTOP_POINT    PassMarkStopPnt;                           /*过标停车位置距离前方信号机*/
}S_RAILLINE_BADGEPOINT;
#endif
typedef struct TAG_BadgePointSetIndex
{	
	E_BADGETYPE BadgePointType;	/*标记点类型*/
	//sUINT16		BadgePointDistance[BADGE_POINT_MAX_NUM];/*标记点距车头距离，单位m*/
	UINT8		Index;			/*标记点信息数据区索引*/
}S_BADGEPOINT_SETINDEX;


/*2019-1-15 新增，TangWei，标记点数组*/
typedef struct TAG_All_BadgePoint
{	
	UINT8		BadgePointVaildNum;						/*标记点总个数*/
	//E_BADGETYPE BadgePointType[BADGE_POINT_MAX_NUM];	/*标记点类型*/
	//UINT16		BadgePointDistance[BADGE_POINT_MAX_NUM];/*标记点距车头距离，单位m*/
	//UINT8		Index[BADGE_POINT_MAX_NUM];				/*标记点信息数据区索引*/
	S_BADGEPOINT_SETINDEX BadgePointSetIndex[BADGE_POINT_MAX_NUM];
	S_RAILLINEINFO_BADGEPOINT *pRailLineBadgePointInfo;				
//	S_SPDLIMIT_BADGEPOINT *pSpdLimitBadgePointInfo;
}S_ALL_BADGEPOINT;



/*感知数据-机车相关状态数据-李铁兵*/
typedef struct TAG_LocosStatusData
{
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

	UINT8   LocoStatus;														/*机车状态字节：Bit0：主断闭合状态 Bit1：空电联合隔离 Bit2：惩罚制动施加状态 Bit3：紧急制动施加状态 
	                                                                          Bit4：停放制动缓解状态（1=缓解）Bit5:牵引封锁 Bit6:电制封锁*/
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
	UINT16  PressureDecrement;                      						/*当前减压量（Kpa）*/
	UINT16  ABHExTargetACK;													/*列车管目标值减压量设定反馈*/
	UINT16  IBHExTargetACK;													/*制动缸目标值设定反馈*/
	UINT16  PressureTotalVal;                       						/*当前总风缸压力*/	
	UINT16  BrakeCylinder;						   							/*当前制动缸压力*/	
	UINT16  EqualReservoir; 						   						/*当前均衡风缸*/	
	UINT16  RateOfFlow;                             						/*充风流量*/	
	UINT16  PriVolt;														/*机车原边电压（V）0-38000v*/
	UINT16  TcmsSpeed;														/*当前TCMS速度，1=0.01km/h*/
	UINT16  Force;          							   					/*当前实际牵引/电制动 1=0.1KN*/
	UINT16  TrcFmax;                                   						/*当前可用最大牵引力*/	
	UINT16  EBrFmax;                                   						/*当前可用最大电制动力*/	
	UINT16  TrcPowerLostPercent;                                   			/*牵引力动力损失百分比1=0.1%*/	
	UINT16  EBrkPowerLostPercent;                                   		/*电制力动力损失百分比1=0.1%*/
	/*2019.01.09新增，YipingYang*/
	UINT16  LocoType;                                                       /*机车类型编码*/
	UINT16  BrkInitSpeed;                                                   /*制动初速度，1=0.01km/h*/
	/*2019.01.11新增，zxm*/
	UINT16  WheelDiameter;													/*机车轮径*/	
	UINT16  LkjSpeed;        							   					/*当前LKJ速度*/
	/*2019.03.04,liuyexuan,新增，加速度计算*/
	UINT16  PreSpdCount;													/*本次速度变化所用的周期数*/
	UINT16  BaseSpd;														/*以3周期前速度作为计算加速度的基准速度*/
	UINT16  OrgiSpd;													    /*两周期前的速度值*/
	UINT16	PreSpd;															/*一个周期之前的速度值*/
	REAL32  SpdChg;															/*两个周期的速度变化数值*/
	REAL32	Acceleration;													/*计算得出的加速度值*/
}S_LOCOS_STATUSDATA;


/*感知数据-车辆相关状态数据-李铁兵*/
typedef struct TAG_VehiclesStatusData
{
	UINT8   BCUBrakeHandleType;                            					/*闸类型*/
	UINT8   BCUPressureType;                              	 				/*定压类型*/
	UINT8   TrainLoadType;                                 					/*负载类型*/
	UINT8   VehicleType;                                   					/*车辆类型*/
}S_VEHICLES_STATUSDATA;

/*感知数据-列尾相关状态数据-李铁兵*/
typedef struct TAG_EotStatusData
{	
	UINT8   TrainTailType;                                 				/*列尾类型*/
	UINT16  TrainTailValue;                         					/*尾部风压*/	
}S_EOT_STATUSDATA;

/*感知数据-机车信号相关数据-李铁兵*/
typedef struct TAG_LocoSignalData
{
	UINT8   SingalStatus;                               				/*信号异常状态字节：
																		  Bit0：信号异常-信号机前控速20km/h
																		  Bit1：--
																		  Bit2：-- 
																		  Bit3：-- 
																		  Bit4：-- 
																		  Bit5：-- 
																		  Bit6：--  
																		  Bit7 ：-*/
	UINT8 	Singal;          									   		/*机车信号*/
	UINT8 	LKJMode;													/*监控状态*/
	UINT8  	CurrentSideLine;			                                /*本分区侧线*/
	UINT8  	NextSideLine;				                                /*下分区侧线*/
	/*增加本分区支线 和下分区支线号*/
	UINT8  	CurrentBranch;			        							/*本分区支线 */
	UINT8  	NextBranch;				        							/*下分区支线 */

}S_LOCOSIGNAL_DATA;

/*感知数据-列车编组信息-李铁兵*/
typedef struct TAG_TrainConsistData
{
	E_MODEL_CONSISTTYPE   ConsistType;                                  /*编组模式*/
	UINT8   ClosedVehicleNums;                                   		/*关门车数量*/
	UINT8   SleepLocoNums;												/*附挂机车数量*/
	UINT16  BrkShoePresPHT;												/*每百吨闸瓦压力*/
	/*2019/03/26，TangWei增加*/
	REAL32  ConvertBrakeRate;											/*列车换算制动率*/
	/*2019/01/09，YipingYang增加*/
	UINT8   TrainType;                                                  /*列车类型*/
	UINT16  TrainLength;                                                /*列车计长*/
	UINT16	TrainActualLength;											/*列成总长(机车长度+车辆长度)*/
	UINT16  LocosWeight;                                                /*机车总重*/
	UINT16  VehicleWeight;                                              /*车辆总重（LKJ输入的总重）*/
	UINT16  TrainWeight;												/*列车总重（机车加车辆）*/
	UINT16  LoadWeight;												    /*列车载重*/
	/*新加-zxm-2019-1-11*/
	UINT16  VehicleNum;				 									/*车辆辆数*/
	UINT16 	HeavyCar;													/*重车数量*/
	UINT16 	EmptyCar;				  									/*空车数量*/
	UINT16  LocoNums;													/*机车数量（重联机车数+附挂机车数）*/
}S_TRAINCONSIST_DATA;

/*感知数据-机车相关状态数据-李铁兵*/
typedef struct TAG_TrainStatusData{
	S_LOCOS_STATUSDATA 	   LocosStatusData;                            /*机车状态数据*/
	S_VEHICLES_STATUSDATA  VehiclesStatusData;                         /*车辆状态数据*/
	S_EOT_STATUSDATA	   EotStatusData;							   /*列尾状态数据*/
	S_TRAINCONSIST_DATA    TrainConsistData;                           /*列车编组数据*/ 
}S_TRAINSTATUSDATA;

/*感知数据-列车定位数据-李铁兵*/
typedef struct TAG_TrainLocateData
{	
	UINT32                  Position;   							   /*机车相对距离-相对基础线路更新时机车0点的位置距离*/
	UINT32                  TravlledDistance;                          /*机车位移，累计位移,单位：米 */
	UINT16                  NextSigRelaDist;				  		   /*机车到下一信号机的距离*/
	UINT16                  PassSigRelaDist;				  		   /*机车到越过信号机的距离*/
	UINT32                  NextStationRelaDist;                       /*机车到下一站的距离*/
	UINT32                  PassStationRelaDist;                       /*机车越过上一个站距离*/
	S_NEUTRAL_POINT         NeutralPnt;                                /*分相区距离*/
	S_BRAKETEST_POINT       BrakeTestPnt;                              /*贯通区距离*/
	S_STOPBEFNEU_POINT      StopBefNeuPnt;                             /*分相前停车点距离*/
	S_STOPBEHNEU_POINT      StopBehNeuPnt;                             /*分相后停车点距离*/
	S_PASSMARKSTOP_POINT    PassMarkStopPnt;                           /*过标停车位置距离前方信号机距离*/
	
	/*分线前后停车点，2019.04.23新增，Tangwei*/
	S_STOP_NEU_RELA_DIST	StopNeuRelaDist;	
	
}S_TRAIN_LOCATEDATA;

/*感知数据-算法运行模式控制数据-李铁兵*/
typedef struct TAG_AlgoModeCtrlData
{	
	UINT8   ATOFlag;                                       					/*机车控制信号	bit0-自动驾驶允许,bit1-自动驾驶激活 ,bit2-自动发车，bit3-ATO控车，bit4-主控接管保护控制*/
	UINT8   DmiCmd;															/*人机交互命令：Bit0：赶点模式  Bit1：点单模式, Bit2:慢行模式 Bit3: 贯通  bit4:自动模式下人工缓解   Bit5~Bit7 预留*/
	UINT8   FastRunTime;													/*快行时间（min）-司机设置*/
	UINT8   SlowRunTime;													/*慢行时间（min）-司机设置*/
}S_ALGO_MODECTRLDATA;
typedef struct TAG_AlgoStrategyCtrlData
{
	UINT16  PlanCalcStep;												/*计算步长*/
	UINT8	TriggerNum;													/*触发规划值*/
	/*2019.03.02 YipingYang增加最大规划长度*/
	UINT16  MaxPlanLen; 												/*最大规划长度m*/
	E_SysBool IsNeedBkTest;												/*是否需要试闸，true为试闸，false为不试闸*/
}S_ALGO_STRATEGYCTRLDATA;

/*限速变化索引数组，2019.01.04修改定义，YipingYang*/
typedef struct TAG_InterProjectInfo
{
	E_SENSE_SPDCHNGTYPE SpdChngType[ALGO_LIMIT_SPEED_NUM_MAX];
	S_LKJ_PROJECTCURVE InterProjectCurve;
}S_INTERPROJECT_INFO;

/*感知数据处理后数据库*/
typedef struct TAG_KernelSenseData
{
	S_INTERPROJECT_INFO       InterProjectInfo;                         /*内部防护曲线信息*/
	S_RAILLINECALC_RESULT     RaillineCalcResult;						/*线路信息计算结果*/
	/*2019_1_29删除S_BADGEPOINT，唐伟*/
	S_RAILLINEINFO_BADGEPOINT RailLineBadgePointData;					/*标记点数据*/
	S_TRAINSTATUSDATA         TrainStatusData;							/*列车状态数据*/
	S_LOCOSIGNAL_DATA         LocoSignalData;			  				/*机车信号相关数据（LKJ）*/
	S_TRAIN_LOCATEDATA        TrainLocateData;                           /*列车定位数据*/
	S_ALGO_MODECTRLDATA       AlgoModeCtrlData;							/*算法模式控制数据*/
	S_ALGO_STRATEGYCTRLDATA	  AlgoStrategyCtrlData;						/*算法策略数据*/
	    
	S_ALGO_INPUT_BASICDATA*  pAlgoInputBasicData;                       /*代码调整后删除---朱保林*/      
}S_KERNEL_SENSEDATA;
/*记录空气制动状态*/
#if 1
typedef struct TAG_AirBrkStatus
{
	UINT16      LastPressureDec;       /*缓解前的列车管压力*/
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
 *Function: 对车长取整,从45-51对车长取余，返回最小误差值
 *Para    : 
 *Return  : 返回加算坡道步长
 *NOTE    : V1.0.0  	zxm 		 2018/12/25		
******************************************************************************/
UINT16  Atoalgo_Math_CalcTrainLength(UINT16 TrainLength);
  /******************************************************************************
*Name    : Atoalgo_Plan_StrategyCalc
*Function: 规划策略计算，如步长处理
*Para    : void
*Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
*NOTE    : V1.0.0  zxm 	 2019/1/10      函数创建
******************************************************************************/
E_SysBool Atoalgo_Plan_StrategyCalc(S_KERNEL_SENSEDATA* 		const 	pKernelSenseData,
									S_ALGO_STRATEGYCTRLDATA*    const   pAlgoStrategyCtrlData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcFinalSpd
 *Function: 计算起车弯道初始值
 *Para    : 
 *Return  : 起车平均弯道值
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.0  tw 		 2018/12/10			modified
******************************************************************************/
REAL32 Atoalgo_Sense_CalcCurveInitAvgValue(const S_TRAINSTATUSDATA* 	const pTrainStatusData,
						   	   	    	   const S_FORWARDRLDATA* 		const pForwardRailLineData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcCurveAvgValue
 *Function: 计算弯道加算阻力
 *Para    : 
 *Return  : 按步长计算平均弯道值
 *NOTE    : V1.0.0  tw 		 2018/12/10			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_CalcCurveAvgValue(const S_TRAINSTATUSDATA*			const pTrainStatusData,
										   const S_ALGO_STRATEGYCTRLDATA*	const pAlgoStrategyCtrlData,
						   	   	    	   const S_FORWARDRLDATA* 			const pForwardRailLineData, 
						   	   	    	   	   	 REAL32*						  AvgCurve);
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcRampInitAvgValue
 *Function: 计算起车坡道初始值
 *Para    : 
 *Return  : 平均坡道值
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.0  tw	 	 2018/12/09			modified
 *NOTE    : V1.0.0  zxm 	 2018/12/21			modified
******************************************************************************/
REAL32 Atoalgo_Sense_CalcRampInitAvgValue(const S_TRAINSTATUSDATA* 			const pTrainStatusData,
						   	   	   	   	  const S_FORWARDRLDATA* 			const pForwardRailLineData,
						   	   	   	   	  	    E_SysBool*				    const Degrade2Normal);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcRampAvgValue
 *Function: 计算定长平均坡道，50米为一个步长
 *Para    : 
 *Return  : 平均坡道值
 *NOTE    : V1.0.0  zxm 	 2018/11/13			create
 *NOTE    : V1.0.0  tw 		 2018/12/09			modified
******************************************************************************/
E_SysBool Atoalgo_Sense_CalcRampAvgValue(const S_TRAINSTATUSDATA* 		const pTrainStatusData,
										 const S_ALGO_STRATEGYCTRLDATA*	const pAlgoStrategyCtrlData,
						   	   	   	  	 const S_FORWARDRLDATA* 		const pForwardRailLineData,
						   	   	   	  	 	   REAL32*						  AvgRamp);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcAddRes
 *Function: 计算线路加算阻力
 *Para    : 
 *Return  : 加算阻力
 *NOTE    : V1.0.0  tw 		 2018/12/10			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_CalcAddRes(const S_TRAINSTATUSDATA* 	const pTrainStatusData,
								    const S_FORWARDRLDATA* 		const pForwardRailLineData, 
								          S_KERNEL_SENSEDATA*	const pKernelSensedataIO,
								    	  REAL32* 					  InAvgRampTemp,
								    	  REAL32* 					  InAvgCurveTemp);
/******************************************************************************
 *Name    : Atoalgo_Sense_CalcAddRes
 *Function: 计算线路加算阻力、变坡点
 *Para    : 
 *Return  : 加算阻力数组，变坡点数组
 *NOTE    : V1.0.0  tw 		 2019/1/8			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_RailLineClac(const S_FORWARDRLDATA* 		const pForwardRailLineData, 
								 	      	S_KERNEL_SENSEDATA*		const pKernelSensedataIO);
/******************************************************************************
 *Name    : Atoalgo_Sense_RampValueClac
 *Function: 变坡点坡道属性
 *Para    : 变坡点数组
 *Return  : 输出变坡点平均坡道数组 (ChangeRampPointAveRamp[0]为机车位置到索引为0的变坡点这段的平均值
 *Return  						  ChangeRampPointAveRamp[1]为变坡点数组索引为0到索引为1这段的平均值，以此类推)
 *NOTE    : V1.0.0		tw 		 2019/04/12			create
******************************************************************************/
E_SysBool  Atoalgo_Sense_RampChangePointAveRamp(S_KERNEL_SENSEDATA*	const pKernelSensedataIO);
/******************************************************************************
 *Name    : Atoalgo_Sense_SectionRampAve
 *Function: 计算一段距离的平均附加阻力
 *Para    : 输入该段初始位置和结束位置（1=1m,距车头距离）
 *Return  : 返回该段平均附加阻力值（1=1单位力）
 *NOTE    : V1.0.0		tw 		 2019/02/22			create
******************************************************************************/
REAL32  Atoalgo_Sense_SectionRampAve( UINT32 BeginDistance,
									  UINT32 EndDistance,
									 const S_RAILLINECALC_RESULT* const  RaillineCalcResult,
									  UINT16 PlanCalcStep);
/******************************************************************************
 *Name    : Atoalgo_Sense_SectionChangeRampPoint
 *Function: 判断区段内变坡点信息
 *Para    : 输入起始位置与结束点位置，变坡点数组
 *Return  : 输出区段内变坡点个数及第一个变坡点索引值
 *NOTE    : V1.0.0		tw 		 2019/02/26			create
******************************************************************************/
UINT8  Atoalgo_Sense_SectionChangeRampPoint(const UINT32 BeginDistance,
									 const UINT32 EndDistance,
									 const S_CHANGERAMPPOINT* const pChangeRampPointStr,
									 UINT16* const pBeginIndexOut);
/******************************************************************************
 *Name    : Atoalgo_Sense_RampValueClac
 *Function: 计算任意位置的附加阻力
 *Para    : 附加阻力数组，相对位置
 *Return  : 输出附加阻力值
 *NOTE    : V1.0.0		tw 		 2019/01/08			create
******************************************************************************/
REAL32  Atoalgo_Sense_RampValueClac(const S_ALGO_STRATEGYCTRLDATA* 	const pAlgoStategyCtrlData,
									const REAL32* 					const RailAddRes,
										  REAL32					const Distance);
/******************************************************************************
 *Name      : Atoalgo_Sense_CurPtLkjSpd2InterSpd
 *Function  : 将当前点的LKJ速度转换为内部防护速度
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn 
 *Return    : UINT16 对应的内部防护速度（1=1km/h)
 *Note		: V1.0.0       YipingYang    2019/01/18   Create
 *Note		: V1.0.1       YipingYang    2019/01/19   Modify
 *Note		: V1.0.2       YipingYang    2019/01/21   Modify
 ******************************************************************************/
UINT16 Atoalgo_Sense_CurPtLkjSpd2InterSpd(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
										  const S_KERNEL_SENSEDATA* const pSenseDataIn,
		   	   	   	   	   	   	   	   	   	    				const UINT16 curIndexIn);
/******************************************************************************
 *Name      : 
 *Function  : 计算内部防护曲线速度
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Return    : UINT16 对应的内部防护速度（1=1km/h)
 *Note		: V1.0.0       Tangwei    2019/08/12   Create
 ******************************************************************************/
E_SysBool LkjSpd2InterSpd(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
								S_KERNEL_SENSEDATA* const pSenseDataIn);
 /******************************************************************************
 *Name    : Atoalgo_Sense_LocolData
 *Function: 获取机车输入参数数据
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
 *Function: 获取车辆输入参数数据
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
 *Function: 获取机车信号相关数据
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
 *Function  : 计算防护曲线闭口点的距离
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurve      
 *Return    : UINT32
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
UINT32 Atoalgo_Sense_RsSpdShutUpPointDist(const S_LKJ_PROJECTCURVE* const pProjectCurveIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdRiseSegStartPoint
 *Function  : 判断是否为限速升高区段起始点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool，如果是限速升高起始点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdRiseSegStartPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                       const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdDeclinePoint
 *Function  : 判断是否为限速下降起始点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool，如果是限速下降起始点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdDeclineSegStartPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                          const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdRiseSegEndPoint
 *Function  : 判断是否为限速升高区段终点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool，如果是限速升高终点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdRiseSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                     const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_ExistSpdRiseSegEndPoint
 *Function  : 判断最小识别距离内是否存在限速升高区段终点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn,   UINT16* riseSegEndIndexOut  
 *Return    : E_SysBool，如果存在限速升高终点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/31   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_ExistSpdRiseSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                        const UINT16 curIndexIn,
		                                        UINT16* riseSegEndIndexOut);

/******************************************************************************
 *Name      : Atoalgo_Sense_IsSpdDeclineSegEndPoint
 *Function  : 判断是否为限速下降终点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn     
 *Return    : E_SysBool，如果是限速下降终点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_IsSpdDeclineSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                        const UINT16 curIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_ExistSpdDeclineSegEndPoint
 *Function  : 判断最小识别距离内是否存在限速下降终点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn,    UINT16* declineSegEndIndexOut 
 *Return    : E_SysBool，如果存在限速下降终点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2018/12/30   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_ExistSpdDeclineSegEndPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                        const UINT16 curIndexIn,
		                                        UINT16* declineSegEndIndexOut);

/******************************************************************************
 *Name      : Atoalgo_Sense_CalcSpdChngRecognise
 *Function  : 根据防护曲线识别速度变化
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurve
 *Para      ：S_KERNEL_SENSEDATA* const pSenseDataOut      
 *Return    : E_SysBool,检索成功返回e_TRUE，检索失败返回e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/14   Create
 *Note		：V1.0.1       YipingYang    2019/01/17   modify 修改输入参数
 ******************************************************************************/
E_SysBool Atoalgo_Sense_CalcSpdChngRecognise(const S_LKJ_PROJECTCURVE* 	const pProjectCurveIn,
		                                     	   S_KERNEL_SENSEDATA* 	const pSenseDataOut);

#if 1

/******************************************************************************
*Name    : Atoalgo_Sense_AutoModeData
*Function: 自动驾驶允许模式处理
*Para    : const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData
*Para    : const S_FORWARDRLDATA* const ForwardRailLineData
*Para    : S_KERNEL_SENSEDATA* const pKernelSenseData
*Return  : E_SysBool，正常返回e_TRUE 异常返回e_FALSE
*NOTE    : V1.0.0  zxm           2019/01/11     create
******************************************************************************/
E_SysBool Atoalgo_Sense_AutoModeData(const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,
								     const S_FORWARDRLDATA* 		const ForwardRailLineData,
								       	   S_KERNEL_SENSEDATA* 		const pKernelSenseData);

/******************************************************************************
*Name    : Atoalgo_Sense_AutoDriveAllowProc
*Function: 自动驾驶允许处理
*Para    : const S_ALGO_INPUT_DYNDATA* const pAlgoInputDynData
*Para    : const S_FORWARDRLDATA* const ForwardRailLineData
*Para    : S_KERNEL_SENSEDATA* const pKernelSenseData
*Return  : E_SysBool，正常返回e_TRUE 异常返回e_FALSE
*NOTE    : V1.0.0  zxm           2019/01/11     create
******************************************************************************/
E_SysBool Atoalgo_Sense_AutoDriveAllowProc(const S_ALGO_INPUT_DYNDATA* 		const pAlgoInputDynData,
								     	   const S_FORWARDRLDATA* 			const ForwardRailLineData,
								       	   	     S_KERNEL_SENSEDATA* 		const pKernelSenseData);


/******************************************************************************
 *Name      : Atoalgo_Sense_ExistSpdRiseSegStartPoint
 *Function  : 判断当前索引点之前是否存在限速上升起点
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : const UINT16 curIndexIn,    UINT16* riseSegStartIndexOut 
 *Return    : E_SysBool，如果存在限速上升起点返回e_TRUE，否则为e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/18   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_ExistSpdRiseSegStartPoint(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
		                                          const UINT16 curIndexIn,
		                                          UINT16* riseSegStartIndexOut);

/******************************************************************************
 *Name      : Atoalgo_Sense_SpdDwSegEndPtComfirm
 *Function  : 处理尖峰，速度下降终点确认
 *Para      : const S_LKJ_PROJECTCURVE* const pProjectCurveIn 
 *Para      : S_KERNEL_SENSEDATA* const pSenseDataOut
 *Para      : const UINT16 spdDwEndIndexIn，降速终点索引 
 *Return    : void
 *Note		: V1.0.0       YipingYang    2019/01/18   Create
 ******************************************************************************/
void Atoalgo_Sense_SpdDwSegEndPtComfirm(const S_LKJ_PROJECTCURVE* const pProjectCurveIn,
												   S_KERNEL_SENSEDATA* const pSenseDataOut,
		                                     const UINT16 spdDwEndIndexIn);

/******************************************************************************
 *Name      : Atoalgo_Sense_BadgePointRecognise
 *Function  : 识别列车前方区段的标记点
 *Para      : const S_SPECIALZONEDATA* const pSpecZoneData 
 *Para      : S_KERNEL_SENSEDATA* const pSenseData 
 *Return    : E_SysBool，正常返回e_TRUE 异常返回e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/21   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_BadgePointRecognise(const S_SPECIALZONEDATA* const pSpecZoneData,
		   	   	   	   	   	   	   	   	   	    	S_KERNEL_SENSEDATA* const pSenseData);

/******************************************************************************
 *Name      : Atoalgo_Sense_FirstSpecAreaInfront
 *Function  : 探索列车前方的第一个特殊区段
 *Para      : const S_SPECIALZONEDATA* const pSpecZoneData 
            : const UINT32 LocoPosIn, UINT8* SpecAreaIndex 
 *Return    : E_SysBool，如果列车前方有特殊区段返回e_TRUE，反之返回e_FALSE
 *Note		: V1.0.0       YipingYang    2019/01/22   Create
 ******************************************************************************/
E_SysBool Atoalgo_Sense_FirstSpecAreaInfront(const S_SPECIALZONEDATA* const pSpecZoneData,
		   	   	   	   	   	   	   	   	   	 const UINT32 LocoPosIn,
		   	   	   	   	   	   	   	   	   	 UINT8* SpecAreaIndex);


/******************************************************************************
 *Name    : Atoalgo_Sense_CalcTrainHeavyEmptyWgt
 *Function: 计算列车空重车重量
 *Para    : 
 *Return  : 
 *NOTE    : V1.0.0  zhouww 	 2019/02/19      create
******************************************************************************/
void Atoalgo_Sense_CalcTrainHeavyEmptyWgt(const S_TRAINSTATUSDATA* const pTrainStatusData,
										  	      UINT32* 				   heavy,
										  	      UINT32* 				   empty);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcTotalLocosWgt
 *Function: 计算总机车重量
 *Para    :                          
 *Return  : 
 *NOTE    : V1.0.0  zhouww 	 2018/08/04      create
******************************************************************************/
UINT16 Atoalgo_Sense_CalcTotalLocosWgt(S_TRAINSTATUSDATA* const pTrainStatusData);

/******************************************************************************
 *Name    : Atoalgo_Sense_RailLineBasicData
 *Function: 将外部输入的线路基础数据加入感知数据
 *Para    :                          
 *Return  : 操作成功返回e_TRUE，失败返回e_FALSE
 *NOTE    : V1.0.0  YipingYang 	 2019/02/26      create
******************************************************************************/
E_SysBool Atoalgo_Sense_RailLineBasicData(S_ALGO_INPUT_BASICDATA*  pAlgoInputBasicData,
									 	  S_ALGO_INPUT_BASICDATA** pBasicDataOut);

/******************************************************************************
 *Name    : Atoalgo_Sense_SearchLongRamp
 *Function: 探索前方长大上坡或长大下坡
 *Para    :                          
 *Return  : 操作成功返回e_TRUE，失败返回e_FALSE
 *NOTE    : V1.0.0  zxm 	 2019/03/05      create
******************************************************************************/
E_SysBool Atoalgo_Sense_SearchLongRamp(const S_FORWARDRLDATA* 		const pForwardRailLineData,
											 S_KERNEL_SENSEDATA*	const pKernelSensedataIO);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcWorkStatusChngTime
 *Function: 根据感知数据计算工况转换时间
 *Para    : const S_KERNEL_SENSEDATA* const pSenseData                         
 *Return  : 工况转换时间，输入无效或者无编组模式返回0U
 *NOTE    : V1.0.0  YipingYang 	 2019/02/28      create
******************************************************************************/
UINT8 Atoalgo_Sense_CalcWorkStatusChngTime(const S_KERNEL_SENSEDATA* const pSenseData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalAirBrkReleaseTime
 *Function: 空气制动缓解时间
 *Para    : const S_TRAINSTATUSDATA* const pTrainStatusData
          : const UINT16 PressureDecrement
 *Return  : 空气制动缓解时间(1=1ms)
 *NOTE    : V1.0.0  zhubaolin 		 2018/01/08     create
          : V1.0.1  YipingYang       2019/03/05     modify 修改函数输入参数
******************************************************************************/
UINT32 Atoalgo_Sense_CalAirBrkReleaseTime(const S_TRAINSTATUSDATA* const pTrainStatusData,
										  const UINT16 PressureDecrement);

/******************************************************************************
Name    : ATO_Sense_BPVentTime
*Function: 计算列车管排风时间
*Para    : const S_TRAINSTATUSDATA* const pTrainStatusData
         : const UINT16 PressureDecrement
*Return  : UINT32(1=1ms)
*NOTE    : V1.0.0     YipingYang    2019/03/04    Create
         : V1.0.1     YipingYang    2019/03/05    modify  修改函数输入参数
******************************************************************************/
UINT32 ATO_Sense_BPVentTime(const S_TRAINSTATUSDATA* const pTrainStatusData,
						    const UINT16 PressureDecrement);

/******************************************************************************
 *Name    : Atoalgo_Sense_TrainRuningCoastProc
 *Function: 列车运行惰行工况处理。惰行断定：实际运行状态值为0，且输出力为0，二者同时满足才感知为惰行工况，传递给跟随控制。
 *Para    : 
 *Return  : 工况转换类型
 *NOTE    : V1.0.0  zhubaolin 		 2018/01/08     create
******************************************************************************/
E_SysBool Atoalgo_Sense_TrainRuningCoastProc(const S_ALGO_INPUT_DYNDATA* 	const pAlgoInputDynData,\
											S_KERNEL_SENSEDATA* 		const pKernelSenseData);
/******************************************************************************
 *Name    : Atoalgo_Ctrl_JudgingAirBrk
 *Function: 空气制动工况判断
 *Para    : 
 *Return  : 工况转换类型
 *NOTE    : V1.0.0  zhubaolin 		 2018/01/08     create
******************************************************************************/
E_SysBool Atoalgo_Sense_JudgingAirBrk(const S_KERNEL_SENSEDATA*     const pKernelSenseData);
/******************************************************************************
 *Name    : Atoalgo_Sense_AccCalc
 *Function: 计算机车加速度
 *Para    : 
 *Return  : 无
 *NOTE    : V1.0.0  	LiuYeXuan 		 2019/02/25		
******************************************************************************/
E_SysBool Atoalgo_Sense_AccCalc(S_KERNEL_SENSEDATA * const pKernelSenseData);

/******************************************************************************
 *Name    : Atoalgo_Sense_IsNeededBreakTest
 *Function: 感知是否要做贯通试验
 *Para    : const S_KERNEL_SENSEDATA* const pSenseData                         
 *Return  : e_TRUE:要做；e_FALSE:不做
 *NOTE    : V1.0.0  zxm 	 2019/04/02      create
******************************************************************************/
E_SysBool Atoalgo_Sense_IsNeededBreakTest(S_KERNEL_SENSEDATA* const pSenseData);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcStopPntPosFromSignal
 *Function: 计算停车点距停车信号机的位置
 *Para    : const S_KERNEL_SENSEDATA* const pSenseData
          : UINT8* StopPntIndex，停车点索引值 
 *Return  : UINT32，停车点位置，与0点距离
 *NOTE    : V1.0.1  zxm 	 2019/04/02         create 
******************************************************************************/
UINT16 Atoalgo_Sense_CalcStopPntPosFromSignal(S_KERNEL_SENSEDATA* const pSenseData,
											  UINT16                    Distance);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcStopPntPosFromSignal
 *Function: 计算分相前停车点距相对0点的位置
 *Para    : const S_SPECIALZONEDATA*   const pSpecZoneData,
 *Para    : S_KERNEL_SENSEDATA*  const pSenseData,
 *Para    : S_STOP_NEU_RELA_DIST* const pStopNeuRelaDist
 *Return  : 成功返回e_TRUE,失败返回e_FALSE
 *NOTE    : V1.0.1  TangWei 	 2019/04/19         create 
******************************************************************************/
E_SysBool Atoalgo_Sense_CalcStopBef_NeuRelaDist(const S_SPECIALZONEDATA*   const pSpecZoneData,
  	   	   	   	    							   S_KERNEL_SENSEDATA*  const pSenseData,
  	   	   	   	    							   S_STOP_NEU_RELA_DIST* const pStopNeuRelaDist);

/******************************************************************************
 *Name    : Atoalgo_Sense_CalcStopBef_NeuMinDist
 *Function: 计算分相前停车点距相对0点的位置
 *Para    : 
 *Return  :
 *NOTE    : V1.0.1  TangWei 	 2019/04/19         create 
******************************************************************************/
UINT16 Atoalgo_Sense_CalcStopBef_NeuMinDist(const S_SPECIALZONEDATA*   const pSpecZoneData,
  	   	   	   	    							  S_KERNEL_SENSEDATA*  const pKernelSenseDataIn,
  	   	   	   	    							  REAL32	Spd,	   UINT16	RelaDis);
#endif
#endif