# Trabalho - Busca Sequencial e Busca Binária

## Como compilar
gcc main.c -o prog

## Como executar
./prog

## Testes realizados
Foram testados tamanhos: 100, 1000, 5000, 10000.
O valor buscado foi 7 (ímpar, portanto não existe).

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
