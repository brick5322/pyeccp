extern int test1_BMPcodec();
extern int test2_Camera();
extern int test3_ECCP();
extern int test4_ECCP_code_func();

typedef int (*currentTest)();
currentTest test = test4_ECCP_code_func;



int main()
{
    return test();
}