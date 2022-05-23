#include <ECCP.h>
#include <ECCP_net.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char ip_recv[20];

    int sockfd;

    char msg[1024];

    ECCP_message *msgpro = msg;

    sockfd = set_listen(0x3030, 20);

    printf("out1\n");

    recv_eccp_msg(sockfd, msgpro, ip_recv);

    printf("%d", msgpro->func_code);


    return 0;
}