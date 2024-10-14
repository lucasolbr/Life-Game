#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

Cel* alocaCelula(){
	Cel *novo = (Cel*)malloc(sizeof(Cel));
	novo->direita = NULL;
	novo->baixo = NULL;

	return novo;
}


// alocar mat
Matriz* alocaReticulado(int n) {
    Matriz *mat = (Matriz*)malloc(sizeof(Matriz));

    mat->cabecaColuna = (Cel*)malloc(sizeof(Cel));
    mat->cabecaLinha = (Cel*)malloc(sizeof(Cel));

    mat->n = n;
    Cel *aux = mat->cabecaColuna;
    Cel *aux2 = mat->cabecaLinha;

    for (int i = 0; i < mat->n; i++)
    {
        //alocando cabeca de coluna
        aux->direita = alocaCelula();
        aux->direita->coluna = i;
        aux->direita->linha = -1;

        // alocando cabeca de linha
        aux2->baixo = alocaCelula();
        aux2->baixo->coluna = -1;
        aux2->baixo->linha = i;

        // pulando pra proxima cabeca
        aux = aux->direita;
        aux2 = aux2->baixo;
    }
    
    return mat;
}

void desalocarReticulado(Matriz* mat) {
    Cel *plinha = mat->cabecaLinha->baixo;
    Cel *pcoluna = mat->cabecaColuna->direita;
    Cel *aux;

    // Desaloca todas as células vivas
    for (int i = 0; i < mat->n; i++) {
        for (int j = 0; j < mat->n; j++) {
            deletaCelula(mat, i, j);
        }
    }

    // Desaloca as cabeças das linhas e colunas
    while (plinha != NULL) {
        aux = plinha;
        plinha = plinha->baixo;
        free(aux);
    }

    while (pcoluna != NULL) {
        aux = pcoluna;
        pcoluna = pcoluna->direita;
        free(aux);
    }

    // Liberando as cabeças principais
    free(mat->cabecaColuna);
    free(mat->cabecaLinha);
    free(mat);
}


bool pesquisar(Matriz* mat , int linha, int coluna){


    Cel *aux = mat->cabecaLinha;

    // chegando na linha certa 
    for (int i = 0; i <= linha; i++)
        aux = aux->baixo;
    
    
    // combinando os dois indices e retornando indicando qu esta vivo
    while (aux != NULL)
    {
        if (aux->coluna == coluna)
            return true; // vivo
        
        aux = aux->direita;
    }
    
    
    return false; // morto
}

void inserirCelula(Matriz *mat, int linha, int coluna) {

    Cel* newCel = alocaCelula();
    Cel *aux = mat->cabecaColuna;
    Cel *aux2 = mat->cabecaLinha;
    newCel->linha = linha;
    newCel->coluna = coluna;

    //indo ate a cabeca certa
    for (int i = 0; i <= coluna; i++) {
        aux = aux->direita;
    }

    //indo ate a cabeca certa
    for (int i = 0; i <= linha; i++) {
        aux2 = aux2->baixo;
    }

    // insercao pela cabeca de coluna
    Cel *atual = aux->baixo;
    Cel *prev = aux; //inicia pela cabeca de coluna

    while (atual != NULL && atual->linha < linha) {
        prev = atual;
        atual = atual->baixo;
    }
    //nova celula na posicao correta da coluna(baixo)
    prev->baixo = newCel;
    newCel->baixo = atual;

    //lista de linhahas (direita)
    atual = aux2->direita;
    prev = aux2; // cabeça da linhas

    while (atual != NULL && atual->coluna < coluna) {
        prev = atual;
        atual = atual->direita;
    }
    //Insere a nova celula na posição correta na linha(do jogo)
    prev->direita = newCel;
    newCel->direita = atual;
}



bool deletaCelula(Matriz *mat, int linha, int coluna){

    // variaveis para percorrer a lista e matriz
    Cel *linhaAux = mat->cabecaLinha;

    Cel *colunaAux = mat->cabecaColuna;

    Cel *celRemovida = NULL;

    Cel *anterior = NULL;

    // indo ate as cordenadas corretas
    for(int i = 0; i <= linha; i++)
        linhaAux = linhaAux->baixo;

    for(int i = 0; i <= coluna; i++)
        colunaAux = colunaAux->direita;

    // achando a celula que deve ser removida
    anterior = linhaAux;
    while(linhaAux != NULL && linhaAux->coluna != coluna){
        anterior = linhaAux;
        linhaAux = linhaAux->direita;
    }
    
    if(linhaAux == NULL)
        return false;

    // obtendo por ponteiro e removendo
    celRemovida = linhaAux;   
    if(anterior != linhaAux)   
        anterior->direita = linhaAux->direita;


    // achando a celula que deve ser removida
    anterior = colunaAux;
    while(colunaAux != NULL && colunaAux->linha != linha){
        anterior = colunaAux;
        colunaAux = colunaAux->baixo;
    }
    if(colunaAux == NULL)
        return false;

    // remove das colunas
    if(anterior != colunaAux)
        anterior->baixo = colunaAux->baixo;

    free(celRemovida);

    return true;
}