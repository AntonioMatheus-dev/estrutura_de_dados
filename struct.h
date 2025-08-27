//
// Created by juanm on 23/08/2025.
//

#ifndef STRUCT_H
#define STRUCT_H

typedef enum {
    DISPONIVEL,
    EMPRESTADO
} StatusLivro;


typedef enum {
    ACAO_CADASTRAR_LIVRO,
    ACAO_EMPRESTAR,
    ACAO_DEVOLVER
} TipoAcao;



typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    StatusLivro status;
    int vezesEmprestado; 
} Livro;

typedef struct {
    int id;
    char nome[100];
    char email[100];
} Usuario;

typedef struct {
    int idLivro;
    int idUsuario;
} Emprestimo;

typedef struct {
    TipoAcao tipo;
    int id_principal; 
    int id_secundario; 
} Acao;



typedef struct Nolivro {
    Livro dado;
    struct Nolivro *anterior;
    struct Nolivro *proximo;
} Nolivro;

typedef struct Nousuario {
    Usuario dado;
    struct Nousuario *proximo;
    struct Nousuario *anterior;
} Nousuario;

typedef struct NoFila {
    int idLivro;
    int idUsuario;
    struct NoFila *proximo;
} NoFila;

typedef struct NoPilha {
    Acao dado;
    struct NoPilha *proximo;
} NoPilha;

typedef struct NoEmprestimo {
    Emprestimo dado;
    struct NoEmprestimo *proximo;
    struct NoEmprestimo *anterior;
} NoEmprestimo;



typedef struct {
    Nolivro* inicio;
    Nolivro* fim;
} Catalogo;

typedef struct {
    Nousuario *inicio;
    Nousuario *fim;
} ListaUsuarios;

typedef struct {
    NoFila *inicio;
    NoFila *fim;
} FilaEspera;

typedef struct {
    NoPilha *topo;
} PilhaAcoes;

typedef struct {
    NoEmprestimo *inicio;
    NoEmprestimo *fim;
} ListaEmprestimos;

#endif