#ifndef pilhas_h
#define pilhas_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX 100

typedef char* tp_itemp;


typedef struct {
    int topo;
    tp_itemp item[MAX];
} tp_pilha;

void inicializaPilha(tp_pilha *p) {
    p->topo = -1;
}


int pilhaVazia(tp_pilha *p) {
    return p->topo == -1;
}


int pilhaCheia(tp_pilha *p) {
    return p->topo == MAX - 1;
}

int push(tp_pilha *p, tp_itemp e) {
    if (pilhaCheia(p)) return 0;
    p->topo++;
    p->item[p->topo] = strdup(e);
    return 1;
}


int pop(tp_pilha *p, tp_itemp *e) {
    if (pilhaVazia(p)) return 0;
    *e = p->item[p->topo];
    p->topo--;
    return 1;
}



int top(tp_pilha *p, tp_itemp *e) {
    if (!pilhaVazia(p)) {
        *e = p->item[p->topo];
        printf("Topo: %s\n", *e);
        return 1;
    }
    return 0;
}



void imprimePilha(tp_pilha p) {
    tp_itemp e;
    printf("\nConteúdo da Pilha 1:\n");
    while (!pilhaVazia(&p)) {
        pop(&p, &e);
        printf("%s ", e);
        free(e);
    }
    printf("\n");
}



int limpaPilha(tp_pilha *p, tp_itemp *e) {
    while (!pilhaVazia(p)) {
        pop(p, e);
    }
    return 1;
}

#endif
