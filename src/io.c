#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "io.h"

Ponto* ler_pontos(int *n, int *m, int *G){
    // n -> Número de pontos
    // m -> Tamanho da população
    // G -> Número de gerações

    // Abrindo o input.dat    
    FILE *arquivo = fopen("config/input.dat", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return NULL;
    }
    
    // Lendo o input.dat

    // Primeira linha
    fscanf(arquivo, "%d %d %d", n, m, G);

    Ponto *dados = (Ponto*) malloc((*n) * sizeof(Ponto));
    
    if (dados == NULL) {
        printf("Erro de alocação de memória\n");
        return NULL;
    }

    // Leitura dos pontos
    for (int i = 0; i < *n; i++) {
        fscanf(arquivo, "%f %f", &dados[i].x, &dados[i].y);
    }

    fclose(arquivo);

    return dados;
}

void imprimir_populacao(Individuo *populacao, int m, int i, FILE *arquivo){
    printf("Geração: %d\n", i+1);
    fprintf(arquivo, "Geração %d\n", i+1);
    for (int i = 0; i < m; i++){
        printf("%d-) a: %.2f, b: %.2f, fitness: %.2f\n", i+1, populacao[i].a, populacao[i].b, populacao[i].fitness);
        fprintf(arquivo, "%d: a: %.2f, b: %.2f, fitness: %.2f\n", i+1, populacao[i].a, populacao[i].b, populacao[i].fitness);
    }
}
