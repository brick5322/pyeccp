//
// Created by bric on 22-4-15.
//

#include <pcap/socket.h>
#include "ECCP_net.h"
#include <string.h>
#include <printf.h>
#include <stdlib.h>

#define SERV_PORT 4399
#define MAXLINE 1024


/**
 * @brief 设置监听UDP端口的套接字
 *
 * @param port 要监听的端口
 * @param max_access 最大接入量
 * @return SOCKET 开启的套接字 错误则返回-1
 */
SOCKET set_listen(unsigned short port,int max_access){
    int sockfd;
    struct sockaddr_in serveraddr;




    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serveraddr, sizeof serveraddr);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htonl(port);


    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof serveraddr);


    return sockfd;

}





/**
 * 这里应该是已经打开了bind端口
 * 设置一个默认的端口号 需要约定一个最大长度
 * @todo 这里有个函数没写
 * @param socket 提供的socket socket 这里提供的是一个sockfd
 * @param msg 调用者会提供了一块内存以接收msg
 * @param IP_buffer 调用者提供一块内存接收点分十进制的IP
 * @return msg的长度 返回的是msg的长度
 */
int recv_eccp_msg(SOCKET socket,ECCP_message* msg,char* IP_buffer)
{
    struct sockaddr_in servaddr, cliaddr;
    // in_port_t port;

    // 完成bind
    // memset(&servaddr, 0, sizeof servaddr);
    // servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(socket, (struct sockaddr*)&servaddr, sizeof servaddr);



    // 打开recvform 并不面相连接，所以没有那么多奇奇怪怪的，加一个超时就行吧
    int n;
    socklen_t len;

    // msg = (ECCP_message *) malloc(10240);
    //  memset(msg, 0, 10240);

    // IP_buffer = malloc(30);
    n = recvfrom(socket, msg, MAXLINE, 0, (struct sockaddr* )&cliaddr, &len);
    sprintf(IP_buffer, "%s:%d", inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

    return n;

}


/**

 * @param socket 提供的socket
 * @param ip 要传达的IP地址，点分十进制“192.168.0.1:8080”
 * @param msg 要传出的message
 * @return 成功返回0，否则返回其他
 */
int send_eccp_msg(SOCKET socket,const char *ip,ECCP_message* msg)
{
    struct sockaddr_in server_addr;
    in_port_t port;
    char *IP_address;

    // 解析ip
    char *rest = ip;
    char *s = ":";
    IP_address = strtok_r(rest, s, &rest);
    port = atoi(strtok_r(rest, s, &rest));



    //  清零操作
    memset(&server_addr, 0, sizeof server_addr);

    // 基础发送数据
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, IP_address, &server_addr.sin_addr);

    if(sendto(socket, msg, sizeof msg, 0, (struct sockaddr *)&server_addr, sizeof server_addr))
        return 0;

}
