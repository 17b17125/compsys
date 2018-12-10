#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

int monte_carlo(int n, double *pi){
  int i;
  int m;
  double x,y;

  srand((unsigned int)time(NULL));
  if(n < 0) return -1;
  for(i = 0, m = 0; i < n; i++){
    x = rand() / (double)RAND_MAX;
    y = rand() / (double)RAND_MAX;
    if(x * x + y * y <= 1) m++;
  }
  *pi = (double)m / (double)n * 4.0;
  return 0;
}

int main(void){
  double *pi;

  if(monte_carlo(N, pi)){
    printf("error\n");
  }else{
    printf("%f\n", *pi);
  }
}
