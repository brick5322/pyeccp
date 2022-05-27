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

static PyObject* PyCameraObject_new_is_banned(PyTypeObject* obj)
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

static PyObject* PyCamera_repr(PyCameraObject* obj)
{
    char buf[sizeof("<class 'Camera'> with ID = ")+32];
    sprintf(buf, "<class 'Camera'> with ID = ");
    memcpy(buf+sizeof("<class 'Camera'> with ID = ")-1,obj->info.staticID,32);
    return _PyUnicode_FromASCII(buf, sizeof("<class 'Camera'> with ID = ")+31);
}

static PyObject* PyCamera_str(PyCameraObject* obj)
{
    return _PyUnicode_FromASCII(obj->info.staticID, 32);
}

static PyObject* PyCameraObject_get_ID(PyCameraObject* obj)
{
    return _PyUnicode_FromASCII(obj->info.staticID,32);
}

static PyObject* PyCameraObject_get_filePath(PyCameraObject* obj)
{
    int len = strlen(obj->info.filepath);
    if(len)
        return _PyUnicode_FromASCII(obj->info.filepath, len);
    else
        Py_RETURN_NONE;
}

static PyObject* PyCameraObject_set_filePath(PyCameraObject* obj,PyObject* args)
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


static PyObject* PyCameraObject_getPic(PyCameraObject* obj)
{
    ECCP_set_message_3(&obj->event);
    Py_RETURN_NONE;
}

static PyObject* PyCameraObject_startPicStream(PyCameraObject* obj,PyObject* args)
{
    int duration = 0;
    if (!PyArg_ParseTuple(args, "i", &duration))
        return NULL;
    ECCP_set_message_4(&obj->event,duration);
    Py_RETURN_NONE;
}

static PyObject* PyCameraObject_finishPicStream(PyCameraObject* obj)
{
    ECCP_set_message_6(&obj->event);
    Py_RETURN_NONE;
}
static void PyCameraObject_dealloc(PyCameraObject* obj)
{
    EventQueue_clear(&obj->event);
    PyObject_DEL(obj);
}



static PyMethodDef PyCamera_methods[] =
{
        {"get_ID",(unaryfunc)PyCameraObject_get_ID,METH_NOARGS,"Get Camera ID."},
        {"get_filePath",(unaryfunc)PyCameraObject_get_filePath,METH_NOARGS,"Get FilePath."},
        {"set_filePath",(binaryfunc)PyCameraObject_set_filePath,METH_VARARGS,"Set FilePath."},
        {"get_pic",(binaryfunc)PyCameraObject_getPic,METH_VARARGS,"Get a picture."},
        {"start_picStream",(binaryfunc)PyCameraObject_startPicStream,METH_VARARGS,"start pic receiving stream with a fixed duration."},
        {"stop_picStream",(unaryfunc)PyCameraObject_finishPicStream,METH_NOARGS,"stop pic receiving stream."},
        {NULL,NULL,0,NULL}
};



PyTypeObject PyCamera_Type =
{
        PyObject_HEAD_INIT(NULL)
        "PyECCPServer.camera",
        sizeof(PyCameraObject),
        0,
        (destructor)PyCameraObject_dealloc,
        0,
        0,
        0,
        0,
        (reprfunc)PyCamera_repr,
        0,
        0,
        0,
        0,
        0,
        (reprfunc)PyCamera_str,
        PyObject_GenericGetAttr,
        PyObject_GenericSetAttr,
        0,
        Py_TPFLAGS_DEFAULT ,
        "a driver for Camera worked on Internet",
        0,
        0,
        0,
        0,
        0,
        0,
        PyCamera_methods,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        (newfunc)PyCameraObject_new_is_banned,
        0,
};