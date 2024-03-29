#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include "avl.h"


/* PROTOTIPOS */
void printTituloArquivo(FILE *saida, char argv[]);//printa o cabecalho do arquivo
void printDadosArvore(FILE *saida,  char argv[], pNodoA *a, double time);//printa os dados da arvore, como rotacoes, nodos, altura, fator de balanceamento, etc
void printArquivo(FILE *saida, char dado[], char palavra[], char argv[]);//printa no arquivo de saida
void printOcorrenciasArquivo(FILE *saida, int frequencia, char argv[]);//printa a qunatidade de ocorrencias de determinada palavra
void imprimeRange(FILE *saida, pNodoA *a, int rangeMin, int rangeMax);//imprime as palavras as quais estao no range k1 k2
void printRange(FILE *saida, char dado[], int rangeMin, int rangeMax, char argv[]);//print range no arquivo
void palavraRange(FILE *saida, pNodoA *a, int chave);//busca a palavra que deve-se pesquisar o range
void printPalavraRange(FILE *saida, char palavra[], int frequencia);//printa a palavra que esta dentre k1 e k2
void printTempo(FILE *saida, double time);//printa no artquivo o tempo decorrido


/* Exemplo de uso dos argumentos para main
O programa le um arquivo texto como entrada e gera um arquivo como saida com o conteudo do arquivo de entrada convertido para letras maiusculas
Para chamar, digite "exemplo entrada.txt entrada2.txt saida.txt" */

int main(int argc, char *argv[]){//argc conta o numero de parametros e argv armazena as strings correspondentes aos paramentros digitados

    setlocale(LC_ALL,"portuguese"); //para imprimir corretamente na tela os caracteres acentuados

    pNodoA *avl = NULL;//inicializa a arvore
    TipoInfo word;//estrutura para guardar a palavra lida do arquivo de entrada
    clock_t t;//para funcao de tempo
    clock_t t2;//para funcao de tempo
    double time_taken;//tempo decorrido total (final - inicial)
    int ok;//para realizar rotacoes
    int rangeMin, rangeMax;//k1 e k2
    int frequencia;//variavel auxiliar para armazenar a frequencia de determinada palvra
    FILE *texto;//arquivo de texto de entrada
    FILE *operacoes;//arquivo de texto com as operacoes a serem realizadas
    FILE *saida;//arquivo de saida
    char *palavra, linha[MAX_LINHA]; // linhas a serem lidas do arquivo
    char *linhaOperacao, tipoDado[MAX_PALAVRA];//armazena a linha do arquivo de operacao
    char buscaPalavra[MAX_PALAVRA];//armazena a palavra que sera buscada na arvore
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};


    rangeMax = 0;//inicializa k1 e k2 com 0
    rangeMin = 0;

    if (argc != 4){//o numero de parametros esperado e 4: nome do programa (argv[0]), nome do arq texto de entrada (argv[1]), nome do arquivo de operacoes de entrada (argv[2]) e nome do arq de saida(argv[3])
        printf ("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_entrada> <arq_saida>\n");
        return 1;
    }else{
        texto = fopen (argv[1], "r"); // abre o arquivo para leitura -- argv[1] eh o primeiro parametro apos o nome do arquivo.
        if (texto == NULL){ //se nao conseguiu abrir o arquivo
            printf ("Erro ao abrir o arquivo %s",argv[1]);
            return 1;
        }else{ // arquivo de entrada OK
            operacoes = fopen (argv[2], "r"); // abre o arquivo para leitura -- argv[1] eh o primeiro parametro apos o nome do arquivo.

            if (operacoes == NULL){ //se nao conseguiu abrir o arquivo
                printf ("Erro ao abrir o arquivo %s",argv[2]);
                return 1;
            }else{ // arquivo de entrada OK
                saida = fopen (argv[3], "w"); // abre o arquivo para saida -- argv[2] eh o segundo par�metro ap�s o nome do arquivo.

                if (saida == NULL){
                    printf ("Erro ao abrir o arquivo %s",argv[3]);
                    return 1;
                }else{
                    //percorre todo o arquivo lendo linha por linha
                    t2 = clock();
                    while(fgets(linha, sizeof(linha), texto)){
                        palavra = strtok(linha, separador);
                        while(palavra != NULL){//pega as palavras com strtok
                            strcpy(word.palavra, strlwr(palavra));

                            avl = InsereAVL(avl, word, &ok);

                            palavra = strtok(NULL, separador);

                        }
                    }
                    t2 = clock() - t2;
                    time_taken = ((double)t2)/CLOCKS_PER_SEC * 1000; // in miliseconds
                }


                printTituloArquivo(saida, argv[3]);//printa cabecalho no arquivo
                printDadosArvore(saida, argv[3], avl, time_taken);//Printa no arquivo os dados da arvotre


                //percorre todo o arquivo de operacoes
                while(fgets(linha, sizeof(linha), operacoes) != NULL){
                    linhaOperacao = strtok(linha, separador);


                    if(strcmp(linhaOperacao, "F") == 0){//verifica se e um F para buscar a frequencia que vem logo apos
                        strcpy(tipoDado, linhaOperacao);

                        linhaOperacao = strtok(NULL, separador);

                        strcpy(buscaPalavra, strlwr(linhaOperacao));

                        printArquivo(saida, tipoDado, buscaPalavra, argv[3]);

                        frequencia = consultaAVL(avl, buscaPalavra);

                        printOcorrenciasArquivo(saida, frequencia, argv[3]);

                        //Chama a funcao para imprimir as frequencias dessas palavras
                    }else{
                        if(strcmp(linhaOperacao, "C") == 0){//verifica se e um C para pegar os dois valores numericos apos C que serao os k1 e k2
                            strcpy(tipoDado, linhaOperacao);
                            rangeMin = atoi(strtok(NULL, separador));
                            rangeMax = atoi(strtok(NULL, separador));
                            printRange(saida, tipoDado, rangeMin, rangeMax, argv[3]);
                            t = clock();
                            imprimeRange(saida, avl, rangeMin, rangeMax);
                            t = clock() - t;
                            time_taken = ((double)t)/CLOCKS_PER_SEC * 1000; // in miliseconds
                        }
                    }
                }
            }
        }
    }
    printTempo(saida, time_taken);
    printf("\nArquivo %s gerado com sucesso.\n",argv[3]);
    system("pause");

    fclose (texto); //fecha os arquivos
    fclose (operacoes);
    fclose (saida);

    return 0;
}

