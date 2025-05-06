/**
 * @file funcoesFase2.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de implementação das funções utilizadas no programa, corresponde-te a Fase 2 do projeto. Contém a lógica das operações definidas em funcoes.h
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funcoesFase2.h"

/**
 * @brief Lê o ficheiro "mapaGrafos.txt" e imprime o seu conteúdo no terminal.
 * 
 * @return Retorna NULL pois não altera a lista ligada, apenas exibe os dados.
 */
Grafos* ListarMapaGrafos(const char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "r");

    if (file == NULL) {
        return NULL;
    }

    int c; // Para armazenar cada caractere lido

    while ((c = fgetc(file)) != EOF) { // Lê até ao fim do ficheiro
        putchar(c); // Escreve o caractere no ecrã
    }
    fclose(file);
    return NULL;
}


/**
 * @brief Liberta a memória alocada para a lista ligada dos grafos
 * 
 * Esta função percorre toda a lista ligada e liberta a memória ocupada por cada nodo.
 * 
 * @param grafo apontador para a estrutura que contem a lista ligada de vértices 
 */
bool LimparMemoriaGrafos(Grafos* grafo) {
    if (grafo == NULL) return true;

    Vertices* atualVertice = grafo->listaVertices;
    while (atualVertice != NULL) {
        Arestas* atualAresta = atualVertice->adjacencias;
        while (atualAresta != NULL) {
            Arestas* tempAresta = atualAresta;
            atualAresta = atualAresta->prox;
            free(tempAresta);
        }

        Vertices* tempVertice = atualVertice;
        atualVertice = atualVertice->prox;
        free(tempVertice);
    }

    free(grafo);
    return true;
}



