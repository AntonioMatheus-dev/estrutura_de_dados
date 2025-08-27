//
// Created by juanm on 23/08/2025.
//
#ifndef PILHA_ACOES_H
#define PILHA_ACOES_H
#include "struct.h"

void iniciarPilha(PilhaAcoes* pilha);
void empilharAcao(PilhaAcoes* pilha, TipoAcao tipo, int id_principal, int id_secundario);
int desempilharAcao(PilhaAcoes* pilha, Acao* acao);
void liberarPilha(PilhaAcoes* pilha);

#endif