//
// Created by bric on 2022/4/1.
//

#include "PyCameraObject.h"

int isDir(const char *filepath) {
    if(filepath)
        return 1;
    else
        return 0;
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
        PyErr_SetString(PyExc_MemoryError,"A Camera has assess into the system,but connot alloc a Camera Object for it.");
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

static PyObject* exec(PyObject * self,PyObject* args)
{
    Py_RETURN_NONE;
}