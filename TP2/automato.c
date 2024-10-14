#include<stdio.h>
#include<stdlib.h>
#include"automato.h"

bool leituraReticulado(Matriz **mat, int *geracoes){
    int tamanho;
    scanf("%d %d", &tamanho, geracoes);

    *mat = alocaReticulado(tamanho);

    int vivo;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            scanf("%d", &vivo);// insere celula se for vivo
            if (vivo == 1) {
                inserirCelula(*mat, i, j);
            }
        }
    }
    return true;
}

// copia uma matriz para outra
void copiaMatriz(Matriz* mat,Matriz* mat2){
    for (int i = 0; i < mat->n; i++)
    {
        for (int j = 0; j < mat->n; j++)
        {   //condição que copia as celulas vivas para não copiar elas novamente
            if(pesquisar(mat, i, j) && !pesquisar(mat2, i, j))
                inserirCelula(mat2, i, j);
                
            else if(!pesquisar(mat, i, j) && pesquisar(mat2, i, j))
            deletaCelula(mat2, i, j);
        }
    }
}

void evoluirReticulado(Matriz* mat, int n, int geracoes) {
    
    
    for (int x = 0; x < geracoes; x++) {
        Matriz* matrizAux = alocaReticulado(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int vizinhosVivos = contaVizinho(mat, i, j);

                if (pesquisar(mat, i, j)) {
                    if (vizinhosVivos == 2 || vizinhosVivos == 3) {
                        inserirCelula(matrizAux, i, j);
                    }// deixa viva
                } else {
                    if (vizinhosVivos == 3) {
                        inserirCelula(matrizAux, i, j);
                    }// revive
                }
            }
        }
        copiaMatriz(matrizAux, mat);
        //copia e desaloca no fim do loop
        desalocarReticulado(matrizAux);
    }
}


//Impressão
void imprimeReticulado(Matriz* mat){
    for (int i = 0; i < mat->n; i++) {
        for (int j = 0; j < mat->n; j++) {
            if (pesquisar(mat, i, j)) {
                printf("1 ");
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}


int contaVizinho(Matriz* mat, int linha, int coluna){
    int vizinhosVivos = 0;
    int n = mat->n;

    // Verifica vizinho superior
    if (linha > 0 && pesquisar(mat, linha - 1, coluna))
        vizinhosVivos++;

    // Verifica vizinho inferior
    if (linha < n - 1 && pesquisar(mat, linha + 1, coluna))
        vizinhosVivos++;

    // Verifica vizinho esquerda
    if (coluna > 0 && pesquisar(mat, linha, coluna - 1))
        vizinhosVivos++;

    // Verifica vizinho direita
    if (coluna < n - 1 && pesquisar(mat, linha, coluna + 1))
        vizinhosVivos++;

    // Verifica vizinho superior esquerdo
    if (linha > 0 && coluna > 0 && pesquisar(mat, linha - 1, coluna - 1))
        vizinhosVivos++;

    // Verifica vizinho superior direito
    if (linha > 0 && coluna < n - 1 && pesquisar(mat, linha - 1, coluna + 1))
        vizinhosVivos++;

    // Verifica vizinho inferior esquerdo
    if (linha < n - 1 && coluna > 0 && pesquisar(mat, linha + 1, coluna - 1))
        vizinhosVivos++;

    // Verifica vizinho inferior direito
    if (linha < n - 1 && coluna < n - 1 && pesquisar(mat, linha + 1, coluna + 1))
        vizinhosVivos++;

    return vizinhosVivos;
}
