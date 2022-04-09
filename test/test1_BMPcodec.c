//
// Created by bric on 2022/4/9.
//

#include <libCodec/BMPcodec.h>
#include <stdio.h>
#include <stdlib.h>

extern unsigned int mem_to_file(stream *stm, unsigned int size);



int test1_BMPcodec()
{
    FILE *fp = fopen("testfile1.bmp", "wb+");
    stream* fstm = stream_alloc(0,mem_to_file,NULL);
    fstm->handler_object = fp;
    BMPcodec* pcodec = BMPcodec_alloc(fstm);
    BMPcodec_resize(pcodec,510,510,_24Bits);
    unsigned char* buffer =BMPcodec_buffer_alloc(pcodec);
    for(int i = 0;i<pcodec->info_header.width;i++)
        for (int j = 0; j < pcodec->info_header.height; j++) {
            color* currentPos = &buffer[BMPcodec_getpos(pcodec,i,j)];
            currentPos->r = i/2;
            currentPos->g = j/2;
            currentPos->b = 0;
        }
    BMPcodec_setHeader(pcodec);
    fstm->handler_subject = buffer;
    BMPcodec_writeAll(pcodec);
    free(buffer);
    return 0;
}