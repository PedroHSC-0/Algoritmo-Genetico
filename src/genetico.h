#ifndef GENETICO_H
#define GENETICO_H

Individuo* criar_populacao(int m);

void calcular_fitness(Individuo *populacao, int m, Ponto *dados, int n);

int comparar_fitness(const void *a, const void *b);

void ordenar_populacao(Individuo *populacao, int m);

void imprimir_populacao(Individuo *populacao, int m, int i, FILE *arquivo);

void mutacao(Individuo *populacao, int m);

#endif