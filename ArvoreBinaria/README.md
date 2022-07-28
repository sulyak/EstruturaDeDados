Segundo a Wikipedia:

Uma **árvore binária** é uma estrutura de dados caracterizada por:

-   Ou não tem elemento algum (árvore vazia).
-   Ou tem um elemento distinto, denominado raiz, com dois ponteiros para duas estruturas diferentes, denominadas subárvore esquerda e subárvore direita.

Perceba que a definição é recursiva e, devido a isso, muitas operações sobre árvores binárias utilizam recursão.


Podendo ser representada em C pela seguinte estrutura:
```c
struct arvbin {
    int info;
    struct arvbin *esq, *dir;
};
typedef struct arvbin TAB;
```

Table of contents:
* Criando um nó
* Copiando uma árvore
* Espelhando uma árvore　
* Encontrando menor/maior elemento de uma árvore　
* Comparando duas árvores
* Retirando os nos pares de uma árvore
* Contando os nos
* Contando os nos internos
* Contando os nos folhas
* Transformando em um vetor
* Transformando em uma Lista Simplismente Encadeada
* Transformando em uma Árvore Binária de Busca
#### Criando um nó
```c
TAB *TAB_cria(int info, TAB *esq, TAB *dir) {
    TAB *no = (TAB *) malloc(sizeof(TAB));
    no->info = info;
    no->esq = esq;
    no->dir = dir;
    return no;
}
```
#### Copiando uma árvore
1. Copiar a informação da raiz
2. Copiar as sub-arvores da esquerda e direita
```c
TAB *copia(TAB *a) {
    if(!a)
        return NULL;
    return TAB_cria(a->info, copia(a->esq), copia(a->dir));
}
```
```c
// identico
TAB *copia(TAB *a) {
    if(!a)
        return NULL;
    
    // aloca uma nova arvore
    TAB *novo = (TAB *) malloc(sizeof(TAB));

    // copia a informação
    novo->info = a->info;

    // copia as subarvores
    novo->esq = copia(a->esq);
    novo->dir = copia(a->dir);

    return novo;
}
```
#### Espelhando uma árvore
Semanticamente, podemos pensar num espelhamento da seguinte maneira:
1. Copiar a informação da raiz
2. Minha sub-árvore da esquerda vai ser o espelho da sub-árvore da direita
3. Minha sub-árvore da direita vai ser o espelho da sub-árvore da esquerda
```c
TAB *espelho(TAB *a) {
    if(!a)
        return NULL;
    return TAB_cria(a->info, espelho(a->dir), espelho(a->esq));
}
```
#### Encontrando menor/maior elemento de uma árvore
1. Encontrar o maior elemento das sub-árvores
2. Comparar esses dois elementos com a raiz e retornar o maior dos 3.
```c
TAB *maior(TAB *a) {
    if(!a)
        return a;

    TAB *result = a;

    // maior elem da sub-arv da esquerda
    TAB *e = maior(a->esq);

    // maior elem da sub-arv da direita
    TAB *d = maior(a->dir);

    // comparar o elemento da raiz com os maiores das sub-arvores
    if(e && e->info > result->info)
        result = e;    
    if(d && d->info > result->info)
        result = d;
    return result;
}
```

#### Comparando duas árvores
1. Comparar a informacao das duas raizes.
2. Se as raizes foram iguais, as sub-árvores tambem precisam ser iguais.

Obs: Duas arvores vazias (NULL) sao iguais.
```c
int igual(TAB *a, TAB *b) {
    // duas arvores vazias
    if(!a && !b)
        return 1;

    // uma das arvores vazia, a outra nao
    if(!a || !b)
        return 0;
    
    // se as raizes forem iguais, as sub arvores tambem preciam ser iguas
    if(a->info == b->info)
        return igual(a->esq, b->esq) && igual(a->dir, b->dir);
    return 0;
}
```

#### Retirando os nos pares de uma árvore

