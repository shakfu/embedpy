#include <stdio.h>  
#include <unistd.h>
#include <string.h>

/* python */
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* --------------------------------------- */
// constants

#define N_CMDS 5
#define N_CHARS 5


/* --------------------------------------- */
// types

typedef struct _py {
    PyObject *p_globals;
} t_py;

typedef void (*t_func)(t_py *, char *);


/* --------------------------------------- */
// forward func declarations

int py_check(char *cmd);
void py_free(t_py *x);
void py_import(t_py *x, char *args);
void py_eval(t_py *x, char *args);
void py_exec(t_py *x, char *args);
void py_execfile(t_py *x, char *args);
void py_run(t_py *x, char *args);


int main(int argc, char *argv[])
{
    t_py obj = {.p_globals = NULL};
    t_py *x  = &obj;
    char line[50];
    char *index = NULL;
    char *cmd = NULL;
    
    const char *keyword[N_CMDS] = {
        "import",
        "eval",
        "exec",
        "execfile",
        "run"
    };

    t_func method[N_CMDS] = {
        py_import,
        py_eval,
        py_exec,
        py_execfile,
        py_run
    };

    Py_Initialize();

    // python init
    PyObject *main_module = PyImport_AddModule("__main__"); // borrowed reference
    x->p_globals = PyModule_GetDict(main_module);           // borrowed reference

    // prepopulate globals dict
    int err = PyDict_SetItemString(x->p_globals, "testing", PyLong_FromLong(20));
    if (err != 0) {
        printf("PyDict_SetItemString with key 'testing', failed\n");
    }

    printf("usage: [import, eval, exec, execfile, run] [args] \n");
    while (fgets(line, sizeof line, stdin)) {
        cmd = strtok(line, " ");
        for (int i=0; i <= N_CMDS; i++) {
            if ((strncmp(cmd, keyword[i], N_CHARS)) == 0) { //match      
                // printf("cmd: %s\n", cmd);
                index = strstr(line, cmd);
                if (index) {
                    char *args = index + strlen(cmd)+1;
                    args = strtok(args,"\n");
                    printf("size of args: %ld\n", strlen(args));
                    // printf("found -> keyword:%s args:%s\n", cmd, args);
                    method[i](x, args);
                }
            }
        }
    }
    printf("\ndone!");

    Py_FinalizeEx();
    return 0;
}


//--------------------------------------------------------------------------

void py_import(t_py *x, char *args)
{
    PyObject* x_module = NULL;

    if (args != NULL) {
        x_module = PyImport_ImportModule(args); // x_module borrrowed ref
        if (x_module == NULL) {
            PyErr_SetString(PyExc_ImportError, "Ooops again.");
            goto error;
        }
        PyDict_SetItemString(x->p_globals, args, x_module);
        printf("imported: %s\n", args);
    }
    //else goto error;

    error:
        if(PyErr_Occurred()) {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);
            const char *pStrErrorMessage = PyUnicode_AsUTF8(pvalue);
            printf("PyException('import %s'): %s\n", args, pStrErrorMessage);
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
            // Py_XDECREF(x_module);
        }
}


void py_run(t_py *x, char *args)
{
    PyObject *pval = NULL;
    FILE* fhandle  = NULL;
    int ret = -0;

    if (args == NULL) {
        printf("%s: could not retrieve args\n", args);
        goto error;
    }
    printf("START run: %s\n", args);

    pval = Py_BuildValue("s", args); // new reference
    if (pval == NULL) {
        goto error;
    }

    fhandle = _Py_fopen_obj(pval, "r+");
    if (fhandle == NULL) {
        printf("could not open file '%s'\n", args);
        goto error;
    }

    ret = PyRun_SimpleFile(fhandle, args);
    if (ret == -1){
        goto error;
    }

    // success
    fclose(fhandle);
    Py_DECREF(pval);
    printf("END run: %s\n", args);

    error:
        if(PyErr_Occurred()) {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);
            const char *pStrErrorMessage = PyUnicode_AsUTF8(pvalue);
            printf("PyException('run %s'): %s\n", args, pStrErrorMessage);
            Py_XDECREF(pval);   
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
        }
}


