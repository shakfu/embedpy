
echo "compiling..."

for fname in py_string py_file py_module py_eval
do
    echo "compiling $fname"
    gcc `python3.7-config --cflags --ldflags` $fname.c -o $fname
done

echo "cleaning up..."
rm -rf *.dSYM



