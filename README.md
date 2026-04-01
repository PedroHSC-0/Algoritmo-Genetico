# Algoritmo Genético — Ajuste de Função Linear

![STATUS](http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge)
![Linguagem](https://img.shields.io/static/v1?label=Linguagem&message=C&color=GREEN&style=for-the-badge)

---

## 📃 Introdução

Algoritmos Genéticos (AGs) pertencem à classe das meta-heurísticas inspiradas nos princípios da seleção natural e da evolução biológica. Sua lógica central reside em manter uma população de soluções candidatas que, ao longo de gerações sucessivas, são avaliadas, selecionadas e modificadas por operadores evolutivos — como cruzamento e mutação — com o objetivo de convergir progressivamente para soluções de maior qualidade frente ao problema em estudo.

Este projeto implementa um Algoritmo Genético simplificado voltado ao problema de **ajuste de parâmetros de uma função linear** da forma `ŷ = ax + b`, dado um conjunto de pontos empíricos no plano cartesiano. Cada indivíduo da população representa um par de parâmetros `(a, b)`, e sua qualidade é avaliada pelo **Erro Absoluto Médio (MAE)** entre a reta por ele definida e os pontos observados. O processo evolutivo opera pela seleção dos melhores indivíduos, aplicação de crossover entre pares e mutação estocástica dos parâmetros, substituindo os indivíduos de menor desempenho a cada geração.

Embora o contexto seja a otimização de uma reta, o foco do trabalho não está na teoria estatística por trás do ajuste, mas sim nos aspectos de **programação estruturada em C**, como alocação dinâmica de memória, organização modular, manipulação de vetores e controle iterativo do ciclo evolutivo.

O trabalho foi proposto pelo professor Michel Pires da Silva, na disciplina de **Algoritmos e Estruturas de Dados I**, do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG), Campus V — Divinópolis.

## 📋 Problema Proposto

O problema consiste em, dado um conjunto fixo de `n` pontos no plano cartesiano:

```
D = {(x₁, y₁), (x₂, y₂), ..., (xₙ, yₙ)}
```

encontrar os parâmetros `a` (coeficiente angular) e `b` (coeficiente linear) de uma reta `ŷ = ax + b` que melhor se ajuste a esses dados, minimizando o erro global entre os valores reais e os estimados pela reta.

Cada solução candidata — chamada de **indivíduo** — representa um par `(a, b)`. Para cada indivíduo, a reta é aplicada sobre todos os pontos do conjunto amostral, gerando predições `ŷᵢ = axᵢ + b`. A qualidade de cada indivíduo é medida pelo **Erro Absoluto Médio (MAE)**:

```
MAE = (1/n) * Σ |yᵢ - ŷᵢ|
```

Como o objetivo é **minimizar** o erro, o fitness de cada indivíduo é interpretado diretamente como o MAE calculado — indivíduos com menor MAE são considerados melhores. A população é ordenada de forma crescente por fitness a cada geração, de modo que os primeiros índices sempre correspondem aos melhores indivíduos.

### Ciclo Evolutivo

O algoritmo opera em um laço de `G` gerações. A cada geração:

1. **Seleção** — os indivíduos já estão ordenados por fitness; os melhores (primeira metade) são usados como base para gerar novos indivíduos.
2. **Crossover** — combina o parâmetro `a` de um indivíduo com o parâmetro `b` de outro (ou vice-versa), gerando um novo par `(a, b)`.
3. **Mutação** — aplica uma pequena variação proporcional (`δ`) sobre `a`, `b` ou ambos de um indivíduo selecionado.
4. **Substituição** — os indivíduos gerados substituem os piores da população (última metade).
5. **Reavaliação** — o fitness de toda a população é recalculado e a população é reordenada.

### Requisitos Técnicos

O projeto deve ser desenvolvido em **C**, com organização modular do código em arquivos separados (`src/`, headers). A compilação é gerenciada via `Makefile` e o executável deve ser compatível com sistemas **Linux**. A entrada é lida a partir do arquivo `config/input.dat` e os resultados de cada geração são registrados em `config/output.dat`.

## 🖥️ Ambiente de Criação

O código foi desenvolvido utilizando as seguintes ferramentas:

