NAME=hello

echo "generating"
cython -3 --embed ${NAME}.pyx

echo "compiling..."
clang `python3.7-config --cflags --ldflags` ${NAME}.c -o ${NAME}

echo "cleaning up..."
rm -rf *.dSYM *.o



