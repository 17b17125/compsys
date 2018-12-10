#include <stdio.h>
#include <stdlib.h>

#define N ((1<<8)+1)

void ary_sort(int *ary, int ary_size){
  int i, j;
  int c;
  int tmp;

  if(ary_size < 1){
    printf("error\n");
    return;
  }
  for(i = 0; i < ary_size; i++){
    c = 1;
    for(j = 0; j < ary_size; j++){
      if(*(ary + j) > *(ary + j + 1)){
        tmp = *(ary + j);
        *(ary + j) = *(ary + j + 1);
        *(ary + j + 1) = tmp;
        c = 0;
      }
    }
    if(c) return;
  }
}

int main(void){
  int i;
  int e;
  int *A;

  A = (int*)(malloc(sizeof(int) * N));
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (int) A[i-1] * A[1] % N;
  }
  for(i = 0; i < N; i++){
    printf("[%3d]:%8d\n", i, A[i]);
  }
  ary_sort(A, N);
  printf("--sort--\n");
  for(i = 0; i < N; i++){
    printf("[%3d]:%8d\n", i, A[i]);
  }
  printf("--check--\n");
  e = 0;
  for(i = 0; i < N; i++){
    if(A[i] != i){
      printf("A[%3d] should equal (%d)\n", A[i], i);
      e++;
    }
  }
  printf("%d errors\n", e);
}
