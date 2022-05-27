//
// Created by bric on 22-4-15.
//
#ifdef MACOS
#elif defined(__linux)

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#elif defined(WIN32)

#endif

#include "ECCP_net.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define SERV_PORT 4399
#define MAXLINE 1024


void NetWork_Initialize()
{
#ifdef _WIN32
    WSAStartup(MAKEWORD(2, 0), &wsadata);
#endif // _WIN32
}

void NetWork_Finialize()
{
#ifdef _WIN32
    WSACleanup();
#endif // _WIN32
}

/**
 * @brief 设置监听UDP端口的套接字
 *
 * @param port 要监听的端口
 * @param max_access 最大接入量
 * @return SOCKET 开启的套接字 错误则返回-1
 * 考虑一个问题，是否进出可以开启同一个端口，udp发送的时候是否需要bind端口
 */
SOCKET set_listen(unsigned short port, int max_access) {
    int sockfd;
    struct sockaddr_in serveraddr;


    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);  // 绑定一个端口号


    // 绑定socket对象于通信链接
    int ret = bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
    if (ret < 0) {
        printf("bind fail\n");
        close(sockfd);
        return -1;
    }


    return sockfd;

}


/**
 * 这里应该是已经打开了bind端口
 * 设置一个默认的端口号 需要约定一个最大长度
 * @param socket 提供的socket socket 这里提供的是一个sockfd
 * @param msg 调用者会提供了一块内存以接收msg
 * @param IP_buffer 调用者提供一块内存接收点分十进制的IP
 * @return msg的长度 返回的是msg的长度
 */
int recv_eccp_msg(SOCKET socket, ECCP_message *msg, char *IP_buffer) {

    struct sockaddr_in cliaddr;
    size_t len = sizeof(cliaddr);

    int n;


    n = (int) recvfrom(socket, &((char *) msg)[1], ECCP_buffersz - 1, 0, (struct sockaddr *) &cliaddr, &len);
    sprintf(IP_buffer, "%s:%d", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

    return n;

}


/**

 * @param socket 提供的socket
 * @param ip 要传达的IP地址，点分十进制“192.168.0.1:8080”
 * @param msg 要传出的message
 * @return 成功返回0，否则返回其他
 */
int send_eccp_msg(SOCKET socket, const char *ip, ECCP_message *msg) {
    struct sockaddr_in server_addr;
    size_t port;
    char IP_address[16];
    size_t TotalDatalen = 0;
    int i = 0;
    for (i = 0; i < 22; ++i) {
        if (ip[i] == ':') {
            IP_address[i] = 0;
            break;
        } else
            IP_address[i] = ip[i];
    }
    //IP_address = strtok_r(ip, ":", &ip);
    port = atoi(ip + i + 1);


    TotalDatalen = sizeof(ECCP_message) + msg->length;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(IP_address);


    return sendto(socket, &((char *) msg)[1], TotalDatalen - 1, 0, (struct sockaddr *) &server_addr, sizeof server_addr)
           ? 0 : -1;

}
