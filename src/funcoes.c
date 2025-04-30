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
#include <stdbool.h>
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
        return NULL; // Erro na alocação
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
 * @brief Modifica as propriedades de uma antena existente na lista encadeada.
 * 
 * Esta função procura uma antena nas coordenadas fornecidas (x, y) e, se encontrada,
 * altera a sua frequência e move-a para novas coordenadas (novoX, novoY), garantindo
 * que não haja duplicação de antenas nessas novas coordenadas.
 * 
 * @param inicio Ponteiro para o início da lista encadeada de antenas.
 * @param x Coordenada X da antena a ser modificada.
 * @param y Coordenada Y da antena a ser modificada.
 * @param novaFreq Nova frequência a ser atribuída à antena.
 * @param novoX Nova coordenada X para onde a antena será movida.
 * @param novoY Nova coordenada Y para onde a antena será movida.
 * @return Antenas* Retorna o ponteiro para o início da lista (possivelmente modificada).
 * 
 * @note Se já existir uma antena nas novas coordenadas (novoX, novoY), a modificação não ocorre.
 * @note Caso a antena não seja encontrada, a lista mantém-se inalterada.
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
 * @brief Calcula o efeito nefasto entre as antenas com a mesma frequência.
 * 
 * Esta função percorre todas as antenas na lista e, para cada par de antenas que possuem
 * a mesma frequência, calcula dois novos pontos que representam o efeito nefasto causado
 * por essas antenas. Os pontos resultantes são inseridos em uma lista, desde que as 
 * coordenadas sejam válidas (ou seja, x >= 1 e y >= 1).
 * 
 * @param lista Lista ligada de antenas.
 * @return ListaEfeitoNefasto* Retorna uma lista ligada com os pontos calculados do efeito nefasto.
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
 * @brief Insere um novo ponto na lista de efeito nefasto, se ele não existir ainda.
 * 
 * Esta função verifica se o ponto especificado pelas coordenadas (x, y) já existe na lista.
 * Se o ponto não existir, ele será inserido no início da lista. Caso contrário, a lista permanece
 * inalterada. Essa função é usada para garantir que não haja duplicatas na lista do efeito nefasto.
 * 
 * @param lista Lista ligada de pontos do efeito nefasto.
 * @param x Coordenada X do ponto a ser inserido.
 * @param y Coordenada Y do ponto a ser inserido.
 * @return ListaEfeitoNefasto* Retorna a lista com o ponto inserido, caso ele não existisse.
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
 * @brief Remove uma antena da lista ligada e também remove os efeitos nefastos relacionados.
 * 
 * Esta função remove uma antena específica da lista ligada com base nas coordenadas fornecidas.
 * Além disso, também remove os efeitos nefastos gerados por essa antena na lista de efeitos nefastos.
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas.
 * @param inicioNefasto Ponteiro para o início da lista de efeitos nefastos.
 * @param x Coordenada X da antena a remover.
 * @param y Coordenada Y da antena a remover.
 * @return Antenas* Retorna o ponteiro para o início da lista ligada após a remoção da antena.
 * @return ListaEfeitoNefasto* Retorna o ponteiro para o início da lista de efeitos nefastos após a remoção dos efeitos relacionados.
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
 * @brief Remove os efeitos nefastos gerados por uma antena específica.
 * 
 * Esta função percorre a lista de efeitos nefastos e remove todos os efeitos
 * relacionados à antena fornecida pelas coordenadas (x, y).
 * 
 * @param inicio Ponteiro para o início da lista de efeitos nefastos.
 * @param x Coordenada X da antena cujos efeitos nefastos serão removidos.
 * @param y Coordenada Y da antena cujos efeitos nefastos serão removidos.
 * @return ListaEfeitoNefasto* Retorna o ponteiro para o início da lista de efeitos nefastos após a remoção.
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
 * Esta função percorre toda a lista ligada e liberta a memória ocupada por cada node.
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
 * Esta função percorre toda a lista ligada e liberta a memória ocupada por cada node.
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

