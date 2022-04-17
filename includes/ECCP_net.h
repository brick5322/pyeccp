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
 * @todo ����Ҫ��windows��Linuxƽ̨
 * 
 */

/**
 * @brief ��ʼ����ͬ����ϵͳ�����µ�����
 * @todo
 */
void NetWork_Initialize();

/**
 * @brief �������绷������ @ref NetWork_Initialize �ɶԵ���
 * @todo
 */
void NetWork_Finialize();

/**
 * @brief ���ü���UDP�˿ڵ��׽���
 *
 * @todo
 * @param port Ҫ�����Ķ˿�
 * @param max_access ��������
 * @return SOCKET �������׽���
 */
SOCKET set_listen(unsigned short port,int max_access);

/**
 * @brief �������Ľ���socket��UDP������msg�Ϲ���ΪECCP_message��
 * \n ���Ե��ʮ���Ƶ��ַ����ĸ�ʽ��IP��ַ��UDP�˿ڱ��浽IP_buffer��
 * @todo 
 * @param socket 
 * @param msg 
 * @param IP_buffer ���ʮ���� �硰127.0.0.1:8080��
 * @return int 
 */
int recv_eccp_msg(SOCKET socket,ECCP_message* msg,char* IP_buffer);

/**
 * @brief ����һ��ECCP���ĵ�ָ��IP:Port
 * @todo
 * @param socket 
 * @param ip 
 * @param msg 
 * @return int 
 */
int send_eccp_msg(SOCKET socket,const char *ip,ECCP_message* msg);
#endif //PYECCP_ECCP_NET_H
