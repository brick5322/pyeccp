extern int test1_BMPcodec();
extern int test2_Camera();



typedef int (*currentTest)();
currentTest test = test1_BMPcodec;



int main()
{
    return test();
}