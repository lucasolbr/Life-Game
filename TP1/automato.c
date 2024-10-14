#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

// Função para criar uma matriz alocada dinamicamente
void alocarReticulado(AutomatoCelular** ret, int n) {
    *ret = (AutomatoCelular*)malloc(sizeof(AutomatoCelular));
    (*ret)->n = n;
    (*ret)->reticulado = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        (*ret)->reticulado[i] = (int*)malloc(n * sizeof(int));
}

// Função para liberar a matriz alocada dinamicamente
void desalocarReticulado(AutomatoCelular* ret) {
    for (int i = 0; i < ret->n; i++)
        free(ret->reticulado[i]);
    free(ret->reticulado);
    free(ret);
}

// Função para ler os dados do reticulado
AutomatoCelular* leituraReticulado() {
    AutomatoCelular* ret;
    int n, geracoes;
    scanf("%d %d", &n, &geracoes);
    alocarReticulado(&ret, n);
    ret->geracoes = geracoes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &ret->reticulado[i][j]);
        }
    }
    return ret;
}

// Função para evoluir o reticulado (recursiva)
int** evoluirReticulado(AutomatoCelular* ret) {
    if (ret->geracoes == 0)
        return ret->reticulado;

    int n = ret->n;
    int vizinhos;

    // Malha Auxiliar
    int** retTemp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        retTemp[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vizinhos = contaVizinho(ret, i, j);
            if (ret->reticulado[i][j] == 1) {
                if (vizinhos == 2 || vizinhos == 3)
                    retTemp[i][j] = 1;
                else
                    retTemp[i][j] = 0;
            } else {
                if (vizinhos == 3)
                    retTemp[i][j] = 1;
                else
                    retTemp[i][j] = 0;
            }
        }
    }

    // Transferindo conteúdo da matriz auxiliar para a matriz original
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ret->reticulado[i][j] = retTemp[i][j];
        }
    }

    // Liberando a matriz auxiliar
    for (int i = 0; i < n; i++)
        free(retTemp[i]);
    free(retTemp);

    ret->geracoes--;
    // Aplicando a recursividade
    return evoluirReticulado(ret);
}

// Função para imprimir o reticulado
void imprimeReticulado(AutomatoCelular* ret) {
    for (int i = 0; i < ret->n; i++) {
        for (int j = 0; j < ret->n; j++)
            printf("%d ", ret->reticulado[i][j]);
        printf("\n");
    }
}

// Função para contar vizinhos
int contaVizinho(AutomatoCelular* ret, int i, int j) {
    int cont = 0;
    int n = ret->n;

    // Verifica vizinho superior
    if (i > 0 && ret->reticulado[i-1][j] == 1)
        cont++;

    // Verifica vizinho inferior
    if (i < n-1 && ret->reticulado[i+1][j] == 1)
        cont++;

    // Verifica vizinho à esquerda
    if (j > 0 && ret->reticulado[i][j-1] == 1)
        cont++;

    // Verifica vizinho à direita
    if (j < n-1 && ret->reticulado[i][j+1] == 1)
        cont++;

    // Verifica vizinho superior esquerdo
    if (i > 0 && j > 0 && ret->reticulado[i-1][j-1] == 1)
        cont++;

    // Verifica vizinho superior direito
    if (i > 0 && j < n-1 && ret->reticulado[i-1][j+1] == 1)
        cont++;

    // Verifica vizinho inferior esquerdo
    if (i < n-1 && j > 0 && ret->reticulado[i+1][j-1] == 1)
        cont++;

    // Verifica vizinho inferior direito
    if (i < n-1 && j < n-1 && ret->reticulado[i+1][j+1] == 1)
        cont++;

    return cont;
}