void printTempo(FILE *saida, double time){
    fprintf(saida, "Tempo: %f ms\n", time);
    fprintf(saida, "Comparacoes: %d\n", comparacoes_totais);
}
void imprimeRange(FILE *saida, pNodoA *a, int rangeMin, int rangeMax){//varre toda a arvore em busca do valor que sera i(solucao burra porem facil)
    int i;
    for(i = rangeMax;i >= rangeMin; i--){
        palavraRange(saida, a, i);
    }
}
void palavraRange(FILE *saida, pNodoA *a, int chave){
    char palavra[MAX_PALAVRA];
    int frequencia;
    comparacoes_totais++;
    if (a != NULL){
        palavraRange(saida, a->esq, chave);
        if(a->info.quantidade == chave){//verifica se encontroi na arvore a palavra chave
            strcpy(palavra, a->info.palavra);
            frequencia = a->info.quantidade;
            printPalavraRange(saida, palavra, frequencia);
        }
        palavraRange(saida, a->dir, chave);
    }
}
void printPalavraRange(FILE *saida, char palavra[], int frequencia){
    fprintf(saida, "%s %d\n\n", palavra, frequencia);
}
void printRange(FILE *saida, char dado[], int rangeMin, int rangeMax, char argv[]){
    fprintf(saida, "%s %d %d\n\n", dado, rangeMin, rangeMax);
}
void printArquivo(FILE *saida, char dado[], char palavra[], char argv[]){
    fprintf(saida, "%s %s\n", dado, palavra);
}
void printOcorrenciasArquivo(FILE *saida, int frequencia, char argv[]){
    fprintf(saida, "%d ocorrencias\n", frequencia);
    fprintf(saida, "******************************\n");
}
void printTituloArquivo(FILE *saida, char argv[]){
    fprintf(saida, "********   ESTATISTICAS DA GERACAO DA ARVORE AVL   ***********\n");
}
void printDadosArvore(FILE *saida, char argv[], pNodoA *avl, double tempo){
    if(avl != NULL){
        fprintf(saida, "Numero de nodos: %d\n", ContaAVL(avl));
        fprintf(saida, "Altura: %d\n", Altura(avl));
        fprintf(saida, "Fator de balanceamento: %d\n", fatorBalanceamento(avl));
        fprintf(saida, "Tempo: %f ms\n", tempo);
        fprintf(saida, "Rotacoes: %d\n", contador_rotacao_simples_esquerda + 2*contador_rotacao_dupla_esquerda + 2*contador_rotacao_dupla_direita + contador_rotacao_simples_direita);
        fprintf(saida, "Comparacoes: %d\n", contador_comparacoes);
        fprintf(saida, "**********************************************************************\n");
    }
}

