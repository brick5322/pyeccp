#include "Camera.h"
#include <stdio.h>
#include <string.h>

unsigned int mem_to_file(stream *stm, unsigned int size)
{
    FILE *fp = stm->handler_object;
    unsigned int len = fwrite(stm->handler_subject, size, 1, fp);
    *(int *)&stm->handler_subject += len * size;
    return len * size;
}

void Camera_info_basic_set(Camera_info* info, char* filepath,const char* staticID,clock_t TTL)
{
    if(filepath)
        strcpy(info->filepath,filepath);
    if(staticID)
        memcpy(info->staticID,staticID,32);
    info->TTL = TTL;
    int infoLock = 0;
}

int Camera_save_picture(clock_t time, Camera_info *info, const char *data)
{
    static char filename[PATH_MAX];
    sprintf(filename, "%s/%ld.bmp", info->filepath, time);
    FILE *fp = fopen(filename, "wb+");
    if (!fp)
        return -1;

    stream *fstm = stream_alloc(0, mem_to_file, NULL);
    fstm->handler_object = fp;

    info->codec.stm = fstm;

    BMPcodec_writeHeader(&info->codec);
    fstm->handler_subject = (void*)data;

    BMPcodec_writeAll(&info->codec);

    stream_free(fstm);
    info->codec.stm = NULL;

    fclose(fp);
    return 0;
}
