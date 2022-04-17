//
// Created by bric on 2022/4/9.
//

#ifndef PYECCP_ECCP_H
#define PYECCP_ECCP_H
#include <Camera.h>

#define PKT_BLOCK_SIZE (8192)
#define ECCP_buffersz (PKT_BLOCK_SIZE + 16)


#define ERR_FILE_CANNOT_OPEN (-22)
#define ERR_NO_CODE_FUNC (-2)

/**
 * @class ECCP_message
 * @brief ECCP事件结构体
 * @details 每个ECCP事件对应一个ECCP报文，而存储ECCP事件的本质，就是存储这些个报文
 * \n 应当将这个结构体套用在某块内存上，所以并不会提供ECCP_message_alloc()这样的函数
 */
typedef struct ECCP_message
{
    const char reserved;
    char func_code;
    unsigned short length;
    char data[];
}ECCP_message;

typedef int (*ECCP_func)(const char* data,unsigned short length,Camera_info* camera);

/**
 * @brief 检验报文合法性
 * @param Emsg 要检验的报文内容
 * @param length 报文实际长度（即UDP包长）
 * @return 成功返回0
 */
int ECCP_is_Invalid(ECCP_message* Emsg,int length);

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
