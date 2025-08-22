#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livros.h"
#include "usuario.h"

int main()
{
    ListaLivro catalogo;
    ListaUsuario usuarios;
    iniciarlivro(&catalogo);
    iniciarUsuario(&usuarios);

    int opcao, subopcao;
    int idLivro = 1, idUsuario = 1;
    char titulo[100], nome[100];

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Gerenciar Livros\n");
        printf("2 - Gerenciar Usuários\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            do
            {
                printf("\n--- Menu Livros ---\n");
                printf("1 - Cadastrar Livro\n");
                printf("2 - Editar Livro\n");
                printf("3 - Remover Livro\n");
                printf("4 - Listar Livros\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &subopcao);
                getchar();

                if (subopcao == 1)
                {
                    Livro l;
                    l.id = idLivro++;
                    printf("Título: ");
                    fgets(l.titulo, 100, stdin);
                    l.titulo[strcspn(l.titulo, "\n")] = 0;
                    printf("Autor: ");
                    fgets(l.autor, 100, stdin);
                    l.autor[strcspn(l.autor, "\n")] = 0;
                    cadastrarlivro(&catalogo, l);
                }
                else if (subopcao == 2)
                {
                    char novoTitulo[100], novoAutor[100];
                    printf("Título do livro a editar: ");
                    fgets(titulo, 100, stdin);
                    titulo[strcspn(titulo, "\n")] = 0;
                    printf("Novo título (ou ENTER p/ manter): ");
                    fgets(novoTitulo, 100, stdin);
                    novoTitulo[strcspn(novoTitulo, "\n")] = 0;
                    printf("Novo autor (ou ENTER p/ manter): ");
                    fgets(novoAutor, 100, stdin);
                    novoAutor[strcspn(novoAutor, "\n")] = 0;
                    editarLivro(&catalogo, titulo,
                                         strlen(novoTitulo) ? novoTitulo : NULL,
                                         strlen(novoAutor) ? novoAutor : NULL);
                }
                else if (subopcao == 3)
                {
                    printf("Título do livro a remover: ");
                    fgets(titulo, 100, stdin);
                    titulo[strcspn(titulo, "\n")] = 0;
                    removerLivro(&catalogo, titulo);
                }
                else if (subopcao == 4)
                {
                    listarLivros(&catalogo);
                }
            } while (subopcao != 0);
            break;

        case 2:
            do
            {
                printf("\n--- Menu Usuários ---\n");
                printf("1 - Cadastrar Usuário\n");
                printf("2 - Editar Usuário\n");
                printf("3 - Remover Usuário\n");
                printf("4 - Listar Usuários\n");
                printf("0 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &subopcao);
                getchar();

                if (subopcao == 1)
                {
                    Usuario u;
                    u.id = idUsuario++;
                    printf("Nome: ");
                    fgets(u.nome, 100, stdin);
                    u.nome[strcspn(u.nome, "\n")] = 0;
                    printf("Email: ");
                    fgets(u.email, 100, stdin);
                    u.email[strcspn(u.email, "\n")] = 0;
                    cadastrarUsuario(&usuarios, u);
                }
                else if (subopcao == 2)
                {
                    char novoNome[100], novoEmail[100];
                    printf("Nome do usuário a editar: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    printf("Novo nome (ou ENTER p/ manter): ");
                    fgets(novoNome, 100, stdin);
                    novoNome[strcspn(novoNome, "\n")] = 0;
                    printf("Novo email (ou ENTER p/ manter): ");
                    fgets(novoEmail, 100, stdin);
                    novoEmail[strcspn(novoEmail, "\n")] = 0;
                    editarUsuarioPorNome(&usuarios, nome,
                                         strlen(novoNome) ? novoNome : NULL,
                                         strlen(novoEmail) ? novoEmail : NULL);
                }
                else if (subopcao == 3)
                {
                    printf("Nome do usuário a remover: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = 0;
                    removerUsuario(&usuarios, nome);
                }
                else if (subopcao == 4)
                {
                    listarUsuarios(&usuarios);
                }
            } while (subopcao != 0);
            break;
        }

    } while (opcao != 0);

    //Liberar a memoria antes de sair
    liberarLivros(&catalogo);
    liberarUsuarios(&usuarios);

    printf("Saindo...\n");
    return 0;
}