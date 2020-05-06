import cffi
ffibuilder = cffi.FFI()

ffibuilder.embedding_api("""
    int do_stuff(int, int);
""")

cflags='''
-I/usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/include/python3.7m 
-I/usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/include/python3.7m 
-I/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include
-I/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers

-Wno-unused-result -Wsign-compare -Wunreachable-code -fno-common -dynamic -DNDEBUG -g -fwrapv -O3 -Wall -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk
'''

ldflags='''
-L/usr/local/opt/python/Frameworks/Python.framework/Versions/3.7/lib/python3.7/config-3.7m-darwin -lpython3.7m -ldl -framework CoreFoundation
'''

ffibuilder.set_source("my_plugin", "",
    sources=['main.c'],
    include_dirs=[
        '/usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/include/python3.7m' 
        '/usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/include/python3.7m'
        '/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/usr/include'
        '/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers'
    ],
    extra_compile_args=[
        '-Wno-unused-result', 
        '-Wsign-compare',
        '-Wunreachable-code',
        '-fno-common',
        '-dynamic',
        '-DNDEBUG',
        '-g',
        '-fwrapv',
        '-O3',
        '-Wall',
        '-isysroot/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk',
    ],

    libraries=['python3.7m', 'dl'],
    library_dirs=['/usr/local/opt/python/Frameworks/Python.framework/Versions/3.7/lib/python3.7/config-3.7m-darwin'],
    # extra_link_args=['-framework CoreFoundation'],
)

ffibuilder.embedding_init_code("""
    from my_plugin import ffi

    @ffi.def_extern()
    def do_stuff(x, y):
        print("adding %d and %d" % (x, y))
        return x + y
""")

ffibuilder.compile(target="plugin-1.5.*", verbose=True)

