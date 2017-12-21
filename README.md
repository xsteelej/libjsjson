# libjsjson
A C++14 JSON Parser and Serializer

## To build (Mac OSX / Linux):

Install cmake 3.9.0 or above: https://cmake.org

Install a C++14 compiler:
* Mac OSX - Apple LLVM version 9.0.0 (clang-900.0.37)
* Linux - G++ 4.9+

### Followed by the following Bash commands:

```
cd libjsjson
mkdir build
cd build
cmake ..
make
```
Creates the following files in libjsjson/bin folder:

libjsjson.a
test_libjsjson

To test:

```
cd build
ctest
```

Or:

```
../bin/test_libjsjson
```




