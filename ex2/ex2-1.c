#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  int val;
  int isEmpty;  //0: non-Empty, other:Empty
  struct _node *prev;
  struct _node *next;
}node;

int put (node *tail, int val){
  node *new;

  if(tail -> isEmpty){
    tail -> val = val;
    tail -> isEmpty = 0;
    tail -> prev = NULL;
    tail -> next = NULL;
    return 0;
  }
  if(tail -> prev != NULL){
    put(tail -> prev, val);
  } else {
    new = (node *)malloc(sizeof(node));
    if(new == NULL) return -1;
    new -> val = val;
    new -> isEmpty = 0;
    new -> prev = NULL;
    new -> next = tail;
    tail -> prev = new;
  }
  return 0;
}

int get (node *head){
  int v = head -> val;
  node *fnode = NULL;

  if(head -> isEmpty) return -1;
  if(head -> prev != NULL){
    fnode = head -> prev;
    head -> val = head -> prev -> val;
    if(head -> prev -> prev != NULL){
      head -> prev -> prev -> next = head;
      head -> prev = head -> prev -> prev;
    } else {
      head -> prev = NULL;
    }
    free(fnode);
  } else {
    head -> isEmpty = 1;
  }
  return v;
}

int delete(node *head, int val){
  int v = -1;

  if(head == NULL) return v;
  if(head -> prev != NULL){
    v = head -> val;
    if(v == val){
      head -> prev -> next = head -> next;
      head -> next -> prev = head -> prev;
      free(head);
      return v;
    } else {
      delete(head -> prev, val);
    }
  }
  return v;
}

void display(node *head){
  if(head != NULL && !head -> isEmpty) {
    printf("%d\n", head -> val);
    display(head -> prev);
  }
}

int main(int argc, char **argv){
  int i;
  node *n;

  n = (node *)malloc(sizeof(node));
  n -> val = 0;
  n -> isEmpty = 0;
  n -> prev = NULL;
  n -> next = NULL;

  printf("start tests\n");
  printf("-display\n");
  display(n);

  printf("\n--put test--\n");
  for(i = 1; i < 8; i++){
    if(put(n, i)){
      printf("failed putting %d\n", i);
    } else {
      printf("-put %d\n", i);
    }
  }
  printf("-display\n");
  display(n);
  printf("should equal (\n");
  for(i = 0; i < 8; i++) printf("%d\n", i);
  printf(")\n");

  printf("\n--get test--\n");
  printf("-get\n");
  printf("%d should equal (0)\n\n", get(n));
  printf("-display\n");
  display(n);
  printf("should equal (\n");
  for(i = 1; i < 8; i++) printf("%d\n", i);
  printf(")\n");
  printf("%d should equal (1)\n\n", get(n));
  printf("-display\n");
  display(n);
  printf("should equal (\n");
  for(i = 2; i < 8; i++) printf("%d\n", i);
  printf(")\n");

  printf("\n--delete test--\n");
  printf("-delete 4\n");
  delete(n, 4);
  printf("-display\n");
  display(n);
  printf("should equal (\n");
  printf("2\n");
  printf("3\n");
  printf("5\n");
  printf("6\n");
  printf("7\n)\n");
  printf("-delete 6\n");
  delete(n, 6);
  printf("-display\n");
  display(n);
  printf("should equal (\n");
  printf("2\n");
  printf("3\n");
  printf("5\n");
  printf("7\n)\n");

  printf("\n--get until run out nodes--\n");
  printf("%d should equal (2)\n", get(n));
  printf("%d should equal (3)\n", get(n));
  printf("%d should equal (5)\n", get(n));
  printf("%d should equal (7)\n", get(n));
  printf("%d should equal (-1)\n\n", get(n));
  printf("-display\n");
  display(n);
  printf("should equal ()\n");

  printf("--put empty queue 2, 4--\n");
  printf("-put 2\n");
  put(n, 2);
  printf("-put 4\n");
  put(n, 4);
  printf("-display\n");
  display(n);
  printf("should equal (\n");
  printf("2\n");
  printf("4\n)\n");
}
