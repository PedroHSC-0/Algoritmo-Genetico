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

void imprimir_pontos(Ponto *dados, int n);

int comparar_fitness(const void *a, const void *b);

void ordenar_populacao(Individuo *populacao, int m);

void imprimir_populacao(Individuo *populacao, int m, int i, FILE *arquivo);

void mutacao(Individuo *populacao, int m);