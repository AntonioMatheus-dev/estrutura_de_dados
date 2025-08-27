//
// Created by juanm on 23/08/2025.
//

#ifndef STRUCT_H
#define STRUCT_H
// Enum para o status do livro
typedef enum {
    DISPONIVEL,
    EMPRESTADO
} StatusLivro;

// Enum para os tipos de ações que podem ser desfeitas
typedef enum {
    ACAO_CADASTRAR_LIVRO,
    ACAO_EMPRESTAR,
    ACAO_DEVOLVER
} TipoAcao;


// --- ESTRUTURAS PRINCIPAIS ---

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    StatusLivro status;
    int vezesEmprestado; // Contador para o relatório
} Livro;

typedef struct {
    int id;
    char nome[100];
    char email[100];
} Usuario;

// Estrutura para um registro de empréstimo ativo
typedef struct {
    int idLivro;
    int idUsuario;
} Emprestimo;

// Estrutura para uma ação na pilha de Desfazer
typedef struct {
    TipoAcao tipo;
    int id_principal; // ID do livro
    int id_secundario; // ID do usuário (no caso de empréstimo/devolução)
} Acao;


// --- NÓS DAS ESTRUTURAS DE DADOS ---

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


// --- CONTAINERS DAS LISTAS/FILAS/PILHAS ---

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