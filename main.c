#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Busca sequencial */
int buscaSequencial(int *vet, int tam, int valor, int *comparacoes) {
    int i;
    *comparacoes = 0;

    for (i = 0; i < tam; i++) {
        (*comparacoes)++;
        if (vet[i] == valor)
            return i;
    }

    return -1;
}

/* Busca binária (vetor deve estar ordenado) */
int buscaBinaria(int *vet, int tam, int valor, int *comparacoes) {
    int ini = 0, fim = tam - 1;
    *comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        (*comparacoes)++;

        if (vet[meio] == valor)
            return meio;
        else if (valor < vet[meio])
            fim = meio - 1;
        else
            ini = meio + 1;
    }

    return -1;
}

/* Função auxiliar para trocar elementos */
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* QuickSort (implementação própria) */
int particiona(int *vet, int ini, int fim) {
    int pivo = vet[fim];
    int i = ini - 1;
    int j;

    for (j = ini; j < fim; j++) {
        if (vet[j] <= pivo) {
            i++;
            troca(&vet[i], &vet[j]);
        }
    }

    troca(&vet[i + 1], &vet[fim]);
    return i + 1;
}

void quickSort(int *vet, int ini, int fim) {
    if (ini < fim) {
        int p = particiona(vet, ini, fim);
        quickSort(vet, ini, p - 1);
        quickSort(vet, p + 1, fim);
    }
}

int main() {
    int *vet;
    int tam = 0, i;
    int valor;
    int pos;
    int comparacoesA, comparacoesB;
    clock_t inicio, fim;
    double tempoBuscaA, tempoOrdenacao, tempoBuscaB;

    printf("Quantos elementos?\n");
    scanf("%d", &tam);

    if (tam <= 0) {
        printf("ERRO tam tem que ser positivo\n");
        return 1;
    }

    vet = (int *)malloc(tam * sizeof(int));
    if (vet == NULL) {
        printf("ERRO na alocação de %d elementos\n", tam);
        return 2;
    }

    /* Preenchendo o vetor */
    for (i = 0; i < tam; i++) {
        vet[i] = (tam - i) * 2;
    }

    printf("\nDigite um valor para buscar (pares existem, impares nao): ");
    scanf("%d", &valor);

    /* ===============================
       A) Busca Sequencial
       =============================== */
    inicio = clock();
    pos = buscaSequencial(vet, tam, valor, &comparacoesA);
    fim = clock();

    tempoBuscaA = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (pos != -1)
        printf("\n[A] Busca Sequencial: valor encontrado na posicao %d\n", pos);
    else
        printf("\n[A] Busca Sequencial: valor NAO encontrado\n");

    printf("[A] Comparacoes feitas: %d\n", comparacoesA);
    printf("[A] Tempo gasto: %.6f segundos\n", tempoBuscaA);

    /* ===============================
       B) Ordenacao (QuickSort)
       =============================== */
    inicio = clock();
    quickSort(vet, 0, tam - 1);
    fim = clock();

    tempoOrdenacao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n[B] Vetor ordenado com QuickSort\n");
    printf("[B] Tempo gasto na ordenacao: %.6f segundos\n", tempoOrdenacao);

    /* ===============================
       B) Busca Binaria
       =============================== */
    inicio = clock();
    pos = buscaBinaria(vet, tam, valor, &comparacoesB);
    fim = clock();

    tempoBuscaB = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if (pos != -1)
        printf("\n[B] Busca Binaria: valor encontrado na posicao %d\n", pos);
    else
        printf("\n[B] Busca Binaria: valor NAO encontrado\n");

    printf("[B] Comparacoes feitas: %d\n", comparacoesB);
    printf("[B] Tempo gasto: %.6f segundos\n", tempoBuscaB);

    free(vet);

    return 0;
}

/*
===========================
RELATORIO / QUESTOES
===========================

Questao: Quantos testes serao feitos para descobrir que um valor nao existe no caso da versao A?

Resposta:
Na busca sequencial (A), se o valor nao existir, o algoritmo percorre todos os elementos.
Logo serao feitos tam testes (comparacoes).
Complexidade: O(n)

Exemplo:
tam=100 → 100 comparações na busca sequencial
tam=1000 → 1000 comparações
tam=10000 → 10000 comparações
--------------------------------------------

Questao: E no caso da B? Mudou alguma coisa?

Resposta:
Na busca binaria (B), o numero de comparacoes eh muito menor.
Ela reduz o espaco de busca pela metade a cada passo.

Numero de comparacoes no pior caso: aproximadamente log2(tam)

Complexidade: O(log n)

Exemplo:
tam=100 → log2(100) ≈ 7
tam=1000 → log2(1000) ≈ 10
tam=10000 → log2(10000) ≈ 14

--------------------------------------------

Questao: Percebe alguma lentidao no algoritmo a medida que o tamanho do vetor aumenta?

Resposta:
Sim. 

- Na versao A (busca sequencial), o tempo cresce linearmente (O(n)).
  Conforme aumenta o tamanho do vetor, aumenta diretamente o numero de comparacoes.

- Na versao B, a busca binaria eh muito rapida, mas existe o custo da ordenacao.
  O QuickSort tem complexidade media O(n log n). 

Para tamanhos grandes (5000, 10000 ou mais), o tempo de ordenacao pode ser maior
que o tempo de busca.

A parte mais lenta para grandes entradas geralmente sera a ORDENACAO.

--------------------------------------------

Resumo:

(A) Busca sequencial:
    - Pior caso: n comparacoes
    - Complexidade: O(n)

(B) Ordenacao + busca binaria:
    - Ordenacao: O(n log n)
    - Busca: O(log n)
    - Total: O(n log n) (dominada pela ordenacao)

*/