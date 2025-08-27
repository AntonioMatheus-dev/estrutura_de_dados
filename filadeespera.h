//
// Created by juanm on 23/08/2025.
//
#ifndef FILA_ESPERA_H
#define FILA_ESPERA_H
#include "struct.h"

void iniciarFila(FilaEspera* fila);
void enfileirar(FilaEspera* fila, int idLivro, int idUsuario);
int desenfileirar(FilaEspera* fila, int idLivro, int* idUsuario);
void listarFila(FilaEspera* fila);
void liberarFila(FilaEspera* fila);

#endif