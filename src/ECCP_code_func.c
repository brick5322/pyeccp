//
// Created by bric on 2022/4/10.
//

#include "ECCP_code_func.h"
#include <Camera.h>
#include <time.h>
#include <stdio.h>


int func0_login(const char* data, unsigned short length, Camera_info* camera)
{
    Camera_info_basic_set(camera,NULL,data,time(0)+CAMERA_LIVE_SEC);
    return 0;
}

int func1_heartbeat(const char* data,unsigned short length,Camera_info* camera) {
    camera->TTL = time(0) + CAMERA_LIVE_SEC;
    return 0;
}

int func2_camera_detail(const char* data,unsigned short length,Camera_info* camera) {
    BMPcodec_resize(&camera->codec,((unsigned int *) data)[0], ((int *) data)[1],_24Bits);
    camera->TTL = time(0) + CAMERA_LIVE_SEC;
    return 0;
}

int func3_take_photo(const char* data,unsigned short length,Camera_info* camera)
{
    static char filename[PATH_MAX];
    camera_data* cameraData = (camera_data *) data;
    sprintf(filename,"%s/%ld.bmp",camera->filepath,cameraData->time);
    FILE* fp;
    if(!cameraData->pkt_cnt)
    {
        fp = fopen(filename,"wb+");
        if(!fp)
            return ERR_FILE_CANNOT_OPEN;
        camera->codec.stm->handler_object = fp;
        BMPcodec_writeHeader(&camera->codec);
        color32 c;
        *(int*)&c = 0x74E0F9;//0xF699B4;
        BMPcodec_fill(&camera->codec,c);
        fclose(fp);
    }
    fp = fopen(filename,"rb+");
    if(!fp)
        return ERR_FILE_CANNOT_OPEN;
    int pos = cameraData->pkt_cnt*cameraData->pkt_size+(14+camera->codec.info_header.bitInfoHeadersz);
    fseek(fp,pos,SEEK_SET);
    camera->codec.stm->handler_object = fp;
    camera->codec.stm->handler_subject = cameraData->pkt_data;
    BMPcodec_write(&camera->codec,cameraData->pkt_size);
    fclose(fp);
    camera->TTL = time(0) + CAMERA_LIVE_SEC;
    return 0;
}

int func4_start_timer(const char* data,unsigned short length,Camera_info* camera)
{
    camera->TTL = time(0) + CAMERA_LIVE_SEC;
    return 0;
}

int func5_take_photo(const char* data,unsigned short length,Camera_info* camera)
{
    return func3_take_photo(data,length,camera);
}

int func6_stop_timer(const char* data,unsigned short length,Camera_info* camera)
{
    camera->TTL = time(0) + CAMERA_LIVE_SEC;
    return 0;
}