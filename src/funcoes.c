/**
 * @file funcoes.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de implementação das funções utilizadas no programa, Contém a lógica das operações definidas em funcoes.h (Fase 1)
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
#include "funcoes.h"

/**
 * @brief Lê o ficheiro "mapaAntenas.txt" e imprime o seu conteúdo no terminal.
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
 * @brief Cria uma nova antena com os dados fornecidos.
 * 
 * @param freq Carácter que representa a frequência da antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Antenas* Ponteiro para a nova antena criada ou NULL em caso de falha.
 */
Antenas* CriarAntena(char freq, int x, int y) {
    Antenas* nova = (Antenas*)malloc(sizeof(Antenas));
    if (nova == NULL) {
        return NULL; // Erro na alocação
    }

    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;

    return nova;
}

/**
 * @brief Insere uma antena no início da lista ligada.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param nova Ponteiro para a nova antena a ser inserida.
 * @return Antenas* Ponteiro atualizado para o início da lista.
 */
Antenas* InserirAntenaInicio(Antenas* inicio, Antenas* nova) {
    if (nova == NULL) return inicio;

    nova->prox = inicio;
    return nova;
}

/**
 * @brief Insere uma antena no final da lista ligada.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param nova Ponteiro para a nova antena a ser inserida.
 * @return Antenas* Ponteiro para o início da lista após inserção.
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
 * @brief Insere uma antena na lista ligada de forma ordenada pelas coordenadas (x, y).
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param nova Ponteiro para a nova antena a ser inserida.
 * @return Antenas* Ponteiro para o início da lista atualizada.
 */
Antenas* InserirAntenasOrdenado(Antenas* inicio, Antenas* nova) {
    if (nova == NULL) return inicio;

    // Inserir no início se a lista estiver vazia ou nova < primeiro
    if (inicio == NULL ||
        nova->x < inicio->x ||
        (nova->x == inicio->x && nova->y < inicio->y)) {
        return InserirAntenaInicio(inicio, nova); //Chama a função "InserirAntenaInicio"
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
 * @param nomeFicheiro Caminho para o ficheiro de texto.
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

/**
 * @brief Modifica uma antena existente na lista.
 * 
 * Procura uma antena nas coordenadas (x, y) e altera sua frequência e coordenadas,
 * se não houver conflito com outra antena nas novas coordenadas.
 * 
 * @param inicio Ponteiro para o início da lista de antenas.
 * @param x Coordenada X da antena a modificar.
 * @param y Coordenada Y da antena a modificar.
 * @param novaFreq Nova frequência da antena.
 * @param novoX Nova coordenada X.
 * @param novoY Nova coordenada Y.
 * @return Antenas* Ponteiro para o início da lista, possivelmente atualizada.
 */
Antenas* ModificarAntena(Antenas* inicio, int x, int y, char novaFreq, int novoX, int novoY) {
    // Verifica se a lista está vazia
    if (inicio == NULL) {
        return NULL;
    }

    Antenas* atual = inicio;

    // Percorre a lista para encontrar a antena nas coordenadas fornecidas
    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            // Verifica se já existe uma antena nas novas coordenadas para evitar duplicação
            Antenas* aux = inicio;
            while (aux != NULL) {
                if (aux->x == novoX && aux->y == novoY) {
                    return inicio; // Mantém a lista sem alterações (Ocorre quando ja existe uma antena naquelas coordenadas)
                }
                aux = aux->prox;
            }

            // Modifica os valores da antena
            atual->freq = novaFreq;
            atual->x = novoX;
            atual->y = novoY;

            return inicio; // Retorna a lista atualizada
        }
        atual = atual->prox;
    }

    return inicio; // Retorna a lista original se a antena não for encontrada
}

/**
 * @brief Calcula e retorna os pontos com efeito nefasto entre antenas com a mesma frequência.
 * 
 * Para cada par de antenas com a mesma frequência, calcula dois pontos simétricos e adiciona
 * à lista de efeitos nefastos, se forem válidos (x >= 1 e y >= 1).
 * 
 * @param lista Ponteiro para a lista de antenas.
 * @return ListaEfeitoNefasto* Lista com os pontos de efeito nefasto.
 */
ListaEfeitoNefasto* CalcularEfeitoNefasto(Antenas* lista) {
    if (lista == NULL) return NULL;

    ListaEfeitoNefasto* listaNefasto = NULL;

    for (Antenas* a1 = lista; a1 != NULL; a1 = a1->prox) {
        for (Antenas* a2 = a1->prox; a2 != NULL; a2 = a2->prox) {
            if (a1->freq == a2->freq) {
                // Calcula os dois pontos do efeito nefasto
                int x1 = a1->x + (a1->x - a2->x);
                int y1 = a1->y + (a1->y - a2->y);
                int x2 = a2->x + (a2->x - a1->x);
                int y2 = a2->y + (a2->y - a1->y);

                // Inserir na lista se ainda não estiver lá
                if (x1 >= 1 && y1 >= 1) {
                    listaNefasto = InserirEfeitoSeNaoExiste(listaNefasto, x1, y1);
                }
                if (x2 >= 1 && y2 >= 1) {
                    listaNefasto = InserirEfeitoSeNaoExiste(listaNefasto, x2, y2);
                }
                
            }
        }
    }

    return listaNefasto;
}

