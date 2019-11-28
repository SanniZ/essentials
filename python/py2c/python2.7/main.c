
#include <stdio.h>
#include <stdlib.h>
#include <python2.7/Python.h>


int run_python(void) {
    PyObject *pFile, *pModule, *pDict, *pFunc, *pArgs, *pRet, *pVer;

    Py_Initialize();
    if (!Py_IsInitialized()) {
        printf("it is failed to initialize python!");
        return -1;
    }

    pFile = PyString_FromString("func");
    pModule = PyImport_Import(pFile);
    if (!pModule) {
        printf("it is failed to import module");
        goto err;
    }

    pDict = PyModule_GetDict(pModule);
    if (!pDict) {
        printf("it is failed to get dict");
        goto err; 
    }

    pFunc = PyDict_GetItemString(pDict, "testFunc");
    if (!pFunc) {
        printf("it is failed to get func");
        goto err; 
    }

    pVer = PyDict_GetItemString(pDict, "VERSION");
    if (!pVer) {
        printf("it is failed to get version");
        goto err; 
    } else {
        char *version = NULL;
        PyArg_Parse(pVer, "s", &version);
        printf("get version: %s\n", version);
    }

    pArgs = PyTuple_New(3);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "Hi"));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", "testFun"));
    PyTuple_SetItem(pArgs, 2, Py_BuildValue("s", "!"));

    pRet = PyObject_CallObject(pFunc, pArgs);
    if (pRet) {
        char *result = NULL;
        PyArg_Parse(pRet, "s", &result);
        printf("Ret: %s\n", result);
    }

    Py_DECREF(pFile);
    Py_DECREF(pModule);
    Py_DECREF(pDict);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);

    Py_Finalize();

    return 0;

err:

    Py_Finalize();
    return -1;
}


int main(void) {
    return run_python();
}