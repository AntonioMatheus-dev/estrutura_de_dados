#include <stdio.h>
#include <stdlib.h>
#include "filadeespera.h"

void iniciarFila(FilaEspera* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileirar(FilaEspera* fila, int idLivro, int idUsuario) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    if (!novo) return;
    novo->idLivro = idLivro;
    novo->idUsuario = idUsuario;
    novo->proximo = NULL;

    if (fila->fim) {
        fila->fim->proximo = novo;
    }
    fila->fim = novo;

    if (fila->inicio == NULL) {
        fila->inicio = novo;
    }
    printf("Usuario (ID %d) adicionado a fila de espera pelo livro (ID %d).\n", idUsuario, idLivro);
}

int desenfileirar(FilaEspera* fila, int idLivro, int* idUsuario) {
    NoFila *atual = fila->inicio;
    NoFila *anterior = NULL;

    while (atual != NULL) {
        if (atual->idLivro == idLivro) {
            *idUsuario = atual->idUsuario;

            if (anterior == NULL) {
                fila->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            if (fila->fim == atual) {
                fila->fim = anterior;
            }

            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

void listarFila(FilaEspera* fila) {
    NoFila* atual = fila->inicio;
    if (!atual) {
        printf("Fila de espera esta vazia.\n");
        return;
    }
    printf("\n--- Fila de Espera Atual ---\n");
    while(atual) {
        printf("Livro ID: %d, Esperando por Usuario ID: %d\n", atual->idLivro, atual->idUsuario);
        atual = atual->proximo;
    }
}

void liberarFila(FilaEspera* fila) {
    NoFila* atual = fila->inicio;
    while (atual) {
        NoFila* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    fila->inicio = fila->fim = NULL;
}