#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "matriz.h"
#include <stdbool.h>

bool leituraReticulado(Matriz** mat, int* n);

void evoluirReticulado(Matriz* mat, int n, int geracoes);

void imprimeReticulado(Matriz* mat);

int contaVizinho(Matriz* mat, int linha, int coluna);

void copiaMatriz(Matriz*,Matriz*);


#endif // AUTOMATO_H
