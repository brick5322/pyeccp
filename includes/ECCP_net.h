//
// Created by bric on 22-4-15.
//

#ifndef PYECCP_ECCP_NET_H
#define PYECCP_ECCP_NET_H

#include "ECCP.h"

#ifdef __linux
typedef int SOCKET;
#endif
/**
 * @todo 这里要跨windows和Linux平台
 * 
 */

/**
 * @brief 初始化不同操作系统环境下的网络
 * @todo
 */
void NetWork_Initialize();

/**
 * @brief 结束网络环境，与 @ref NetWork_Initialize 成对调用
 * @todo
 */
void NetWork_Finialize();

/**
 * @brief 设置监听UDP端口的套接字
 *
 * @todo
 * @param port 要监听的端口
 * @param max_access 最大接入量
 * @return SOCKET 开启的套接字
 */
SOCKET set_listen(unsigned short port,int max_access);
<<<<<<< HEAD

/**
 * @brief 非阻塞的接收socket的UDP包，在msg上构造为ECCP_message，
 * \n 并以点分十进制的字符串的格式将IP地址和UDP端口保存到IP_buffer中
 * @todo 
 * @param socket 
 * @param msg 
 * @param IP_buffer 点分十进制 如“127.0.0.1:8080”
 * @return int 
 */
int recv_eccp_msg(SOCKET socket,ECCP_message* msg,char* IP_buffer);

/**
 * @brief 发送一个ECCP报文到指定IP:Port
 * @todo
 * @param socket 
 * @param ip 
 * @param msg 
 * @return int 
 */
=======
int recv_eccp_msg(SOCKET socket,ECCP_message* msg,char* IP_buffer);
>>>>>>> 447d461fffc9410aa8cd091e42e189d65f9c4199
int send_eccp_msg(SOCKET socket,const char *ip,ECCP_message* msg);
#endif //PYECCP_ECCP_NET_H
