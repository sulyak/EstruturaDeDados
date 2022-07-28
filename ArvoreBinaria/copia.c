#include <stdio.h>
#include "TAB.h"

TAB *copia(TAB *a) {
    if(!a)
        return a;
    return TAB_cria(a->info, copia(a->esq), copia(a->dir));
}
