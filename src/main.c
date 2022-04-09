extern int test1_BMPcodec();
extern int test2_Camera();
extern int test3_ECCP();


typedef int (*currentTest)();
currentTest test = test3_ECCP;



int main()
{
    return test();
}