#include <Python.h>
#include <PyCameraObject.h>
#ifdef _WIN32
#include <WinSock2.h>
#endif // _WIN32


static PyObject* PyECCPServer_exec(PyObject* self, PyObject* args, PyObject* kwargs)
{
    NetWork_Initialize();
    PyObject* callback_func;
    int port;
    int max_access;
    static time_t timer = 0;
    if (!PyArg_ParseTuple(args, "ii", &port, &max_access))
        return NULL;
    if (port > 0xffff)
    {
        PyErr_SetString(PyExc_TypeError, "port(Arg1) should be an unsigned short value.");
        return NULL;
    }
    if (callback_func = PyDict_GetItemString(kwargs, "callback"))
    {
        if (!PyCallable_Check(callback_func))
        {
            PyErr_SetString(PyExc_TypeError, "\"callback\" should be a function or lambda expression, which means it must be callable");
            return NULL;
        }
    }
    else
    {
        PyErr_SetString(PyExc_TypeError, "must have a keyword parameter whose key-name is \"callback\"");
        return NULL;
    }
    const SOCKET socket = set_listen(port, max_access);
    ECCP_message* msg_buffer = malloc(ECCP_buffersz);
    int msg_length = 0;
    char IP_buffer[20];


    while (1)
    {
        PyCameraObject* camera = NULL;
        //这里要取传过来的msg
        for (int times = 0; times < 10; times++)
            if (msg_length = recv_eccp_msg(socket, msg_buffer, IP_buffer))
                if (!ECCP_is_Invalid(msg_buffer, msg_length))
                    if (msg_buffer->func_code == 0x01) {
                        camera = PyCameraObject_private_new(&PyCamera_Type);
                        ECCP_message_exec(msg_buffer, &camera->info);
                        if (PyObject_CallFunction(callback_func, "O", camera) == Py_False)
                            Py_DECREF(camera);
                        else
                        {
                            PyObject_Init((PyObject*)camera, &PyCamera_Type);
                            PyDict_SetItemString((PyObject*)listen_dict, IP_buffer, (PyObject*)camera);
                        }
                    }
                    else {
                        camera = (PyCameraObject*)PyDict_GetItemString((PyObject*)listen_dict, IP_buffer);
                        ECCP_message_exec(msg_buffer, &camera->info);
                    }

        int timer_over = time(0) > timer;
        PyObject* lAliveCamera = PyDict_Items((PyObject*)listen_dict);
        Py_ssize_t len = PyList_Size(lAliveCamera);
        //遍历listen_dict查询，删除掉线的camera，然后执行发送函数，添加心跳包
        for (Py_ssize_t i = 0; i < len; i++)
        {
            PyObject* socket_camera_tuple = PyList_GetItem(lAliveCamera, i);
            PyArg_ParseTuple(socket_camera_tuple, "sO", IP_buffer, camera);
            if (!camera)
            {
                PyDict_DelItemString((PyObject*)listen_dict, IP_buffer);
                continue;
            }
            if (time(0) > camera->info.TTL)
            {
                PyDict_DelItemString((PyObject*)listen_dict, IP_buffer);
                Py_DECREF(camera);
                continue;
            }
            int elength = camera->event.length;
            for (int nb_list = 0; nb_list < elength; nb_list++)
            {
                ECCP_message* Emsg = EventQueue_out(&camera->event);
                if (send_eccp_msg(socket, IP_buffer, Emsg))
                    EventQueue_in(&camera->event, Emsg);
                else
                    free(Emsg);
            }
            if (timer_over)
                ECCP_set_message_1(&camera->event);
        }
        if (timer_over)
            timer = time(0) + TIMER_DURATION;
        Py_DECREF(lAliveCamera);
    }
    free(msg_buffer);
    NetWork_Finialize();
    Py_RETURN_NONE;
}

static PyMethodDef PyECCPServer_methods[] =
{
        {"exec",(ternaryfunc)PyECCPServer_exec,METH_VARARGS | METH_KEYWORDS,"start ECC service"},
        {NULL,NULL,0,NULL}
};

static PyModuleDef PyECCPServer_Module =
        {
                PyModuleDef_HEAD_INIT,
                "PyECCPServer",
                "ECCP server module",
                -1,
                NULL,
        };

PyMODINIT_FUNC PyInit_PyECCPServer(void)
{
    if (PyType_Ready(&PyCamera_Type) < 0)
        return NULL;
    PyObject* module = PyModule_Create(&PyECCPServer_Module);
    if (!module)
        return NULL;
    listen_dict = (PyDictObject*)PyDict_New();
    if (!listen_dict)
        return NULL;
    Py_INCREF(&PyCamera_Type);
    PyModule_AddObject(module, "camera", (PyObject *) &PyCamera_Type);
    PyModule_AddObject(module, "list_dict", (PyObject *) listen_dict);
    PyModule_AddFunctions(module,PyECCPServer_methods);

    PyModule_AddStringConstant(module, "__author__", "brick");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2022);

    return module;
}
