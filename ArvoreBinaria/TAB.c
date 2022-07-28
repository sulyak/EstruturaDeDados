#include "TAB.h"

TAB *TAB_inicializa(void) {
    return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir) {
    TAB *novo = (TAB *) malloc(sizeof(TAB));
    novo->info = raiz;
    novo->esq = esq;
    novo->dir = dir;
    return novo;
}

TAB *TAB_busca(TAB *a, int elem) {
    if(!a || a->info == elem)
        return a;
    TAB *resp = TAB_busca(a->esq, elem);
    if(resp)
        return resp;
    return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a) {
    if(a) {
        printf("%d ", a->info);
        TAB_imp_pre(a->esq);
        TAB_imp_pre(a->dir);
    }
}

void TAB_imp_pos(TAB *a) {
    if(a) {
        TAB_imp_pos(a->esq);
        TAB_imp_pos(a->dir);
        printf("%d ", a->info);
    }
}

void TAB_imp_sim(TAB *a) {
    if(a) {
        TAB_imp_sim(a->esq);
        printf("%d ", a->info);
        TAB_imp_sim(a->dir);
    }
}

void TAB_libera(TAB *a) {
    if(a) {
        TAB_libera(a->esq);
        TAB_libera(a->dir);
        free(a);
    }
}

int TAB_altura(TAB *a) {
    if(!a)
        return -1;
    int e = TAB_altura(a->esq);
    int d = TAB_altura(a->dir);
    return e > d ? e : d;
}

