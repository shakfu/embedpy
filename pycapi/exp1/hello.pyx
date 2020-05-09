from libc.stdio cimport printf

# from libc.stdlib cimport free

# cdef unicode tounicode(char* s):
#     return s.decode('UTF-8', 'strict')

# cdef unicode tounicode_with_length(
#         char* s, size_t length):
#     return s[:length].decode('UTF-8', 'strict')

# cdef unicode tounicode_with_length_and_free(
#         char* s, size_t length):
#     try:
#         return s[:length].decode('UTF-8', 'strict')
#     finally:
#         free(s)



cpdef hello(str name):
	py_byte_string = name.encode('UTF-8')
	cdef char* cstr = py_byte_string
	printf("cstring: %s", cstr)

