#include <stdio.h>
#include <math.h>

int main(void)
{
  int i = 0;
  double total = 0, summand = 1, ende = pow(10, -15);
  for (i = 1; summand > ende; i++)
    total += (summand = 1/pow(i, i));
  printf("%.15lf\n\n", total);
  return 0;
}
