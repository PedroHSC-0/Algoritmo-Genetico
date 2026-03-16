#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct {
    float x;
    float y;
} Ponto;

typedef struct {
    float a;
    float b;
    float fitness;
} Individuo;

int main(){
    
    srand(time(NULL));

    int n, m, G;
    // n -> Número de pontos
    // m -> Tamanho da população
    // G -> Número de gerações

    // Abrindo o input.dat    
    FILE *arquivo = fopen("../../input.dat", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    
    // Lendo o input.dat

    // Primeira linha
    fscanf(arquivo, "%d %d %d", &n, &m, &G);

    /*
    printf("n = %d\nm = %d\nG = %d\n\n", n, m, G);
    */

    Ponto *dados = (Ponto*) malloc(n * sizeof(Ponto));
    
    if (dados == NULL) {
        printf("Erro de alocação de memória\n");
        return 1;
    }

    // Leitura dos pontos
    for (int i = 0; i < n; i++) {
        fscanf(arquivo, "%f %f", &dados[i].x, &dados[i].y);
    }

    fclose(arquivo);

    // Printar as sementes
    /*
    for (int i = 0; i < n; i++) {
        printf("%d - [%.2f, %.2f]\n", i+1, dados[i].x, dados[i].y);
    }
    */

    // Criar População

    Individuo *populacao = (Individuo*) malloc(m * sizeof(Ponto));

    if (populacao == NULL) {
        printf("Erro de alocação de memória\n");
        return 1;
    }

    for (int i = 0; i <= m;i++){
        populacao[i].a = (rand() % 1001) / 100.0;
        populacao[i].b = (rand() % 1001) / 100.0;
    }

    // Printar a população
    /*
    for (int i = 0; i <= m;i++){
        printf("a: %.2f, b: %.2f\n", populacao[i].a, populacao[i].b);
    }
    */

    // Cálculo do erro

    
    
}