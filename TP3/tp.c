#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main() {
    int geracoes, dimensao;
    Celula *reticulado;

    leituraReticulado(&reticulado, &geracoes, &dimensao);

    evoluirReticulado(reticulado, dimensao, geracoes);

    imprimeReticulado(reticulado, dimensao);

    liberaHash(reticulado);

    return 0;
}