[![Linguagem](https://img.shields.io/badge/Linguagem-C-blue?style=for-the-badge)](https://devdocs.io/c/)
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-blueviolet?style=for-the-badge)](https://code.visualstudio.com/)
[![Sistema Operacional](https://img.shields.io/badge/ISO-Arch%20Linux-blue?style=for-the-badge)](https://archlinux.org/)

---

## 📁 Estrutura Geral do Projeto
```
Algoritmo Genetico/
├── Makefile           # Script para compilar o projeto (build automático)
├── README.md          # Descrição geral do projeto e instruções de uso
├── build/             # Diretório para arquivos binários/compilados
│   └── app            # Executável principal gerado pela compilação
├── config/            # Arquivos de entrada e saída do algoritmo
│   ├── input.dat      # Arquivo de entrada: pontos, tamanho da população e gerações
│   └── output.dat     # Arquivo de saída: registro de cada geração
└── src/               # Código-fonte principal do projeto
    ├── main.c         # Função principal — orquestra o ciclo evolutivo
    ├── genetico.c     # Implementação do algoritmo genético
    ├── genetico.h     # Declarações das funções do algoritmo genético
    ├── io.c           # Leitura do input.dat e escrita no output.dat
    ├── io.h           # Declarações das funções de entrada e saída
    └── model.h        # Definição das structs Ponto e Individuo
```

## 👨‍💻 Metodologia

### 🧩 Estruturas de Dados

O projeto utiliza duas estruturas centrais, definidas em `model.h`:

**`Ponto`** — representa uma observação do conjunto amostral, armazenando as coordenadas `x` e `y` como valores reais.

```c
typedef struct {
    float x;
    float y;
} Ponto;
```

**`Individuo`** — representa uma solução candidata do algoritmo genético, armazenando os parâmetros `a` e `b` da reta estimada, além do valor de fitness calculado.

```c
typedef struct {
    float a;
    float b;
    float fitness;
} Individuo;
```

A população é representada como um vetor dinâmico de `Individuo`, alocado via `malloc` com tamanho `m * sizeof(Individuo)`. O conjunto de pontos é igualmente um vetor dinâmico de `Ponto` com tamanho `n * sizeof(Ponto)`. Não há vetor auxiliar separado para o fitness — ele é armazenado diretamente dentro de cada `Individuo`, mantendo os dados coesos e facilitando a ordenação.

---

### 🔄 Lógica de Evolução

#### Inicialização — `criar_populacao(m)`

A população inicial é gerada aleatoriamente em `genetico.c`. Cada indivíduo recebe valores de `a` e `b` sorteados no intervalo `[0.0, 10.0]`, com precisão de duas casas decimais:

```c
populacao[i].a = (rand() % 1001) / 100.0;
populacao[i].b = (rand() % 1001) / 100.0;
```

A semente do gerador é inicializada com `srand(time(NULL))`, garantindo populações diferentes a cada execução.

#### Avaliação — `calcular_fitness(populacao, m, dados, n)`

Para cada indivíduo, a função percorre todos os `n` pontos do conjunto amostral, calcula a predição `ŷᵢ = a * xᵢ + b` e acumula o erro absoluto. Ao final, divide pelo número de pontos, obtendo o MAE:

```c
y_reta = populacao[i].a * dados[j].x + populacao[i].b;
erro = dados[j].y - y_reta;
if (erro < 0) erro = erro * (-1);
erro_total += erro;

populacao[i].fitness = erro_total / n;
```

A complexidade desta função é **O(m × n)** — para cada um dos `m` indivíduos, todos os `n` pontos são avaliados.

#### Ordenação — `ordenar_populacao(populacao, m)`

A população é ordenada de forma **crescente** por fitness utilizando `qsort` da biblioteca padrão, com função de comparação `comparar_fitness`. Após a ordenação, o índice `0` sempre corresponde ao melhor indivíduo (menor MAE) e o índice `m-1` ao pior.

A complexidade da ordenação é **O(m log m)**.

#### Mutação e Crossover — `mutacao(populacao, m)`

Esta função concentra tanto a mutação quanto o crossover. Ela opera sobre a primeira metade da população (os melhores indivíduos) e usa os resultados para sobrescrever a segunda metade (os piores), renovando a população a cada geração.

Para cada indivíduo `i` da primeira metade, um sorteio decide entre dois operadores:

**Crossover** — combina parâmetros de dois indivíduos adjacentes:

```c
// Filho recebe a de i e b de i+1, ou vice-versa
if(rand() % 2){
    a_pai = populacao[i].a;
    b_pai = populacao[i+1].b;
} else {
    a_pai = populacao[i+1].a;
    b_pai = populacao[i].b;
}
```

**Mutação** — aplica uma variação proporcional `δ` sobre `a`, `b` ou ambos:

```c
float fator = ((rand() % 201) - 100) / 1000.0; // δ ∈ [-0.1, +0.1]

if (rand() % 2) a_pai += populacao[i].a * fator;
if (rand() % 2) b_pai += populacao[i].b * fator;
```

O novo indivíduo gerado substitui o pior correspondente na população:

```c
populacao[m - i - 1].a = a_pai;
populacao[m - i - 1].b = b_pai;
```

A complexidade desta função é **O(m)**.

#### Loop Principal — `main.c`

O ciclo evolutivo completo é orquestrado em `main.c` e segue a sequência abaixo a cada uma das `G` gerações:

```
para cada geração i de 0 até G-1:
    1. mutacao(populacao, m)         → gera novos indivíduos a partir dos melhores
    2. calcular_fitness(...)         → avalia toda a população
    3. ordenar_populacao(...)        → reordena por fitness crescente
    4. imprimir_populacao(...)       → registra o estado da geração no output.dat
```

A complexidade total do loop é **O(G × (m × n + m log m))**, dominada pela avaliação de fitness em cada geração.

---

### 📥 Entrada e Saída

#### Leitura — `ler_pontos(n, m, G)`

O arquivo `config/input.dat` é lido em `io.c`. A primeira linha contém os parâmetros gerais da execução e as linhas seguintes os pares de coordenadas:

```
n m G
x1 y1
x2 y2
...
xn yn
```

Os pontos são alocados dinamicamente e retornados como vetor de `Ponto`. Em caso de falha na abertura do arquivo ou na alocação de memória, o programa encerra com mensagem de erro.

#### Escrita — `imprimir_populacao(populacao, m, i, arquivo)`

A cada geração, o estado completo da população é registrado simultaneamente no terminal (`printf`) e no arquivo `config/output.dat` (`fprintf`), com o número da geração e os valores de `a`, `b` e fitness de cada indivíduo:

```
Geração 1
1: a: 2.30, b: 1.50, fitness: 0.87
2: a: 1.90, b: 2.10, fitness: 1.03
...
```

## 🧪 Casos de Teste

Os testes foram realizados com o conjunto de dados presente em `config/input.dat`, composto por **30 pontos** gerados com distribuição aproximadamente linear. Os parâmetros de execução utilizados foram:

```
n = 30   (número de pontos)
m = 30   (tamanho da população)
G = 10   (número de gerações)
```

Os pontos seguem uma tendência linear visível, com valores de `x` variando entre `0.065` e `9.572` e valores de `y` entre `1.709` e `26.587`, sugerindo uma reta real próxima de `y ≈ 2.5x + 2.5`.

---

### Caso 1 — Execução padrão com 10 gerações

Este caso corresponde à execução direta do programa com o `input.dat` fornecido. A tabela abaixo registra a evolução do **melhor indivíduo** (menor MAE) ao longo das gerações:

| Geração | a    | b    | MAE (fitness) |
|---------|------|------|---------------|
| 1       | 2.59 | 2.30 | 1.21          |
| 2       | 2.31 | 3.33 | 1.09          |
| 3       | 2.31 | 3.33 | 1.09          |
| 4       | 2.31 | 3.33 | 1.09          |
| 5       | 2.31 | 3.33 | 1.09          |
| 6       | 2.31 | 3.33 | 1.09          |
| 7       | 2.31 | 3.33 | 1.09          |
| 8       | 2.31 | 3.33 | 1.09          |
| 9       | 2.38 | 3.55 | 1.07          |
| 10      | 2.38 | 3.55 | 1.07          |

**Observações:**

- O algoritmo convergiu rapidamente já na geração 2, encontrando `a = 2.31, b = 3.33` com MAE de `1.09`.
- Entre as gerações 2 e 8, o melhor indivíduo permaneceu estável, indicando que a mutação não foi suficiente para escapar do platô local nesse intervalo.
- Na geração 9 houve uma melhora discreta para `a = 2.38, b = 3.55` com MAE de `1.07`, encerrando a execução com esse valor.
- A solução final `ŷ = 2.38x + 3.55` é uma boa aproximação da tendência linear dos dados, com erro médio absoluto inferior a `1.1` unidade ao longo de todos os 30 pontos.

---

### Caso 2 — Estagnação da população

Um comportamento observado nas gerações finais do `output.dat` é a **homogeneização da população**: a maioria dos 30 indivíduos converge para valores praticamente idênticos de `a` e `b`, como evidenciado abaixo (geração 10):

```
1:  a: 2.46, b: 3.33, fitness: 1.12
...
19: a: 2.46, b: 3.33, fitness: 1.12
20: a: 2.46, b: 3.37, fitness: 1.13
```

Isso indica que o operador de mutação, com variação proporcional máxima de `±10%`, tende a produzir indivíduos muito semelhantes entre si ao longo das gerações, reduzindo a diversidade genética da população. Esse é um comportamento esperado em AGs com taxa de mutação baixa e ausência de mecanismo de elitismo explícito com reintrodução de diversidade.