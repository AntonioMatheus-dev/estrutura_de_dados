#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura variaveis
typedef struct 
{
    int id;
    char titulo[100];
    char autor[100];

}Livro;

//estrutura No
typedef struct No
{
    Livro dado;
    struct No* anterior;
    struct No* proximo;
}No;

//estrutura lista dupla
typedef struct {

    No* inicio;
    No* fim;
}ListaDupla;

//inicia lista
void iniciarlista(ListaDupla* lista){
    lista->inicio = NULL;
    lista->fim=NULL;
}

//cadastra livro
void cadastrar(ListaDupla* lista, Livro livro){
    No* novo= (No*)malloc(sizeof(No));

    if (novo){
     novo->dado = livro;
     novo->proximo = NULL;
     novo -> anterior = lista->fim;

     if (lista->inicio == NULL){
        lista->inicio = novo;
     }else{
        lista->fim->proximo = novo;
     }
     lista->fim = novo;
    }else{
        printf("Erro ao alocar memoria");
    }
}

//edita esse livro por titulo
int editar(ListaDupla* lista, char* titulo, char* novoTitulo, char* novoAutor){
    No* atual = lista->inicio;
    while (atual != NULL){
        //achar pelo nome
        if (strcmp(atual->dado.titulo, titulo) == 0){
            if (novoTitulo != NULL)
                strcpy(atual->dado.titulo, novoTitulo);
            if (novoAutor != NULL)
                strcpy(atual->dado.autor, novoAutor);
            return 1;
        }
        atual = atual->proximo;//avança
}
return 0;
}

//remove um livro por titulo
int remover(ListaDupla* lista, char* titulo){
    No* atual = lista->inicio;
    while (atual != NULL){
        if (strcmp(atual->dado.titulo, titulo)==0){

            if (atual->anterior != NULL)
                atual->anterior->proximo = atual->proximo;
            else
                lista->inicio = atual->proximo;
            if(atual->proximo != NULL)
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

//Uma lista de todos os livros
void lista(ListaDupla* lista){
    No* atual = lista->inicio;
    while (atual != NULL)
    {
        printf("%d - %s (%s)\n", atual->dado.id, atual->dado.titulo, atual->dado.autor);
        atual = atual->proximo;
    }
}

//exemplo de  teste
int main()
{
    ListaDupla catalogo;
    iniciarlista(&catalogo);

    Livro l1 = {1, "Dom Casmurro", "Machado de Assis"};
    Livro l2 = {2, "1984", "George Orwell"};
    Livro l3 = {3, "O Alienista", "Machado de Assis"};

    cadastrar(&catalogo, l1);
    cadastrar(&catalogo, l2);
    cadastrar(&catalogo, l3);

    printf("Lista inicial:\n");
    lista(&catalogo);

    editar(&catalogo, "1984", "Mil Novecentos e Oitenta e Quatro", NULL);
    remover(&catalogo, "Dom Casmurro");

    printf("\nDepois das alterações:\n");
    lista(&catalogo);

    return 0;
}
