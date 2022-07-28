#include "TAB.h"

TAB *retira_pares(TAB *a){
    if(!a)
        return NULL;
    a->esq = retira_pares(a->esq);
    a->dir = retira_pares(a->dir);
    if(a->info % 2 == 0) {
        if(!a->esq && !a->dir) {
            free(a);
            return NULL;
        }
        TAB *aux = a->esq;
        if(!aux) aux = a->dir;
        int tmp = aux->info;
        aux->info = a->info;
        a->info = tmp;
        a = retira_pares(a);
    }
    return a;
}
