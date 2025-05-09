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

#ifndef DADOSFASE2_H
#define DADOSFASE2_H

#include <stdio.h>
#include <stdbool.h>
 
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
    bool visitado;                  /**< Indica se o vertice ja foi visitado */
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
 * @brief Estrutura que representa os vértices visitados durante a procura de caminhos.
 */
typedef struct Visitados {
    Vertices* vertice;              /**< Apontador para o vértice visitado. */
    struct Visitados* prox;         /**< Apontador para o próximo vértice na lista de visitados. */
} Visitados;

/**
 * @struct Caminho
 * @brief Estrutura que representa um caminho possível entre duas antenas.
 */
typedef struct Caminho {
    Visitados* vertices;            /**< Lista ligada de vértices que constituem o caminho. */
    struct Caminho* prox;           /**< Apontador para o próximo caminho na lista. */
} Caminho;

/**
 * @struct ListaCaminhos
 * @brief Estrutura que guarda a lista de todos os caminhos possíveis entre duas antenas.
 */
typedef struct ListaCaminhos {
    Caminho* primeiro;              /**< Apontador para o primeiro caminho na lista. */
} ListaCaminhos;

/**
 * @struct ParAntenas
 * @brief Estrutura que representa um par de antenas com diferentes frequências.
 */
typedef struct ParAntenas {
    Vertices* a;                    /**< Apontador para a antena com a primeira frequência. */
    Vertices* b;                    /**< Apontador para a antena com a segunda frequência. */
} ParAntenas;

/**
 * @struct ListaPares
 * @brief Estrutura que armazena todos os pares possíveis de antenas entre duas frequências distintas.
 */
typedef struct ListaPares {
    ParAntenas* pares;              /**< Vetor de pares de antenas. */
    int tamanho;                    /**< Número total de pares armazenados. */
} ListaPares;


#endif