
/* Implementacao */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#define MAX_PALAVRA 50



pNodoA* cria_arvore(void)
{
return NULL;
}


int fatorBalanceamento(pNodoA* a){

    return (Altura(a->esq) - Altura(a->dir));//retorna o faotor de balanceamento da arvore
}
int BalanceamentoABP(pNodoA *a)
{
    int x = 0, x1 = 0, x2 = 0;
    if (a == NULL)//verifica se a arvore esta vazia
        return 0;
    else
    {
        x1 = Altura(a->dir);
        x2 = Altura(a->esq);
        x = x1 - x2;
        return x + BalanceamentoABP(a->dir) + BalanceamentoABP(a->esq) + 0;//retorna o fator de balanceamento
    }

}

int Altura (pNodoA *a){
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else{
     Alt_Esq = Altura (a->esq);//calcula a altura da sub-arvore esquerda
     Alt_Dir = Altura (a->dir);//calcula a altura da subarvore esquerda
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
 }
}

int ContaAVL(pNodoA *a){
    if(a != NULL)
        return ContaAVL(a->esq) + ContaAVL(a->dir) + 1;//conta  aquantidade de novod da avl
    else
        return 0;
}

int percorrePreFixadoEsquerda(pNodoA *a){
    int n = 0;
    if (a != NULL){
        n++;//conta  quantidade de nodos da AVL
        percorrePreFixadoEsquerda(a->esq);
        percorrePreFixadoEsquerda(a->dir);
    }
    return n;
}

void centralEsquerda(pNodoA *a){//percorre a arvore com o caminhamento central esquerda para printar em ordem alfabetica
    int x;
    if (a != NULL){
        centralEsquerda(a->esq);
        if(a->info.quantidade > 1){//procura pela frequencia
            x = a->info.quantidade;
            while(x>0){
                puts(a->info.palavra);
                x--;
            }
        }
        else
            puts(a->info.palavra);
        centralEsquerda(a->dir);
    }
}



int consultaAVL(pNodoA *a, char palavra[]){//consulta o nodo cuja palavra foi passada como parametro
    while (a!=NULL){
        if (strcmp(a->info.palavra, palavra) == 0){
            contador_comparacoes ++;
            return a->info.quantidade; //achou então retorna a frequerncia do nodo procuradp
        }else{
            if (strcmp(palavra, a->info.palavra) < 0){//verifica se palavra vem antes no alfabeto
                    contador_comparacoes ++;
                    a = a->esq;
            }else{//se a palavra vir depoir no alfabeto
                contador_comparacoes ++;
                a = a->dir;
            }
        }
    }
    return 0; //se não achou
}

pNodoA* rotacao_esquerda(pNodoA *p){//realiza rotacao
    pNodoA *z;
    contador_rotacao_simples_esquerda ++;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

pNodoA* rotacao_direita(pNodoA* p){//realiza rotacao
    pNodoA *u;
    contador_rotacao_simples_direita ++;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

pNodoA* rotacao_dupla_esquerda (pNodoA *p){//realiza rotacao
    pNodoA *z, *y;
    contador_rotacao_dupla_esquerda ++;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1) p->FB = 1;
        else p->FB = 0;
    if (y->FB == 1) z->FB = -1;
        else z->FB = 0;
    p = y;
    return p;
}

pNodoA* rotacao_dupla_direita (pNodoA* p){//realiza rotacao
    pNodoA *u, *v;
    contador_rotacao_dupla_direita ++;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1) p->FB = -1;
        else p->FB = 0;
    if (v->FB == -1) u->FB = 1;
        else u->FB = 0;
    p = v;
    return p;
}



pNodoA* InsereAVL (pNodoA *a, TipoInfo x, int *ok){
/* Insere nodo em uma arvore AVL, onde A representa a raiz da �rvore,
x, a chave a ser inserida e h a altura da �rvore*/
    if (a == NULL){
        contador_comparacoes ++;
        a = (pNodoA*) malloc(sizeof(pNodoA));
        strcpy(a->info.palavra, x.palavra);
        a->info.quantidade = 1;                                  // Zerando quantidade, pois alocando palavra pela primeira vez
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }else{
        if (strcmp(x.palavra, a->info.palavra) == 0){   // se a palavra estiver mais para o final do alfabeto entao insere na esquerda
            contador_comparacoes ++;
            a->info.quantidade ++;
            *ok = 0;
            return a;
        }else{
            if(strcmp(x.palavra, a->info.palavra) < 0){       // se a palavra for igual a outro, simplesmente incrementa a frequencia
                contador_comparacoes ++;
                a->esq = InsereAVL(a->esq,x,ok);
                if (*ok){//veridica se é necessario rotacao
                    switch (a->FB) {
                        case -1:
                            contador_comparacoes ++;
                            a->FB = 0;
                            *ok = 0;
                            break;
                        case 0:
                            contador_comparacoes ++;
                            a->FB = 1;
                            break;
                        case 1:
                            contador_comparacoes ++;
                            a=Caso1(a,ok);
                            break;
                    }
                }
            }else{                                              // se a palavra esta mais proxima do inicio do alfabeto, entao insere na direita
                contador_comparacoes ++;//incrementa o contador de comparacoes
                a->dir = InsereAVL(a->dir,x,ok);
                if (*ok) {
                    switch (a->FB) {
                        case 1:
                            contador_comparacoes ++;
                             a->FB = 0;
                            *ok = 0;
                            break;
                        case 0:
                            contador_comparacoes ++;
                            a->FB = -1;
                            break;
                        case -1:
                            contador_comparacoes ++;
                            a = Caso2(a,ok);
                            break;
                    }
                }
            }
        }
    }
    return a;
}


pNodoA* Caso1 (pNodoA *a , int *ok){//verifica os casos de rotacao
    pNodoA *z;
    z = a->esq;
    if (z->FB == 1)
        a = rotacao_direita(a);
    else
        a = rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}
pNodoA* Caso2 (pNodoA *a , int *ok){//verifica os casos de rotacao
    pNodoA *z;
    z = a->dir;
    if (z->FB == -1)
        a = rotacao_esquerda(a);
    else
        a = rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}










