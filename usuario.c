#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

void iniciarUsuario(ListaUsuario *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

void cadastrarUsuario(ListaUsuario *lista, Usuario usuario)
{
    Nousuario *novo = (Nousuario *)malloc(sizeof(Nousuario));
    if (novo)
    {
        novo->dado = usuario;
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

int editarUsuarioPorNome(ListaUsuario *lista, char *nome, char *novoNome, char *novoEmail)
{
    Nousuario *atual = lista->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->dado.nome, nome) == 0)
        {
            if (novoNome)
                strcpy(atual->dado.nome, novoNome);
            if (novoEmail)
                strcpy(atual->dado.email, novoEmail);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

int removerUsuario(ListaUsuario *lista, char *nome)
{
    Nousuario *atual = lista->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->dado.nome, nome) == 0)
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

void listarUsuarios(ListaUsuario *lista)
{
    Nousuario *atual = lista->inicio;
    if (atual == NULL)
    {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }
    while (atual != NULL)
    {
        printf("%d - %s (%s)\n", atual->dado.id, atual->dado.nome, atual->dado.email);
        atual = atual->proximo;
    }
}

void liberarUsuarios(ListaUsuario *lista)
{
    Nousuario *atual = lista->inicio;
    while (atual)
    {
        Nousuario *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = lista->fim = NULL;
}
