//
// Created by juanm on 23/08/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

void iniciarUsuarios(ListaUsuarios *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void cadastrarUsuario(ListaUsuarios *lista, Usuario usuario) {
    Nousuario *novo = (Nousuario *)malloc(sizeof(Nousuario));
    if (novo) {
        novo->dado = usuario;
        novo->proximo = NULL;
        novo->anterior = lista->fim;
        if (lista->inicio == NULL)
            lista->inicio = novo;
        else
            lista->fim->proximo = novo;
        lista->fim = novo;
        printf("Usuario '%s' cadastrado com sucesso (ID: %d).\n", usuario.nome, usuario.id);
    } else {
        printf("Erro ao alocar memoria\n");
    }
}

Nousuario* buscarUsuarioPorId(ListaUsuarios* lista, int id) {
    Nousuario* atual = lista->inicio;
    while(atual) {
        if (atual->dado.id == id) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void listarUsuarios(ListaUsuarios *lista) {
    Nousuario *atual = lista->inicio;
    if (atual == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
    printf("\n--- Lista de Usuarios ---\n");
    while (atual != NULL) {
        printf("ID: %d | Nome: %s | Email: %s\n", atual->dado.id, atual->dado.nome, atual->dado.email);
        atual = atual->proximo;
    }
}

void liberarUsuarios(ListaUsuarios *lista) {
    Nousuario *atual = lista->inicio;
    while (atual) {
        Nousuario *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = lista->fim = NULL;
}