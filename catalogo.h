//
// Created by juanm on 23/08/2025.
//

#ifndef CATALOGO_H
#define CATALOGO_H
#include "struct.h"

void iniciarCatalogo(Catalogo* catalogo);
void cadastrarLivro(Catalogo* catalogo, Livro livro, PilhaAcoes* pilha);
int removerLivro(Catalogo* catalogo, int idLivro); // Simplificado para remover por ID
void listarCatalogo(Catalogo* catalogo);
void liberarCatalogo(Catalogo* catalogo);
Nolivro* buscarLivroPorId(Catalogo* catalogo, int id); // Função auxiliar útil

#endif