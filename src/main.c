extern int test2_Camera();



typedef int (*currentTest)();
currentTest test = test2_Camera;



int main()
{
    return test();
}