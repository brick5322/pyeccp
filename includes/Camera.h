#ifndef PYECCP_CAMERA_H
#define PYECCP_CAMERA_H

#include <time.h>
#include <linux/limits.h>
#include <libCodec/BMPcodec.h>
#define CAMERA_LIVE_SEC 30
/**
 * @class Camera_info
 * @brief 存储相机信息的结构体
 */
typedef struct Camera_info
{
    char filepath[PATH_MAX];
    char staticID[32];
    BMPcodec codec;
    int infoLock;
    clock_t TTL;
} Camera_info;
/**
 * @brief 设置Camera基本信息，包括文件路径和相机出厂ID
 * @param info
 * @param filepath
 * @param staticID
 * @param TTL
 */
void Camera_info_basic_set(Camera_info* info, char* filepath,const char* staticID,clock_t TTL);

/**
 * @brief 通过相机信息，将裸数据存储为BMP格式的文件
 * @param time 当前unix时间戳
 * @param info 相机信息
 * @param data 裸数据流，保证长度为width*height个像素长
 * @return 0为成功,其他为失败
 */
int Camera_save_picture(clock_t time, Camera_info *info, const char *data);


#endif // PYECCP_CAMERA_H
