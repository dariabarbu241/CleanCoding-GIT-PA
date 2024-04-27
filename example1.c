/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Node 
{
  int data;
  struct Node *next;
}
NODE;

typedef struct Gph 
{
  int v;
  int *vis;
  NODE **alst;
}
GPH;

typedef struct Stk 
{
  int t;
  int scap;
  int *arr;
}
STK;

NODE *create_node(int v) 
{
  NODE *nn = malloc(sizeof(NODE));
  nn -> data = v;
  nn -> next = NULL;
  return nn;
}

void add_edge(GPH *g, int src, int dest) 
{
  NODE *nn = create_node(dest);
  nn -> next = g -> alst[src];
  g -> alst[src] = nn;
  nn = create_node(src);
  nn -> next = g -> alst[dest];
  g -> alst[dest] = nn;
}

GPH * create_g(int v) 
{
  GPH *g = malloc(sizeof(GPH));
  g -> v = v;
  g -> alst = malloc(v * sizeof(NODE *));
  g -> vis = malloc(v * sizeof(int));

  for (int i = 0; i < v; i++) 
  {
    g -> alst[i] = NULL;
    g -> vis[i] = 0;
  }
  return g;
}

STK *create_s(int scap) 
{
  STK *s = malloc(sizeof(STK));
  s -> arr = malloc(scap * sizeof(int));
  s -> t = -1;
  s -> scap = scap;
  return s;
}

void push(int pshd, STK *s) {
  s -> t = s -> t + 1;
  s -> arr = realloc(s -> arr, (s -> t + 1) * sizeof(int));
  s -> arr[s -> t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
  NODE *adj_list = g -> alst[v_nr];
  NODE *aux = adj_list;
  g -> vis[v_nr] = 1;

  push(v_nr, s);

  while (aux != NULL) 
  {
    int con_ver = aux -> data;

    if (g -> vis[con_ver] == 0)
      DFS(g, s, con_ver);
    aux = aux -> next;
  }
}

void insert_edges(GPH * g, int edg_nr, int nrv) 
{
  int src, dest;
  printf("adauga %d muchii (de la 0 la %d)\n", edg_nr, nrv - 1);
  for (int i = 0; i < edg_nr; i++) 
  {
    scanf("%d%d", & src, & dest);
    add_edge(g, src, dest);
  }
}

void wipe(GPH * g, int nrv) 
{
  for (int i = 0; i < nrv; i++) 
  {
    g -> vis[i] = 0;
  }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2, int v1, int v2) 
{
  int ok = 0;
  wipe(g, nrv);
  DFS(g, s1, v1);
  wipe(g, nrv);
  DFS(g, s2, v2);
  for (int k = 0; k < nrv; k++) 
  {
    for (int l = 0; l < nrv; l++) 
    {
      if ((s1 -> arr[k] == v2) && (s2 -> arr[l] == v1)) 
      {
        ok = 1;
        break;
      }
    }
  }

  printf("Existenta unui drum direct intre restaurantele %d si %d: \n", v1, v2);
  if (ok == 1)
    printf("DA\n");
  else printf("NU\n");

}

int main() 
{

  int nrv;
  int edg_nr;
  int src, dest;
  int i;
  int vortex_1;
  int vortex_2;
  int ans;

  printf("cate noduri are graful? ");
  scanf("%d", &nrv);

  printf("cate muchii are graful? ");
  scanf("%d", &edg_nr);
  printf("intre ce noduri se verifica existenta drumului? (de la 0 la %d) ", nrv - 1);
  scanf("%d%d", &vortex_1, &vortex_2);
  GPH *g = create_g(nrv);

  STK *s1 = create_s(2 * nrv);
  STK *s2 = create_s(2 * nrv);

  insert_edges(g, edg_nr, nrv);

  canbe(g, nrv, s1, s2, vortex_1, vortex_2);
  for (int i = 0; i < nrv; i++) 
  {
    NODE *current = g -> alst[i];
    while (current != NULL) 
    {
      NODE *next = current -> next;
      free(current);
      current = next;
    }
  }

  free(g -> alst);
  free(g -> vis);
  free(g);
  free(s1 -> arr);
  free(s1);
  free(s2 -> arr);
  free(s2);

}