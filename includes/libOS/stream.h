#pragma once

typedef struct stream stream;

typedef unsigned int (*RWfunc)(stream *, unsigned int);

/**
 * @class stream
 * @brief 流，除自身和缓冲区外，不拥有任何的资源，通过从外部赋值@ref handler_subject 和@ref handler_object设置流的主体和客体,并传递函数指针来实现流的读取和写入
 * @todo 可能会考虑设计流的开启、关闭和刷新
 */
struct stream
{
    void *buffer;
    unsigned int length;
    const unsigned int maxnb_buffer;
    void *handler_subject;
    void *handler_object;
    RWfunc write;
    RWfunc read;
};

/**
 * @brief 流的构造
 * @param sz 缓冲区大小，可以为0
 * @param write_func 流从主体写入客体的函数指针
 * @param read_func 流从主体读取客体的函数指针
 * @return 构造的流对象
 */
stream *stream_alloc(unsigned int sz, RWfunc write_func, RWfunc read_func);
/**
 * @brief 流的析构
 * @param stm 要析构的流
 */
void stream_free(stream *stm);
