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

static PyObject* PyTypeObject_new_is_banned(PyTypeObject* obj); //用报异常来封掉构造
static PyCameraObject* PyTypeObject_private_new(PyTypeObject* obj);
static PyObject* get_ID(PyCameraObject*);
static PyObject* get_filePath(PyCameraObject*);
static PyObject* set_filePath(PyCameraObject*,PyObject* args);
static PyObject* getPic(PyCameraObject*);
static PyObject* startPicStream(PyCameraObject*,PyObject* args);
static PyObject* finishPicStream(PyCameraObject*);

static PyObject* exec(PyObject * self,PyObject* args);

#endif //PYECCP_PYCAMERAOBJECT_H
