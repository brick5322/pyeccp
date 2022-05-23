//
// Created by bric on 22-5-23.
//
#include <ECCP.h>
#include <ECCP_net.h>
#include <unistd.h>

int main()
{
    char ip_buffer[20] = "127.0.0.1:12336";

    int sockfd;
    char msg[1024];
    ECCP_message *msgpro = msg;
    msgpro->func_code = 3;
    msgpro->length = 0;

    sockfd = set_listen(0x3030,20);

    send_eccp_msg(sockfd,ip_buffer,msgpro);

    // recv_eccp_msg(sockfd,msgpro,ip_buffer);



    return 0;
}