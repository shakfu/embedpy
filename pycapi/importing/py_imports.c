#define PY_SSIZE_T_CLEAN
#include <Python.h>

int
main(int argc, char *argv[])
{
    PyObject *pval;
    int sum;

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    
    // setup local and global namespaces
    PyObject* locals = PyDict_New();
    PyObject* globals = PyDict_New();
    //PyObject* main_module = PyImport_AddModule("__main__");
    //PyObject* globals = PyModule_GetDict(main_module);
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    
    // add hello and world modules to global namespace
    PyObject* x_module = PyImport_ImportModule("hello");
    PyDict_SetItemString(globals, "hello", x_module);
    
    PyObject* y_module = PyImport_ImportModule("world");
    PyDict_SetItemString(globals, "world", y_module);
    
    //Py_XDECREF(x_module);
    
    pval = PyRun_String("hello.x + world.y", Py_eval_input, 
            globals, locals);
    
    sum  = PyLong_AsLong(pval);
    printf("hello.x + world.y = %d", sum);

    Py_DECREF(pval);
    Py_XDECREF(x_module);
    Py_XDECREF(y_module);
    
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    return 0;
}

