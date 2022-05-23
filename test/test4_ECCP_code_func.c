//
// Created by bric on 2022/4/11.
//

#include <ECCP_code_func.h>
#include <string.h>
#include <ECCP.h>
#include <stdlib.h>

extern unsigned int mem_to_file(stream *stm, unsigned int size);

int main()
{
    char buffer[8207];

    unsigned char* bmpfile = malloc(256*256*3);

    for(int i = 0;i < 256;i++)
        for(int j = 0;j < 256;j++)
        {
            bmpfile[(i*256+j)*3] = 0xff;
            bmpfile[(i*256+j)*3 + 1] = 0xff;
            bmpfile[(i*256+j)*3 + 2] = 0xff;
        }

    for(int i = 0;i<8195;i++)
        buffer[i] = 0;

    Camera_info inf;
    inf.codec.stm = stream_alloc(0,mem_to_file,NULL);
    strcpy(inf.filepath,"./log");

    BMPFileHeader_default_set(&inf.codec.f_header);
    BMPInfoHeader_default_set(&inf.codec.info_header);

    ECCP_func func = func0_login;
    vec_ECCP_FUNC(0|0x80, &func);
    func = func1_heartbeat;
    vec_ECCP_FUNC(1|0x80, &func);
    func = func2_camera_detail;
    vec_ECCP_FUNC(2|0x80, &func);
    func = func3_take_photo;
    vec_ECCP_FUNC(3|0x80, &func);

    ECCP_message *Emsg = (ECCP_message *) buffer;
    camera_data * cameraData = (camera_data *) Emsg->data;
    Emsg->func_code = 0;
    Emsg->length = 32;
    memcpy(Emsg->data,"Liufubai2000053047301710chuan030",32);
    ECCP_message_exec(Emsg,&inf);

    Emsg->func_code = 1;
    Emsg->length = sizeof(clock_t);
    memcpy(Emsg->data,"00000000",sizeof(clock_t));
    ECCP_message_exec(Emsg,&inf);

    Emsg->func_code = 2;
    Emsg->length = 8;
    int tmpwh[2] = {256,256};
    memcpy(Emsg->data,&tmpwh,8);
    ECCP_message_exec(Emsg,&inf);

    Emsg->func_code = 3;
    Emsg->length = 8204;
    cameraData->time=1;
    cameraData->pkt_size=8192;
    for(int i = 0;i<256*256*3/16384;i++)
    {
        cameraData->pkt_cnt = i*2;
        memcpy(cameraData->pkt_data,bmpfile+i*2*PKT_BLOCK_SIZE,PKT_BLOCK_SIZE);
        ECCP_message_exec(Emsg,&inf);
    }


    free(bmpfile);
    return 0;
}