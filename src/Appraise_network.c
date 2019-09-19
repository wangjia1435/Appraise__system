/******************************************************************************
 *File Name	     :	Appraise_network.c
 *Copyright	     :	Zhuzhou CRRC Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/9/18
 *Description    :	提供评价系统网络数据接收、发送功能.
 *
 *Modification history:
 *REV1.0.0		WangJia     2019/09/18   File Create

 ******************************************************************************/
 /******************************************************************************
  *    Debug switch Section
  ******************************************************************************/


  /******************************************************************************
   *    Include File Section
   ******************************************************************************/


#include "../h/Appraise_network.h"

   /*#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
/******************************************************************************
*    Global Variable Define Section
******************************************************************************/
/*从ato接收的数据缓存通道 */
UINT8 g_RecvPipeBuffer[25][1400];

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

/******************************************************************************
*    Function Define Section
******************************************************************************/

E_SysBool Net_SocketInit(const char* ipStr, UINT16 port, UINT32* recvSocketFd, struct sockaddr_in* myAddr)
{
	int reFlag = 1;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 10;
	*recvSocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(myAddr, 0, sizeof(struct sockaddr_in));
	myAddr->sin_family = AF_INET;
	myAddr->sin_addr.s_addr = inet_addr(ipStr);
	myAddr->sin_port = htons(port);

	/*端口重新使用 */
	if (0 != setsockopt(*recvSocketFd, SOL_SOCKET, SO_REUSEADDR, &reFlag, sizeof(int)))
	{
		return e_FALSE;
	}
	//设置接收超时
	if (0 !=setsockopt(*recvSocketFd, SOL_SOCKET, SO_RCVTIMEO, (char*)& tv, sizeof(struct timeval)))
	{
		return e_FALSE;
	}
	if (0 != bind(*recvSocketFd, (struct sockaddr*)myAddr, sizeof(struct sockaddr_in)))
	{
		return e_FALSE;
	}
	return e_TRUE;
}

E_SysBool Net_SocketRcv(INT32 recvSocketFd, struct sockaddr_in* pAddr, char* rcvBuf, INT32 *rcvLen)
{
	/*只接收指定IP和port的数据 */
	struct timeval tv;
	INT32 addrLen = sizeof(struct sockaddr_in);
	fd_set readfds;
	struct sockaddr_in addr;

	tv.tv_sec = 0;
	tv.tv_usec = 100;
	FD_ZERO(&readfds);
	FD_SET(recvSocketFd, &readfds);
	bzero(pAddr, sizeof(struct sockaddr_in));

	/*pAddr->sin_family = AF_INET;
	pAddr->sin_port = htons(5000);
	pAddr->sin_addr.s_addr = htonl(INADDR_ANY);*/

	switch(select(recvSocketFd + 1, &readfds, NULL, NULL, &tv))
	{
		case -1: 
			return e_FALSE;
		case 0: 
			return e_TRUE;
		default:

			if(FD_ISSET(recvSocketFd, &readfds))/*有可读数据 */
			{
				bzero(rcvBuf, 1400);
				do
				{
					*rcvLen = recvfrom(recvSocketFd, rcvBuf, 1024, 0, (struct sockaddr*) pAddr, (socklen_t*)& addrLen);
					printf("recv %s, ip=%s, port=%d\n", rcvBuf, inet_ntoa(pAddr->sin_addr), ntohs(pAddr->sin_port));
				} while (*rcvLen > 0);
			}
			return e_TRUE;
	}
}

/******************************************************************************
 *Name    : Net_RcvDataStroe
 *Function: 网络接收数据缓存在g_RecvPipeBuffer[][]变量中
 *Para    :  UINT8* rcvBuf
 *Para    :  UINT32 rcvLen
 *Return  : 初始化状态，正常返回e_TRUE 异常返回e_FALSE
 *NOTE    : V1.0.0  Wangjia 	 2019/09/19     create
******************************************************************************/
E_SysBool Net_RcvDataStroe(UINT8* rcvBuf, UINT32 rcvLen)
{

}

UINT8* Get_RecvPipeBuffer()
{
	return &g_RecvPipeBuffer;
}


