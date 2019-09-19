/******************************************************************************
 *File Name	     :	ACS_BasicFunction.c
 *Copyright	     :	Zhuzhou CRRC Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/8/12 
 *Description    :	提供ACS的公共基础函数.
 *                  
 *Modification history:
 *REV1.0.0		TangWei     2019/08/12   File Create 

 ******************************************************************************/
/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/
#ifndef    ACS_BASIC_FUNCTIONG_H
#define	   ACS_BASIC_FUNCTIONG_H

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/GL_Basic_Type_Definition.h"

/******************************************************************************
*    Global Variable Define Section
******************************************************************************/


/******************************************************************************
*    Local Macro Define Section
******************************************************************************/

/*以2000年开始计算时间秒数*/
#define  YEAR_START                      (2000UL) 
/*最大的年*/
#define  IBM_YEAR_END                    (2099UL)
/*闰年秒数*/
#define  LEAPYEAR_CONVERTTO_SECONEDS     (31622400UL)
/*平年秒数*/
#define  AVERAGEYEAR_CONVERTTO_SECONEDS  (31536000UL)
/*一天秒数*/
#define  DAY_CONVERTTO_SECONEDS          (86400UL)
/*一时秒数*/
#define  HOUR_CONVERTTO_SECONEDS         (3600UL)
/*一分秒数*/
#define  MINUTE_CONVERTTO_SECONEDS       (60UL)
/*闰年天数*/
#define  LEAPYEAR_DAYS                   (366UL)
/*平年天数*/
#define  AVERAGEYEAR_DAYS                (365UL)
/*闰年2月天数*/
#define  LEAPYEAR_FEBRUARY_DAYS          (29UL)
/*平年2月天数*/
#define  AVERAGEYEAR_FEBRUARY_DAYS       (28UL)
/*以2000年开始计算时间LKJ*/
#define  LKJ_YEAR_START                  (2000UL)
/*判断是否为闰年*/
#define IS_LEAPYEAR(YEAR)               (YEAR % 4 ? 0UL : YEAR % 100 ? 1UL : YEAR % 400 ? 0UL : 1UL )

/*从1970.1.1.0.0.0到2000.1.1.0.0.0的秒数*/
#define  c_SECFROM1970TO2000YEAR         (946684800UL)

typedef enum TAG_MonthType
{  
  e_JANUARY,
  e_FEBRUARY,
  e_MARCH,
  e_APRIL,
  e_MAY,
  e_JUNE,
  e_JULY,
  e_AUGUST,
  e_SEPTEMBER,
  e_OCTOBER,
  e_NOVOMBER,
  e_DECEMBER
}E_MonthType;
/******************************************************************************
*    Local Struct    Define Section
******************************************************************************/
/** ATO时间信息 */
typedef struct TAG_ATO_DateTime {
  UINT8 										Year;
  UINT8											Month;					    /** 范围1～12 */
  UINT8											Day;					    /** 范围1～31 */
  UINT8											Hour; 					    /** 范围0～23 */
  UINT8											Minutes;				    /** 范围0～59 */
  UINT8											Second;					    /** 范围0～59 */
} S_ATO_DATETIME;

/******************************************************************************
*    Local Prototype Declare Section
******************************************************************************/

/******************************************************************************
*    Static Variable Define Section
******************************************************************************/


/******************************************************************************
*    static Function Define Section
******************************************************************************/

/******************************************************************************
*    Function Define Section
******************************************************************************/


