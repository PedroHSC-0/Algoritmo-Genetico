#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct {
    float x;
    float y;
} Ponto;

int main(){
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
    printf("n = %d\nm = %d\nG = %d\n\n", n, m, G);
    
    // Alocamento do vetor dinâmico
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
    
    for (int i = 0; i < n; i++) {
        printf("%d - [%f, %f]\n", i+1, dados[i].x, dados[i].y);
    }
}