Using the IRBuilder
===================

This is an example pass that uses the [IRBuilder](http://llvm.org/docs/ProgrammersManual.html#creating-and-inserting-new-instructions) to
inject instructions that replace calls to ``get_global_id(x)``
with

```
get_local_id(x) + get_group_id(x)*get_local_size(x)
```

To try this out run

```
$ run.sh
```
