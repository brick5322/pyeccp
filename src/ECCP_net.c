//
// Created by bric on 22-4-15.
//

#include "ECCP_net.h"

int recv_eccp_msg(SOCKET socket,ECCP_message* msg,char* IP_buffer)
{
    if(socket)
        return 1;
    else
        return 0;
}

int send_eccp_msg(SOCKET socket,const char *ip,ECCP_message* msg)
{
    if(socket)
        return 1;
    else
        return 0;
}
