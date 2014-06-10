
int foo(unsigned int x)
{
  if (x > 0)
    return x* foo(x -1);
  else
    return 1;
}

int main()
{
  return foo(5);
}
