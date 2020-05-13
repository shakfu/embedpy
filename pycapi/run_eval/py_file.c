#define PY_SSIZE_T_CLEAN
#include <Python.h>

int
main(int argc, char *argv[])
{
    char *fname;
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */

    if (argc > 1) {
        fname = argv[1];
    } else {
        fname = "hello.py";
    }

    Py_Initialize();

    PyObject *locals = PyDict_New();
    PyObject *globals = PyDict_New();
    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    
    PyObject *obj = Py_BuildValue("s", fname);
    FILE *file = _Py_fopen_obj(obj, "r+");
    if (file != NULL) {
        PyObject *pval = PyRun_File(file, fname, Py_eval_input, globals, locals);

        if (pval != NULL) {
            printf("pval not null\n");
            /* convert to C ----------------------------------------------------*/

            // string/unicode
            if PyUnicode_Check(pval) {
                char *cstr;
                PyArg_Parse(pval, "s", &cstr);
                // cstr = PyUnicode_AsUTF8(pval1);
                printf("c-string: %s\n", cstr);
            }

            // int/long
            if PyLong_Check(pval) {
                int cint;
                cint = (int) PyLong_AsLong(pval);
                printf("c-int: %d\n", cint);
            }
            
            // float
            if PyFloat_Check(pval) {
                float cfloat;
                cfloat = (float) PyFloat_AsDouble(pval);
                printf("c-float: %f\n", cfloat);
            }            
        }
        Py_DECREF(pval);
    }
    Py_DECREF(locals);
    Py_DECREF(globals);


    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    return 0;
}

