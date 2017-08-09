#ifndef DICIONARIO_H
#define DICIONARIO_H
#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

int InserirFimArquivo(char * nomeArq);
void BuscaArquivo(char * nomeArquivo, int posicao);
void InsereArvore(char * nomeArquivo, struct ArvoreB * A);
void RemoveArquivo(char * nomeArquivo, int posicao);

#endif