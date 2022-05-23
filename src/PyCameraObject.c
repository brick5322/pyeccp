//
// Created by bric on 2022/4/1.
//

#include "PyCameraObject.h"
#include <ECCP_net.h>
#include <time.h>

int isDir(const char *filepath) {
    PyObject* obj = PyImport_ImportModule("os.path");
    if(!obj)
    {
        PyErr_SetString(PyExc_ModuleNotFoundError,"No module named 'os.path'.");
        return NULL;
    }
    return PyObject_CallFunction(PyDict_GetItemString(PyModule_GetDict(obj), "isdir"), "s", filepath)==Py_True;
}

 PyObject* PyCameraObject_new_is_banned(PyTypeObject* obj)
{
    PyErr_SetString(PyExc_PermissionError,"The camera object is not allowed to construct by this way.");
    return NULL;
}

 PyCameraObject* PyCameraObject_private_new(PyTypeObject* self)
{
    PyCameraObject *ret = PyObject_New(PyCameraObject,self);
    if(!ret)
    {
        PyErr_SetString(PyExc_MemoryError,"A Camera has access into the system,but connot alloc a Camera Object for it.");
        return NULL;
    }
    EventQueue_init(&ret->event);
    return ret;
}

 PyObject* PyCamera_repr(PyCameraObject* obj)
{
    char buf[sizeof("<class 'Camera'> with ID = ")+32];
    sprintf(buf, "<class 'Camera'> with ID = ");
    memcpy(buf+sizeof("<class 'Camera'> with ID = ")-1,obj->info.staticID,32);
    return _PyUnicode_FromASCII(buf, sizeof("<class 'Camera'> with ID = ")+31);
}

 PyObject* PyCamera_str(PyCameraObject* obj)
{
    return _PyUnicode_FromASCII(obj->info.staticID, 32);
}

 PyObject* PyCameraObject_get_ID(PyCameraObject* obj)
{
    return _PyUnicode_FromASCII(obj->info.staticID,32);
}

 PyObject* PyCameraObject_get_filePath(PyCameraObject* obj)
{
    int len = strlen(obj->info.filepath);
    if(len)
        return _PyUnicode_FromASCII(obj->info.filepath, len);
    else
        Py_RETURN_NONE;
}

 PyObject* PyCameraObject_set_filePath(PyCameraObject* obj,PyObject* args)
{
    const char *buffer = NULL;
    if (!PyArg_ParseTuple(args, "s", &buffer))
        return NULL;
    int length = strlen(buffer);
    if(length>PATH_MAX)
    {
        PyErr_SetString(PyExc_TypeError,"This is too long to be a filepath.");
        return NULL;
    }
    if(!isDir(obj->info.filepath))
    {
        PyErr_SetString(PyExc_NotADirectoryError,"This is not an Existed Directory.");
        return NULL;
    }
    memcpy(obj->info.filepath,buffer, length);
    Py_RETURN_NONE;
}


 PyObject* PyCameraObject_getPic(PyCameraObject* obj)
{
    ECCP_set_message_3(&obj->event);
    Py_RETURN_NONE;
}

 PyObject* PyCameraObject_startPicStream(PyCameraObject* obj,PyObject* args)
{
    int duration = 0;
    if (!PyArg_ParseTuple(args, "i", &duration))
        return NULL;
    ECCP_set_message_4(&obj->event,duration);
    Py_RETURN_NONE;
}

 PyObject* PyCameraObject_finishPicStream(PyCameraObject* obj)
{
    ECCP_set_message_6(&obj->event);
    Py_RETURN_NONE;
}
 void PyCameraObject_dealloc(PyCameraObject* obj)
{
    EventQueue_clear(&obj->event);
    PyObject_DEL(obj);
}


 PyObject* PyECCPserver_exec(PyObject * self,PyObject* args,PyObject* kwargs)
{
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
    const SOCKET socket = set_listen(port,max_access);
    ECCP_message* msg_buffer = malloc(ECCP_buffersz);
    int msg_length = 0;
    char IP_buffer[20];


    while(1)
    {
        PyCameraObject * camera = NULL;
        //这里要取传过来的msg
        for(int times;times<10;times++)
            if(msg_length = recv_eccp_msg(socket,msg_buffer,IP_buffer))
                if(!ECCP_is_Invalid(msg_buffer,msg_length))
                    if (msg_buffer->func_code == 0x01) {
                        camera = PyCameraObject_private_new(&PyCamera_Type);
                        ECCP_message_exec(msg_buffer, &camera->info);
                        if (PyObject_CallFunction(callback_func, "O", camera) == Py_False)
                            Py_DECREF(camera);
                        else
                        {
                            PyObject_Init((PyObject *) camera, &PyCamera_Type);
                            PyDict_SetItemString((PyObject *) listen_dict, IP_buffer, (PyObject *) camera);
                        }
                    }
                else {
                        camera = (PyCameraObject *) PyDict_GetItemString((PyObject *) listen_dict, IP_buffer);
                        ECCP_message_exec(msg_buffer, &camera->info);
                    }

        int timer_over = time(0)>timer;
        PyObject * lAliveCamera = PyDict_Items((PyObject *) listen_dict);
        Py_ssize_t len = PyList_Size(lAliveCamera);
        //遍历listen_dict查询，删除掉线的camera，然后执行发送函数，添加心跳包
        for(Py_ssize_t i = 0;i<len;i++)
        {
            PyObject * socket_camera_tuple = PyList_GetItem(lAliveCamera,i);
            PyArg_ParseTuple(socket_camera_tuple,"sO",IP_buffer,camera);
            if(!camera)
            {
                PyDict_DelItemString((PyObject *) listen_dict, IP_buffer);
                continue;
            }
            if(time(0)>camera->info.TTL)
            {
                PyDict_DelItemString((PyObject *) listen_dict, IP_buffer);
                Py_DECREF(camera);
                continue;
            }
            int elength = camera->event.length;
            for(int nb_list = 0;nb_list<elength;nb_list++)
            {
                ECCP_message *Emsg = EventQueue_out(&camera->event);
                if(send_eccp_msg(socket,IP_buffer,Emsg))
                    EventQueue_in(&camera->event, Emsg);
                else
                    free(Emsg);
            }
            if(timer_over)
                ECCP_set_message_1(&camera->event);
        }
        if(timer_over)
            timer = time(0)+TIMER_DURATION;
        Py_DECREF(lAliveCamera);
    }
    free(msg_buffer);
    Py_RETURN_NONE;
}