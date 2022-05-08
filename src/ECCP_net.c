//
// Created by bric on 22-4-15.
//

#include "ECCP_net.h"
/**
 * @todo 这里有个函数没写
 * @param socket 提供的socket
 * @param msg 调用者会提供了一块内存以接收msg
 * @param IP_buffer 调用者提供一块内存接收点分十进制的IP
 * @return msg的长度
 */
int recv_eccp_msg(SOCKET socket,ECCP_message* msg,char* IP_buffer)
{
    if(socket)
        return 1;
    else
        return 0;
}
/**
 * @todo 这里有个函数没写
 * @param socket 提供的socket
 * @param ip 要传达的IP地址，点分十进制“192.168.0.1:8080”
 * @param msg 要传出的message
 * @return 成功返回0，否则返回其他
 */
int send_eccp_msg(SOCKET socket,const char *ip,ECCP_message* msg)
{
    if(socket)
        return 1;
    else
        return 0;
}
