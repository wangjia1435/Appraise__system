/******************************************************************************
 *File Name	     :	ACS_BasicFunction.c
 *Copyright	     :	Zhuzhou CRRC Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/8/12 
 *Description    :	�ṩACS�Ĺ�����������.
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

/*��2000�꿪ʼ����ʱ������*/
#define  YEAR_START                      (2000UL) 
/*������*/
#define  IBM_YEAR_END                    (2099UL)
/*��������*/
#define  LEAPYEAR_CONVERTTO_SECONEDS     (31622400UL)
/*ƽ������*/
#define  AVERAGEYEAR_CONVERTTO_SECONEDS  (31536000UL)
/*һ������*/
#define  DAY_CONVERTTO_SECONEDS          (86400UL)
/*һʱ����*/
#define  HOUR_CONVERTTO_SECONEDS         (3600UL)
/*һ������*/
#define  MINUTE_CONVERTTO_SECONEDS       (60UL)
/*��������*/
#define  LEAPYEAR_DAYS                   (366UL)
/*ƽ������*/
#define  AVERAGEYEAR_DAYS                (365UL)
/*����2������*/
#define  LEAPYEAR_FEBRUARY_DAYS          (29UL)
/*ƽ��2������*/
#define  AVERAGEYEAR_FEBRUARY_DAYS       (28UL)
/*��2000�꿪ʼ����ʱ��LKJ*/
#define  LKJ_YEAR_START                  (2000UL)
/*�ж��Ƿ�Ϊ����*/
#define IS_LEAPYEAR(YEAR)               (YEAR % 4 ? 0UL : YEAR % 100 ? 1UL : YEAR % 400 ? 0UL : 1UL )

