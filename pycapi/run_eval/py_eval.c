#define PY_SSIZE_T_CLEAN
#include <Python.h>



// float eval_py(float in_val)
// {
//   PyObject *pval;
//   PyObject *globals, *locals;

//     Py_Initialize();

//     locals = PyDict_New();
//     globals = PyDict_New();

//     PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());

//     pval = PyRun_String(string, Py_eval_input, globals, locals);
//     Py_DECREF(pval);

//     Py_FinalizeEx();

//     PyRun_SimpleString("from time import time,ctime\n"
//                        "print('Today is', ctime(time()))\n");
//     if (Py_FinalizeEx() < 0) {
//         exit(120);
//     }
//     PyMem_RawFree(program);
//     return 0.0;
// }


int main(int argc, char *argv[])
{
    // const char *cstr; // if using PyUnicode_AsUTF8
    char *cstr; // if using PyArg_Parse
    int cint;
    float cfloat;
    PyObject *pval1, *pval2, *pval3;
    PyObject *locals, *globals;

    Py_Initialize();

    // setup local and global dicts
    locals = PyDict_New();
    globals = PyDict_New();
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    
    // add a bit of python code as a string
    pval1 = PyRun_String("f'hel{1+2}lo'", Py_eval_input, globals, locals);
    pval2 = PyRun_String("100+200", Py_eval_input, globals, locals);
    pval3 = PyRun_String("1.5+2.1", Py_eval_input, globals, locals);
    
    /* convert to C ----------------------------------------------------*/
    
    // string/unicode
    if (PyUnicode_Check(pval1)) {
        PyArg_Parse(pval1, "s", &cstr);
        // cstr = PyUnicode_AsUTF8(pval1);
        printf("c-string: %s\n", cstr);
        Py_DECREF(pval1);
    } else {
        Py_DECREF(pval1);
    }

    // int/long
    if (PyLong_Check(pval2)) {
        cint = (int) PyLong_AsLong(pval2);
        printf("c-int: %d\n", cint);
        Py_DECREF(pval2);
    } else {
        Py_DECREF(pval2);
    }
    

    // float
    if (PyFloat_Check(pval3)) {
         cfloat = (float) PyFloat_AsDouble(pval3);
         printf("c-float: %f\n", cfloat);
         Py_DECREF(pval3);
    } else {
        Py_DECREF(pval3);
    }

    Py_FinalizeEx();

    return 0;
}

