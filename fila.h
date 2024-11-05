#ifndef FILAS_H
#define FILAS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 100
#define MAXt 5

typedef char* tp_item;


typedef struct {
    tp_item item[MAX];
    int ini, fim;
} tp_fila;



void inicializaFila(tp_fila *p) {
    p->ini = p->fim = 0;
}

int filaVazia(tp_fila *p){
  if(p->ini==p->fim) return 1;
  return 0;
}

int pos(int pos) {
    if (pos == MAXt - 1) return 0;
    return pos + 1;
}

int filaCheia(tp_fila *p){
  if(pos(p->fim)==p->ini) return 1;
  return 0;
}

int inFila(tp_fila *p, tp_item e) {
    if (filaCheia(p)) return 0;
    p->item[p->fim] = strdup(e);
    p->fim = pos(p->fim);
    return 1;
}

int deFila(tp_fila *p, tp_item *e) {
    if (filaVazia(p)) return 0;
    *e = strdup(p->item[p->ini]);
    p->ini = pos(p->ini);
    return 1;
}

void imprimeFila(tp_fila p) {
    tp_item e;
    while (!filaVazia(&p)) {
        if (deFila(&p, &e)) {
            printf("%s ", e);
        }
    }
    printf("\n");
}

int tamanhoFila(tp_fila p) {
    int cont = 0;
    tp_item e;
    while (!filaVazia(&p)) {
        if (deFila(&p, &e)) {
            cont++;
        }
    }
    return cont;
}

int impFim(tp_fila *p, tp_item *e) {
  if (filaVazia(p)) return 0;
  int posFim;
  if (p->fim == 0) {
      posFim = MAXt - 1; 
  } else {
      posFim = p->fim - 1;
  }
  *e = strdup(p->item[posFim]);
  printf(" %s", *e);
  return 1;
}




#endif
