
//
// Created by juanm on 23/08/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogo.h"
#include "acoesdapilha.h"

void iniciarCatalogo(Catalogo *catalogo)
{
    catalogo->inicio = NULL;
    catalogo->fim = NULL;
}

void cadastrarLivro(Catalogo *catalogo, Livro livro, PilhaAcoes *pilha)
{
    Nolivro *novo = (Nolivro *)malloc(sizeof(Nolivro));
    if (novo)
    {
        novo->dado = livro;
        novo->dado.status = DISPONIVEL;
        novo->dado.vezesEmprestado = 0;
        novo->proximo = NULL;
        novo->anterior = catalogo->fim;
        if (catalogo->inicio == NULL)
            catalogo->inicio = novo;
        else
            catalogo->fim->proximo = novo;
        catalogo->fim = novo;

        empilharAcao(pilha, ACAO_CADASTRAR_LIVRO, livro.id, -1);
        printf("Livro '%s' cadastrado com sucesso (ID: %d).\n", livro.titulo, livro.id);
    }
    else
    {
        printf("Erro ao alocar memoria\n");
    }
}

Nolivro *buscarLivroPorId(Catalogo *catalogo, int id)
{
    Nolivro *atual = catalogo->inicio;
    if (catalogo == NULL)
    {
        printf("\nBIBLIOTECA VAZIA\n");
        return NULL;
    }

    while (atual)
    {
        if (atual->dado.id == id)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

Nolivro *buscarLivroPorTitulo(Catalogo *catalogo, const char *titulo)
{
    Nolivro *atual = catalogo->inicio;
    if (catalogo == NULL)
    {
        printf("\nBIBLIOTECA VAZIA\n");
        return NULL;
    }

    while (atual)
    {
        if (strcmp(atual->dado.titulo, titulo) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void ordenarCatalogo(Catalogo *catalogo)
{
    if (catalogo == NULL || catalogo->inicio == NULL)
    {
        printf("\nBIBLIOTECA VAZIA\n");
        return;
    }
    printf("\n--- Livros do Catalogo ---\n");
    Nolivro *atual = catalogo->inicio;
    while (atual)
    {
        printf("ID: %d | Titulo: %s | Autor: %s\n", atual->dado.id, atual->dado.titulo, atual->dado.autor);
        atual = atual->proximo;
    }
}

int removerLivro(Catalogo *catalogo, int idLivro)
{
    Nolivro *alvo = buscarLivroPorId(catalogo, idLivro);
    if (alvo == NULL)
        return 0; 

    if (alvo->dado.status == EMPRESTADO)
    {
        printf("Acao negada: O livro '%s' esta emprestado e nao pode ser removido.\n", alvo->dado.titulo);
        return 0;
    }

    if (alvo->anterior)
        alvo->anterior->proximo = alvo->proximo;
    else
        catalogo->inicio = alvo->proximo;

    if (alvo->proximo)
        alvo->proximo->anterior = alvo->anterior;
    else
        catalogo->fim = alvo->anterior;

    free(alvo);
    return 1;
}

void listarCatalogo(Catalogo *catalogo)
{
    Nolivro *atual = catalogo->inicio;
    if (!atual)
    {
        printf("Catalogo de livros esta vazio.\n");
        return;
    }
    printf("\n--- Catalogo de Livros ---\n");
    while (atual != NULL)
    {
        const char *statusStr = (atual->dado.status == DISPONIVEL) ? "Disponivel" : "Emprestado";
        printf("ID: %d | Titulo: %s | Autor: %s | Status: [%s] | Emprestado %d vez(es)\n",
               atual->dado.id, atual->dado.titulo, atual->dado.autor, statusStr, atual->dado.vezesEmprestado);
        atual = atual->proximo;
    }
}

void liberarCatalogo(Catalogo *catalogo)
{
    Nolivro *atual = catalogo->inicio;
    while (atual)
    {
        Nolivro *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    catalogo->inicio = catalogo->fim = NULL;
}