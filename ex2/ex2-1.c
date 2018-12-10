#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
  int val;
  struct _node *prev;
  struct _node *next;
}node;

int put (node *tail, int val){
  node *new;

  if(tail -> prev != NULL){
    put(tail -> prev, val);
  } else {
    new = (node *)malloc(sizeof(node));
    if(new == NULL) return -1;
    new -> val = val;
    new -> prev = NULL;
    new -> next = tail;
    tail -> prev = new;
  }
  return 0;
}

int get (node *head){
  int v = -1;

  if(head -> prev != NULL){
    v = head -> val;
    head -> val = head -> prev -> val;
    if(head -> prev -> prev != NULL){
      head -> prev = head -> prev -> prev;
      head -> prev -> prev -> next = head;
    }
    free(head -> prev);
  }
  return v;
}

int delete(node *head, int val){
  int v;

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
  } else {
    -1;
  }
}

void display(node *head){
  if(head != NULL) {
    printf("%d\n", head -> val);
    display(head -> prev);
  }
}

int main(int argc, char **argv){
  int i;
  node *n;

  n = (node *)malloc(sizeof(node));
  n -> val = 0;
  n -> prev = NULL;
  n -> next = NULL;
  printf("start tests\n");
  display(n);

  printf("\n--put test--\n");
  for(i = 1; i < 8; i++){
    if(put(n, i)){
      printf("failed putting %d\n", i);
    } else {
      printf("-put %d\n", i);
    }
  }
  display(n);
  printf("should equal (\n");
  for(i = 0; i < 8; i++) printf("%d\n", i);
  printf(")\n");

  printf("\n--get test--\n");
  printf("-get\n");
  printf("%d should equal (0)\n\n", get(n));
  display(n);
  printf("should equal (\n");
  for(i = 1; i < 8; i++) printf("%d\n", i);
  printf(")\n");
  printf("-get\n");
  printf("%d should equal (1)\n\n", get(n));
  display(n);
  printf("should equal (\n");
  for(i = 2; i < 8; i++) printf("%d\n", i);
  printf(")\n");

  printf("\n--delete test--\n");
  printf("- delete 4\n");
  delete(n, 4);
  display(n);
  printf("should equal (\n");
  printf("2\n");
  printf("3\n");
  printf("5\n");
  printf("6\n");
  printf("7\n)\n");
  printf("- delete 6\n");
  delete(n, 6);
  display(n);
  printf("should equal (\n");
  printf("2\n");
  printf("3\n");
  printf("5\n");
  printf("7\n)\n");

  printf("\n--get untill run out nodes\n");
  printf("%d should equal (2)\n", get(n));
  printf("%d should equal (3)\n", get(n));
//  printf("%d should equal (5)\n", get(n));
  printf("%d should equal (7)\n\n", get(n));
  display(n);
  printf("shoud equal ()\n");
}
