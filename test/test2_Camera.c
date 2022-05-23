//
// Created by bric on 2022/4/6.
//
#include <libCodec/BMPcodec.h>
#include "Camera.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    Camera_info inf;

    strcpy(inf.filepath,"./log");
    strcpy(inf.staticID,"Liufubai2000053047301710chuan030");

    BMPFileHeader_default_set(&inf.codec.f_header);
    BMPInfoHeader_default_set(&inf.codec.info_header);

    color* buffer = malloc(BMPcodec_resize(&inf.codec,256,256,_24Bits));
    for(int i = 0;i<inf.codec.info_header.width;i++)
        for (int j = 0; j < inf.codec.info_header.height; j++) {
            buffer[i*256+j].r = i;
            buffer[i*256+j].g = j;
            buffer[i*256+j].b = (511-i-j)/2;
        }

    Camera_save_picture(time(0),&inf,(char*)buffer);
    return 0;
}