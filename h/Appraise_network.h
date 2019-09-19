/******************************************************************************
 *File Name	     :	Appraise_network.h
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2019/09/18
 *Description    :
 *Modification history:
 *REV1.0.0    WangJia     2019/09/18    File Create
******************************************************************************/
/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef APPRAISE_NETWORK_
#define	APPRAISE_NETWORK_

/******************************************************************************
*    Debug switch Section
******************************************************************************/

/******************************************************************************
*    Include File Section
******************************************************************************/
#include "../h/GL_Basic_Type_Definition.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/******************************************************************************
*    Global Macro Define Section
******************************************************************************/

/******************************************************************************
*    Global Struct    Define Section
******************************************************************************/


E_SysBool Net_SocketInit(const char* ipStr, UINT16 port, UINT32* recvSocketFd, struct sockaddr_in* myAddr);

E_SysBool Net_SocketRcv(INT32 recvSocketFd, struct sockaddr_in* addr, char* rcvBuf, INT32* rcvLen);

#endif