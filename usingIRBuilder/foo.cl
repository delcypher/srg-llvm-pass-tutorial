// HACK. You don't normal declare built-ins in OpenCL
// but to make things easier for clang I'll declare them here
int get_global_id(int);

void __kernel foo(__global int* A, int x)
{
    A[ get_global_id(0)] = 1 + get_global_id(x);
}
