//
// Created by bric on 2022/4/1.
//

#include "PyCameraObject.h"
#include <ECCP_net.h>

int isDir(const char *filepath) {
    PyObject* obj = PyImport_ImportModule("os.path");
    if(!obj)
    {
        PyErr_SetString(PyExc_ModuleNotFoundError,"No module named 'os.path'.");
        return NULL;
    }
    return PyObject_CallFunction(PyDict_GetItemString(PyModule_GetDict(obj), "isdir"), "s", filepath)==Py_True;
}

static PyObject* PyTypeObject_new_is_banned(PyTypeObject* obj)
{
    PyErr_SetString(PyExc_PermissionError,"The camera object is not allowed to construct by this way.");
    return NULL;
}

static PyCameraObject* PyTypeObject_private_new(PyTypeObject* self)
{
    PyCameraObject *ret = (PyCameraObject *) self->tp_alloc(self, self->tp_basicsize);
    if(!ret)
        PyErr_SetString(PyExc_MemoryError,"A Camera has access into the system,but connot alloc a Camera Object for it.");
    return ret;
}


static PyObject* get_ID(PyCameraObject* obj)
{
    return _PyUnicode_FromASCII(obj->info.staticID,32);
}

static PyObject* get_filePath(PyCameraObject* obj)
{
    int len = strlen(obj->info.filepath);
    if(len)
        return _PyUnicode_FromASCII(obj->info.filepath, len);
    else
        Py_RETURN_NONE;
}

static PyObject* set_filePath(PyCameraObject* obj,PyObject* args)
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


static PyObject* getPic(PyCameraObject* obj)
{
    ECCP_set_message_3(&obj->event);
    Py_RETURN_NONE;
}

static PyObject* startPicStream(PyCameraObject* obj,PyObject* args)
{
    int duration = 0;
    if (!PyArg_ParseTuple(args, "i", &duration))
        return NULL;
    ECCP_set_message_4(&obj->event,duration);
    Py_RETURN_NONE;
}

static PyObject* finishPicStream(PyCameraObject* obj)
{
    ECCP_set_message_6(&obj->event);
    Py_RETURN_NONE;
}

static PyObject* exec(PyObject * self,PyObject* args,PyObject* kwargs)
{
    PyObject* callback_func;
    int port;
    int max_access;
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
        for(int times;times<10;times++)
            if(msg_length = recv_eccp_msg(socket,msg_buffer,IP_buffer))
                if(!ECCP_is_Invalid(msg_buffer,msg_length))
                    if (msg_buffer->func_code == 0x01) {
                        camera = PyTypeObject_private_new(&PyCamera_Type);
                        ECCP_message_exec(msg_buffer, &camera->info);
                        if (PyObject_CallFunction(callback_func, "O", camera) == Py_False)
                            Py_DECREF(camera);
                        else
                            PyDict_SetItemString(&listen_dict, IP_buffer, camera);
                    }
                else {
                        camera = (PyCameraObject *) PyDict_GetItemString((PyObject *) &listen_dict, IP_buffer);
                        ECCP_message_exec(msg_buffer, &camera->info);
                    }


        PyObject * lAliveCamera = PyDict_Items((PyObject *) &listen_dict);
        Py_ssize_t len = PyList_Size(lAliveCamera);
        //遍历listen_dict查询
        for(Py_ssize_t i = 0;i<len;i++)
        {
            PyObject * socket_camera_tuple = PyList_GetItem(lAliveCamera,i);
            PyArg_ParseTuple(socket_camera_tuple,"sO",IP_buffer,camera);
            if(!camera)
                continue;
            if(time(0)>camera->info.TTL)
            {
                PyDict_DelItemString((PyObject *) &listen_dict, IP_buffer);
                Py_DECREF(camera);
                continue;
            }
            for(int nb_list = 0;nb_list<camera->event.length;nb_list++)
            {
                ECCP_message *Emsg = queue_out_move_message(&camera->event);
                if(send_eccp_msg(socket,IP_buffer,Emsg))
                    queue_in_message(&camera->event,Emsg);
                else
                    free(Emsg);
            }
            ECCP_set_message_1(&camera->event);
        }
    }
    free(msg_buffer);
    Py_RETURN_NONE;
}