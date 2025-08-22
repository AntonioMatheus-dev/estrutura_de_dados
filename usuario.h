#ifndef USUARIOS_H
#define USUARIOS_H
#include "structs.h"

void iniciarUsuario(ListaUsuario* lista);
void cadastrarUsuario(ListaUsuario* lista, Usuario usuario);
int editarUsuarioPorNome(ListaUsuario* lista, char* nome, char* novoNome, char* novoEmail);
int removerUsuario(ListaUsuario* lista, char* nome);
void listarUsuarios(ListaUsuario* lista);
void liberarUsuarios(ListaUsuario *lista);

#endif
