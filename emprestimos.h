//
// Created by juanm on 23/08/2025.
//

#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H
#include "struct.h"

void iniciarEmprestimos(ListaEmprestimos* lista);
void emprestarLivro(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha, int idUsuario, int idLivro);
void devolverLivro(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha, int idLivro);
void desfazerUltimaAcao(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha);
void liberarEmprestimos(ListaEmprestimos* lista);


#endif
