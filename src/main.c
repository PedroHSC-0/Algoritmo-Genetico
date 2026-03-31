#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "io.h"
#include "genetico.h"

int main(){ 
    int n, m, G;
    Ponto *dados = ler_pontos(&n, &m, &G);

    // Criar População
    Individuo *populacao = criar_populacao(m);

    calcular_fitness(populacao, m, dados, n);
    ordenar_populacao(populacao, m);

    FILE *arquivo = fopen("config/output.dat", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    // Evolução
    // Loop das gerações
    for (int i = 0; i < G; i++){
        // Fazer mutação dos melhores indivíduos

        mutacao(populacao, m);

        calcular_fitness(populacao, m, dados, n);
        ordenar_populacao(populacao, m);

        imprimir_populacao(populacao, m, i, arquivo);
    }

    // Liberar memória
    fclose(arquivo);
    free(dados);
    free(populacao);

    return 0;
}