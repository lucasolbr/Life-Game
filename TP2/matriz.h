#ifndef MATRIZ_H
#define MATRIZ_H
#include <stdbool.h>


typedef struct Celula {
    int linha;
    int coluna;
    struct Celula *direita;
    struct Celula *baixo;
} Cel;

typedef struct{
    int n; // tamanho da matriz
    Cel *cabecaLinha;
    Cel *cabecaColuna;
} Matriz;

Cel* alocaCelula();

Matriz* alocaReticulado(int n);

void desalocarReticulado(Matriz* mat);

bool pesquisar(Matriz* mat, int lin, int col);

void inserirCelula(Matriz *mat, int linha, int coluna);

bool deletaCelula(Matriz *reticulado, int linha, int coluna);

#endif // MATRIZ_H

//valgrind --leak-check=full --show-leak-kinds=all  -s ./exe < 3.in