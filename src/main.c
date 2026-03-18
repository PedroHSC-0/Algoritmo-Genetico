#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){ 
    int n, m, G;
    Ponto *dados = ler_pontos(&n, &m, &G);

    // Printar as sementes
    printf("Sementes\n");
    for (int i = 0; i < n; i++) {
        printf("%d - [%.2f, %.2f]\n", i+1, dados[i].x, dados[i].y);
    }

    // Criar População
    Individuo *populacao = criar_populacao(m);

    calcular_fitness(populacao, m, dados, n);

    // Ordenar os melhores indivíduos
     
    // Encontrar o melhor indivíduo
    int i_melhor;
    Individuo melhor = melhor_individuo(populacao, m, &i_melhor);
    
    //printf("\nO Melhor: %d-) %f\n", i_melhor, populacao[i_melhor].fitness);

    // Evolução
    imprimir_populacao(populacao, m, );

    // Liberar memória

    free(dados);
    free(populacao);

    return 0;
}