echo
echo "testing py_string"
./py_string

echo
echo "testing py_file"
./py_file

echo
echo "testing py_module"
PYTHONPATH=. ./py_module pylib multiply 2 4

