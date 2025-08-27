#include <stdio.h>
#include <stdlib.h>
#include "acoesdapilha.h"

void iniciarPilha(PilhaAcoes* pilha) {
    pilha->topo = NULL;
}

void empilharAcao(PilhaAcoes* pilha, TipoAcao tipo, int id_principal, int id_secundario) {
    NoPilha* novo = (NoPilha*) malloc(sizeof(NoPilha));
    if (!novo) return;
    
    novo->dado.tipo = tipo;
    novo->dado.id_principal = id_principal;
    novo->dado.id_secundario = id_secundario;
    
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

int desempilharAcao(PilhaAcoes* pilha, Acao* acao) {
    if (pilha->topo == NULL) {
        return 0;
    }
    NoPilha* temp = pilha->topo;
    *acao = temp->dado;
    
    pilha->topo = temp->proximo;
    free(temp);
    return 1;
}

void liberarPilha(PilhaAcoes* pilha) {
    NoPilha* atual = pilha->topo;
    while(atual) {
        NoPilha* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    pilha->topo = NULL;
}