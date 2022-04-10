//
// Created by bric on 2022/4/10.
//

#ifndef PYECCP_ECCP_CODE_FUNC_H
#define PYECCP_ECCP_CODE_FUNC_H
/**
 * @brief 这个头文件内的函数供 ECCP协议使用，旨在为上位机提供接到下位机回复后的操作
 */

#include <Camera.h>

int func0_login(const char* data,unsigned short length,Camera_info* camera);

int func1_heartbeat(const char* data,unsigned short length,Camera_info* camera);

int func2_camera_detail(const char* data,unsigned short length,Camera_info* camera);

int func3_take_photo(const char* data,unsigned short length,Camera_info* camera);

int func4_start_timer(const char* data,unsigned short length,Camera_info* camera);

int func5_heartbeat(const char* data,unsigned short length,Camera_info* camera);

int func6_stop_timer(const char* data,unsigned short length,Camera_info* camera);

#endif //PYECCP_ECCP_CODE_FUNC_H
