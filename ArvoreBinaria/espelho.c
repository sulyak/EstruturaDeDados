#include "TAB.h"

TAB *espelho(TAB *a) {
    if(!a)
        return a;
    return TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
}