/******************************************************************************
 *Name     : Comn_F_MemCpy
 *Function : 内存拷贝
 *Para     : outDst             -[out]拷贝数据的目的地址。
 *           inSrc              -[in]拷贝数据的源地址。
 *           inSize             -[in]拷贝数据的字节数。
 *           inBufSize          -[in]拷贝数据的目的缓存的大小。
 *Return   : E_SysBool           -拷贝是否成功。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
E_SysBool Comn_F_MemCpy(void* const outDst,
                       const void* const inSrc,
                       const INT32 inSize,
                       const INT32 inBufSize);
/******************************************************************************
 *Name     : Comn_F_MemSet
 *Function : 内存填充
 *Para     : outMem             -[out]填充缓存的目的地址。
 *           inValue            -[in]填充的值。
 *           inSize             -[in]填充的字节数。
 *Return   : 无
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_MemSet(void* const outMem, const INT32 inValue, const INT32 inSize);


/******************************************************************************
 *Name     : Comn_F_MemCmp
 *Function : 比较两段缓存是否相同。
 *Para     : inBuff1 :          -[in]数据区1地址
             inBuff2 :          -[in]数据区2地址
             inSize  :          -[in]待比较数据的大小(单位:byte)
 *Return   : E_SysBool           -两段缓存是否相同。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
E_SysBool Comn_F_MemCmp(const void* const inBuff1, const void* const inBuff2, const INT32 inSize);
/******************************************************************************
 *Name     : Comn_F_Abs
 *Function : 取绝对值
 *Para     : inValue            -[in]待取绝对值的数字。
 *Return   : INT32            -绝对值。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
INT32 Comn_F_Abs(const INT32 inValue);

/******************************************************************************
 *Name     : Comn_F_GetUINT32
 *Function : 将四个UINT8数据组合成一个UINT32的值。
 *Para     : inBYTE1             -[in]D31-D24
 *           inBYTE2             -[in]D23-D16
 *           inBYTE3             -[in]D15-D8
 *           inBYTE4             -[in]D7-D0
 *Return   : UINT32              -组合之后的数值。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT32 Comn_F_GetUINT32(const UINT8 inBYTE1,
                       const UINT8 inBYTE2,
                       const UINT8 inBYTE3,
                       const UINT8 inBYTE4);

/******************************************************************************
 *Name     : Comn_F_GetUINT32
 *Function : 将二个UINT16数据组合成一个UINT32的值。
 *Para     : inBYTE1             -[in]D31-D16
 *           inBYTE2             -[in]D15-D0
 *Return   : UINT32              -组合之后的数值。
 *
 *Note    : REV1.0.0    likai    2019/3/11   Function Create 
******************************************************************************/
UINT32 Comn_F_GetUINT32Ex(const UINT16 inBYTE1,
                          const UINT16 inBYTE2);

/******************************************************************************
 *Name     : Comn_F_GetUINT24
 *Function : 将三个UINT8数据组合成一个UINT24的值。
 *Para     : inBYTE1             -[in]D23-D16
 *           inBYTE2             -[in]D15-D8
 *           inBYTE3             -[in]D7-D0
 *Return   : UINT32              -组合之后的数值。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT32 Comn_F_GetUINT24(const UINT8 inBYTE1,
                       const UINT8 inBYTE2,
                       const UINT8 inBYTE3);

/******************************************************************************
 *Name     : Comn_F_GetUINT16
 *Function : 将2个UINT8数据组合成一个UINT16的值。
 *Para     : inBYTE1             -[in]D15-D8
 *           inBYTE2             -[in]D7-D0
 *Return   : UINT32              -组合之后的数值。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT16 Comn_F_GetUINT16(const UINT8 inBYTE1, const UINT8 inBYTE2);

/******************************************************************************
 *Name     : Comn_F_SetUINT32
 *Function : 将一个UINT32数字分解成四个UINT8数字。
 *Para     : inData              -[in]UINT32的数。
 *           outBYTE1            -[out]D31-D24
 *           outBYTE2            -[out]D23-D16
 *           outBYTE3            -[out]D15-D8
 *           outBYTE4            -[out]D7-D0
 *Return   : 无
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_SetUINT32(const UINT32 inData,
                     UINT8* const outBYTE1,
                     UINT8* const outBYTE2,
                     UINT8* const outBYTE3,
                     UINT8* const outBYTE4);

/******************************************************************************
 *Name     : Comn_F_SetUINT24
 *Function : 将一个UINT32数字分解成三个UINT8数字。
 *Para     : inData              -[in]UINT32的数。
 *           outBYTE1            -[out]D23-D16
 *           outBYTE2            -[out]D15-D8
 *           outBYTE3            -[out]D7-D0
 *Return   : 无
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_SetUINT24(const UINT32 inData, UINT8* const outBYTE1,
                     UINT8* const outBYTE2, UINT8* const outBYTE3);
/******************************************************************************
 *Name     : Comn_F_SetUINT16
 *Function : 将一个UINT16数字分解成两个UINT8数字。
 *Para     : inData              -[in]UINT16的数。
 *           outBYTE1            -[out]D15-D8
 *           outBYTE2            -[out]D7-D0
 *Return   : 无
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_SetUINT16(const UINT16 inData, UINT8* const outBYTE1, UINT8* const outBYTE2);
/******************************************************************************
*Name    : Comn_F_Date2Stamp
*Function: 日期转换为时间戳 
*Para    : 输入时间S_ATO_DATETIME 输出时间pTimeStampOut，
*Return  : 空
*NOTE    : LinBo/zhouww     2018/03/05    Create
******************************************************************************/ 
void Comn_F_Date2Stamp( const S_ATO_DATETIME* const pDateTimeIn, UINT32* const pTimeStampOut);
#endif
