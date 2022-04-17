//
// Created by bric on 2022/4/10.
//

#ifndef PYECCP_ECCP_CODE_FUNC_H
#define PYECCP_ECCP_CODE_FUNC_H
/**
 * @brief 这个头文件内的函数供 ECCP协议使用，旨在为上位机提供接到下位机回复后的操作
 */

#include <Camera.h>
#include <ECCP.h>
/**
 * @class camera_data
 * @brief 这个结构体储存了一个图像数据包的信息
 */
typedef struct camera_data
{
    time_t time;
    unsigned short pkt_cnt;
    short pkt_size;
    char pkt_data[];
}camera_data;

/**
 * @brief 以0号功能码函数为例，介绍形参和返回值
 * 
 * @param data ECCP协议的内容
 * @param length data的长度
 * @param camera 要处理功能码函数的相机信息
 * @return int >=0 成功，<0失败
 */
int func0_login(const char* data,unsigned short length,Camera_info* camera);

int func1_heartbeat(const char* data,unsigned short length,Camera_info* camera);

int func2_camera_detail(const char* data,unsigned short length,Camera_info* camera);

int func3_take_photo(const char* data,unsigned short length,Camera_info* camera);

int func4_start_timer(const char* data,unsigned short length,Camera_info* camera);

int func5_take_photo(const char* data,unsigned short length,Camera_info* camera);

int func6_stop_timer(const char* data,unsigned short length,Camera_info* camera);

#endif //PYECCP_ECCP_CODE_FUNC_H
