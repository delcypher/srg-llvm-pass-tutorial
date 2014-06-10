#!/usr/bin/bash
clang -S -emit-llvm loop.c

# You can use this instead if LLVM was compiled with xdot in PATH
# opt -view-regions loop.ll > /dev/null

# Otherwise this will work
opt -dot-regions loop.ll > /dev/null
xdot reg.main.dot
