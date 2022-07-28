#include "TAB.h"

TAB *maior(TAB *a) {
    if(!a)
        return a;

    TAB *result = a;
    TAB *e = maior(a->esq);
    TAB *d = maior(a->dir);

    if(e && e->info > result->info)
        result = e;
    if(d && d->info > result->info)
        result = d;
    return result;
}
