#pragma once

#include <libOS/stream.h>
typedef enum BitCount
{
    _1Bit = 1,
    _8Bits = 8,
    _16Bits = 16,
    _24Bits = 24,
    _32Bits = 32
}BitCount;


typedef struct color24
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}color24,color;

typedef struct color32
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
}color32;

typedef struct BMPFileHeader
{
    unsigned short reserved;
    unsigned short identifier;
    unsigned int fileSz;
    unsigned int resevered;
    unsigned int dataOffset;
} BMPFileHeader;

typedef struct BMPInfoHeader
{
    unsigned int bitInfoHeadersz;
    unsigned int width;
    int height;
    unsigned short planes;
    unsigned short bitCount; // Bits Per Pixel
    unsigned int compression;
    unsigned int dataSz;
    unsigned int DPMw; // Dots Per Meter in Width
    unsigned int DPMh; // Dots Per Meter in Height
    unsigned int colors;
    unsigned int importantColors;

} BMPInfoHeader;

typedef struct BMPcodec
{
    BMPFileHeader f_header;
    BMPInfoHeader info_header;
    stream *stm;
} BMPcodec;

BMPcodec *BMPcodec_alloc(stream* stm);

void BMPFileHeader_default_set(BMPFileHeader *pFHeader);

void BMPInfoHeader_default_set(BMPInfoHeader *pIHeader);

unsigned int BMPcodec_write(BMPcodec* pcodec,unsigned int sz);

unsigned int BMPcodec_writeAll(BMPcodec* pcodec);

unsigned int BMPcodec_read(BMPcodec* pcodec,unsigned int sz);

unsigned int BMPcodec_readAll(BMPcodec* pcodec);

unsigned int BMPcodec_resize(BMPcodec* pcodec, unsigned int width, int height, BitCount bitCount);
/*从流读取文件头*/
int BMPcodec_getHeader(BMPcodec* pcodec);
/*将文件头写入到流*/
int BMPcodec_setHeader(BMPcodec* pcodec);

void BMPcodec_free(BMPcodec* pcodec);