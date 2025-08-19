# README.md
# Lista Duplamente Encadeada de Livros

Este repositório contém minha parte do trabalho de Estrutura de Dados, onde implementei uma lista duplamente encadeada para gerenciar um catálogo de livros em linguagem C.

## Sobre o código


O arquivo [`listaDuplamenteEndadeada.c`](listaDuplamenteEndadeada.c) implementa as seguintes funcionalidades:

- **Cadastro de livros:** Adiciona novos livros ao final da lista.
- **Edição de livros:** Permite editar o título e/ou autor de um livro, buscando pelo título.
- **Remoção de livros:** Remove um livro da lista, buscando pelo título.
- **Listagem de livros:** Exibe todos os livros cadastrados, mostrando ID, título e autor.
- **Busca de livros:** Permite buscar um livro pelo título e exibe mensagem se o livro não for encontrado.
- **Mensagens de biblioteca vazia:** Ao tentar listar, buscar ou remover em uma lista vazia, o programa exibe uma mensagem informando que a biblioteca está vazia.

A estrutura de dados utilizada é uma lista duplamente encadeada, onde cada nó armazena as informações de um livro e ponteiros para o nó anterior e o próximo.

O programa inclui um exemplo de uso no `main`, cadastrando três livros, exibindo a lista, editando e removendo livros, e mostrando o resultado final.

## Como compilar e executar

1. Compile o código:
   ```sh
   gcc listaDuplamenteEndadeada.c -o output/listaDuplamenteEndadeada.exe
   ```

2. Execute o programa:
   ```sh
   ./output/listaDuplamenteEndadeada.exe
   ```

## Estruturas principais

- [`Livro`](listaDuplamenteEndadeada.c): Estrutura que representa um livro.
- [`No`](listaDuplamenteEndadeada.c): Nó da lista duplamente encadeada.
- [`ListaDupla`](listaDuplamenteEndadeada.c): Estrutura que representa a lista.

## Funções implementadas

- [`iniciarlista`](listaDuplamenteEndadeada.c): Inicializa a lista.
- [`cadastrar`](listaDuplamenteEndadeada.c): Adiciona um livro.
- [`editar`](listaDuplamenteEndadeada.c): Edita um livro pelo título.
- [`remover`](listaDuplamenteEndadeada.c): Remove um livro pelo título.
- [`lista`](listaDuplamenteEndadeada.c): Lista todos os livros.
- [`buscarLivro`](listaDuplamenteEndadeada.c): Busca um livro pelo título.

---
Trabalho desenvolvido para a disciplina de Estrutura de Dados.