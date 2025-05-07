/**
 * @file funcoesFase2.h
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho onde são declaradas as assinaturas das funções implementadas em funcoes.c (Fase 2)
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "dadosFase2.h"
 #include <stdbool.h>
 

#ifndef FUNCOESFASE2_H //Include Guard - evita inclusões múltiplas do mesmo cabeçalho durante a compilação.
#define FUNCOESFASE2_H

/** 
  * @brief Lê o ficheiro "mapaVertices.txt" e imprime o seu conteúdo no terminal.
*/
Vertices* ListarMapaVertices(const char *nomeFicheiro);

/**
 * @brief Cria um novo vértice com os dados fornecidos.
 */
Vertices* CriarVertice(char freq, int x, int y);

/**
 * @brief Insere uma antena no início da lista ligada.
 */
Vertices* InserirVerticeInicio(Vertices* inicio, Vertices* nova);

/**
 * @brief Insere um vertice no final da lista ligada.
 */
Vertices* InserirVerticeFim(Vertices* inicio, Vertices* nova);

/**
 * @brief Insere um vertice na lista ligada de forma ordenada pelas coordenadas (x, y).
 */
Vertices* InserirVerticeOrdenado(Vertices* inicio, Vertices* nova);

/**
 * @brief Carrega os vertices do ficheiro "mapaVertices.txt" para uma lista ligada.
 */
Vertices* CarregarMapaVertices(const char *nomeFicheiro);

/**
 * @brief Cria uma nova aresta com os dados fornecidos.
 */
Arestas* CriarAresta(Vertices* origem, Vertices* destino);

/**
 * @brief Insere uma aresta na lista de adjacências do vértice de origem.
 */
bool InserirAresta(Vertices* origem, Vertices* destino);

/**
 * @brief Cria arestas bidirecionais entre vértices da mesma frequência.
 */
bool CriarArestasMesmoFreq(Vertices* lista);

/**
 * @brief Cria uma estrutura de grafo a partir da lista de vértices existente.
 */
Grafos* CriarGrafo(Vertices* listaVertices);

/**
 * @brief * @brief Procura um vértice com coordenadas (x, y) numa lista ligada de vértices.
 */
Vertices* EncontrarVerticePorCoordenadas(Vertices* lista, int x, int y);

/**
 * @brief Adiciona um vértice no final da lista de visitados.
 */
Visitados* AdicionarVisitado(Visitados* lista, Vertices* v);

/**
 * @brief Realiza uma procura em profundidade recursiva a partir de um vértice.
 */
Visitados* ProcuraRecursiva(Vertices* v, Visitados* visitados);

/**
 * @brief Inicia uma procura em profundidade (DFS) a partir de um vértice com coordenadas específicas.
 */
Visitados* ProcuraProfundidade(Vertices* listaVertices, int x, int y);


Visitados* ProcuraLargura(Vertices* listaVertices, int x, int y);

/**
 * @brief Liberta a memória alocada para a lista ligada dos grafos
 */
bool LimparMemoriaGrafos(Grafos* grafo);

void MostrarListaVertices(Vertices* inicio);

void MostrarAdjacencias(Vertices* lista);

#endif
