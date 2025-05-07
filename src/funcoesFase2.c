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
 * @brief Lê o ficheiro "mapaVertices.txt" e imprime o seu conteúdo no terminal.
 * 
 * @return Retorna NULL pois não altera a lista ligada, apenas exibe os dados.
 */
Vertices* ListarMapaVertices(const char *nomeFicheiro) {
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
 * @brief Cria um novo vértice com os dados fornecidos.
 * 
 * @param freq Carácter que representa a frequência do vertice.
 * @param x Coordenada X do vertice.
 * @param y Coordenada Y do vertice.
 * @return Vertices* Ponteiro para o novo vértice criado ou NULL em caso de falha.
 */
Vertices* CriarVertice(char freq, int x, int y) {
    Vertices* novo = (Vertices*)malloc(sizeof(Vertices));
    if (novo == NULL) {
        return NULL; // Erro na alocação
    }

    novo->freq = freq;
    novo->x = x;
    novo->y = y;
    novo->adjacencias = NULL; // Nenhuma aresta ainda
    novo->prox = NULL;        // Não está ligado a nenhum outro vértice ainda

    return novo;
}

/**
 * @brief Insere um vertice no início da lista ligada.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param nova Ponteiro para o novo vertice a ser inserido.
 * @return Vertices* Ponteiro atualizado para o início da lista.
 */
Vertices* InserirVerticeInicio(Vertices* inicio, Vertices* nova) {
    if (nova == NULL) return inicio;

    nova->prox = inicio;
    return nova;
}

/**
 * @brief Insere um verticie no final da lista ligada.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param nova Ponteiro para o novo vertice a ser inserido.
 * @return Vertices* Ponteiro para o início da lista após inserção.
 */
Vertices* InserirVerticeFim(Vertices* inicio, Vertices* nova) {
    if (nova == NULL) return inicio;

    nova->prox = NULL;

    if (inicio == NULL) {
        return nova;
    }

    Vertices* atual = inicio;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = nova;
    return inicio;
}

/**
 * @brief Insere um vertice na lista ligada de forma ordenada pelas coordenadas (x, y).
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param nova Ponteiro para o novo vertice a ser inserido.
 * @return Vertices* Ponteiro para o início da lista atualizada.
 */
Vertices* InserirVerticeOrdenado(Vertices* inicio, Vertices* nova) {
    if (nova == NULL) return inicio;

    // Inserir no início se a lista estiver vazia ou nova < primeiro
    if (inicio == NULL ||
        nova->x < inicio->x ||
        (nova->x == inicio->x && nova->y < inicio->y)) {
        return InserirVerticeInicio(inicio, nova); //Chama a função "InserirVerticeInicio"
    }

    Vertices* atual = inicio;
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
 * @brief Carrega os vertices do ficheiro "mapaVertices.txt" para uma lista ligada.
 * 
 * Esta função lê um ficheiro de texto que contém o mapa dos vertices, identificando
 * os vertices com base nos caracteres presentes. Cada verticie é adicionado ao final
 * da lista ligada utilizando a função InserirVerticeFim().
 * 
 * @param nomeFicheiro Caminho para o ficheiro de texto.
 * @return Vertices* Retorna a lista de vertices encontrados no mapa.
 */
Vertices* CarregarMapaVertices(const char *nomeFicheiro) {
    FILE *fp = fopen(nomeFicheiro, "r");
    if (fp == NULL) {
        return NULL; // Erro ao abrir o ficheiro
    }

    Vertices* lista = NULL;
    int x = 1; // Linha inicial
    int y = 1; // Coluna inicial

    // Leitura caractere por caractere
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            x++; // Incrementa a linha quando encontramos um '\n'
            y = 1; // Resetar coluna para a linha seguinte
        } else if (c != '.' && c >= 33) { // Ignora '.' e caracteres não visíveis
            // Se for um caractere válido (Vertice), insere na lista
            Vertices* nova = CriarVertice(c, x, y);
            lista = InserirVerticeFim(lista, nova);
        }
        y++; // Incrementa a coluna
    }

    fclose(fp); // Fecha o ficheiro após a leitura
    return lista; // Retorna a lista de antenas
}

