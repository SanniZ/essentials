
#include <stdio.h>
#include <stdlib.h>
#include <python3.5/Python.h>


int run_python(void) {
    PyObject *pModule, *pFunc, *pArgs, *pVer, *pRet;
    char *pVersion = NULL;

    Py_Initialize();
    if (!Py_IsInitialized()) {
        printf("it is failed to initialize python!");
        return -1;
    }

    pModule = PyImport_ImportModule("func");
    if (!pModule) {
        printf("it is failed to import module");
        goto err;
    }

    pFunc = PyObject_GetAttrString(pModule, "testFunc");
    if (!pFunc) {
        printf("it is failed to get func");
        goto err; 
    }

    pVer = PyObject_GetAttrString(pModule, "VERSION");
    if (!pVer) {
        printf("it is failed to get version");
        goto err; 
    } else {
        PyArg_Parse(pVer, "s", &pVersion);
        printf("Version: %s\n", pVersion);
    }

    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", "Say Hello to func: Hi testFunc!"));

    pRet = PyEval_CallObject(pFunc, pArgs);
    if (pRet) {
        char *result = NULL;
        PyArg_Parse(pRet, "s", &result);
        printf("get return from testFunc: %s\n", result);
    }

    Py_DECREF(pModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);
    Py_DECREF(pVer);
    Py_DECREF(pRet);

    Py_Finalize();

    return 0;

err:

    Py_Finalize();
    return -1;
}


int main(void) {
    return run_python();
}