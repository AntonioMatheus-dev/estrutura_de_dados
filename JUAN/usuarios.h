//
// Created by juanm on 23/08/2025.
//
#ifndef USUARIOS_H
#define USUARIOS_H
#include "struct.h"

void iniciarUsuarios(ListaUsuarios* lista);
void cadastrarUsuario(ListaUsuarios* lista, Usuario usuario);
void listarUsuarios(ListaUsuarios* lista);
void liberarUsuarios(ListaUsuarios *lista);
Nousuario* buscarUsuarioPorId(ListaUsuarios* lista, int id);

#endif