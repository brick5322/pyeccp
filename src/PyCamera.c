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

static PyMethodDef PyECCPserver_methods[] =
        {
                {"exec",(ternaryfunc) PyECCPserver_exec,METH_VARARGS|METH_KEYWORDS,"start ECC service"},
                {NULL,NULL,0,NULL}
        };

PyTypeObject PyCamera_Type =
        {
                PyObject_HEAD_INIT(NULL)
                "PyECCPserver.camera",
                sizeof(PyCameraObject),
                0,
                (destructor) PyCameraObject_dealloc,
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
                0,/* @todo 在这里填入dict？*/
                0,
                0,
                0,
                0,
                0,
                (newfunc)PyCameraObject_new_is_banned,
                0,
        };
static PyModuleDef PyECCPserver_Module =
        {
                PyModuleDef_HEAD_INIT,
                "PyECCPserver",
                "ECCP server module",
                -1,
                NULL,
        };

PyMODINIT_FUNC PyInit_PyECCPserver(void)
{
    if (PyType_Ready(&PyCamera_Type) < 0)
        return NULL;
    PyObject* module = PyModule_Create(&PyECCPserver_Module);

    if (!module)
        return NULL;
    Py_INCREF(&PyCamera_Type);

    PyModule_AddObject(module, "camera", &PyCamera_Type);
    PyModule_AddObject(module, "list_dict", listen_dict);
    PyModule_AddFunctions(module,PyECCPserver_methods);

    PyModule_AddStringConstant(module, "__author__", "brick");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2022);

    return module;
}