
echo "compiling..."

for fname in redirect
do
    echo "compiling $fname"
    gcc $fname.c -o $fname
done

echo "cleaning up..."
rm -rf *.dSYM



