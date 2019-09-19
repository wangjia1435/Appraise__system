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
#ifndef    ACS_BASIC_FUNCTION
#define	   ACS_BASIC_FUNCTION

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "../h/Appraise_BasicFunction.h"
#include "../h/GL_Basic_Type_Definition.h"

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

/******************************************************************************
*    Static Variable Define Section
******************************************************************************/


/******************************************************************************
*    static Function Define Section
******************************************************************************/
const UINT32  MONTHTABLE[12UL]={31UL,28UL,31UL,30UL,31UL,30UL,31UL,31UL,30UL,31UL,30UL,31UL};
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
                       const INT32 inBufSize)
{
	if(inSize <= inBufSize)
    {

        const UINT8* const v_ptrSrc = (const UINT8* const)inSrc;
        UINT8* const v_ptrDst = (UINT8* const)outDst;
        const INT32 c_DestAddr = (INT32)outDst;
        const INT32 c_SrcAddr  = (INT32)inSrc;

        INT32 v_Index = inSize;

        /*如果源数据区与目标数据区有重叠 => 保全目标数据区*/
        if((c_DestAddr > c_SrcAddr) && (c_DestAddr < (c_SrcAddr + inSize)))
        {
            while(v_Index > 0L)
            {
                v_Index--;
                v_ptrDst[v_Index] = v_ptrSrc[v_Index];
            }
        }
        /*源数据区与目标数据区无重叠*/
        else
        {
        	v_Index = 0L;
        	while(v_Index < inSize)
        	{
        	    v_ptrDst[v_Index] = v_ptrSrc[v_Index];
        	    v_Index++;
        	}
        }
        return e_TRUE;
    }

    return e_FALSE;
}
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
void Comn_F_MemSet(void* const outMem, const INT32 inValue, const INT32 inSize)
{
    UINT8* const v_ptrMem = (UINT8* const)outMem;
    INT32  v_DataLen = inSize;
    while(v_DataLen > 0L)
    {
        v_DataLen--;
        v_ptrMem[v_DataLen] = (UINT8)inValue;
    }
}


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
E_SysBool Comn_F_MemCmp(const void* const inBuff1, const void* const inBuff2, const INT32 inSize)
{
    const UINT8* const v_ptrBuf1 = (const UINT8* const)inBuff1;
    const UINT8* const v_ptrBuf2 = (const UINT8* const)inBuff2;
    INT32 v_Index = inSize;

    while(v_Index > 0L)
    {
        v_Index--;
        if(0L != ((INT32)(v_ptrBuf1[v_Index])) - ((INT32)(v_ptrBuf2[v_Index])))
        {
            return e_FALSE;
        }
    }
    return e_TRUE;
}

