# Algoritmo Genético — Ajuste de Função Linear

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

O MAE é transformado em um fitness normalizado no intervalo `(0, 1]` pela fórmula `1 / (MAE + 1)` — quanto menor o erro, maior o fitness. Dessa forma, **indivíduos com maior fitness são considerados melhores**, e a população é ordenada de forma decrescente a cada geração, de modo que os primeiros índices sempre correspondem aos melhores indivíduos.

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

A semente do gerador é inicializada com `srand(73)` em `main.c`, fixando a aleatoriedade e garantindo **reprodutibilidade** — toda execução com o mesmo `input.dat` produz os mesmos resultados.

#### Avaliação — `calcular_fitness(populacao, m, dados, n)`

Para cada indivíduo, a função percorre todos os `n` pontos do conjunto amostral, calcula a predição `ŷᵢ = a * xᵢ + b` e acumula o erro absoluto. O MAE é então transformado em um valor de fitness normalizado no intervalo `(0, 1]` pela fórmula:

```c
y_reta = populacao[i].a * dados[j].x + populacao[i].b;
erro = dados[j].y - y_reta;
if (erro < 0) erro = erro * (-1);
erro_total += erro;

populacao[i].fitness = 1 / ((erro_total / n) + 1);
```

A transformação `1 / (MAE + 1)` garante que o fitness seja sempre positivo e limitado entre `0` e `1`: quando o erro tende a zero, o fitness tende a `1` (solução perfeita); quando o erro é muito grande, o fitness tende a `0`. Dessa forma, **quanto maior o fitness, melhor o indivíduo**, seguindo a convenção clássica de algoritmos genéticos.

#### Ordenação — `ordenar_populacao(populacao, m)`

A população é ordenada de forma **decrescente** por fitness utilizando `qsort` da biblioteca padrão, com função de comparação `comparar_fitness`. Após a ordenação, o índice `0` sempre corresponde ao melhor indivíduo (maior fitness) e o índice `m-1` ao pior.

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

#### Loop Principal — `main.c`

O ciclo evolutivo completo é orquestrado em `main.c` e segue a sequência abaixo a cada uma das `G` gerações:

