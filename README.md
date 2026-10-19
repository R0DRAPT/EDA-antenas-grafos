# Antenas e Interferências — Listas Ligadas e Grafos em C

Projeto desenvolvido no âmbito da unidade curricular de **Estruturas de Dados Avançadas (EDA)**, lecionada pelo professor Luís Ferreira, no 2.º semestre do 1.º ano da Licenciatura em Engenharia de Sistemas Informáticos — **IPCA 2024/2025**.

O programa modela a distribuição de antenas de transmissão numa cidade representada por uma matriz bidimensional. Cada antena tem uma frequência de ressonância, identificada por um caractere (`A`, `O`, …). O objetivo é processar estes dados, identificar zonas de interferência e estruturar a informação de forma eficiente com **listas ligadas** (Fase 1) e **grafos** (Fase 2).

## Funcionalidades

### Fase 1 — Listas ligadas
- Leitura do mapa da cidade a partir de ficheiro e carregamento das antenas para uma lista ligada
- Inserção, alteração e remoção de antenas
- Cálculo das localizações com **efeito nefasto** (interferência entre antenas da mesma frequência), recalculado após cada alteração
- Listagem tabular das antenas e dos efeitos nefastos
- Gravação e leitura da lista de antenas em **ficheiro binário**

### Fase 2 — Grafos
- Construção de um grafo em que cada antena é um vértice, com arestas entre antenas da mesma frequência
- **Procura em profundidade (DFS)** e **procura em largura (BFS)** a partir de uma antena
- Identificação de **todos os caminhos** possíveis entre duas antenas
- Cálculo das **interseções** entre pares de antenas de frequências diferentes
- Gravação do grafo em **ficheiro binário**

## Exemplo de execução

Mapa de entrada:

```
............
........O...
.....O......
.......O....
....O.......
......A.....
............
............
........A...
.........A..
............
............
```

Excerto do resultado:

```
Grafo criado com 10 vértices e 12 arestas.

Procura em Profundidade:
Visitado: O (3, 7)
Visitado: O (5, 6)
Visitado: O (4, 9)
Visitado: O (2, 10)

Caminho(s) encontrado(s):
Caminho 1: (A - 2,2) -> (A - 6,8)
Caminho 2: (A - 2,2) -> (A - 9,10) -> (A - 6,8)
...
```

## Organização

- **`src/`** — código-fonte (`main.c`, `funcoes.c` para a Fase 1, `funcoesFase2.c` para a Fase 2) e `Makefile`
- **`doxdoc/`** — documentação do código gerada com Doxygen

## Como compilar e executar

### Pré-requisitos
- [gcc](https://gcc.gnu.org/install/) e [make](https://www.gnu.org/software/make/) (no Windows, através do [MSYS2](https://www.msys2.org/) / MinGW)
- [Doxygen](https://www.doxygen.nl/index.html) (apenas para gerar a documentação)

### Compilar e executar

Na pasta `src/`:

```bash
make
```

O comando compila o projeto e executa o programa.

Para apagar os ficheiros gerados na compilação:

```bash
make clean
```

> **Nota (Windows):** se os acentos aparecerem trocados na consola, execute `chcp 65001` antes de correr o programa.

## Documentação

A documentação do código está na pasta `doxdoc/`. Para a gerar de novo:

```bash
doxygen Doxyfile
```