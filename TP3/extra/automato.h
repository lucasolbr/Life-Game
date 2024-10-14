
#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "double_hash.h"
#include <stdbool.h>

void limpaHash(Celula* hash, int dimensao);

void leituraReticulado(Celula** reticulado, int *geracoes, int *dimensao);

void evoluirReticulado(Celula* reticulado,int dimensao, int geracoes);

void imprimeReticulado(Celula* reticulado, int dimensao);

int contaVizinho(Celula* reticulado, int dimensao, int linha, int coluna);

void copiaMatriz(Celula*,Celula*);

void hashRemove(Celula* reticulado, int dimensao, int i, int j);


#endif // AUTOMATO_H