#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "funcoes.h"

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

Individuo* criar_populacao(int m){
    srand(time(NULL)); 
    Individuo *populacao = (Individuo*) malloc(m * sizeof(Individuo));

    if (populacao == NULL) {
        printf("Erro de alocação de memória\n");
        return NULL;
    }

    for (int i = 0; i < m;i++){
        populacao[i].a = (rand() % 1001) / 100.0;
        populacao[i].b = (rand() % 1001) / 100.0;
    }
    return populacao;
}

void calcular_fitness(Individuo *populacao, int m, Ponto *dados, int n){
    float y_reta, erro_total, erro;

    // Cálculo do fitness
    for(int i = 0; i < m; i++){
        erro_total = 0;

        for(int j = 0; j < n; j++){

            // Cálculo da reta
            y_reta = populacao[i].a * dados[j].x + populacao[i].b;
            
            // Cálculo do erro
            erro = dados[j].y - y_reta;
            if (erro < 0) erro = erro * (-1);
            erro_total += erro;
        
        }
        
        populacao[i].fitness = erro_total / n;
    }
}

Individuo melhor_individuo(Individuo *populacao, int m, int *i_melhor){
    float min = populacao[0].fitness;
    min = populacao[0].fitness;
    for(int i = 1; i < m; i++){
        if (populacao[i].fitness < min){
            min = populacao[i].fitness;
            *i_melhor = i;
        }
    }
    return populacao[*i_melhor];
}

void imprimir_pontos(Ponto *dados, int n){
    printf("Sementes:\n");
    for (int i = 0;i < n; i++) {
        printf("%d -) [%.2f, %.2f] \n", i+1, dados[i].x, dados[i].y);
    }
}

void imprimir_populacao(Individuo *populacao, int m, int G_atual, int G_total){
    printf("População: :\n");
    
    for (int i = 0; i < m; i++){
        printf("%d-) a: %.2f, b: %.2f, fitness: %.2f\n", i+1, populacao[i].a, populacao[i].b, populacao[i].fitness);
    }

    FILE *arquivo = fopen("config/output.dat", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return NULL;
    }

    for(int i = 0; i < G_total; i++){
        fprintf(arquivo, "%d-) a: %.2f, b: %.2f| fitness %.2f\n");
    }

    fclose(arquivo);
}

void ordenar_populacao(Individuo *populacao, int n){
    
}