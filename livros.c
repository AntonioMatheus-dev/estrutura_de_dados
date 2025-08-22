#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livros.h"

void iniciarlivro(ListaLivro *Lista)
{
    Lista->inicio = NULL;
    Lista->fim = NULL;
}

void cadastrarlivro(ListaLivro *lista, Livro livro)
{
    Nolivro *novo = (Nolivro *)malloc(sizeof(Nolivro));
    if (novo)
    {
        novo->dado = livro;
        novo->proximo = NULL;
        novo->anterior = lista->fim;
        if (lista->inicio == NULL)
            lista->inicio = novo;
        else
            lista->fim->proximo = novo;
        lista->fim = novo;
    }
    else
        printf("Erro ao alocar memoria\n");
}

int editarLivro(ListaLivro *lista, char *titulo, char *novoTitulo, char *novoAutor)
{
    Nolivro *atual = lista->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->dado.titulo, titulo) == 0)
        {
            if (novoTitulo)
                strcpy(atual->dado.titulo, novoTitulo);
            if (novoAutor)
                strcpy(atual->dado.autor, novoAutor);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

int removerLivro(ListaLivro *lista, char *titulo)
{
    Nolivro *atual = lista->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->dado.titulo, titulo) == 0)
        {
            if (atual->anterior)
                atual->anterior->proximo = atual->proximo;
            else
                lista->inicio = atual->proximo;
            if (atual->proximo)
                atual->proximo->anterior = atual->anterior;
            else
                lista->fim = atual->anterior;
            free(atual);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void listarLivros(ListaLivro *lista)
{
    Nolivro *atual = lista->inicio;
    if (!atual)
    {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    while (atual != NULL)
    {
        printf("%d - %s (%s)\n", atual->dado.id, atual->dado.titulo, atual->dado.autor);
        atual = atual->proximo;
    }
}

void liberarLivros(ListaLivro *lista)
{
    Nolivro *atual = lista->inicio;
    while (atual)
    {
        Nolivro *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = lista->fim = NULL;
}
