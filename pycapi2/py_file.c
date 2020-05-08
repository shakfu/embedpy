#define PY_SSIZE_T_CLEAN
#include <Python.h>

int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    
    PyObject *obj = Py_BuildValue("s", "hello.py");
    FILE *file = _Py_fopen_obj(obj, "r+");
    if(file != NULL) {
        PyRun_SimpleFile(file, "hello.py");
    }
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    return 0;
}

