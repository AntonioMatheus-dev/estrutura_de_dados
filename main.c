#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "catalogo.h"
#include "usuarios.h"
#include "emprestimos.h"
#include "filadeespera.h"
#include "acoesdapilha.h"
#include "relatorios.h"

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    Catalogo catalogo;
    ListaUsuarios usuarios;
    ListaEmprestimos emprestimos;
    FilaEspera fila;
    PilhaAcoes acoes;

    iniciarCatalogo(&catalogo);
    iniciarUsuarios(&usuarios);
    iniciarEmprestimos(&emprestimos);
    iniciarFila(&fila);
    iniciarPilha(&acoes);

    int opcao;
    int idLivroCounter = 1;
    int idUsuarioCounter = 1;

    do
    {
        printf("\n============== MENU PRINCIPAL ==============\n");
        printf("1. Gerenciar Catalogo de Livros\n");
        printf("2. Gerenciar Usuarios\n");
        printf("3. Emprestar Livro\n");
        printf("4. Devolver Livro\n");
        printf("5. Ver Fila de Espera\n");
        printf("6. Gerar Relatorio de Mais Emprestados\n");
        printf("7. Desfazer Ultima Acao\n");
        printf("0. Sair\n");
        printf("==========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
        {
            listarCatalogo(&catalogo);
            printf("\n--- Submenu Catalogo ---\n");
            printf("1. Cadastrar Novo livro\n");
            printf("2. Buscar livros - ID\n");
            printf("3. Buscar livros - Titulo\n");
            printf("4. Ordenar livros\n");
            printf("5. Remover livro\n");
            printf("0. Voltar.\n");
            printf("Escolha: ");
            int subOp;
            scanf("%d", &subOp);
            limparBuffer();
            if (subOp == 1)
            {
                Livro l;
                l.id = idLivroCounter++;
                printf("Titulo: ");
                fgets(l.titulo, 100, stdin);
                l.titulo[strcspn(l.titulo, "\n")] = 0;
                printf("Autor: ");
                fgets(l.autor, 100, stdin);
                l.autor[strcspn(l.autor, "\n")] = 0;
                cadastrarLivro(&catalogo, l, &acoes);
            }
            else if (subOp == 2)
            {
                int idBusca;
                printf("Digite o ID do livro: ");
                scanf("%d", &idBusca);
                limparBuffer();
                Nolivro *resultado = buscarLivroPorId(&catalogo, idBusca);
                if (resultado)
                {
                    printf("\n Livro encontrado: %s (ID: %d)\n", resultado->dado.titulo, resultado->dado.id);
                }
                else
                {
                    printf("Livro nao encontrado.\n");
                }
            }
            else if (subOp == 3)
            {
                char tituloBusca[100];
                printf("Digite o titulo do livro: ");
                fgets(tituloBusca, 100, stdin);
                tituloBusca[strcspn(tituloBusca, "\n")] = 0;
                Nolivro *resultado = buscarLivroPorTitulo(&catalogo, tituloBusca);
                if (resultado)
                {
                    printf("Livro encontrado: %s (ID: %d)\n", resultado->dado.titulo, resultado->dado.id);
                }
                else
                {
                    printf("Livro nao encontrado.\n");
                }
            }
            else if (subOp == 4)
            {
                ordenarCatalogo(&catalogo);
            }
            else if (subOp == 5)
            {
                int idRemover;
                printf("Digite o ID do livro a remover: ");
                scanf("%d", &idRemover);
                limparBuffer();
                int resultado = removerLivro(&catalogo, idRemover);
                if (resultado)
                    printf("Livro removido com sucesso!\n");
                else
                    printf("Nao foi possivel remover o livro.\n");
            }
            break;
        }
        case 2:
        {
            printf("\n--- Submenu Usuarios ---\n");
            printf("1. Cadastrar Novo Usuario\n");
            printf("2. Listar Usuarios\n");
            printf("3. Buscar Usuario por ID\n");
            printf("4. Liberar Usuarios\n");
            printf("0. Voltar\n");
            printf("Escolha: ");
            int subOp;
            scanf("%d", &subOp);
            limparBuffer();
            if (subOp == 1)
            {
                Usuario u;
                u.id = idUsuarioCounter++;
                printf("Nome: ");
                fgets(u.nome, 100, stdin);
                u.nome[strcspn(u.nome, "\n")] = 0;
                printf("Email: ");
                fgets(u.email, 100, stdin);
                u.email[strcspn(u.email, "\n")] = 0;
                cadastrarUsuario(&usuarios, u);
            }
            else if (subOp == 2)
            {
                listarUsuarios(&usuarios);
            }
            else if (subOp == 3)
            {
                int idBusca;
                printf("Digite o ID do usuario: ");
                scanf("%d", &idBusca);
                limparBuffer();
                Nousuario *resultado = buscarUsuarioPorId(&usuarios, idBusca);
                if (resultado)
                    printf("Usuario encontrado: %s (ID: %d)\n", resultado->dado.nome, resultado->dado.id);
                else
                    printf("Usuario nao encontrado.\n");
            }
            else if (subOp == 4)
            {
                liberarUsuarios(&usuarios);
                printf("Todos os usuarios foram liberados (removidos da memoria).\n");
            }
            break;
        }
        case 3:
        {
            int idU, idL;
            printf("--- Emprestar Livro ---\n");
            listarCatalogo(&catalogo);
            listarUsuarios(&usuarios);
            printf("Digite o ID do usuario: ");
            scanf("%d", &idU);
            printf("Digite o ID do livro: ");
            scanf("%d", &idL);
            limparBuffer();
            emprestarLivro(&catalogo, &usuarios, &emprestimos, &fila, &acoes, idU, idL);
            break;
        }
        case 4:
        {
            int idL;
            printf("--- Devolver Livro ---\n");
            listarCatalogo(&catalogo);
            printf("Digite o ID do livro a ser devolvido: ");
            scanf("%d", &idL);
            limparBuffer();
            devolverLivro(&catalogo, &usuarios, &emprestimos, &fila, &acoes, idL);
            break;
        }
        case 5:
        {
            printf("\n--- Fila de Espera ---\n");
            listarFila(&fila);
            printf("1. Adicionar usuario à fila de espera por livro\n");
            printf("2. Atender próximo da fila ao devolver livro\n");
            printf("0. Voltar\n");
            printf("Escolha: ");
            int filaOp;
            scanf("%d", &filaOp);
            limparBuffer();
            if (filaOp == 1)
            {
                int idLivro, idUsuario;
                printf("Digite o ID do livro: ");
                scanf("%d", &idLivro);
                printf("Digite o ID do usuario: ");
                scanf("%d", &idUsuario);
                limparBuffer();
                Nolivro *livro = buscarLivroPorId(&catalogo, idLivro);
                if (livro)
                {
                    if (livro->dado.vezesEmprestado >= 3)
                    {
                        enfileirar(&fila, idLivro, idUsuario);
                        printf("Livro atingiu limite de 3 empréstimos. Usuário adicionado à fila de espera.\n");
                    }
                    else
                    {
                        printf("Livro ainda não atingiu o limite de empréstimos.\n");
                    }
                }
                else
                {
                    printf("Livro não encontrado.\n");
                }
            }
            else if (filaOp == 2)
            {
                int idLivro, idUsuario = -1;
                printf("Digite o ID do livro devolvido: ");
                scanf("%d", &idLivro);
                limparBuffer();
                if (desenfileirar(&fila, idLivro, &idUsuario))
                {
                    printf("Usuário (ID %d) pode pegar o livro (ID %d) agora!\n", idUsuario, idLivro);
                }
                else
                {
                    printf("Nenhum usuário aguardando por esse livro na fila.\n");
                }
            }
            break;
        }
        case 6:
        {
            printf("\n--- Submenu Relatórios/Empréstimos ---\n");
            printf("1. Gerar relatório de mais emprestados\n");
            printf("2. Liberar empréstimos\n");
            printf("0. Voltar\n");
            printf("Escolha: ");
            int relOp;
            scanf("%d", &relOp);
            limparBuffer();
            if (relOp == 1)
            {
                gerarRelatorioMaisEmprestados(&catalogo);
            }
            else if (relOp == 2)
            {
                liberarEmprestimos(&emprestimos);
                printf("Todos os empréstimos foram liberados\n");
            }
            break;
        }
        case 7:
        {
            printf("\n--- Submenu Pilha de Ações ---\n");
            printf("1. Desfazer última ação\n");
            printf("2. Liberar pilha de ações\n");
            printf("0. Voltar\n");
            printf("Escolha: ");
            int pilhaOp;
            scanf("%d", &pilhaOp);
            limparBuffer();
            if (pilhaOp == 1)
            {
                desfazerUltimaAcao(&catalogo, &usuarios, &emprestimos, &fila, &acoes);
            }

            else if (pilhaOp == 2)
            {
                liberarPilha(&acoes);
                printf("Pilha de ações liberada.\n");
            }
            break;
        }
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opcao invalida\n");
        }

    } while (opcao != 0);

    liberarCatalogo(&catalogo);
    liberarUsuarios(&usuarios);
    liberarEmprestimos(&emprestimos);
    liberarFila(&fila);
    liberarPilha(&acoes);

    printf("Sistema finalizado. Memoria liberada.\n");

    return 0;
}