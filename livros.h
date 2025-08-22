#ifndef LIVROS_H
#define LIVROS_H
#include "structs.h"

void iniciarlivro(ListaLivro *Lista);
void cadastrarlivro(ListaLivro *lista, Livro livro);
int editarLivro(ListaLivro *lista, char *titulo, char *novoTitulo, char *novoAutor);
int removerLivro(ListaLivro *lista, char *titulo);
void listarLivros(ListaLivro* lista);
void liberarLivros(ListaLivro* lista);

#endif
