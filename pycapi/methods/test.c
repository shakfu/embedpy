/* python */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main(int argc, char *argv[])
{
    //PyObject *globals = NULL;

    Py_Initialize();

    //PyObject *main_module = PyImport_AddModule("__main__"); // borrowed reference
    //globals = PyModule_GetDict(main_module);           // borrowed reference
    //Py_INCREF(globals);
    //Py_DECREF(globals);

    Py_FinalizeEx();
    return 0;
}

