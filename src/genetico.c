#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "model.h"
#include "genetico.h"

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

int comparar_fitness(const void *a, const void *b){
    Individuo *ind_a = (Individuo *)a;
    Individuo *ind_b = (Individuo *)b;
    
    if (ind_a->fitness < ind_b->fitness) return -1;
    if (ind_a->fitness > ind_b->fitness) return  1;
    return 0;
}

void ordenar_populacao(Individuo *populacao, int m){
    qsort(populacao, m, sizeof(Individuo), comparar_fitness);
}

void mutacao(Individuo *populacao, int m){
    int metade;

    if (m % 2 == 0) {metade = m/2;}
    else {metade = m / 2 + 1;}
    int mut_a = 0;

    float a_pai, b_pai;

    // Pegar a quantidade de indivíduos, e pega primeira metade, onde estão os melhores
    // Copiar os dados mutados dos melhores para a outra metade, onde estão os piores
    // Para cobrir casos ímpares, mutando um a mais que a metade
    for (int i = 0; i < metade; i++){
        float fator = ((rand() % 201) - 100) / 1000.0;

        
        // Mutação
        if(rand() % 2){
            a_pai = populacao[i].a;
            b_pai = populacao[i].b;
            if (rand() % 2){
                
                a_pai += populacao[i].a * fator;
                mut_a = 1;
            }
            if (rand() % 2 || !mut_a) {
                b_pai += populacao[i].b * fator;
            }
        } 
        
        // Crossover  
        else{
            if(rand() % 2){
                a_pai = populacao[i].a;
                b_pai = populacao[i+1].b;
            }
            else{
                a_pai = populacao[i+1].a;
                b_pai = populacao[i].b;
            }

        }  

        populacao[m - i - 1].a = a_pai;
        populacao[m - i - 1].b = b_pai;
    }
}
