#include <stdio.h>

void ulam(int n)
{
  if (n == 1)
  {
    printf("%i\n", n);
    return;
  }
  printf("%i\n", n);
  if (n%2 == 0)
    ulam(n/2);
  else
    ulam(3*n + 1);
}

void ulam2(int n)
{
  int n_ = n;
  if (n == 1)
    {
      printf("%i\n", n);
      return;
    }
  printf("%i\n", n);
  if (n_%2 == 0)
    n_ = n_ / 2;
  else
    n_ = 3*n_ + 1;
  ulam(n_);
}

int main(void)
{
  //ulam(10);

  ulam2(10);
  
  return 0;
}
