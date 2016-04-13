#include <stdio.h>

static long num_steps=100000; double step, pi;

int main()
{  int i;	
   double x, sum = 0.0;

   step = 1.0/(double) num_steps;
   #pragma openmp parallel for reduction(+:sum)
   for (i=0; i< num_steps; i++){
      x = (i+0.5)*step;
      sum = sum + 4.0/(1.0 + x*x);
   }
   pi = step * sum;
   printf("Pi = %.12f\n",pi);
   return 0;
}