/**
 * @brief Cria uma nova aresta entre dois vértices.
 * 
 * Aloca dinamicamente uma nova estrutura de aresta que liga um vértice de origem
 * a um vértice de destino. Retorna um ponteiro para a nova aresta criada.
 * 
 * @param origem Ponteiro para o vértice de origem.
 * @param destino Ponteiro para o vértice de destino.
 * @return Arestas* Ponteiro para a nova aresta criada, ou NULL em caso de erro de alocação.
 */
Arestas* CriarAresta(Vertices* origem, Vertices* destino) {
    Arestas* nova = (Arestas*)malloc(sizeof(Arestas));
    if (nova == NULL) return NULL;

    nova->origem = origem;
    nova->destino = destino;
    nova->prox = NULL;

    return nova;
}

/**
 * @brief Insere uma aresta na lista de adjacências do vértice de origem.
 * 
 * @param origem Ponteiro para o vértice de origem.
 * @param destino Ponteiro para o vértice de destino.
 * @return true se a inserção foi bem-sucedida, false em caso de erro (ex: alocação falhou).
 */
bool InserirAresta(Vertices* origem, Vertices* destino) {
    if (origem == NULL || destino == NULL) return false;

    Arestas* nova = CriarAresta(origem, destino);
    if (nova == NULL) return false;

    nova->prox = origem->adjacencias;
    origem->adjacencias = nova;

    return true;
}

/**
 * @brief Cria arestas bidirecionais entre vértices da mesma frequência.
 * 
 * @param lista Ponteiro para o início da lista de vértices.
 * @return true se todas as arestas foram criadas com sucesso, false se houve erro.
 */
bool CriarArestasMesmoFreq(Vertices* lista) {
    if (lista == NULL) return false;

    for (Vertices* v1 = lista; v1 != NULL; v1 = v1->prox) {
        for (Vertices* v2 = v1->prox; v2 != NULL; v2 = v2->prox) {
            if (v1->freq == v2->freq) {
                // Como o grafo é bidirecional, criamos a ligação em ambos os sentidos
                if (!InserirAresta(v1, v2)) return false;
                if (!InserirAresta(v2, v1)) return false;
            }
        }
    }

    return true;
}

/**
 * @brief Cria uma estrutura de grafo a partir da lista de vértices existente.
 * 
 * @param listaVertices Lista ligada de vértices já com as arestas inseridas.
 * @return Grafos* Ponteiro para a estrutura do grafo criada.
 */
Grafos* CriarGrafo(Vertices* listaVertices) {
    Grafos* novoGrafo = (Grafos*)malloc(sizeof(Grafos));
    if (novoGrafo == NULL) return NULL;

    novoGrafo->listaVertices = listaVertices;

    // Contadores auxiliares
    int totalVertices = 0;
    int totalArestas = 0;

    Vertices* atual = listaVertices;
    while (atual != NULL) {
        totalVertices++;

        Arestas* a = atual->adjacencias;
        while (a != NULL) {
            totalArestas++;
            a = a->prox;
        }

        atual = atual->prox;
    }

    novoGrafo->numVertices = totalVertices;
    novoGrafo->numArestas = totalArestas / 2;

    return novoGrafo;
}

/**
 * @brief Procura um vértice com coordenadas (x, y) numa lista ligada de vértices.
 * 
 * Esta função percorre a lista de vértices e retorna o ponteiro para o vértice
 * que possui as coordenadas indicadas. Se não for encontrado nenhum vértice
 * com essas coordenadas, a função retorna NULL.
 * 
 * @param lista Ponteiro para o início da lista ligada de vértices.
 * @param x Coordenada X a procurar.
 * @param y Coordenada Y a procurar.
 * @return Vertices* Ponteiro para o vértice encontrado, ou NULL se não for encontrado.
 */
