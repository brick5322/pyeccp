//
// Created by bric on 2022/4/9.
//

#ifndef PYECCP_ECCP_H
#define PYECCP_ECCP_H
#include <Camera.h>


/**
 * @class ECCP_message
 * @brief ECCP协议报文结构体
 */
typedef struct ECCP_message
{
    char func_code;
    unsigned short length;
    char* data;
}ECCP_message;

typedef int (*ECCP_func)(const char* data,unsigned short length,Camera_info* camera);

/**
 * @brief 构造ECCP报文结构体
 * @param msg 截获的底层报文内容
 * @return 构造的报文实例
 */
ECCP_message* ECCP_message_alloc(const char* msg);

/**
 * @brief 从新的底层报文中重构结构体
 * @param Emsg 要重构的结构体
 * @param msg 截获的底层报文内容
 * @return 成功返回0
 */
int ECCP_message_realloc(ECCP_message* Emsg,const char* msg);

/**
 * @brief 释放结构体
 * @param Emsg 要释放的结构体
 */
void ECCP_message_free(ECCP_message* Emsg);

/**
 * @brief 执行报文内容
 * @param Emsg
 * @param camera
 * @return 为功能码函数返回值，0为成功
 */
int ECCP_message_exec(ECCP_message* Emsg,Camera_info* camera);

/**
 * @brief 保存功能码函数的容器
 * @param func_code 低位为函数功能码，0~127，最高位置1则为保存函数，置0为读取函数
 * @param func 功能码函数读写指向的地址，值得注意的是，func并不可以是静态的常量，也就是说并不能以函数名本身作为实参
 * @example  ECCP_func fun = A_REAL_EXISTS_FUNCTION; \n ECCP_vec_FUNC(0|0x80,fun);
 */
void vec_ECCP_FUNC(unsigned char func_code,ECCP_func* func);


#endif //PYECCP_ECCP_H
