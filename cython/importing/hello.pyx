# cython: language_level=3

import sys
import os

print(__name__)
print(sys.path)
print(os.getcwd())

if __name__ == "__main__":
    print("Hi, I'm embedded.")
else:
    print("I'm being imported.")

