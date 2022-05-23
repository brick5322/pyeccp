//
// Created by bric on 22-4-15.
//
#include <Python.h>

int main()
{
    Py_Initialize();
    PyObject* os_path = PyImport_ImportModule("os.path");
    os_path = PyImport_ImportModule("os.path");
    os_path = PyImport_ImportModule("os.path");
    os_path = PyImport_ImportModule("os.path");

    PyObject* path_dict = PyModule_GetDict(os_path);
    PyObject* is_dir_func = PyDict_GetItemString(path_dict, "isdir");
    PyObject* exists_func = PyDict_GetItemString(path_dict, "exists");
    PyObject* value;
    PyObject* obj = Py_None;
    char input[255];
    while (1)
    {
        scanf("%s", input);
        obj = PyObject_CallFunction(exists_func, "s", input);
        if (obj == Py_False)
            printf("哦，亲爱的，这东西就像隔壁山姆大叔的头发一样，你懂我的意思吧，我是说，不要拿这些不存在的东西来烦我了。\n");
        else
        {
            value = Py_BuildValue("s", input);
            obj = ((PyFunctionObject*)is_dir_func)->vectorcall(is_dir_func, &value, 1,NULL);
            //obj = PyObject_CallFunction(is_dir_func, "s", input);
            if (obj == Py_True)
                printf("让我看看，天啊，或许应该说，它长得的确有些别致，但请一定要相信我，它确实是个目录没错。\n");
            if (obj == Py_False)
                printf("哦，我的好伙计，别跟我开玩笑了，这样的东西，你管它叫目录？\n");
        }
    }
    Py_Finalize();
    return 0;
}