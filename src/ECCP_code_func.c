//
// Created by bric on 2022/4/10.
//

#include "ECCP_code_func.h"
#include <Camera.h>
#include <time.h>
#include <stdio.h>

int func0_login(const char* data,unsigned short length,Camera_info* camera)
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
    return 0;
}

int func3_take_photo(const char* data,unsigned short length,Camera_info* camera)
{
    static char filename[PATH_MAX];
    camera_data* cameraData = (camera_data *) data;
    sprintf(filename,"%s/%ld.bmp",camera->filepath,cameraData->time);
    FILE* fp = fopen(filename,"rb+");
    if(!fp)
        return 22;
    if(!cameraData->pkt_cnt)
    {
        fseek(fp,0,SEEK_SET);
        camera->codec.stm->handler_object = fp;
        BMPcodec_writeHeader(&camera->codec);
        color32 c;
        *(int*)&c = 0x74E0F9;//0xF699B4;
        BMPcodec_fill(&camera->codec,c);
    }
    int pos = cameraData->pkt_cnt*PKT_BLOCK_SIZE+(14+camera->codec.info_header.bitInfoHeadersz);
    fseek(fp,pos,SEEK_SET);
    camera->codec.stm->handler_object = fp;
    camera->codec.stm->handler_subject = cameraData->pkt_data;
    BMPcodec_write(&camera->codec,cameraData->pkt_size);
    fclose(fp);
    return 0;
}
