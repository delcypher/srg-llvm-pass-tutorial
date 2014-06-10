#include <stdio.h>

int foo()
{
    return 0;
}

int bar()
{
    return 1;
}

int main()
{
    printf("Hello world!\n");
    int x = foo();
    int y = bar();
    return x + y;
}
