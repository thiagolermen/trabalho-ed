/* Headers */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX_PALAVRA 50
#define MAX_LINHA 2000

int contador_comparacoes, num_nodos, contador_comparacoes_ABP, comparacoes_totais;

// Estruturas AVL
typedef struct Informacao_Arvore{
    char palavra[MAX_PALAVRA];
    int quantidade;
}TipoInfo;

typedef struct TNodoA{
    TipoInfo info;
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
}pNodoA;

// Estrutura lista
typedef struct s_PtNo{
    TipoInfo info;
    struct s_PtNo* prox;
}TipoPtNo;

// Funcoes para AVL
pNodoA* cria_arvore(void);                // funcao que cria arvore
int BalanceamentoABP(pNodoA *a);
int fatorBalanceamento(pNodoA* a);
int percorrePreFixadoEsquerda(pNodoA *a);
int Altura (pNodoA *a);                   // funcao que ve altura
int ContaAVL(pNodoA *a);                  // funcao que conta numero de nodos
void centralEsquerda(pNodoA *a);
int consultaAVL(pNodoA *a, char palavra[]);
pNodoA* InsereABP(pNodoA* b, TipoInfo x);


// Funcoes para Lista
void Contador(pNodoA* a, TipoPtNo* ptLista, int k1, int k2);
TipoPtNo* InsereLista(TipoPtNo* ptLista, TipoInfo x);
void ImprimeLista(TipoPtNo* ptLista);













