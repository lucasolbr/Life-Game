#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

typedef struct {
    int i;    // linha 
    int j;    // coluna
    int vivo; // 1 está vivo 0 está morto
} Celula;

void criaHash(Celula** hash, int dimensao);
void liberaHash(Celula* hash);
unsigned int H1(int i, int j, int dimensao);
unsigned int H2(int i, int j, int dimensao);
unsigned int doubleHash(int i, int j, int colisoes, int dimensao);
int hashPesquisa(Celula* hash, int dimensao, int i, int j);
int hashInsere(Celula* hash, int dimensao, int i, int j);

#endif // DOUBLE_HASH_H
