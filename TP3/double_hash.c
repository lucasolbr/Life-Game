#include <stdio.h>
#include <stdlib.h>
#include "double_hash.h"

void criaHash(Celula** hash, int dimensao) {
    int tamanho = dimensao * dimensao;
    *hash = (Celula*)malloc(tamanho * sizeof(Celula));

    for (int x = 0; x < tamanho; x++) {
        (*hash)[x].i = -1;
        (*hash)[x].j = -1;
        (*hash)[x].vivo = 0; // Inicializa todas as células como mortas
    }
}

void liberaHash(Celula* hash) {
    free(hash);
}

//Funções hash
unsigned int H1(int i, int j, int dimensao) {
    return (i * 1 + j * 2) % (dimensao * dimensao);
}

unsigned int H2(int i, int j, int dimensao) {
    return (i * 3 + j * 4) % (dimensao * dimensao);
}

unsigned int doubleHash(int i, int j, int colisoes, int dimensao) {
    return (H1(i, j, dimensao) + colisoes * H2(i, j, dimensao)) % (dimensao * dimensao);
}

// Função para pesquisar se a célula é viva
int hashPesquisa(Celula* hash, int dimensao, int i, int j) {
    int colisoes = 0;
    unsigned int posicao = doubleHash(i, j, colisoes, dimensao);

    while ((hash[posicao].i != i || hash[posicao].j != j)) {
        colisoes++;
        
        posicao = doubleHash(i, j, colisoes, dimensao);
        if (colisoes >= (dimensao * dimensao)) 
            return 0;  // Não encontrado após todas as tentativas
    }

    return hash[posicao].vivo;
}

// Insere uma célula viva na chave correta
int hashInsere(Celula* hash, int dimensao, int i, int j) {

    int colisoes = 0;
    unsigned int posicao = doubleHash(i, j, colisoes, dimensao);

    // Resolve colisões e encontra a posição disponível
    while (hash[posicao].vivo == 1 && colisoes < (dimensao * dimensao)) {
        colisoes += 1;
        posicao = doubleHash(i, j, colisoes, dimensao);
    }

    // Se encontrou uma posição disponível, insere a célula
    if (colisoes < (dimensao * dimensao)) {
        hash[posicao].i = i;
        hash[posicao].j = j;
        hash[posicao].vivo = 1;
        return 1;  // Inserção bem-sucedida
    }

    // Retorna 0 se a tabela estiver cheia ou não conseguiu encontrar posição
    return 0;
}

int hashRemove(Celula* hash, int dimensao, int i, int j) {
    // Retorna -1 se não houver uma célula viva na posição (i, j)
    if (!hashPesquisa(hash, dimensao, i, j))
        return -1;

    int colisoes = 0;
    unsigned int posicao = doubleHash(i, j, colisoes, dimensao);

    // Resolve colisões e encontra a posição da célula a ser removida
    while (hashPesquisa(hash, dimensao, i, j)) {
        // Verifica se a célula na posição é a que queremos remover
        if (hash[posicao].i == i && hash[posicao].j == j) {
            hash[posicao].vivo = 0; // Remove a célula
            return 0;  // Remoção bem-sucedida
        }

        colisoes++;
        posicao = doubleHash(i, j, colisoes, dimensao);

        // Se já verificou todas as posições possíveis
        if (colisoes >= (dimensao * dimensao)) 
            break;
    }

    return 1; // Retorna 1 se não conseguiu remover
}