
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
    contador_comparacoes ++;
    return (Altura(a->esq) - Altura(a->dir));//retorna o faotor de balanceamento da arvore
}
int BalanceamentoABP(pNodoA *a)//verifica se a arvore esta vazia
{
    int x = 0, x1 = 0, x2 = 0;
    if (a == NULL)
        return 0;
    else
    {
        x1 = Altura(a->dir);
        x2 = Altura(a->esq);
        x = x1 - x2;
        return x + BalanceamentoABP(a->dir) + BalanceamentoABP(a->esq) + 0;//verifica se a arvore esta vazia
    }

}

int Altura (pNodoA *a){
    int Alt_Esq, Alt_Dir;
    contador_comparacoes ++;
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







