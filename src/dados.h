/**
 * @file dados.h
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho dedicado à definição de estruturas e outros tipos de dados utilizados no programa. (Fase 1)
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>

/**
 * @struct Antenas
 * @brief Estrutura que representa uma antena com coordenadas e frequência.
 * 
 * Esta estrutura é utilizada para criar uma lista ligada de antenas, onde cada nodo 
 * contém as coordenadas da antena (x, y), a sua frequência e um apontador para o próximo nodo.
 */
typedef struct Antenas {
    int x, y; /**< Coordenadas X e Y da antena */
    char freq; /**< Frequência da antena representada por um carácter */
    struct Antenas *prox; /**< Apontador para o próximo nodo da lista */
} Antenas;

/**
 * @struct ListaEfeitoNefasto
 * @brief Estrutura que representa o efeito nefasto e as suas coordenadas.
 * 
 * Esta estrutura é utilizada para criar uma lista ligada dos efeitos nefastos, onde cada nodo 
 * contém as coordenadas do efeito (x, y) e um apontador para o próximo nodo.
 */
typedef struct ListaEfeitoNefasto {
    int x, y; /**< Coordenadas X e Y do efeito nefasto */
    struct ListaEfeitoNefasto *prox; /**< Apontador para o próximo nodo da lista */
} ListaEfeitoNefasto;

/**
 * @struct AntenasBin
 * @brief Estrutura que representa uma antena com coordenadas e frequência.
 * 
 * Esta estrutura é utilizada para gravação num ficheiro binário.
 * Contém as coordenadas da antena (x, y) e a sua frequência.
 */
typedef struct AntenasBin {
    int x, y; /**< Coordenadas X e Y da antena */
    char freq; /**< Frequência da antena representada por um carácter */
} AntenasBin;