```
para cada geração i de 0 até G-1:
    1. mutacao(populacao, m)         → gera novos indivíduos a partir dos melhores
    2. calcular_fitness(...)         → avalia toda a população
    3. ordenar_populacao(...)        → reordena por fitness decrescente
    4. imprimir_populacao(...)       → registra o estado da geração no output.dat
```

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
1: a: 1.02, b: 3.02, fitness: 0.42
2: a: 1.02, b: 2.75, fitness: 0.40
...
```

## 🧪 Casos de Teste

Os testes foram realizados utilizando o arquivo `config/input.dat`, contendo um conjunto de pontos com tendência linear, e a semente `srand(73)` para garantir reprodutibilidade. O formato de entrada utilizado foi:

```
n m G
x1 y1
x2 y2
...
xn yn
```

---

### Caso 1 — Convergência progressiva do fitness

O comportamento esperado ao longo das gerações é uma melhora gradual do fitness do melhor indivíduo. O algoritmo parte de uma população aleatória com fitness baixo e, a cada geração, os operadores de crossover e mutação geram novos indivíduos que tendem a se aproximar da reta ideal. A progressão não é linear — períodos de estabilização são intercalados com saltos de melhora, refletindo a natureza estocástica dos operadores genéticos.

O formato de saída registrado em `config/output.dat` a cada geração permite acompanhar essa evolução:

```
Geração 1
1: a: X.XX, b: X.XX, fitness: 0.XX   ← melhor indivíduo
2: a: X.XX, b: X.XX, fitness: 0.XX
...
```

---

### Caso 2 — Estagnação da população

Um comportamento recorrente em algoritmos genéticos com taxa de mutação baixa é a **homogeneização da população**: ao longo das gerações, a maioria dos indivíduos converge para valores muito próximos de `a` e `b`, reduzindo a diversidade genética. Quando isso ocorre, os operadores de crossover e mutação passam a gerar indivíduos cada vez mais semelhantes entre si, limitando a capacidade de exploração do espaço de busca e desacelerando a melhora do fitness. Esse fenômeno é esperado no algoritmo implementado, dado que o fator de variação `δ ∈ [-0.1, +0.1]` é de pequena amplitude e proporcional ao valor atual dos parâmetros.

## 💬🎯 Análises e Conclusões

### 1. Comportamento do Fitness ao Longo das Gerações

O fitness do melhor indivíduo tende a crescer de forma não uniforme ao longo das gerações. É esperado observar períodos de estabilização intercalados com saltos pontuais de melhora, o que é comportamento característico de algoritmos genéticos com mutação de pequena amplitude operando em espaços de busca contínuos. Esses platôs ocorrem quando a variação introduzida pelos operadores não é suficiente para escapar de um ótimo local, e os saltos acontecem quando uma combinação favorável de crossover e mutação gera um indivíduo significativamente melhor.

### 2. Limitações Identificadas

**Convergência prematura:** A população tende a se homogeneizar ao longo das gerações, com a maioria dos indivíduos convergindo para valores muito próximos de `a` e `b`. Isso indica que a diversidade genética decresce mais rápido do que a mutação consegue reintroduzir, limitando a capacidade de exploração do espaço de busca nas gerações avançadas.

**Taxa de mutação fixa:** O fator de variação `δ ∈ [-0.1, +0.1]` é proporcional ao valor atual dos parâmetros, o que significa que indivíduos com `a` e `b` pequenos sofrem perturbações menores em magnitude absoluta. Isso pode dificultar o refinamento fino da solução quando os parâmetros já convergem para valores baixos.

**Ausência de elitismo explícito:** O melhor indivíduo não é preservado diretamente entre gerações — ele pode ser sobrescrito dependendo do resultado da ordenação. Um mecanismo de elitismo garantiria que a melhor solução encontrada nunca se perca ao longo do processo evolutivo.

### 3. Conclusão

O algoritmo implementado cumpre o objetivo proposto: buscar iterativamente parâmetros `(a, b)` que minimizem o erro de ajuste de uma reta a um conjunto de dados, utilizando os operadores clássicos de um algoritmo genético. A transformação do MAE em fitness normalizado pela fórmula `1 / (MAE + 1)` torna a métrica limitada ao intervalo `(0, 1]` e compatível com a convenção de maximização, facilitando tanto a interpretação dos resultados quanto a ordenação da população.

Ajustes como aumento do número de gerações, ampliação da taxa de mutação ou introdução de elitismo explícito têm potencial direto de elevar a qualidade da solução encontrada, e representam caminhos naturais para evoluções futuras do projeto.
## ⌨️ Instalação e Configuração

### Requisitos

- GCC (compilador C)
- Make
- Linux (desenvolvido e testado em Arch Linux)

### Passos

**1. Verificar e instalar o compilador GCC**

```bash
gcc --version
```

Caso não esteja instalado:

```bash
# Arch Linux
sudo pacman -S gcc

# Ubuntu/Debian
sudo apt install gcc -y
```

**2. Verificar e instalar o Make**

```bash
make --version
```

Caso não esteja instalado:

```bash
# Arch Linux
sudo pacman -S make

# Ubuntu/Debian
sudo apt install make -y
```

**3. Clonar o repositório**

```bash
git clone <url-do-repositorio>
cd Algoritmo\ Genetico
```

**4. Configurar a entrada**

Edite o arquivo `config/input.dat` com os parâmetros desejados:

```
n m G
x1 y1
x2 y2
...
xn yn
```

Onde `n` é o número de pontos, `m` o tamanho da população e `G` o número de gerações.

**5. Compilar o projeto**

```bash
make
```

Para recompilar do zero:

```bash
make clean
make
```

**6. Executar**

```bash
make run
```

Os resultados serão registrados em `config/output.dat` a cada geração.

---

## 👨‍💻 Autor

Desenvolvido por **Pedro Henrique Silva Costa** para a disciplina de Algoritmos e Estruturas de Dados I — CEFET-MG Campus V, Divinópolis.