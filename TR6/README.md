# Trabalho 6 - AVL (Árvore Binária de Busca com Fator de Balanceamento)

Este projeto implementa uma estrutura de árvore AVL (sem rotações), utilizando como chave o campo **nome**.
O objetivo é permitir inserção de alunos, percursos na árvore, buscas e remoção completa dos nós.

> Importante: conforme solicitado pelo professor, o programa **não realiza rotações AVL**, apenas mantém o campo `bal` atualizado.

---

## Estrutura do Aluno

Cada nó da árvore contém:

- matrícula (int)
- nome (string)
- endereço (string)
- cpf (string)
- bal (fator de balanceamento)
- ponteiros para esquerda e direita

A chave da árvore é o campo **nome**.

---

## Arquivos do projeto

- `trab6.c` → código principal do trabalho
- `dados.txt` → arquivo exemplo com alunos para teste

---

## Como compilar e rodar

No Linux:

```bash
gcc TR6/trab6.c -o TR6/trab6 -> para compilar 

./TR6/trab6 dados.txt -> para rodar o projeto
