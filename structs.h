#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
} Livro;

typedef struct {
    int id;
    char nome[100];
    char email[100];
} Usuario;

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

typedef struct {
    Nolivro* inicio;
    Nolivro* fim;
} ListaLivro;

typedef struct {
    Nousuario *inicio;
    Nousuario *fim;
} ListaUsuario;

#endif
