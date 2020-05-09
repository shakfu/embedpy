NAME=embedded

echo "generating"
cython -3 ${NAME}.pyx

echo "compiling..."
clang `python3.7-config --cflags --ldflags` ${NAME}.c main.c -o ${NAME}

echo "cleaning up..."
rm -rf *.dSYM *.o



