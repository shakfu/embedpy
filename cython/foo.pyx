import sys

from libc.stdio cimport printf, fprintf, stderr, FILE
from libc.stddef cimport wchar_t

cdef extern from "Python.h":
    object PyString_FromStringAndSize(char *s, Py_ssize_t len)
    
    # very high level interface
    int Py_Main(int argc, wchar_t **argv)
    int Py_BytesMain(int argc, char **argv)
    int PyRun_AnyFile(FILE *fp, const char *filename)
    int PyRun_SimpleString(const char *command)
    int PyRun_SimpleFile(FILE *fp, const char *filename)
    int PyRun_InteractiveOne(FILE *fp, const char *filename)
    int PyRun_InteractiveLoop(FILE *fp, const char *filename)

    # returns references
    object PyRun_String(const char *str, int start, object globals, object locals)
    object PyRun_File(FILE *fp, const char *filename, int start, object globals, object locals)

    # type conversion
    ## strings: https://docs.python.org/3/c-api/unicode.html
    char* PyString_AS_STRING(object string) # deprecated
    const char* PyUnicode_AS_DATA(object o)
    const char* PyUnicode_AsUTF8(object unicode)
    const char* PyUnicode_AsUTF8AndSize(object unicode, Py_ssize_t *size)


    ## long: https://docs.python.org/3/c-api/long.html
    long PyLong_AsLong(object obj)

    ## bool: https://docs.python.org/3/c-api/bool.html
    # treated as a subclass of integers
    object PyFloat_FromString(object str)
    object PyFloat_FromDouble(double v)

    ## float: https://docs.python.org/3/c-api/float.html
    double PyFloat_AsDouble(object pyfloat) # with error-checking
    double PyFloat_AS_DOUBLE(object pyfloat) # without error-checking



## ---------------------------------------------------------------------------



cpdef main(str arg):
    cdef const char* s
    #code = compile(sys.argv[1], '<string>', 'exec')
    result = str(eval(arg))
    s = PyUnicode_AsUTF8(result)
    printf("from c, a string result: %s", s)

if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(sys.argv[1]) 

    else:
        print("usage: \tfoo '<python code string'")
        #print("   eg: \tfoo 'import math; print(math.pi)'")
        print("   eg: \tfoo \"f'py{1+1}'\"")

