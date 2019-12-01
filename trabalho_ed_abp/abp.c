
/* Implementacao */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abp.h"
#define MAX_PALAVRA 50



pNodoA* cria_arvore(void)
{
return NULL;
}


int fatorBalanceamento(pNodoA* a){

    return (Altura(a->esq) - Altura(a->dir));
}
int BalanceamentoABP(pNodoA *a)
{
    int x = 0, x1 = 0, x2 = 0;
    if (a == NULL)
        return 0;
    else
    {
        x1 = Altura(a->dir);
        x2 = Altura(a->esq);
        x = x1 - x2;
        return x + BalanceamentoABP(a->dir) + BalanceamentoABP(a->esq) + 0;
    }

}

int Altura (pNodoA *a){
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else{
     Alt_Esq = Altura (a->esq);
     Alt_Dir = Altura (a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
 }
}

int ContaAVL(pNodoA *a){
    if(a != NULL)
        return ContaAVL(a->esq) + ContaAVL(a->dir) + 1;
    else
        return 0;
}

int percorrePreFixadoEsquerda(pNodoA *a){
    int n = 0;
    if (a != NULL){
        n++;
        percorrePreFixadoEsquerda(a->esq);
        percorrePreFixadoEsquerda(a->dir);
    }
    return n;
}

void centralEsquerda(pNodoA *a){
    int x;
    if (a != NULL){
        centralEsquerda(a->esq);
        if(a->info.quantidade > 1){
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



int consultaAVL(pNodoA *a, char palavra[]){
    while (a!=NULL){
        if (strcmp(a->info.palavra, palavra) == 0)
            return a->info.quantidade; //achou então retorna o ponteiro para o nodo
        else
            if (strcmp(palavra, a->info.palavra) < 0)
                a = a->esq;
            else
                a = a->dir;
    }
    return 0; //se não achou
}




//Funcoes para ABP

pNodoA* InsereABP(pNodoA* b, TipoInfo x){
    if (b == NULL){
        contador_comparacoes_ABP ++;
        b = (pNodoA* ) malloc(sizeof(pNodoA));
        strcpy(b->info.palavra, x.palavra);
        b->info.quantidade = 1;                                  // Um na quantidade , pois alocando palavra pela primeira vez
        b->esq = NULL;
        b->dir = NULL;
    }else{
        if (strcmp(x.palavra, b->info.palavra) == 0){   // se a palavra for igual a outro, simplesmente incrementa a frequencia
            b->info.quantidade ++;
            contador_comparacoes_ABP ++;
            return b;
        }else{
            if(strcmp(x.palavra, b->info.palavra) < 0){     // se a palavra estiver mais para o final do alfabeto entao insere na esquerda
                contador_comparacoes_ABP ++;
                b->esq = InsereABP(b->esq,x);
                return b;
            }else{                                              // se a palavra esta mais proxima do inicio do alfabeto, entao insere na direita
                contador_comparacoes_ABP ++;
                b->dir = InsereABP(b->dir,x);
            }
        }
    }
}







