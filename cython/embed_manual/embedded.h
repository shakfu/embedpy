/* Generated by Cython 0.29.17 */

#ifndef __PYX_HAVE__embedded
#define __PYX_HAVE__embedded

#include "Python.h"

#ifndef __PYX_HAVE_API__embedded

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#ifndef DL_IMPORT
  #define DL_IMPORT(_T) _T
#endif

__PYX_EXTERN_C int say_hello_from_python(void);

#endif /* !__PYX_HAVE_API__embedded */

/* WARNING: the interface of the module init function changed in CPython 3.5. */
/* It now returns a PyModuleDef instance instead of a PyModule instance. */

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initembedded(void);
#else
PyMODINIT_FUNC PyInit_embedded(void);
#endif

#endif /* !__PYX_HAVE__embedded */