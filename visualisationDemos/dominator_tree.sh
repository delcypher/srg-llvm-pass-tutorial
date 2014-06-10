#!/usr/bin/bash
clang -S -emit-llvm loop.c

# You can use this instead if LLVM was compiled with xdot in PATH
# opt -view-dom loop.ll > /dev/null

# Otherwise this will work
opt -dot-dom loop.ll > /dev/null
xdot dom.main.dot
