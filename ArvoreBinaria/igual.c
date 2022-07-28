#include "TAB.h"

int igual(TAB *a, TAB *b) {
    if(!a && !b)
        return 1;
    if(!a || !b)
        return 0;
    if(a->info == b->info)
        return igual(a->esq, b->esq) && igual(a->dir, b->dir);
    return 0;
}
