LLVM passes tutorial
====================

These are the sources used in a [tutorial](https://docs.google.com/presentation/d/1fxsbeGIwcMN5iLDLiIImKIwNwATSy1ilDuTOPDBqw_k/) given to the [Software Reliability
Group at Imperial College London](http://srg.doc.ic.ac.uk).

To get started run...

Install or build LLVM 3.5 with the corresponding clang and compiler-rt
and then run the following.

```
$ cd /some/path
$ git clone git://github.com/delcypher/srg-llvm-pass-tutorial.git src/
$ mkdir build
$ cd build
$ cmake-gui ../src
$ make
```

You may need to specify the ``LLVM_DIR`` variable to CMake so it knows
where to find the LLVM CMake modules. This should be a directory to the
folder containing ``LLVMConfig.cmake``. Typically this is something like
``/path/to/llvm/build/share/llvm/cmake/``. You can specify this on the command-line
instead of using ``cmake-gui`` or ``ccmake`` like so...

```
$ cmake -DLLVM_DIR:STRING=/path/to/llvm/build/share/llvm/cmake/ ../src
```

If you built LLVM and Clang from source make sure you put those tools in
your PATH otherwise the plug-ins might not work when running the shell scripts
(e.g. ``helloPass/run.sh``) if you have an older existing LLVM and Clang 
already installed.
