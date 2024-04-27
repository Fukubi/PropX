# PropX

A Open Source Property Selling Manager using QT and C++, created for speed and to be less resource intensive as possible.

## Build Instructions
After cloning this repository and the submodules using
```bash
git clone aaaaa
cd PropX
git submodule update --init --remote
```

Create a build directory using
```bash
mkdir build
```

And use cmake to generate build files, in this example it's used to create MSYS2 make build files
```base
cd build
cmake -G "MSYS Makefiles" ..
```

The application built this way is located at build/src/PropX