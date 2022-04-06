//
// Created by bric on 2022/4/1.
//

#ifndef PYECCP_PYCAMERAOBJECT_H
#define PYECCP_PYCAMERAOBJECT_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <pthread.h>
#include "Camera.h"

typedef pthread_mutex_t mutex;

typedef struct PyCameraObject
{
    PyObject_HEAD
    int socket_fd;
    Camera_info info;
    pthread_t thr;
    char buffer[6];
    mutex locker;
}PyCameraObject;

PyAPI_DATA(PyTypeObject) PyCamera_Type;

PyObject* wrong_alloc(); //用报异常来封掉构造
PyObject* get_ID(PyCameraObject*);
PyObject* get_filePath(PyCameraObject*);
PyObject* set_filePath(PyCameraObject*,PyObject** args);
PyObject* getPic(PyCameraObject*);
PyObject* startPicStream(PyCameraObject*,PyObject**args);
PyObject* finishPicStream(PyCameraObject*);

void CameraTCPservise(PyCameraObject*);

//PyObject* listenCamera(PyModuleObject* module,PyObject** args);

#endif //PYECCP_PYCAMERAOBJECT_H
