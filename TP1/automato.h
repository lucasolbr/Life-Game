#ifndef AUTOMATO_H
#define AUTOMATO_H

// Struct principal
typedef struct Automato {
    int **reticulado;
    int n;
    int geracoes;
} AutomatoCelular;

void alocarReticulado(AutomatoCelular** ret, int n);
void desalocarReticulado(AutomatoCelular* ret);
AutomatoCelular* leituraReticulado();
int** evoluirReticulado(AutomatoCelular* ret);
void imprimeReticulado(AutomatoCelular* ret);
int contaVizinho(AutomatoCelular* ret, int i, int j);

#endif // AUTOMATO_H
