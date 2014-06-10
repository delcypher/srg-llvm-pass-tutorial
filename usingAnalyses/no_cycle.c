int foo(unsigned int x)
{
  unsigned int temp=1;
  for (int i=2; i <=x ; ++i)
    temp *= i;

  return temp;
}

int main()
{
  return foo(5);
}
