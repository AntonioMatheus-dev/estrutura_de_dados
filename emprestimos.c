//
// Created by juanm on 23/08/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include "emprestimos.h"
#include "catalogo.h"
#include "usuarios.h"
#include "filadeespera.h"
#include "acoesdapilha.h"

void emprestarLivro(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha, int idUsuario, int idLivro);

void iniciarEmprestimos(ListaEmprestimos* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

void realizarEmprestimo(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, PilhaAcoes* pilha, int idUsuario, int idLivro){
    Nolivro* livro = buscarLivroPorId(catalogo, idLivro);
    Nousuario* usuario = buscarUsuarioPorId(usuarios, idUsuario);

    NoEmprestimo* novo = (NoEmprestimo*)malloc(sizeof(NoEmprestimo));
    if(!novo) return;

    novo->dado.idLivro = idLivro;
    novo->dado.idUsuario = idUsuario;
    novo->proximo = NULL;
    novo->anterior = emprestimos->fim;
    if(emprestimos->inicio == NULL) emprestimos->inicio = novo;
    else emprestimos->fim->proximo = novo;
    emprestimos->fim = novo;

    livro->dado.status = EMPRESTADO;
    livro->dado.vezesEmprestado++;

    empilharAcao(pilha, ACAO_EMPRESTAR, idLivro, idUsuario);
    printf("SUCESSO: Livro '%s' emprestado para '%s'.\n", livro->dado.titulo, usuario->dado.nome);
}

void emprestarLivro(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha, int idUsuario, int idLivro) {
    Nolivro* livro = buscarLivroPorId(catalogo, idLivro);
    if (!livro) { printf("ERRO: Livro com ID %d nao encontrado.\n", idLivro); return; }

    Nousuario* usuario = buscarUsuarioPorId(usuarios, idUsuario);
    if (!usuario) { printf("ERRO: Usuario com ID %d nao encontrado.\n", idUsuario); return; }

    if (livro->dado.status == DISPONIVEL) {
        realizarEmprestimo(catalogo, usuarios, emprestimos, pilha, idUsuario, idLivro);
    } else {
        char opcao;
        printf("AVISO: Livro '%s' ja esta emprestado. Deseja entrar na fila de espera? (s/n): ", livro->dado.titulo);
        scanf(" %c", &opcao);
        if (opcao == 's' || opcao == 'S') {
            enfileirar(fila, idLivro, idUsuario);
        }
    }
}

void devolverLivro(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha, int idLivro) {
    NoEmprestimo* atual = emprestimos->inicio;
    int idUsuarioQueDevolveu = -1;
    int encontrado = 0;

    while(atual) {
        if (atual->dado.idLivro == idLivro) {
            idUsuarioQueDevolveu = atual->dado.idUsuario;
            if(atual->anterior) atual->anterior->proximo = atual->proximo;
            else emprestimos->inicio = atual->proximo;
            if(atual->proximo) atual->proximo->anterior = atual->anterior;
            else emprestimos->fim = atual->anterior;
            free(atual);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("ERRO: Este livro (ID %d) nao consta como emprestado.\n", idLivro);
        return;
    }

    Nolivro* livro = buscarLivroPorId(catalogo, idLivro);
    livro->dado.status = DISPONIVEL;
    empilharAcao(pilha, ACAO_DEVOLVER, idLivro, idUsuarioQueDevolveu);
    printf("SUCESSO: Livro '%s' devolvido.\n", livro->dado.titulo);

    int proximoUsuarioId;
    if (desenfileirar(fila, idLivro, &proximoUsuarioId)) {
        printf("INFO: Havia um usuario na fila de espera. Realizando novo emprestimo...\n");
        // Empresta automaticamente para o próximo da fila
        realizarEmprestimo(catalogo, usuarios, emprestimos, pilha, proximoUsuarioId, idLivro);
    }
}

void desfazerUltimaAcao(Catalogo* catalogo, ListaUsuarios* usuarios, ListaEmprestimos* emprestimos, FilaEspera* fila, PilhaAcoes* pilha) {
    (void)fila;
    Acao ultimaAcao;
    if (!desempilharAcao(pilha, &ultimaAcao)) {
        printf("Nenhuma acao para desfazer.\n");
        return;
    }

    printf("Desfazendo ultima acao...\n");
    switch (ultimaAcao.tipo) {
        case ACAO_CADASTRAR_LIVRO:
            if (removerLivro(catalogo, ultimaAcao.id_principal)) {
                printf("Desfeito: Cadastro do livro ID %d.\n", ultimaAcao.id_principal);
            }
            break;

        case ACAO_EMPRESTAR:
            
            {
                NoEmprestimo* emprestimo = emprestimos->inicio;
                while(emprestimo) {
                    if (emprestimo->dado.idLivro == ultimaAcao.id_principal) {
                        if(emprestimo->anterior) emprestimo->anterior->proximo = emprestimo->proximo;
                        else emprestimos->inicio = emprestimo->proximo;
                        if(emprestimo->proximo) emprestimo->proximo->anterior = emprestimo->anterior;
                        else emprestimos->fim = emprestimo->anterior;
                        free(emprestimo);
                        break;
                    }
                    emprestimo = emprestimo->proximo;
                }
                Nolivro* livro = buscarLivroPorId(catalogo, ultimaAcao.id_principal);
                livro->dado.status = DISPONIVEL;
                livro->dado.vezesEmprestado--; 
                printf("Desfeito: Emprestimo do livro ID %d.\n", ultimaAcao.id_principal);
            }
            break;

        case ACAO_DEVOLVER:
           
            {
               realizarEmprestimo(catalogo, usuarios, emprestimos, pilha, ultimaAcao.id_secundario, ultimaAcao.id_principal);
              
               Acao temp;
               desempilharAcao(pilha, &temp);
               printf("Desfeito: Devolucao do livro ID %d.\n", ultimaAcao.id_principal);
            }
            break;
    }
}

void liberarEmprestimos(ListaEmprestimos* lista) {
    NoEmprestimo* atual = lista->inicio;
    while(atual) {
        NoEmprestimo* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->inicio = lista->fim = NULL;
}