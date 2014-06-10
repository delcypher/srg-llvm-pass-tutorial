Stripping dead functions
========================

This gives a small demo of stripping dead functions from a bitcode module.

First we run the internalize sets the [linkage type](http://llvm.org/docs/LangRef.html#linkage-types)
of to every function except main to ``internal``. This tells LLVM that these functions cannot be
called externally which means if ``main()`` does not call them then they will never be called.

Second we run the GlobalDCE pass (global dead code elimination) which will remove the dead
functions for us.

In the ``simple.c`` program the function ``foo()`` is clearly a dead function and by running
the necessary passes it is removed.