void py_execfile(t_py *x, char *args)
{
    PyObject *pval = NULL;
    FILE* fhandle  = NULL;

    if (args == NULL) {
        printf("execfile: could not retrieve arg: %s\n", args);
        goto error;
    }
    printf("START execfile: %s\n", args);

    fhandle = fopen(args, "r");
    if (fhandle == NULL) {
        printf("could not open file '%s'\n", args);
        goto error;
    }

    pval = PyRun_File(fhandle, args, Py_file_input, x->p_globals, x->p_globals);
    if (pval == NULL) {
        goto error;
    }

    // success cleanup
    fclose(fhandle);
    Py_DECREF(pval);
    printf("END execfile: %s\n", args);

    error:
        if(PyErr_Occurred()) {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);
            const char *pStrErrorMessage = PyUnicode_AsUTF8(pvalue);
            printf("PyException('execfile %s'): %s\n", args, pStrErrorMessage);
            Py_XDECREF(pval);   
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
        }
}


void py_exec(t_py *x, char *args)
{
    PyObject *pval = NULL;

    if (args == NULL) {
        printf("exec: could not retrieve args: %s\n", args);
        goto error;
    }
    printf("START exec: %s\n", args);

    pval = PyRun_String(args, Py_single_input, x->p_globals, x->p_globals);
    if (pval == NULL) {
        goto error;
    }

    // success cleanup
    Py_DECREF(pval);
    printf("END exec: %s\n", args);

    error:
        if(PyErr_Occurred()) {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);
            const char *pStrErrorMessage = PyUnicode_AsUTF8(pvalue);
            printf("PyException('exec %s'): %s\n", args, pStrErrorMessage);
            Py_XDECREF(pval);   
            Py_XDECREF(ptype);
            Py_XDECREF(pvalue);
            Py_XDECREF(ptraceback);
        }
}



void py_eval(t_py *x, char *args)
{
    PyObject *pval = NULL;
    PyObject *locals = NULL;

    if (args == NULL) {
        printf("eval: could not retrieve quoted args: %s\n", args);
        goto error;
    }
    printf("START eval: %s\n", args);


    locals = PyDict_New();
    if (locals == NULL) {
        goto error;
    }

    pval = PyRun_String(args, Py_eval_input, x->p_globals, locals);
    if (pval == NULL) {
        goto error;
    }

    // handle ints and longs
    if (PyLong_Check(pval)) {
        long int_result = PyLong_AsLong(pval);
        printf("int: %ld\n", int_result);
    } 

    // handle floats and doubles
    if (PyFloat_Check(pval)) {
        float float_result = (float) PyFloat_AsDouble(pval);
        printf("int: %f\n", float_result);
    }

    // handle strings
    if (PyUnicode_Check(pval)) {
        const char *unicode_result = PyUnicode_AsUTF8(pval);
        printf("unicode: %s\n", unicode_result);

    }

    // handle lists, tuples and sets
    if (PyList_Check(pval) || PyTuple_Check(pval) || PyAnySet_Check(pval)) {
        PyObject *iter = NULL;
        PyObject *item = NULL;
        int i = 0;

        Py_ssize_t seq_size = PySequence_Length(pval);
        if (seq_size <= 0) {
            printf("cannot convert python sequence with zero or less length");
            goto error;
        }

        if ((iter = PyObject_GetIter(pval)) == NULL) {
            goto error;
        }
        
        while ((item = PyIter_Next(iter)) != NULL) {
            if (PyLong_Check(item)) {
                long long_item = PyLong_AsLong(item);
                printf("%d long: %ld\n", i, long_item);
                i++;
            }
            
            if (PyFloat_Check(item)) {
                float float_item = PyFloat_AsDouble(item);
                printf("%d float: %f\n", i, float_item);
                i++;
            }

            if (PyUnicode_Check(item)) {
                const char *unicode_item = PyUnicode_AsUTF8(item);
                printf("%d unicode: %s\n", i, unicode_item);
                i++;
            }
            Py_DECREF(item);
        }
        printf("end iter op: %d\n", i);

    }

    // success cleanup
    Py_XDECREF(pval);
    printf("END eval: %s\n", args);

    error:
        if (PyErr_Occurred()) {
            PyObject *ptype, *pvalue, *ptraceback;
            PyErr_Fetch(&ptype, &pvalue, &ptraceback);

            // get error message
            const char *pStrErrorMessage = PyUnicode_AsUTF8(pvalue);
            printf("PyException('eval %s'): %s\n", args, pStrErrorMessage);
            Py_DECREF(ptype);
            Py_DECREF(pvalue);
            Py_DECREF(ptraceback);
        }
        // cleanup
        Py_XDECREF(pval);    
}


