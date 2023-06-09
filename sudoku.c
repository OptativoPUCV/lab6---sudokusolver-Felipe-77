#include <stdio.h>
#include <stdlib.h>
#include "list.h"
  
  
typedef struct{
  int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(!fscanf (file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      printf("%d ", n->sudo[i][j]);
      printf("\n");
    }
    printf("\n");
  }
}

int validateRange(Node * n){
  int i, j;

  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (n->sudo[i][j] < 0 || n->sudo[i][j] > 9)
        return 0;
    }
  }
  return 1;
}

void reciclarArreglo(int * a){
  for (int i = 0; i < 10; i++)
    a[i] = 0;
}

int is_valid(Node* n){
  if (validateRange(n) == 0) return 0;

  int *nums = calloc(10, sizeof(int));
  if (nums == NULL) exit(EXIT_FAILURE);

  int i, j, k, p;
  //Recorrer filas
  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (n->sudo[i][j] == 0) continue;
      if (nums[n->sudo[i][j]] == 0)
        nums[n->sudo[i][j]] = 1;
      else
        return 0;
    }
    reciclarArreglo(nums);
  }

  //Recorrer columnas
  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (n->sudo[j][i] == 0) continue;
      if (nums[n->sudo[j][i]] == 0)
        nums[n->sudo[j][i]] = 1;
      else
        return 0;
    }
    reciclarArreglo(nums);
  }

  for (k = 0; k < 9; k++){
    for(p=0;p<9;p++){
    int i=3*(k/3) + (p/3) ;
    int j=3*(k%3) + (p%3) ;
    if (n->sudo[j][i] == 0) continue;
      if (nums[n->sudo[j][i]] == 0)
        nums[n->sudo[j][i]] = 1;
      else
        return 0;
    }
    reciclarArreglo(nums);
  }

  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i, j, k;
  if (n == NULL) return NULL;

  for (i = 0; i < 9; i++){
    for (j = 0; j < 9; j++){
      if (n->sudo[i][j] == 0){
        for (k = 1; k < 10; k++){
          Node * new = copy(n);
          new->sudo[i][j] = k;
          if (is_valid(new) == 1)
            pushBack(list, new);
        }
        return list;
      }
    }
  }  
  return list;
}


int is_final(Node* n){

  int i, j, max = 8;
  for (i = 0; i < 5; i++){
    for (j = 0; j < 5; j++){
      if (n->sudo[i][j] == 0 || n->sudo[max - i][max - j] == 0)  return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){

  Stack * s = createStack();
  push(s, initial);

  while (get_size(s) > 0){
    Node * n = (Node*) top(s);
    pop(s);
    
    if (is_final(n) == 1) return n;
    List * adj = get_adj_nodes(n);
    Node * adjNode = first(adj);
    while (adjNode){
      push(s, adjNode);
      adjNode = next(adj);
    }
    (*cont)++;
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/