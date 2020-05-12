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
    Py_SetProgramName(program);
    Py_Initialize();
   
    // create list
    PyObject *list = PyList_New(0); // empty list
    PyObject *n1 = PyLong_FromLong(10);
    PyObject *n2 = PyLong_FromLong(20);
    PyObject *n3 = PyFloat_FromDouble(1.4);
    PyObject *n4 = PyFloat_FromDouble(12.1);
    PyList_Append(list, n1);
    PyList_Append(list, n2);
    PyList_Append(list, n3);
    PyList_Append(list, n4);

    PyObject *s1 = PyUnicode_FromString("abc");
    PyObject *s2 = PyUnicode_FromString("def");
    PyObject *s3 = PyUnicode_FromString("ghi");
    PyList_Append(list, s1);
    PyList_Append(list, s2);
    PyList_Append(list, s3);

    if (PySequence_Check(list)) {
        Py_ssize_t length = PySequence_Length(list);
        printf("object is a sequence with a length of %ld\n", length);
    } else {
        printf("object is not a sequence");
    }

    PyObject *iter;
    PyObject *item;
    int i = 0;

    if ((iter = PyObject_GetIter(list)) == NULL) {
        return -1;
    }

    while ((item = PyIter_Next(iter)) != NULL) {
        if (PyLong_Check(item)) {
            i++;
            long long_item = PyLong_AsLong(item);
            printf("%d long: %ld\n", i, long_item);
        }
        
        if PyFloat_Check(item) {
            i++;
            float float_item = PyFloat_AsDouble(item);
            printf("%d float: %f\n", i, float_item);
        }

        if PyUnicode_Check(item) {
            i++;
            const char *unicode_item = PyUnicode_AsUTF8(item);
            printf("%d unicode: %s\n", i, unicode_item);
        }

        Py_DECREF(item);
    }

    Py_DECREF(iter);
    Py_DECREF(n1);
    Py_DECREF(n2);
    Py_DECREF(n3);
    Py_DECREF(n4);
    Py_DECREF(s1);
    Py_DECREF(s2);
    Py_DECREF(s3);
    Py_DECREF(list);

    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
    return 0;
}



