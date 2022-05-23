#include <ECCP.h>
#include <ECCP_net.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char ip_recv[20];

    int sockfd;

    char msg[10240];

    ECCP_message *msgpro = msg;


    sockfd = set_listen(8887, 20);

    printf("out1\n");

    recv_eccp_msg(sockfd, msgpro, ip_recv);

    printf("%d\n", msgpro->func_code);
    printf("IP地址为：%s\n", ip_recv);
    printf("包含的数据为：%s", msgpro->data);


    return 0;
}