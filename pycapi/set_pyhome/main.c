#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <libgen.h>

int main(int argc, char *argv[])
{
    // char path[150];

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */

    // STRANGE: if I run the next line the python_home isn't set properly!!
    // char* exec_path = Py_EncodeLocale(Py_GetProgramFullPath(), NULL);
    // printf("exec_path: %s\n", exec_path);
    // printf("parent_dir: %s\n", dirname(exec_path));
    // printf("parent_parent_dir: %s\n", dirname(dirname(exec_path)));
    // sprintf(path, "%s/Resources", dirname(dirname(exec_path)));
    // wchar_t *python_home = Py_DecodeLocale(path, NULL);

    wchar_t *python_home = Py_DecodeLocale("$HOME/Downloads/projects/embedpy/pycapi/set_pyhome/Resources", NULL);
    // wchar_t *python_home = Py_DecodeLocale("../Resources", NULL);
    if (python_home == NULL) {
        fprintf(stderr, "Fatal error: cannot set python_home\n");
        exit(1);
    }
    Py_SetPythonHome(python_home);    
    printf("python_home: %s\n", Py_EncodeLocale(Py_GetPythonHome(), NULL));

    Py_Initialize();
    PyRun_SimpleString("import os\n"
                       "print('os.__file__: ', os.__file__)\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    return 0;
}

