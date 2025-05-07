/**
 * @file dadosFase2.h
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho dedicado à definição de estruturas e outros tipos de dados utilizados no programa. (Fase 2)
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
 
/**
 * @struct Arestas
 * @brief Estrutura que representa a ligação entre vértices com a mesma frequência.
 */
typedef struct Arestas {
    struct Vertices* destino;      /**< Apontador para o vértice de destino (antena ligada). */
    struct Vertices* origem;       /**< Apontador para o vértice de origem (antena ligada). */
    struct Arestas* prox;          /**< Apontador para a próxima aresta na lista de adjacencias. */
} Arestas;

/**
 * @struct Vertices
 * @brief Estrutura que representa uma antena no grafo.
 */
typedef struct Vertices {
    char freq;                      /**< Frequência da antena */
    int x, y;                       /**< Coordenadas X e Y da antena */
    bool visitado;                  /**< Verifica se o vertico ja foi visitado */
    Arestas* adjacencias;           /**< Lista de arestas que ligam a antenas com a mesma frequência. */
    struct Vertices* prox;          /**< Apontador para o próximo vértice na lista ligada. */
} Vertices;

/**
 * @struct Grafos
 * @brief Estrutura principal de um grafo, contendo os vértices e suas conexões.
 */
typedef struct Grafos {
    Vertices* listaVertices;    /**< Lista ligada de vértices (antenas) presentes na cidade. */
    int numVertices;            /**< Número total de vértices no grafo. */
    int numArestas;             /**< Número total de arestas no grafo. */
} Grafos;

/**
 * @struct Visitados
 * @brief Estrutura que reprenta os vertices visitados 
 */
typedef struct Visitados {
    Vertices* vertice;
    struct Visitados* prox;
} Visitados;

