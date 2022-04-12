//
// Created by bric on 2022/4/1.
//

#ifndef PYECCP_PYCAMERAOBJECT_H
#define PYECCP_PYCAMERAOBJECT_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <ECCP_event.h>
#include <Camera.h>


typedef struct PyCameraObject
{
    PyObject_HEAD
    Camera_info info;
    EventQueue event;
}PyCameraObject;

PyDictObject listen_dict;

PyAPI_DATA(PyTypeObject) PyCamera_Type;

PyObject* banned_alloc(); //用报异常来封掉构造
PyObject* get_ID(PyCameraObject*);
PyObject* get_filePath(PyCameraObject*);
PyObject* set_filePath(PyCameraObject*,PyObject** args);
PyObject* getPic(PyCameraObject*);
PyObject* startPicStream(PyCameraObject*,PyObject**args);
PyObject* finishPicStream(PyCameraObject*);

PyObject* exec(PyObject * self,PyObject** args);

#endif //PYECCP_PYCAMERAOBJECT_H
