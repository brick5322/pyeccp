//
// Created by bric on 2022/4/9.
//

#include <libCodec/BMPcodec.h>
#include <stdio.h>
#include <stdlib.h>

extern unsigned int mem_to_file(stream *stm, unsigned int size);



int main()
{
    FILE *fp = fopen("testfile1.bmp", "wb+");
    stream* fstm = stream_alloc(0,mem_to_file,NULL);
    fstm->handler_object = fp;
    BMPcodec* pcodec = BMPcodec_alloc(fstm);
    BMPcodec_resize(pcodec,512,512,_24Bits);
    unsigned char* buffer = BMPcodec_buffer_alloc(pcodec);
    for(int i = 0;i<pcodec->info_header.width;i++)
        for (int j = 0; j < pcodec->info_header.height; j++) {
            /*color* currentPos = &buffer[BMPcodec_getpos(pcodec,i,j)];
            currentPos->r = (i+j)/4;
            currentPos->g = (i+j)/4;
            currentPos->b = (i+j)/4;*/
            buffer[(i*512+j)*3] = (i+j)/4;
            buffer[(i*512+j)*3 + 1] = (i+j)/4;
            buffer[(i*512+j)*3 + 2] = (i+j)/4;
        }
    BMPcodec_writeHeader(pcodec);
    fstm->handler_subject = buffer;
    BMPcodec_writeAll(pcodec);
    free(buffer);
    fclose(fp);
    fp = fopen("testfile2.bmp","wb+");
    BMPcodec_writeHeader(pcodec);
    color32 c;
    c.r = 246;
    c.g = 153;
    c.b = 180;
    BMPcodec_fill(pcodec,c);
    fclose(fp);
    return 0;
}