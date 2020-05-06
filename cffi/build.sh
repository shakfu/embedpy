
echo "generating"
python embedme.py

echo "compiling..."
clang `python3.7-config --cflags --ldflags` my_plugin.c main.c -o main

echo "cleaning up..."
rm -rf *.dSYM *.o



