/**
 * @file funcoes.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de implementação das funções utilizadas no programa. Contém a lógica das operações definidas em funcoes.h
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/**
 * @brief Lê o ficheiro "mapaAntenas.txt" e imprime o seu conteúdo no terminal.
 * 
 * A função abre o ficheiro localizado na pasta "Ficheiros" e exibe as informações
 * armazenadas nele.
 * 
 * @return Retorna NULL pois não altera a lista ligada, apenas exibe os dados.
 */
Antenas* ListarMapaAntenas(const char *nomeFicheiro) {
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
 * @brief 
 * 
 * @param freq 
 * @param x 
 * @param y 
 * @return Antenas* 
 */
Antenas* CriarAntena(char freq, int x, int y) {
    Antenas* nova = (Antenas*)malloc(sizeof(Antenas));
    if (nova == NULL) {
        return NULL; // Falha de alocação
    }

    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;

    return nova;
}

/**
 * @brief 
 * 
 * @param inicio 
 * @param nova 
 * @return Antenas* 
 */
Antenas* InserirAntenaInicio(Antenas* inicio, Antenas* nova) {
    if (nova == NULL) return inicio;

    nova->prox = inicio;
    return nova;
}

/**
 * @brief 
 * 
 * @param inicio 
 * @param nova 
 * @return Antenas* 
 */
Antenas* InserirAntenaFim(Antenas* inicio, Antenas* nova) {
    if (nova == NULL) return inicio;

    nova->prox = NULL;

    if (inicio == NULL) {
        return nova;
    }

    Antenas* atual = inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = nova;
    return inicio;
}

/**
 * @brief 
 * 
 * @param inicio 
 * @param nova 
 * @return Antenas* 
 */
Antenas* InserirAntenasOrdenado(Antenas* inicio, Antenas* nova) {
    if (nova == NULL) return inicio;

    // Inserir no início se a lista estiver vazia ou nova < primeiro
    if (inicio == NULL ||
        nova->x < inicio->x ||
        (nova->x == inicio->x && nova->y < inicio->y)) {
        nova->prox = inicio;
        return nova;
    }

    Antenas* atual = inicio;
    while (atual->prox != NULL &&
          (atual->prox->x < nova->x ||
          (atual->prox->x == nova->x && atual->prox->y < nova->y))) {
        atual = atual->prox;
    }

    nova->prox = atual->prox;
    atual->prox = nova;

    return inicio;
}

/**
 * @brief Carrega as antenas do ficheiro "mapaAntenas.txt" para uma lista ligada.
 * 
 * Esta função lê um ficheiro de texto que contém o mapa das antenas, identificando
 * as antenas com base nos caracteres presentes. Cada antena é adicionada ao final
 * da lista ligada utilizando a função InserirAntenaFim().
 * 
 * @param filename Caminho para o ficheiro de texto.
 * @return Antenas* Retorna a lista de antenas encontradas no mapa.
 */
Antenas* CarregarMapaAntenas(const char *nomeFicheiro) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (fp == NULL) {
        return NULL; // Erro ao abrir o ficheiro
    }

    Antenas* lista = NULL;
    int x = 1; // Linha inicial
    int y = 1; // Coluna inicial

    // Leitura caractere por caractere
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            x++; // Incrementa a linha quando encontramos um '\n'
            y = 1; // Resetar coluna para a linha seguinte
        } else if (c != '.' && c >= 33) { // Ignora '.' e caracteres não visíveis
            // Se for um caractere válido (antena), insere na lista
            Antenas* nova = CriarAntena(c, x, y);
            lista = InserirAntenaFim(lista, nova);
        }
        y++; // Incrementa a coluna
    }

    fclose(fp); // Fecha o ficheiro após a leitura
    return lista; // Retorna a lista de antenas
}

void MostrarLista(Antenas* inicio) {
    Antenas* atual = inicio; // Começa pelo primeiro elemento

    // Se a lista estiver vazia
    if (atual == NULL) {
        return;
    }

    // Percorre a lista e imprime cada antena
    printf("Lista de Antenas:\n");
    while (atual != NULL) {
        printf("%c - (%d, %d)\n", atual->freq, atual->x, atual->y);
        atual = atual->prox; // Avança para o próximo elemento
    }
}