/**
 * @brief Insere um ponto na lista de efeito nefasto se ele ainda não existir.
 * 
 * Evita duplicações ao inserir novos pontos na lista.
 * 
 * @param lista Lista de pontos do efeito nefasto.
 * @param x Coordenada X do novo ponto.
 * @param y Coordenada Y do novo ponto.
 * @return ListaEfeitoNefasto* Lista atualizada com o novo ponto, se inserido.
 */
ListaEfeitoNefasto* InserirEfeitoSeNaoExiste(ListaEfeitoNefasto* lista, int x, int y) {
    ListaEfeitoNefasto* atual = lista;

    while (atual != NULL) {
        if (atual->x == x && atual->y == y)
            return lista; // Já existe, não insere
        atual = atual->prox;
    }

    // Cria novo nodo
    ListaEfeitoNefasto* novo = (ListaEfeitoNefasto*)malloc(sizeof(ListaEfeitoNefasto));
    if (novo == NULL) return lista; // Erro de alocação

    novo->x = x;
    novo->y = y;
    novo->prox = lista;

    return novo;
}

/**
 * @brief Remove uma antena da lista e os efeitos nefastos associados.
 * 
 * Remove a antena localizada nas coordenadas (x, y) e elimina os efeitos nefastos
 * relacionados a ela. A memória da antena removida é libertada.
 * 
 * @param inicio Ponteiro para o início da lista de antenas.
 * @param inicioNefasto Ponteiro para a lista de efeitos nefastos.
 * @param x Coordenada X da antena a remover.
 * @param y Coordenada Y da antena a remover.
 * @return Antenas* Ponteiro para a lista de antenas após a remoção.
 */
Antenas* RemoverAntena(Antenas* inicio, ListaEfeitoNefasto* inicioNefasto, int x, int y) {
    // Verifica se a lista de antenas está vazia
    if (inicio == NULL) {
        return NULL; // Se estiver vazia retorna NULL
    }

    Antenas *atual = inicio;
    Antenas *anterior = NULL;

    // Percorre a lista de antenas para encontrar a antena a ser removida
    while (atual != NULL) {
        if (atual->x == x && atual->y == y) {
            // Antena encontrada
            if (anterior == NULL) {
                // A antena a remover é a primeira da lista
                inicio = atual->prox;
            } else {
                // A antena a remover está no meio ou fim da lista
                anterior->prox = atual->prox;
            }

            // Remover os efeitos nefastos gerados por esta antena
            ListaEfeitoNefasto* efeitosRemovidos = RemoverEfeitosNefastos(inicioNefasto, atual->x, atual->y);

            // Libera a memória da antena removida
            free(atual);
            
            return inicio; // Retorna a lista de antenas atualizada
        }
        anterior = atual;
        atual = atual->prox;
    }

    return inicio; // Se a antena não foi encontrada, retorna a lista original
}

/**
 * @brief Remove efeitos nefastos relacionados a uma antena.
 * 
 * Percorre a lista de efeitos e remove todos os pontos afetados pelas coordenadas (x, y).
 * 
 * @param inicio Ponteiro para o início da lista de efeitos nefastos.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return ListaEfeitoNefasto* Lista atualizada sem os efeitos removidos.
 */
