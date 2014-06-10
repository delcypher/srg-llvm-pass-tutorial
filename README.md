LLVM passes tutorial
====================

These are the sources used in a tutorial given to the Software Reliability
Group at Imperial College London.

To get started run...

Install or build LLVM 3.5 with the corresponding clang and compiler-rt.

```
$ cd /some/path
$ git clone <the path to the git repo> src/
$ mkdir build
$ cd build
$ cmake-gui ../src
$ make
```

You may need to specify the ``LLVM_DIR`` variable to CMake so it knows
where to find the LLVM CMake modules. This should be a directory to the
folder containing ``LLVMConfig.cmake``.
