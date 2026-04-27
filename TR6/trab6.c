#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 200

typedef struct ARV {
    int mat;
    char nome[STRMAX + 1];
    char endereco[STRMAX * 10];
    char cpf[20];
    int bal;
    struct ARV *e;
    struct ARV *d;
} AVL;

/* Remove \n do final */
void removeQuebraLinha(char *s) {
    size_t tam = strlen(s);
    if (tam > 0 && s[tam - 1] == '\n') {
        s[tam - 1] = '\0';
    }
}

/* Retorna altura do nó */
int altura(AVL *r) {
    if (r == NULL) return 0;

    int he = altura(r->e);
    int hd = altura(r->d);

    return (he > hd ? he : hd) + 1;
}

/* Atualiza fator de balanceamento */
void atualizaBal(AVL *r) {
    if (r == NULL) return;

    int he = altura(r->e);
    int hd = altura(r->d);

    r->bal = hd - he; // fb = altura(direita) - altura(esquerda)
}

/* Cria novo nó */
AVL *criaNo(int mat, char *nome, char *endereco, char *cpf) {
    AVL *novo = (AVL *)malloc(sizeof(AVL));
    if (!novo) return NULL;

    novo->mat = mat;
    strcpy(novo->nome, nome);
    strcpy(novo->endereco, endereco);
    strcpy(novo->cpf, cpf);

    novo->e = NULL;
    novo->d = NULL;
    novo->bal = 0;

    return novo;
}

/* Inserção por nome (chave) */
AVL *insere(AVL *r, int mat, char *nome, char *endereco, char *cpf) {
    if (r == NULL) {
        return criaNo(mat, nome, endereco, cpf);
    }

    int cmp = strcmp(nome, r->nome);

    if (cmp < 0) {
        r->e = insere(r->e, mat, nome, endereco, cpf);
    } else {
        r->d = insere(r->d, mat, nome, endereco, cpf);
    }

    atualizaBal(r);
    return r;
}

/* Busca por nome (rápida) */
AVL *buscaNome(AVL *r, char *nome) {
    if (r == NULL) return NULL;

    int cmp = strcmp(nome, r->nome);

    if (cmp == 0) return r;
    if (cmp < 0) return buscaNome(r->e, nome);
    return buscaNome(r->d, nome);
}

/* Busca por matrícula (lenta, percorre tudo) */
AVL *buscaMatricula(AVL *r, int mat) {
    if (r == NULL) return NULL;

    if (r->mat == mat) return r;

    AVL *p = buscaMatricula(r->e, mat);
    if (p != NULL) return p;

    return buscaMatricula(r->d, mat);
}

/* Percurso em ordem */
void emOrdem(AVL *r) {
    if (r == NULL) return;

    emOrdem(r->e);
    printf("Mat: %d | Nome: %s | Bal: %d\n", r->mat, r->nome, r->bal);
    emOrdem(r->d);
}

/* Percurso pré-ordem */
void preOrdem(AVL *r) {
    if (r == NULL) return;

    printf("Mat: %d | Nome: %s | Bal: %d\n", r->mat, r->nome, r->bal);
    preOrdem(r->e);
    preOrdem(r->d);
}

/* Percurso pós-ordem */
void posOrdem(AVL *r) {
    if (r == NULL) return;

    posOrdem(r->e);
    posOrdem(r->d);
    printf("Mat: %d | Nome: %s | Bal: %d\n", r->mat, r->nome, r->bal);
}

/* Libera todos os nós */
void liberaTudo(AVL *r) {
    if (r == NULL) return;

    liberaTudo(r->e);
    liberaTudo(r->d);
    free(r);
}

/* Mostra dados completos */
void mostraAluno(AVL *a) {
    if (a == NULL) {
        printf("Aluno nao encontrado.\n");
        return;
    }

    printf("\n=== DADOS DO ALUNO ===\n");
    printf("Matricula: %d\n", a->mat);
    printf("Nome: %s\n", a->nome);
    printf("Endereco: %s\n", a->endereco);
    printf("CPF: %s\n", a->cpf);
    printf("Balanceamento (bal): %d\n", a->bal);
}

/* Leitura do arquivo */
AVL *lerArquivo(AVL *raiz, char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro: nao foi possivel abrir o arquivo %s\n", nomeArquivo);
        return raiz;
    }

    char linha[STRMAX * 10];
    int mat;
    char nome[STRMAX + 1];
    char endereco[STRMAX * 10];
    char cpf[20];

    while (fgets(linha, sizeof(linha), f)) {
        removeQuebraLinha(linha);

        if (strlen(linha) == 0) continue;

        mat = atoi(linha);

        if (!fgets(nome, sizeof(nome), f)) break;
        removeQuebraLinha(nome);

        if (!fgets(endereco, sizeof(endereco), f)) break;
        removeQuebraLinha(endereco);

        if (!fgets(cpf, sizeof(cpf), f)) break;
        removeQuebraLinha(cpf);

        raiz = insere(raiz, mat, nome, endereco, cpf);
    }

    fclose(f);
    return raiz;
}

int main(int argc, char *argv[]) {
    AVL *raiz = NULL;

    if (argc < 2) {
        printf("Uso: %s dados.txt\n", argv[0]);
        return 1;
    }

    raiz = lerArquivo(raiz, argv[1]);

    printf("Arquivo carregado com sucesso!\n");

    int opcao;
    char nomeBusca[STRMAX + 1];
    int matBusca;
    AVL *res;

    do {
        printf("\n=============================\n");
        printf("MENU\n");
        printf("1 - Percurso Em-Ordem\n");
        printf("2 - Percurso Pre-Ordem\n");
        printf("3 - Percurso Pos-Ordem\n");
        printf("4 - Buscar por Nome\n");
        printf("5 - Buscar por Matricula\n");
        printf("0 - Sair\n");
        printf("=============================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar \n do buffer

        switch (opcao) {
            case 1:
                printf("\n--- EM ORDEM ---\n");
                emOrdem(raiz);
                break;

            case 2:
                printf("\n--- PRE ORDEM ---\n");
                preOrdem(raiz);
                break;

            case 3:
                printf("\n--- POS ORDEM ---\n");
                posOrdem(raiz);
                break;

            case 4:
                printf("Digite o nome completo: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                removeQuebraLinha(nomeBusca);

                res = buscaNome(raiz, nomeBusca);
                mostraAluno(res);
                break;

            case 5:
                printf("Digite a matricula: ");
                scanf("%d", &matBusca);

                res = buscaMatricula(raiz, matBusca);
                mostraAluno(res);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    liberaTudo(raiz);
    printf("Memoria liberada com sucesso.\n");

    return 0;
}
