# Algoritmo Genético para Ajuste de Função Linear

**Disciplina:** Algoritmos e Estruturas de Dados I  
**Docente** CEFET-MG  
**Autor:** Pedro Henrique 
**Data de Entrega:** 05 de abril de 2026

---

## Descrição

---

## Objetivos

[Descreva o que o trabalho busca consolidar: manipulação de vetores/matrizes, alocação dinâmica, modularização, etc.]

-------------------------------------------

## Estrutura do Repositório

Algoritmo Genetico
|── config/
│   ├── input.h
│   └── output.h
├── src/
│   ├── genetico.c
│   ├── genetico.h
│   ├── io.c
│   ├── io.h
│   ├── main.c
│   └── model.h
├── Makefile
└── README.md

-------------------------------------------

## Estruturas de Dados

[Descreva as principais estruturas utilizadas: como a população é representada (matriz m×2), o vetor de fitness, etc.]

---

## Lógica de Evolução

### Inicialização
[Como a população inicial é gerada.]

### Avaliação (Fitness)
[Como o erro (MSE ou MAE) é calculado e como o fitness é definido a partir dele.]

### Seleção
[Critério de seleção dos dois melhores indivíduos.]

### Crossover
[Descrição da operação de crossover entre dois pais.]

### Mutação
[Descrição da mutação pontual com variação δ.]

### Atualização
[Como o indivíduo de menor fitness é substituído a cada geração.]

---

## Entrada e Saída

### Formato de `input.dat`
```
n m G
x1 y1
x2 y2
...
xn yn
```

### Formato de `output.dat`

---

## Compilação e Execução

---

## Experimentos e Resultados

---

## Análise de Complexidade

---

## Dependências

- GCC / G++
- Make
- Linux (Ubuntu / Zorin)
