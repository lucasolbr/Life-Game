#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main() {
    AutomatoCelular* ret = leituraReticulado();

    ret->reticulado = evoluirReticulado(ret);

    imprimeReticulado(ret);

    desalocarReticulado(ret);

    return 0;
}
