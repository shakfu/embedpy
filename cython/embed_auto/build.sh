NAME=hello
PYTHON_VERSION=$(python3 --version | sed s/Python[[:space:]]//) # 3.9.5
PYTHON_VER=${PYTHON_VERSION%.*}          # 3.9
CFLAGS=`python3-config --cflags`
LDFLAGS=`python3-config --ldflags`


echo "generating"
cython -3 --embed ${NAME}.pyx

echo "compiling ${NAME}"
clang -v $CFLAGS $LDFLAGS -lpython${PYTHON_VER} ${NAME}.c -o ${NAME}

echo "cleaning up..."
rm -rf *.dSYM



