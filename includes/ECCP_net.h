//
// Created by bric on 22-4-15.
//

#ifndef PYECCP_ECCP_NET_H
#define PYECCP_ECCP_NET_H

#include "ECCP.h"

#ifdef __linux
typedef int SOCKET;
#endif

SOCKET set_listen(unsigned short port,int max_access);
int recv_eccp_msg(SOCKET socket,ECCP_message* msg);
int send_eccp_msg(SOCKET socket,const char *ip,ECCP_message* msg);
#endif //PYECCP_ECCP_NET_H
