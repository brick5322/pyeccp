//
// Created by bric on 2022/4/9.
//

#include <stdlib.h>
#include <string.h>
#include "ECCP.h"



ECCP_message *ECCP_message_alloc(const char *msg) {
    ECCP_message *ret = malloc(sizeof(ECCP_message));
    if(!ret)
        goto err;
    ret->func_code = *msg;
    ret->length = *(unsigned short *) (msg + 1);
    if (ret->length) {
        ret->data = malloc(ret->length);
        if (!ret->data)
            goto err;
    } else
        ret->data = NULL;
    memcpy(ret->data, msg + 3, ret->length);
    return ret;
err:
    free(ret);
    return NULL;
}

int ECCP_message_realloc(ECCP_message *Emsg, const char *msg) {
    unsigned short length = *(unsigned short *) (msg + 1);
    char* data = malloc(length);
    if(!data)
        return -1;
    free(Emsg->data);
    Emsg->length = length;
    Emsg->func_code = *msg;
    Emsg->data = data;
    memcpy(data, msg + 3, length);
    return 0;
}

void ECCP_message_free(ECCP_message *Emsg) {
    free(Emsg->data);
    free(Emsg);
}

int ECCP_message_exec(ECCP_message *Emsg, Camera_info *camera) {
    ECCP_func func;
    vec_ECCP_FUNC(Emsg->func_code, &func);
    if(func)
        return func(Emsg->data, Emsg->length, camera);
    else
        return 0;
}

void vec_ECCP_FUNC(unsigned char func_code,ECCP_func* func)
{
    static ECCP_func eccpFunc[128] = {0};
    if(func_code&0x80)
        eccpFunc[func_code&0x7f] = *func;
    else
        *func = eccpFunc[func_code];
}