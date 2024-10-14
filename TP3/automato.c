#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

void leituraReticulado(Celula** reticulado, int *geracoes, int *dimensao) {
    // Leitura da dimensão e número de gerações
    scanf("%d %d", dimensao, geracoes);

    criaHash(reticulado, *dimensao);
    int aux;
    for (int x = 0; x < *dimensao; x++) {
        for (int y = 0; y < *dimensao; y++) {
            scanf("%d", &aux);
            if (aux == 1) {
                hashInsere(*reticulado, *dimensao, x, y);
            }
        }
    }
}

void evoluirReticulado(Celula* reticulado, int dimensao, int geracoes) {
    Celula* aux;
    criaHash(&aux, dimensao);
    for (int g = 0; g < geracoes; g++) {
        // Copia o estado atual do reticulado para o auxiliar
        for (int i = 0; i < dimensao*dimensao; i++) {
            aux[i].i = reticulado[i].i;
            aux[i].j = reticulado[i].j;
            aux[i].vivo = reticulado[i].vivo;
        }
        // Evolui o reticulado com base no auxiliar
        for (int i = 0; i < dimensao; i++) {
            for (int j = 0; j < dimensao; j++) {
                int vizinhosVivos = contaVizinho(aux, dimensao, i, j);

                if (hashPesquisa(reticulado, dimensao, i, j)) {
                    if (vizinhosVivos != 2 && vizinhosVivos != 3) {
                        hashRemove(reticulado, dimensao, i, j); // Célula morre
                    }
                } else {
                    if (vizinhosVivos == 3) {
                        hashInsere(reticulado, dimensao, i, j);
                    }
                }
            }
        }

        // Limpa o auxiliar para a próxima geração
        limpaHash(aux, dimensao);

    }

    free(aux);
}

void limpaHash(Celula* hash, int dimensao) {
    int tamanho = dimensao * dimensao;
    for (int x = 0; x < tamanho; x++) {
        hash[x].vivo = 0; // Redefine todas as células como mortas
    }
}



// Impressão
void imprimeReticulado(Celula* reticulado, int dimensao) {
    for (int x = 0; x < dimensao; x++) {
        for (int y = 0; y < dimensao; y++) {
            if (hashPesquisa(reticulado, dimensao, x, y)) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int contaVizinho(Celula* reticulado, int dimensao, int linha, int coluna) {
    int vizinhosVivos = 0;

    // Verifica vizinho superior
    if (linha > 0) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha - 1, coluna);
    }

    // Verifica vizinho inferior
    if (linha < dimensao - 1) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha + 1, coluna);
    }

    // Verifica vizinho à esquerda
    if (coluna > 0) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha, coluna - 1);
    }

    // Verifica vizinho à direita
    if (coluna < dimensao - 1) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha, coluna + 1);
    }

    // Verifica vizinho superior esquerdo
    if (linha > 0 && coluna > 0) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha - 1, coluna - 1);
    }

    // Verifica vizinho superior direito
    if (linha > 0 && coluna < dimensao - 1) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha - 1, coluna + 1);
    }

    // Verifica vizinho inferior esquerdo
    if (linha < dimensao - 1 && coluna > 0) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha + 1, coluna - 1);
    }

    // Verifica vizinho inferior direito
    if (linha < dimensao - 1 && coluna < dimensao - 1) {
        vizinhosVivos += hashPesquisa(reticulado, dimensao, linha + 1, coluna + 1);
    }

    return vizinhosVivos;
}
