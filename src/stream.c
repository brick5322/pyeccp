//
// Created by bric on 2022/4/3.
//

#include <libOS/stream.h>
#include <stdlib.h>

stream *stream_alloc(unsigned int sz, RWfunc write_func, RWfunc read_func)
{
    unsigned char *buffer = NULL;
    stream *ret = malloc(sizeof(stream));
    if (!ret)
    {
        return NULL;
    }
    if (sz)
    {
        buffer = malloc(sz * sizeof(unsigned char));
        if (!buffer)
        {
            free(ret);
            return NULL;
        }
    }

    ret->read = read_func;
    ret->write = write_func;
    ret->buffer = buffer;
    ret->length = 0;
    *(unsigned int *)&ret->maxnb_buffer = sz;
    return ret;
}

void stream_free(stream *stm)
{
    free(stm->buffer);
    free(stm);
}
