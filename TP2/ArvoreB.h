#ifndef ARVOREB_H
#define ARVOREB_H

#define ORDEM 4

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct No
{
	int Chave[ORDEM-1];
	struct No *Filho[ORDEM];
	int numElementos;
};

struct ArvoreB
{
	struct No *raiz;
};

struct ArvoreB* CriaArvoreB();
void Insere(struct ArvoreB *A, int e);
void Remove(struct ArvoreB *A, int e);
int Busca(struct ArvoreB *A, int e);
void Imprime(struct ArvoreB *A);

#endif
