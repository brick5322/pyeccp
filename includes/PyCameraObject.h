//
// Created by bric on 2022/4/1.
//

#ifndef PYECCP_PYCAMERAOBJECT_H
#define PYECCP_PYCAMERAOBJECT_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <ECCP_event.h>
#include <Camera.h>

#define TIMER_DURATION (20)

typedef struct  PyCameraObject
{
    PyObject_HEAD
    Camera_info info;
    EventQueue event;
}PyCameraObject;

PyDictObject* listen_dict;

PyAPI_DATA(PyTypeObject) PyCamera_Type;

 PyObject* PyCameraObject_new_is_banned(PyTypeObject* obj); //用报异常来封掉构造
 PyCameraObject* PyCameraObject_private_new(PyTypeObject* obj);
 PyObject* PyCamera_repr(PyCameraObject* obj);
 PyObject* PyCamera_str(PyCameraObject* obj);
 PyObject* PyCameraObject_get_ID(PyCameraObject*);
 PyObject* PyCameraObject_get_filePath(PyCameraObject*);
 PyObject* PyCameraObject_set_filePath(PyCameraObject*, PyObject* args);
 PyObject* PyCameraObject_getPic(PyCameraObject*);
 PyObject* PyCameraObject_startPicStream(PyCameraObject*, PyObject* args);
 PyObject* PyCameraObject_finishPicStream(PyCameraObject*);
 void PyCameraObject_dealloc(PyCameraObject*);
 PyObject* PyECCPserver_exec(PyObject * self, PyObject* args, PyObject* kwargs);

#endif //PYECCP_PYCAMERAOBJECT_H
