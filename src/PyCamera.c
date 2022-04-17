//
// Created by bric on 22-4-16.
//
#include <Python.h>
#include <PyCameraObject.h>

static PyMethodDef PyCamera_methods[] =
        {
                {"get_ID",(unaryfunc)PyCameraObject_get_ID,METH_NOARGS,"Get Camera ID."},
                {"get_filePath",(unaryfunc) PyCameraObject_get_filePath,METH_NOARGS,"Get FilePath."},
                {"set_filePath",(binaryfunc) PyCameraObject_set_filePath,METH_VARARGS,"Set FilePath."},
                {"get_pic",(binaryfunc) PyCameraObject_getPic,METH_VARARGS,"Get a picture."},
                {"start_picStream",(binaryfunc) PyCameraObject_startPicStream,METH_VARARGS,"start pic receiving stream with a fixed duration."},
                {"stop_picStream",(unaryfunc) PyCameraObject_finishPicStream,METH_NOARGS,"stop pic receiving stream."},
                {NULL,NULL,0,NULL}
        };


PyTypeObject PyCamera_Type =
        {
                PyObject_HEAD_INIT(NULL)
                "ECCP.camera",
                sizeof(PyCameraObject),
                0,
                (destructor) PyCameraObject_dealloc(),
                0,
                0,
                0,
                0,
                (reprfunc)PyRDR2Pic_repr,
                0,
                0,
                0,
                0,
                0,
                (reprfunc)PyRDR2Pic_str,
                PyObject_GenericGetAttr,
                0,
                0,
                Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
                "a drive ",
                0,
                0,
                0,
                0,
                0,
                0,
                PyRDR2Pic_methods,//tp_methods 成员函数
                0,//tp_members 成员变量
                0,
                0,
                0,//dict
                0,
                0,
                0,
                0,
                0,
                (newfunc)PyRDR2Pic_new,
                (freefunc)PyRDR2Pic_free,
        };