/*��1970.1.1.0.0.0��2000.1.1.0.0.0������*/
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
/** ATOʱ����Ϣ */
typedef struct TAG_ATO_DateTime {
  UINT8 										Year;
  UINT8											Month;					    /** ��Χ1��12 */
  UINT8											Day;					    /** ��Χ1��31 */
  UINT8											Hour; 					    /** ��Χ0��23 */
  UINT8											Minutes;				    /** ��Χ0��59 */
  UINT8											Second;					    /** ��Χ0��59 */
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
 *Function : �ڴ濽��
 *Para     : outDst             -[out]�������ݵ�Ŀ�ĵ�ַ��
 *           inSrc              -[in]�������ݵ�Դ��ַ��
 *           inSize             -[in]�������ݵ��ֽ�����
 *           inBufSize          -[in]�������ݵ�Ŀ�Ļ���Ĵ�С��
 *Return   : E_SysBool           -�����Ƿ�ɹ���
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
E_SysBool Comn_F_MemCpy(void* const outDst,
                       const void* const inSrc,
                       const INT32 inSize,
                       const INT32 inBufSize);
/******************************************************************************
 *Name     : Comn_F_MemSet
 *Function : �ڴ����
 *Para     : outMem             -[out]��仺���Ŀ�ĵ�ַ��
 *           inValue            -[in]����ֵ��
 *           inSize             -[in]�����ֽ�����
 *Return   : ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_MemSet(void* const outMem, const INT32 inValue, const INT32 inSize);


/******************************************************************************
 *Name     : Comn_F_MemCmp
 *Function : �Ƚ����λ����Ƿ���ͬ��
 *Para     : inBuff1 :          -[in]������1��ַ
             inBuff2 :          -[in]������2��ַ
             inSize  :          -[in]���Ƚ����ݵĴ�С(��λ:byte)
 *Return   : E_SysBool           -���λ����Ƿ���ͬ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
E_SysBool Comn_F_MemCmp(const void* const inBuff1, const void* const inBuff2, const INT32 inSize);
/******************************************************************************
 *Name     : Comn_F_Abs
 *Function : ȡ����ֵ
 *Para     : inValue            -[in]��ȡ����ֵ�����֡�
 *Return   : INT32            -����ֵ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
INT32 Comn_F_Abs(const INT32 inValue);

/******************************************************************************
 *Name     : Comn_F_GetUINT32
 *Function : ���ĸ�UINT8������ϳ�һ��UINT32��ֵ��
 *Para     : inBYTE1             -[in]D31-D24
 *           inBYTE2             -[in]D23-D16
 *           inBYTE3             -[in]D15-D8
 *           inBYTE4             -[in]D7-D0
 *Return   : UINT32              -���֮�����ֵ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT32 Comn_F_GetUINT32(const UINT8 inBYTE1,
                       const UINT8 inBYTE2,
                       const UINT8 inBYTE3,
                       const UINT8 inBYTE4);

/******************************************************************************
 *Name     : Comn_F_GetUINT32
 *Function : ������UINT16������ϳ�һ��UINT32��ֵ��
 *Para     : inBYTE1             -[in]D31-D16
 *           inBYTE2             -[in]D15-D0
 *Return   : UINT32              -���֮�����ֵ��
 *
 *Note    : REV1.0.0    likai    2019/3/11   Function Create 
******************************************************************************/
UINT32 Comn_F_GetUINT32Ex(const UINT16 inBYTE1,
                          const UINT16 inBYTE2);

/******************************************************************************
 *Name     : Comn_F_GetUINT24
 *Function : ������UINT8������ϳ�һ��UINT24��ֵ��
 *Para     : inBYTE1             -[in]D23-D16
 *           inBYTE2             -[in]D15-D8
 *           inBYTE3             -[in]D7-D0
 *Return   : UINT32              -���֮�����ֵ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT32 Comn_F_GetUINT24(const UINT8 inBYTE1,
                       const UINT8 inBYTE2,
                       const UINT8 inBYTE3);

/******************************************************************************
 *Name     : Comn_F_GetUINT16
 *Function : ��2��UINT8������ϳ�һ��UINT16��ֵ��
 *Para     : inBYTE1             -[in]D15-D8
 *           inBYTE2             -[in]D7-D0
 *Return   : UINT32              -���֮�����ֵ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT16 Comn_F_GetUINT16(const UINT8 inBYTE1, const UINT8 inBYTE2);

/******************************************************************************
 *Name     : Comn_F_SetUINT32
 *Function : ��һ��UINT32���ַֽ���ĸ�UINT8���֡�
 *Para     : inData              -[in]UINT32������
 *           outBYTE1            -[out]D31-D24
 *           outBYTE2            -[out]D23-D16
 *           outBYTE3            -[out]D15-D8
 *           outBYTE4            -[out]D7-D0
 *Return   : ��
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
 *Function : ��һ��UINT32���ַֽ������UINT8���֡�
 *Para     : inData              -[in]UINT32������
 *           outBYTE1            -[out]D23-D16
 *           outBYTE2            -[out]D15-D8
 *           outBYTE3            -[out]D7-D0
 *Return   : ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_SetUINT24(const UINT32 inData, UINT8* const outBYTE1,
                     UINT8* const outBYTE2, UINT8* const outBYTE3);
/******************************************************************************
 *Name     : Comn_F_SetUINT16
 *Function : ��һ��UINT16���ַֽ������UINT8���֡�
 *Para     : inData              -[in]UINT16������
 *           outBYTE1            -[out]D15-D8
 *           outBYTE2            -[out]D7-D0
 *Return   : ��
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
void Comn_F_SetUINT16(const UINT16 inData, UINT8* const outBYTE1, UINT8* const outBYTE2);
/******************************************************************************
*Name    : Comn_F_Date2Stamp
*Function: ����ת��Ϊʱ��� 
*Para    : ����ʱ��S_ATO_DATETIME ���ʱ��pTimeStampOut��
*Return  : ��
*NOTE    : LinBo/zhouww     2018/03/05    Create
******************************************************************************/ 
void Comn_F_Date2Stamp( const S_ATO_DATETIME* const pDateTimeIn, UINT32* const pTimeStampOut);
#endif
