Hello pass
==========

This is simply the Hello and Hello2 passes taken with minor modification from the LLVM
source tree. The code here really just serves to demonstrate building
an "out of tree" pass and using it as a plugin to opt.

To try it out make sure you've built and then run

```
$ run.sh
```

DO NOT RUN ``run.sh.in`` that won't work!

Running the Hello pass in clang
===============================

It is possible to run the Hello2 pass in clang directly by loading it as a
plug-in in clang and setting up the necessary code in Hello.cpp to register the
pass with the pass registry.

To try this out run

```
$ run_pass_in_clang.sh
```
