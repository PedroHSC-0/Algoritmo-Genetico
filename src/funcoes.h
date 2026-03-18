typedef struct {
    float x;
    float y;
} Ponto;

typedef struct {
    float a;
    float b;
    float fitness;
} Individuo;

Ponto* ler_pontos(int *n, int *m, int *G);

Individuo* criar_populacao(int m);

void calcular_fitness(Individuo *populacao, int m, Ponto *dados, int n);

Individuo melhor_individuo(Individuo *populacao, int m, int *i_melhor);

void imprimir_populacao(Individuo *populacao, int m, int G_atual, int G_total);

void evoluir(Individuo *populacao, int m);