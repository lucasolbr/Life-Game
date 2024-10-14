#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main() {
    int geracoes;
    Matriz *mat = NULL;

    leituraReticulado(&mat, &geracoes);

    evoluirReticulado(mat, mat->n, geracoes);

    imprimeReticulado(mat);

    desalocarReticulado(mat);

    return 0;
}
