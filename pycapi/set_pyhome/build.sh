
echo "compiling..."

CFLAGS=$(python3-config --cflags)
LDFLAGS=$(python3-config --ldflags)

for fname in main
do
    echo "compiling $fname"
    clang -v $CFLAGS $LDFLAGS -lpython3.8 $fname.c -o MacOS/$fname
    # clang -v $CFLAGS $LDFLAGS -lpython3.8 $fname.c -o $fname
done

echo "cleaning up..."
rm -rf *.dSYM