/******************************************************************************
 *Name     : Comn_F_Abs
 *Function : 取绝对值
 *Para     : inValue            -[in]待取绝对值的数字。
 *Return   : INT32            -绝对值。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
INT32 Comn_F_Abs(const INT32 inValue)
{
    INT32 vValue;

    if(inValue < 0L)
    {
        vValue = -inValue;
    }
    else
    {
        vValue = inValue;
    }
    return vValue;
}


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
                       const UINT8 inBYTE4)
{
    UINT32 vResult;

    vResult = (UINT32)inBYTE1;
    vResult <<= 8UL;
    vResult += (UINT32)inBYTE2;
    vResult <<= 8UL;
    vResult += (UINT32)inBYTE3;
    vResult <<= 8UL;
    vResult += (UINT32)inBYTE4;

    return vResult;
}

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
                          const UINT16 inBYTE2)
{
    UINT32 vResult;

    vResult = (UINT32)inBYTE1;
    vResult <<= 16UL;
    vResult += (UINT32)inBYTE2;
    return vResult;
}

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
                       const UINT8 inBYTE3)
{
    UINT32 vResult;

    vResult = (UINT32)inBYTE1;
    vResult <<= 8UL;

    vResult += (UINT32)inBYTE2;
    vResult <<= 8UL;

    vResult += (UINT32)inBYTE3;

    return vResult;
}

/******************************************************************************
 *Name     : Comn_F_GetUINT16
 *Function : 将2个UINT8数据组合成一个UINT16的值。
 *Para     : inBYTE1             -[in]D15-D8
 *           inBYTE2             -[in]D7-D0
 *Return   : UINT32              -组合之后的数值。
 *
 *Note    : REV1.0.0    zhouww     2018/1/13    Function Create 
******************************************************************************/
UINT16 Comn_F_GetUINT16(const UINT8 inBYTE1, const UINT8 inBYTE2)
{
    UINT16 vResult;

    vResult = (UINT16)inBYTE1;
    vResult <<= 8UL;
    vResult += (UINT16)inBYTE2;

    return vResult;
}

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
                     UINT8* const outBYTE4)
{
    UINT32 vData = inData;

    (*outBYTE4) = (UINT8)(vData & 0x000000FFUL);
    vData >>= 8UL;
    (*outBYTE3) = (UINT8)(vData & 0x000000FFUL);
    vData >>= 8UL;
    (*outBYTE2) = (UINT8)(vData & 0x000000FFUL);
    vData >>= 8UL;
    (*outBYTE1) = (UINT8)(vData & 0x000000FFUL);
}

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
                     UINT8* const outBYTE2, UINT8* const outBYTE3)
{
    UINT32 vData = inData;

    (*outBYTE3) = (UINT8)(vData & 0x000000FFUL);
    vData >>= 8UL;
    (*outBYTE2) = (UINT8)(vData & 0x000000FFUL);
    vData >>= 8UL;
    (*outBYTE1) = (UINT8)(vData & 0x000000FFUL);
}
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
void Comn_F_SetUINT16(const UINT16 inData, UINT8* const outBYTE1, UINT8* const outBYTE2)
{
    UINT16 vData = inData;

    (*outBYTE2) = (UINT8)(vData & 0x00FFU);
    vData >>= 8UL;
    (*outBYTE1) = (UINT8)(vData & 0x00FFU);
}
/******************************************************************************
*Name    : Comn_F_Date2Stamp
*Function: 日期转换为时间戳 
*Para    : 输入时间S_ATO_DATETIME 输出时间pTimeStampOut，
*Return  : 空
*NOTE    : LinBo/zhouww     2018/03/05    Create
******************************************************************************/ 
void Comn_F_Date2Stamp( const S_ATO_DATETIME* const pDateTimeIn, UINT32* const pTimeStampOut)
{
	UINT16 i; 
	UINT32 current_second  = 0;
	UINT16 current_year    = (UINT16)pDateTimeIn->Year + (UINT16)LKJ_YEAR_START;
	UINT8  current_month   = pDateTimeIn->Month;
	UINT8  current_day     = pDateTimeIn->Day;
	UINT8  current_hour    = pDateTimeIn->Hour;
	UINT8  current_minute  = pDateTimeIn->Minutes;
		
	if((current_year < YEAR_START) || (current_year > IBM_YEAR_END))
	{
		*pTimeStampOut = 0;
		return;
	}
	
	for (i = YEAR_START; i < current_year; i++)
	{
		if(IS_LEAPYEAR(i)) /*如果为闰年*/
		{
			current_second += LEAPYEAR_CONVERTTO_SECONEDS;
		}
		else
		{
			current_second += AVERAGEYEAR_CONVERTTO_SECONEDS;
		}
	}
	
	if(current_month == 0U)
	{
		*pTimeStampOut = 0UL;
		return;
	}
	else
	{
	  for ( i = 0; i < (current_month - 1); i++)
	  {
		current_second += (UINT32)MONTHTABLE[i] * DAY_CONVERTTO_SECONEDS;
		if(IS_LEAPYEAR(current_year) && (i == (UINT16)e_FEBRUARY))
		{
			current_second += DAY_CONVERTTO_SECONEDS;
		}
	  }
	}
	if(current_day == 0U)
	{
		*pTimeStampOut = 0UL;
		return;
	}
	current_second += (UINT32)(current_day - 1) * DAY_CONVERTTO_SECONEDS;
	
	current_second += (UINT32)current_hour * HOUR_CONVERTTO_SECONEDS;
	current_second += (UINT32)current_minute * MINUTE_CONVERTTO_SECONEDS;
	current_second += pDateTimeIn->Second;   
	*pTimeStampOut = current_second; 
}


#endif
