#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------ESTRUTURAS------------------------
// estrutura variaveis
typedef struct
{
    int id;
    char titulo[100];
    char autor[100];

} Livro;
typedef struct
{
    int id;
    char nome[100];
    char email[100];

} Usuario;

// estrutura No
typedef struct Nolivro
{
    Livro dado;
    struct Nolivro *anterior;
    struct Nolivro *proximo;
} Nolivro;

typedef struct Nousuario
{
    Usuario dado;
    struct Nousuario *proximo;
    struct Nousuario *anterior;

} Nousuario;

typedef struct {
    Nolivro* inicio;
    Nolivro* fim;
}ListaLivro;

typedef struct {
    Nousuario *inicio;
    Nousuario *fim;
} ListaUsuario;

//------------------------FUNÇÕES PARA LIVROS------------------------

void iniciarlivro(ListaLivro *Lista)
{
    Lista->inicio = NULL;
    Lista->fim = NULL;
}
// cadastra livro
void cadastrarlivro(ListaLivro *lista, Livro livro)
{
    Nolivro* novo = (Nolivro*)malloc(sizeof(Nolivro));
    if (novo)
    {
        novo->dado = livro;
        novo->proximo = NULL;
        novo->anterior = lista->fim;

        if (lista->inicio == NULL)
        {
            lista->inicio = novo;
        }
        else
        {
            lista->fim->proximo = novo;
        }
        lista->fim = novo;
    }
    else
    {
        printf("Erro ao alocar memoria");
    }
}

// edita esse livro por titulo
int editarLivro(ListaLivro *lista, char *titulo, char *novoTitulo, char *novoAutor)
{
    Nolivro* atual = lista->inicio;
    while (atual != NULL)
    {
        // achar pelo nome
        if (strcmp(atual->dado.titulo, titulo) == 0)
        {
            if (novoTitulo != NULL)
                strcpy(atual->dado.titulo, novoTitulo);
            if (novoAutor != NULL)
                strcpy(atual->dado.autor, novoAutor);
            return 1;
        }
        atual = atual->proximo; // avança
    }
    return 0;
}

// remove um livro por titulo
int removerLivro(ListaLivro *lista, char *titulo)
{
    Nolivro* atual = lista->inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->dado.titulo, titulo) == 0)
        {

            if (atual->anterior != NULL)
                atual->anterior->proximo = atual->proximo;
            else
                lista->inicio = atual->proximo;
            if (atual->proximo != NULL)
                atual->proximo->anterior = atual->anterior;
            else
                lista->fim = atual->anterior;

            free(atual);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

// Uma lista de todos os livros
void listarLivros(ListaLivro* lista)
{
    Nolivro* atual = lista->inicio;
    if (atual == NULL){
        printf("Nenhum usuario cadastrado.\n");
        return;
    }
    while (atual != NULL)
    {
        printf("%d - %s (%s)\n", atual->dado.id, atual->dado.titulo, atual->dado.autor);
        atual = atual->proximo;
    }
}
//------------------------FUNÇÕES PARA USUARIOS------------------------

void iniciarUsuarios(ListaUsuario* lista){
    lista->fim=NULL;
    lista->inicio=NULL;
}

void cadastrarUsuario(ListaUsuario* lista, Usuario usuario){
    Nousuario* novo=(Nousuario*)malloc(sizeof(Nousuario));
    if (novo){
        novo->dado = usuario;
        novo->proximo = NULL;
        novo->anterior = lista->fim;

        if (lista->inicio == NULL){
            lista->inicio = novo;
        }else{
            lista->fim->proximo = novo;
        }
        lista->fim = novo;
    }else{
        printf("Erro ao alocar memoria. \n");
    }
}

int editarUsuarioPorNome(ListaUsuario* lista, char* nome,char* novoNome, char* novoEmail){
    Nousuario* atual = lista->inicio;
    while (atual != NULL){
        if (strcmp(atual->dado.nome, nome)==0){
            if (novoNome != NULL)
                strcpy(atual->dado.nome, novoNome);
            if (novoEmail != NULL)
                strcpy(atual->dado.email, novoEmail);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

int removerUsuario(ListaUsuario* lista, char* nome){
    Nousuario* atual = lista->inicio;
    while (atual != NULL){
        if (strcmp(atual->dado.nome, nome)==0){
            if (atual->anterior != NULL){
                atual->anterior->proximo = atual->proximo;
            }else{
                lista->inicio = atual->proximo;
            }
            if (atual->proximo != NULL){
                atual->proximo->anterior = atual->anterior;
            }else{
                lista->fim = atual->anterior;
            }
            free(atual);
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void listarUsuarios(ListaUsuario* lista){
    Nousuario* atual = lista->inicio;
    if (atual == NULL){
        printf("%d - %s (%s) \n",atual->dado.id, atual->dado.nome, atual->dado.email);
        atual = atual->proximo;
    }
}
// exemplo de  teste

int main()
{
    ListaLivro catalogo;
    ListaUsuario usuarios;
    iniciarlivro(&catalogo);
    iniciarUsuarios(&usuarios);

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

    printf("Saindo...\n");
    return 0;
}