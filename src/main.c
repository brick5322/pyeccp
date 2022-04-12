
#define test(func) \
extern int func();   \
int main() \
{                             \
    return func();\
}

#define test_num 4

#if test_num==1
    test(test1_BMPcodec)
#elif test_num==2
    test(test2_Camera)
#elif test_num==3
    test(test3_ECCP)
#elif test_num==4
    test(test4_ECCP_code_func)
#endif
