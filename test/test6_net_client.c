//
// Created by bric on 22-5-23.
//
#include <ECCP.h>
#include <ECCP_net.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char ip_buffer[20] = "127.0.0.1:8887";

    int sockfd;
    // char msg[10240];
    const char *msg = "Tooyoung too simple!!!"; // 准备不定长的数据

    ECCP_message *msgpro = (ECCP_message *) malloc(10240);;
    msgpro->func_code = 3;
    msgpro->length = strlen(msg)+1;
    memcpy(msgpro->data, msg, msgpro->length);


    //sockfd = set_listen(8887, 20);
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    printf("%d,%d",((char*)msgpro)[0],((char*)msgpro)[1]);
    send_eccp_msg(sockfd, ip_buffer, msgpro);

    // recv_eccp_msg(sockfd,msgpro,ip_buffer);



    return 0;
}