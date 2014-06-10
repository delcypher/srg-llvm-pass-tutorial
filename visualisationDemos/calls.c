extern int baz();

int bar()
{
    baz();
    return 4;
}

int foo()
{
    return bar();
}

int fac(unsigned int N)
{
    if ( N  < 2 )
        return 1;
    else
        return N * fac(N-1);
}

int main()
{
    foo();

    fac(5);
    return 0;
}
