# Trabalho Final de Estrutura de Dados

Este repositório contém minha parte do **trabalho final da disciplina de Estrutura de Dados**, onde desenvolvi um sistema em C para gerenciamento de livros e usuários utilizando listas duplamente encadeadas.

## Sobre o projeto

O sistema permite cadastrar, editar, remover e listar livros e usuários. Todas as operações são realizadas por meio de um menu interativo no terminal. O objetivo é demonstrar o uso prático de listas duplamente encadeadas para manipulação dinâmica de dados.

### Funcionalidades implementadas

#### Livros
- **Cadastro:** Adiciona novos livros ao catálogo.
- **Edição:** Permite editar título e autor de um livro, buscando pelo título.
- **Remoção:** Remove um livro pelo título.
- **Listagem:** Exibe todos os livros cadastrados.

#### Usuários
- **Cadastro:** Adiciona novos usuários.
- **Edição:** Permite editar nome e email do usuário, buscando pelo nome.
- **Remoção:** Remove um usuário pelo nome.
- **Listagem:** Exibe todos os usuários cadastrados.

### Estruturas utilizadas

- `Livro` e `Usuario`: Estruturas que armazenam os dados de cada entidade.
- `Nolivro` e `Nousuario`: Nós das listas duplamente encadeadas.
- `ListaLivro` e `ListaUsuario`: Estruturas que representam as listas.

### Organização dos arquivos

- `main.c`: Menu principal e lógica de interação.
- `livros.c` / `livros.h`: Funções e estruturas para manipulação de livros.
- `usuario.c` / `usuario.h`: Funções e estruturas para manipulação de usuários.
- `structs.h`: Definição das estruturas de dados utilizadas.

## Como compilar e executar

1. Compile todos os arquivos juntos:
   ```sh
   gcc main.c livros.c usuario.c -o output/main.exe
   ```

2. Execute o programa:
   ```sh
   ./output/main.exe
   ```
   Ou, no Windows:
   ```sh
   output\main.exe
   ```

## Observações

- O projeto foi desenvolvido com foco em praticar conceitos de listas duplamente encadeadas, manipulação de ponteiros e modularização de código em C.
- Este trabalho faz parte da avaliação final da disciplina de Estrutura de Dados.

---

