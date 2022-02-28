
echo "generating"
python plugin_build.py

echo "compiling..."

PYTHON_VERSION=$(python3 --version | sed s/Python[[:space:]]//) # 3.9.5
PYTHON_VER=${PYTHON_VERSION%.*}          # 3.9
CFLAGS=`python3-config --cflags`
LDFLAGS=`python3-config --ldflags`
TARGETS="main"


for fname in $TARGETS
do
    echo "compiling $fname"
    gcc $CFLAGS $LDFLAGS -lpython${PYTHON_VER} my_plugin.c $fname.c -o $fname
done

echo "cleaning up..."
rm -rf *.dSYM



