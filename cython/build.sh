
echo "generating"
cython -3 --embed foo.pyx

echo "compiling..."
clang `python3.7-config --cflags --ldflags` foo.c -o foo

echo "cleaning up..."
rm -rf *.dSYM *.o



