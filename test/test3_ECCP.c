//
// Created by bric on 2022/4/9.
//

#include <stdlib.h>
#include <ECCP.h>
#include <stdio.h>
#include <string.h>

int fun1(const char* data,unsigned short length,Camera_info* camera)
{
    printf("%s",data);
    return 0;
}

int fun2(const char* data,unsigned short length,Camera_info* camera)
{
    printf("func2:%s",data);
    return 0;
}

int main()
{
    char msg[]={0,0, 14, 0, 'H','e','l','l','o',' ','W','o','r','l','d','!','\n','\0'};
    char msg2[]={0,1, 13, 0, 'H','e','l','l','o',' ','E','C','C','P','!','\n','\0'};
    ECCP_func fun = fun1;
    vec_ECCP_FUNC(0|0x80,&fun);
    fun = fun2;
    vec_ECCP_FUNC(1|0x80,&fun);
    if(!ECCP_is_Invalid((ECCP_message *) msg, sizeof(msg) - 1))
        ECCP_message_exec((ECCP_message *) msg, NULL);
    if(!ECCP_is_Invalid((ECCP_message *) msg2, sizeof(msg2) - 1))
        ECCP_message_exec((ECCP_message *) msg2, NULL);
    return 0;
}
