#include "TAB.h"

int ni(TAB *a) {
    if(!a)
        return 0;
    if(a->esq || a->dir)
        return 1 + ni(a->esq) + ni(a->dir);
    return 0;
}
