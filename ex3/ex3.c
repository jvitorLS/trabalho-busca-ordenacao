#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tempo.h"

typedef struct {
    int mat;
    char nome[200];
} ALUNO;

/* Gera dados ordenados */
void geraOrdenado(ALUNO *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i].mat = i;
        sprintf(v[i].nome, "Aluno %05d", i);
    }
}

/* Gera dados invertidos */
void geraInvertido(ALUNO *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i].mat = n - i - 1;
        sprintf(v[i].nome, "Aluno %05d", n - i - 1);
    }
}

/* Copia vetor */
void copiaVetor(ALUNO *dest, ALUNO *orig, int n) {
    memcpy(dest, orig, n * sizeof(ALUNO));
}

/* Insert Sort */
void insertSort(ALUNO *v, int n) {
    for (int i = 1; i < n; i++) {
        ALUNO chave = v[i];
        int j = i - 1;

        while (j >= 0 && v[j].mat > chave.mat) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

/* Troca */
void troca(ALUNO *a, ALUNO *b) {
    ALUNO temp = *a;
    *a = *b;
    *b = temp;
}

/* Particiona QuickSort */
int particiona(ALUNO *v, int ini, int fim) {
    int pivo = v[fim].mat;
    int i = ini - 1;

    for (int j = ini; j < fim; j++) {
        if (v[j].mat <= pivo) {
            i++;
            troca(&v[i], &v[j]);
        }
    }

    troca(&v[i + 1], &v[fim]);
    return i + 1;
}

/* QuickSort */
void quickSort(ALUNO *v, int ini, int fim) {
    if (ini < fim) {
        int p = particiona(v, ini, fim);
        quickSort(v, ini, p - 1);
        quickSort(v, p + 1, fim);
    }
}

/* Verifica se ordenou */
int estaOrdenado(ALUNO *v, int n) {
    for (int i = 1; i < n; i++) {
        if (v[i].mat < v[i - 1].mat)
            return 0;
    }
    return 1;
}

int main() {
    int tamanhos[] = {5000, 10000, 15000, 20000, 25000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    FILE *arq = fopen("ex3/resultados.csv", "w");
    if (!arq) {
        printf("Erro: nao foi possivel criar o arquivo resultados.csv\n");
        return 1;
    }

    /* Cabeçalho no arquivo */
    fprintf(arq, "Tamanho;Caso;InsertSort(us);QuickSort(us)\n");

    /* Cabeçalho na tela */
    printf("Tamanho;Caso;InsertSort(us);QuickSort(us)\n");

    for (int t = 0; t < numTamanhos; t++) {
        int n = tamanhos[t];

        ALUNO *base = (ALUNO *)malloc(n * sizeof(ALUNO));
        ALUNO *v1 = (ALUNO *)malloc(n * sizeof(ALUNO));
        ALUNO *v2 = (ALUNO *)malloc(n * sizeof(ALUNO));

        if (!base || !v1 || !v2) {
            printf("Erro ao alocar memoria para %d alunos\n", n);
            fclose(arq);
            return 2;
        }

        /* =============================
           CASO 1: Dados ordenados
           ============================= */
        geraOrdenado(base, n);

        copiaVetor(v1, base, n);
        copiaVetor(v2, base, n);

        ulong ti = tempo();
        insertSort(v1, n);
        ti = tempo();

        ulong tq = tempo();
        quickSort(v2, 0, n - 1);
        tq = tempo();

        if (!estaOrdenado(v1, n) || !estaOrdenado(v2, n)) {
            printf("Erro: vetor nao ordenado corretamente\n");
            free(base);
            free(v1);
            free(v2);
            fclose(arq);
            return 3;
        }

        printf("%d;Ordenado;%lu;%lu\n", n, ti, tq);
        fprintf(arq, "%d;Ordenado;%lu;%lu\n", n, ti, tq);

        /* =============================
           CASO 2: Dados invertidos
           ============================= */
        geraInvertido(base, n);

        copiaVetor(v1, base, n);
        copiaVetor(v2, base, n);

        ti = tempo();
        insertSort(v1, n);
        ti = tempo();

        tq = tempo();
        quickSort(v2, 0, n - 1);
        tq = tempo();

        if (!estaOrdenado(v1, n) || !estaOrdenado(v2, n)) {
            printf("Erro: vetor nao ordenado corretamente\n");
            free(base);
            free(v1);
            free(v2);
            fclose(arq);
            return 3;
        }

        printf("%d;Invertido;%lu;%lu\n", n, ti, tq);
        fprintf(arq, "%d;Invertido;%lu;%lu\n", n, ti, tq);

        free(base);
        free(v1);
        free(v2);
    }

    fclose(arq);

    printf("\nArquivo resultados.csv gerado com sucesso!\n");

    return 0;
}