1. Retirar os elementos pares das sub-arvores
2. Se o elemento da raiz for par:
a. Se esse elemento for folha, libera e retorna NULL;
b. Se nao for folha, troca o elemento da raiz com um de seus filhos (que nao vao ser pares devido ao passo 1) e tentar retirar os pares novamente.
```c
TAB *retira_pares(TAB *a){
    if(!a)
        return NULL;
        
    // retiro os pares das minhas duas sub-arvores
    a->esq = retira_pares(a->esq);
    a->dir = retira_pares(a->dir);

    // se a raiz for par...
    if(a->info % 2 == 0) {

        // se for uma folha
        if(!a->esq && !a->dir) {
            free(a);
            return NULL;
        }

        // trocar a raiz com um elem de uma sub-arvore
        // como ja foram tirado os pares das sub-arvores, garanto que esse elemento nao vai ser par
        TAB *aux = a->esq;
        if(!aux)
            aux = a->dir;

        // trocando
        int tmp = aux->info;
        aux->info = a->info;
        a->info = tmp;
        
        // depois da troca, tentar retirar de novo
        a = retira_pares(a);
    }
    return a;
}
```

#### Contando os nos 
O numero de nos de uma arvore pode ser pensado como:
Numero de nos da raiz (1) + numero de nos das sub-arvores.
```c
int nn(TAB *a) {
    if(!a)
        return 0;
    return 1 + nn(a->esq) + nn(a->dir);
```
#### Contando os nos internos
Se a raiz for um no interno, o numero de nos internos da arvore vai ser 1 (raiz) + nos internos das sub-arvores.
Caso a raiz for uma folha, nao tem nenhum no interno.
```c
int ni(TAB *a) {
    if(!a)
        return 0;
        
    // se o no for folha
    if(!a->esq && !a->dir)
        return 0;
    
    // a raiz + os nos internos das sub-arvores
    return 1 + ni(a->esq) + ni(a->dir);
```

#### Contando os nos folhas
Semelhante a contagem de nos internos, porem com a logica invertida.
```c
int ni(TAB *a) {
    if(!a)
        return 0;
        
    // se o no for folha
    if(!a->esq && !a->dir)
        return 1;
    
    // os nos folhas das sub-arvores
    return nf(a->esq) + nf(a->dir);
```
#### Transformando em um vetor
1. Descobrir o tamanho do vetor (AKA o numero de nos da arvore)
2. Para cara no, preciso guardar um espaco para a sub-arvore da esquerda, inserir a informacao do no atual e depois inserir a sub-arvore da esquerda nas posicoes que sobraram.
     a. guardar espaco pra sub-arvore da esquerda: contar quantos nos existem na subarvore da esquerda e colocar a informacao atual na posicao seguinte
     b. fazer o mesmo processo para a sub-arvore da esquerda e direita. (Obs: o vetor referencia da sub-arvore da direita vai ser o sub-vetor que comeca a partir da posicao atual)
```c
int *ab2vet(TAB *a) {
    if(!a)
        return NULL;
    int n = nn(a);
    int *v = (int *) malloc(sizoef(int) * n);
    tovet(a, v);
    return v;
}

void tovet(TAB *a, int *vet) {
    if(!a)
        return;
    int pos = nn(a->esq);
    v[pos] = a->info;
    tovet(a->esq, v);
    tovet(a->dir, v + pos + 1);
}
```

#### Transformando em uma Lista Simplismente Encadeada
para cada elemento da arvore, inserir na lista. bem simples, so precisa tomar cuidado para passar a lista por parametro e retornar a lista atualizada.
```c
TLSE *ab2lse(TAB *a) {
    if(!a)
        return NULL;
    return tolse(a, NULL);
}

TLSE *tolse(TAB *a, TLSE *l) {
    if(!a)
        return l;
    l = tolse(a->esq);
    l = TLSE_insere(l, a->info);
    l = tolse(a->dir);
    return l;
}
```
#### Transformando em uma Árvore Binária de Busca
spooky stuff
```c
TABB *ab2abb(TAB *a) {
    if(!a)
        return NULL;
    int *v = ab2vet(a);
    
    // alguma funcao qualquer para ordenar v
    sort(v);
    
    return vet2abb(v, nn(a));
}

TABB *vet2abb(int *v, int n) {
    if(n == 0)
        return NULL;
    return TAB_cria(v[n/2], vet2abb(v, n/2), vet2abb(v + n/2 + 1, n - n/2 - 1));
}
```

