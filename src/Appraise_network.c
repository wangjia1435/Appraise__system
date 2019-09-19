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

	*recvSocketFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(myAddr, 0, sizeof(struct sockaddr_in));
	myAddr->sin_family = AF_INET;
	myAddr->sin_addr.s_addr = inet_addr(ipStr);
	myAddr->sin_port = htons(port);

	/*端口重新使用 */
	setsockopt(*recvSocketFd, SOL_SOCKET, SO_REUSEADDR, &reFlag, sizeof(int));
	if (0 != bind(*recvSocketFd, (struct sockaddr*)myAddr, sizeof(struct sockaddr_in)))
	{
		return e_FALSE;
	}
	return e_TRUE;
}

E_SysBool Net_SocketRcv(INT32 recvSocketFd, struct sockaddr_in* addr, char* rcvBuf, INT32 *rcvLen)
{
	/*只接收指定IP和port的数据 */
	struct timeval tv;
	INT32 addrLen = sizeof(struct sockaddr_in);
	fd_set readfds;

	tv.tv_sec = 1;
	tv.tv_usec = 100;
	FD_ZERO(&readfds);
	FD_SET(recvSocketFd, &readfds);


	switch(select(recvSocketFd + 1, &readfds, NULL, NULL, &tv))
	{
		case -1: 
			break;
		case 0: 
			break;
		default:
			if (FD_ISSET(recvSocketFd, &readfds))/*有可读数据 */
			{
				while ((*rcvLen = recvfrom(recvSocketFd, rcvBuf, 1024, 0, (struct sockaddr*) & addr, (socklen_t*)& addrLen)) >= 0)
				{
					printf("recv %s, ip=%d, port=%d\n", rcvBuf, addr->sin_addr.s_addr, addr->sin_port);
				}
			}
	}

}

