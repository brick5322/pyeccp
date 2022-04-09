#pragma once

#include <libOS/stream.h>

/**
 * @enum BitCount
 * @brief BMP色彩深度
 */
typedef enum BitCount
{
    _1Bit = 1,
    _8Bits = 8,
    _16Bits = 16,
    _24Bits = 24,
    _32Bits = 32
}BitCount;

/**
 * @class color（color24）
 * @brief 默认24位像素存储格式
 */
typedef struct color24
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}color24,color;

/**
 * @class color32
 * @brief 32位像素存储格式
 */
typedef struct color32
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
}color32;

/**
 * @class BMPFileHeader
 * @brief BMP文件头结构体
 * @details 存入文件时，从第2字节开始存放
 */
typedef struct BMPFileHeader
{
    unsigned short reserved;
    unsigned short identifier;
    unsigned int fileSz;
    unsigned int resevered;
    unsigned int dataOffset;
} BMPFileHeader;

/**
 * @class BMPInfoHeader
 * @brief BMP信息头结构体
 * */
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

/**
 * @class BMPcodec
 * @brief BMP解码器
 */
typedef struct BMPcodec
{
    BMPFileHeader f_header;
    BMPInfoHeader info_header;
    stream *stm;
} BMPcodec;

/**
 * @brief 构造BMPcodec结构体，将会在这个函数里分配内存，并通过 @ref BMPFileHeader_default_set 和 @ref BMPInfoHeader_default_set 配置文件头和信息头
 * @param stm 传入流
 * @return 构造的结构体
 */
BMPcodec *BMPcodec_alloc(stream* stm);

/**
 * @brief 默认的文件头配置
 * @param pFHeader 将要配置的文件头
 */
void BMPFileHeader_default_set(BMPFileHeader *pFHeader);

/**
 * @brief 默认的信息头配置
 * @param pIHeader 将要配置的信息头
 */
void BMPInfoHeader_default_set(BMPInfoHeader *pIHeader);

/**
 * @brief 从流中写入图像信息
 * @param pcodec 一个带有流的解码器实例
 * @param sz 写入的信息大小
 * @return 流写入函数的返回值
 */
unsigned int BMPcodec_write(BMPcodec* pcodec,unsigned int sz);

/**
 * @brief 从流中写入全部的图像信息
 * @param pcodec 一个带有流的解码器实例
 * @return 流写入函数的返回值
 */
unsigned int BMPcodec_writeAll(BMPcodec* pcodec);

/**
 * @brief 从流中读取图像信息
 * @param pcodec 一个带有流的解码器实例
 * @return 流读取的返回值
 */
unsigned int BMPcodec_read(BMPcodec* pcodec,unsigned int sz);

/**
 * @brief 从流中读取全部的图像信息
 * @param pcodec 一个带有流的解码器实例
 * @return 流读取的返回值
 */
unsigned int BMPcodec_readAll(BMPcodec* pcodec);

/**
 * @brief 重新设置BMP图像大小
 * @param pcodec 一个解码器实例
 * @param width 图像的新宽度
 * @param height 图像的新高度
 * @param bitCount 图像色彩深度
 * @return
 */
unsigned int BMPcodec_resize(BMPcodec* pcodec, unsigned int width, int height, BitCount bitCount);

/**
 * @brief 基于pcodec的参数申请一块适合大小的内存
 * @details 这里考虑到了行的4字节对齐
 * @param pcodec
 * @return
 */
unsigned char* BMPcodec_buffer_alloc(BMPcodec* pcodec);

/**
 * @brief 从流读取文件头
 * @param pcodec 一个带有流的解码器实例
 * @return 流读取的返回值
 */
int BMPcodec_getHeader(BMPcodec* pcodec);

/**
 * @brief 将文件头写入到流
 * @param pcodec 一个带有流的解码器实例
 * @return 流写入的返回值
 */
int BMPcodec_setHeader(BMPcodec* pcodec);

/**
 * @brief 释放pcodec，这里不会释放流
 * @param pcodec 要释放的解码器
 */
void BMPcodec_free(BMPcodec* pcodec);