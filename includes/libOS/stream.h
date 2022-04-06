#pragma once

typedef struct stream stream;

typedef unsigned int (*RWfunc)(stream *, unsigned int);

struct stream
{
    void *buffer;
    unsigned int length;
    const unsigned int maxnb_buffer;
    void *handler_subject;
    void *handle_object;
    RWfunc write;
    RWfunc read;
};

stream *stream_alloc(unsigned int sz, RWfunc write_func, RWfunc read_func);

void stream_free(stream *);