Vertices* EncontrarVerticePorCoordenadas(Vertices* lista, int x, int y) {
    while (lista != NULL) {
        if (lista->x == x && lista->y == y) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

/**
 * @brief Adiciona um vértice à lista de visitados.
 * 
 * Esta função aloca memória para um novo elemento da lista de visitados
 * e insere o vértice dado no início da lista.
 * 
 * @param lista Ponteiro para a lista atual de vértices visitados.
 * @param v Ponteiro para o vértice a ser adicionado.
 * @return Visitados* Ponteiro para o início atualizado da lista de visitados.
 */
Visitados* AdicionarVisitado(Visitados* lista, Vertices* v) {
    Visitados* novo = malloc(sizeof(Visitados));
    if (novo == NULL) return lista;

    novo->vertice = v;
    novo->prox = lista;
    return novo;
}

/**
 * @brief Realiza uma procura em profundidade recursiva a partir de um vértice.
 * 
 * Esta função marca o vértice como visitado, adiciona-o à lista de visitados
 * e continua a procura recursivamente para todos os seus vértices adjacentes.
 * 
 * @param v Ponteiro para o vértice atual.
 * @param visitados Ponteiro para a lista de vértices visitados.
 * @return Visitados* Lista atualizada de vértices visitados após a procura.
 */
Visitados* ProcuraRecursiva(Vertices* v, Visitados* visitados) {
    if (v == NULL || v->visitado) return visitados;

    v->visitado = true;
    visitados = AdicionarVisitado(visitados, v);

    Arestas* atual = v->adjacencias;
    while (atual != NULL) {
        visitados = ProcuraRecursiva(atual->destino, visitados);
        atual = atual->prox;
    }

    return visitados;
}

/**
 * @brief Inicia uma procura em profundidade (DFS) a partir de um vértice com coordenadas específicas.
 * 
 * Esta função reinicia o estado de todos os vértices como não visitados, 
 * encontra o vértice de origem com as coordenadas fornecidas e inicia a 
 * procura em profundidade recursiva a partir dele.
 * 
 * @param listaVertices Ponteiro para o início da lista de vértices do grafo.
 * @param x Coordenada X do vértice de origem.
 * @param y Coordenada Y do vértice de origem.
 * @return Visitados* Lista de vértices visitados durante a procura em profundidade, ou NULL se o vértice de origem não for encontrado.
 */
Visitados* ProcuraProfundidade(Vertices* listaVertices, int x, int y) {
    // Visitado = 0 (reinicia os visitados)
    Vertices* temp = listaVertices;
    while (temp != NULL) {
        temp->visitado = false;
        temp = temp->prox;
    }

    Vertices* origem = EncontrarVerticePorCoordenadas(listaVertices, x, y);
    if (origem == NULL) return NULL;

    return ProcuraRecursiva(origem, NULL);
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


void MostrarListaVertices(Vertices* inicio) {
    Vertices* atual = inicio; // Começa pelo primeiro elemento

    // Se a lista estiver vazia
    if (atual == NULL) {
        return;
    }

    // Percorre a lista e imprime cada antena
    printf("Lista de Vertices:\n");
    while (atual != NULL) {
        printf("%c - (%d, %d)\n", atual->freq, atual->x, atual->y);
        atual = atual->prox; // Avança para o próximo elemento
    }
};

void MostrarAdjacencias(Vertices* lista) {
    Vertices* atual = lista;

    while (atual != NULL) {
        printf("Vértice (%c - %d, %d): ", atual->freq, atual->x, atual->y);
        
        Arestas* adj = atual->adjacencias;
        if (adj == NULL) {
            printf("Sem adjacências.");
        } else {
            while (adj != NULL) {
                printf("-> (%c - %d, %d) ", 
                    adj->destino->freq, 
                    adj->destino->x, 
                    adj->destino->y);
                adj = adj->prox;
            }
        }

        printf("\n");
        atual = atual->prox;
    }
    printf("\n\n");
}


