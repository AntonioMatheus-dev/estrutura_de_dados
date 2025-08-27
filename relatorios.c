#include <stdio.h>
#include <stdlib.h>
#include "relatorios.h"

int compararLivros(const void* a, const void* b) {
    Livro* livroA = *(Livro**)a;
    Livro* livroB = *(Livro**)b;
    return livroB->vezesEmprestado - livroA->vezesEmprestado;
}

void gerarRelatorioMaisEmprestados(Catalogo* catalogo) {
    int count = 0;
    Nolivro* atual = catalogo->inicio;
    if (!atual) {
        printf("Catalogo vazio. Nenhum relatorio a ser gerado.\n");
        return;
    }

    while (atual) {
        count++;
        atual = atual->proximo;
    }

    Livro** arrayDeLivros = (Livro**)malloc(count * sizeof(Livro*));
    if (!arrayDeLivros) {
        printf("Erro de alocacao de memoria para o relatorio.\n");
        return;
    }

    atual = catalogo->inicio;
    for (int i = 0; i < count; i++) {
        arrayDeLivros[i] = &atual->dado;
        atual = atual->proximo;
    }

    qsort(arrayDeLivros, count, sizeof(Livro*), compararLivros);

    printf("\n--- Relatorio de Livros Mais Emprestados ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Titulo: %s | Vezes Emprestado: %d\n", 
               i + 1, arrayDeLivros[i]->titulo, arrayDeLivros[i]->vezesEmprestado);
    }

    free(arrayDeLivros);
}