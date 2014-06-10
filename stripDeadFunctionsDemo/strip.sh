#!/bin/bash
clang -S -emit-llvm simple.c
opt -S -print-before-all -print-after-all -internalize \
    -internalize-public-api-list=main \
    -globaldce simple.ll 2>&1 | less
