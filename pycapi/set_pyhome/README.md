# Notes

Test to help embedded python interpreter to find custom location of lib/pythonX.Y stdlib via Py_SetPythonHome 

test:

set py_home to

## Test inside same 

'.' -> './lib/python3.8'
 
Works


## Test in relative directory

'../Resources' -> '../Resources/lib/python3.8'

Works, but it has to be run inside 'MacOS', if run from location of
this README, it fails


## Test use of @executable_path

'@executable_path/../Resources' -> ?

FAIL. Does not convert @... to actual path


## Test in-program conversion of relative to absolute path


