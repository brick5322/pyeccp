//
// Created by bric on 2022/4/9.
//

#include "ECCP.h"


int ECCP_is_invalid(ECCP_message* Emsg,int length)
{
    if(length>=ECCP_buffersz)
        return 7;//E2BIG
    else if(Emsg->length!=length-3)
        return 107;//EBFONT
    return 0;
}

int ECCP_message_exec(ECCP_message *Emsg, Camera_info *camera) {
    ECCP_func func;
    vec_ECCP_FUNC(Emsg->func_code, &func);
    if(func)
        return func(Emsg->data, Emsg->length, camera);
    else
        return ERR_NO_CODE_FUNC;
}

void vec_ECCP_FUNC(unsigned char func_code,ECCP_func* func)
{
    static ECCP_func eccpFunc[128] = {0};
    if(func_code&0x80)
        eccpFunc[func_code&0x7f] = *func;
    else
        *func = eccpFunc[func_code];
}