ListaEfeitoNefasto* RemoverEfeitosNefastos(ListaEfeitoNefasto* inicio, int x, int y) {
    ListaEfeitoNefasto* atual = inicio;
    ListaEfeitoNefasto* anterior = NULL;

    // Percorre a lista de efeitos nefastos
    while (atual != NULL) {
        // Verifica se o efeito nefasto é gerado pela antena (x, y)
        if (atual->x == x || atual->y == y) {
            // Efeito nefasto encontrado, remove-o
            if (anterior == NULL) {
                // Efeito nefasto é o primeiro da lista
                inicio = atual->prox;
            } else {
                // Efeito nefasto está no meio ou fim da lista
                anterior->prox = atual->prox;
            }
            
            // Libera a memória do efeito removido
            ListaEfeitoNefasto* temp = atual;
            atual = atual->prox;
            free(temp);
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }

    return inicio; // Retorna a lista de efeitos nefastos atualizada
}

/**
 * @brief Avança simultaneamente nas listas de antenas e efeitos nefastos.
 *
 * A cada chamada, devolve os dados de uma linha para listagem tabular.
 * Quando ambas as listas forem totalmente percorridas, retorna false.
 *
 * @param ant Ponteiro para ponteiro da lista de antenas.
 * @param nef Ponteiro para ponteiro da lista de efeitos nefastos.
 * @param freq Saída com a frequência da antena (ou '\0' se não houver).
 * @param xAnt, yAnt Coordenadas da antena.
 * @param xNef, yNef Coordenadas do efeito nefasto.
 * @return true se ainda há dados, false se fim das listas.
 */
bool ProximaLinhaTabular(Antenas** ant, ListaEfeitoNefasto** nef, char* freq, int* xAnt, int* yAnt, int* xNef, int* yNef) {
    bool temAntena = (*ant != NULL);
    bool temEfeito = (*nef != NULL);

    if (!temAntena && !temEfeito) return false;

    if (temAntena) {
        *freq = (*ant)->freq;
        *xAnt = (*ant)->x;
        *yAnt = (*ant)->y;
        *ant = (*ant)->prox;
    } else {
        *freq = '\0';
        *xAnt = 0;
        *yAnt = 0;
    }

    if (temEfeito) {
        *xNef = (*nef)->x;
        *yNef = (*nef)->y;
        *nef = (*nef)->prox;
    } else {
        *xNef = 0;
        *yNef = 0;
    }

    return true;
}

/**
 * @brief Grava a lista de antenas num ficheiro binário.
 * 
 * Escreve os dados de cada antena no ficheiro especificado, sem guardar ponteiros.
 * 
 * @param inicio Ponteiro para a lista de antenas.
 * @param nomeFicheiro Nome do ficheiro binário.
 * @return true Se a gravação for bem-sucedida.
 * @return false Em caso de erro.
 */
bool GravarListaFicheiro(Antenas* inicio, const char* nomeFicheiro) {
    if (inicio == NULL) return false;

    FILE* fp = fopen(nomeFicheiro, "wb");
    if (fp == NULL) return false;

    Antenas* aux = inicio;
    AntenasBin elemento;

    while (aux != NULL) {
        elemento.x = aux->x;
        elemento.y = aux->y;
        elemento.freq = aux->freq;

        fwrite(&elemento, sizeof(AntenasBin), 1, fp);
        aux = aux->prox;
    }

    fclose(fp);
    return true;
}

/**
 * @brief Lê antenas de um ficheiro binário e devolve uma string formatada.
 * 
 * Lê os dados de antenas do ficheiro binário e devolve uma string com as informações.
 * A string é alocada dinamicamente e deve ser libertada com `free()`.
 * 
 * @param nomeFicheiro Nome do ficheiro a ler.
 * @return char* String formatada ou NULL em caso de erro.
 */
char* LerListaFicheiro(const char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "rb");
    if (fp == NULL) return NULL;

    size_t tamanho = 2048;
    char* buffer = malloc(tamanho);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }
    buffer[0] = '\0';

    AntenasBin elemento;
    char linha[64];

    while (fread(&elemento, sizeof(AntenasBin), 1, fp) == 1) {
        snprintf(linha, sizeof(linha), "%c - (%d, %d)\n", elemento.freq, elemento.x, elemento.y); //Formata e armazena caracteres no buffer

        // Expande buffer se necessário
        if (strlen(buffer) + strlen(linha) + 1 > tamanho) {
            tamanho *= 2;
            char* novo = realloc(buffer, tamanho);
            if (!novo) {
                free(buffer);
                fclose(fp);
                return NULL;
            }
            buffer = novo;
        }

        strcat(buffer, linha);
    }

    fclose(fp);
    return buffer;
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

void MostrarListaNefasto(ListaEfeitoNefasto* inicio) {
    ListaEfeitoNefasto* atual = inicio; // Começa pelo primeiro elemento

    // Se a lista estiver vazia
    if (atual == NULL) {
        return;
    }

    // Percorre a lista e imprime cada antena
    printf("Lista do Efeito Nefasto:\n");
    while (atual != NULL) {
        printf("(%d, %d)\n", atual->x, atual->y);
        atual = atual->prox; // Avança para o próximo elemento
    }
}



/**
 * @brief Liberta a memória alocada para a lista ligada de antenas.
 * 
 * Esta função percorre toda a lista ligada e liberta a memória ocupada por cada nodo.
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas.
 */
bool LimparMemoria(Antenas* inicio) {
    Antenas *atual = inicio;
    while (atual != NULL) {
        Antenas* aux = atual;
        atual = atual->prox;
        free(aux);
    }
    return true;
}

/**
 * @brief Liberta a memória alocada para a lista ligada do efeito nefasto.
 * 
 * Esta função percorre toda a lista ligada e liberta a memória ocupada por cada nodo.
 * 
 * @param inicio Ponteiro para o início da lista ligada do efeito nefasto.
 */
bool LimparMemoriaEfeito(ListaEfeitoNefasto* lista) {
    while (lista != NULL) {
        ListaEfeitoNefasto* temp = lista;
        lista = lista->prox;
        free(temp);
    }
    return true;
}
