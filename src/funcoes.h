/**
 * @file funcoes.h
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro de cabeçalho onde são declaradas as assinaturas das funções implementadas em funcoes.c
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "dados.h"

 #ifndef FUNCOES_H //Include Guard - evita inclusões múltiplas do mesmo cabeçalho durante a compilação.
 #define FUNCOES_H

/** 
  * @brief Lê o ficheiro "mapaAntenas.txt" e imprime o seu conteúdo no terminal.
  */
Antenas* ListarMapaAntenas(const char *nomeFicheiro);

/**
 * @brief Cria uma nova antena com os dados fornecidos.
 */
Antenas* CriarAntena(char freq, int x, int y);

/**
 * @brief Insere uma antena no início da lista ligada.
 */
Antenas* InserirAntenaInicio(Antenas* inicio, Antenas* nova);

/**
 * @brief Insere uma antena no final da lista ligada.
 */
Antenas* InserirAntenaFim(Antenas* inicio, Antenas* nova);

/**
 * @brief Insere uma antena na lista ligada de forma ordenada pelas coordenadas (x, y).
 */
Antenas* InserirAntenasOrdenado(Antenas* inicio, Antenas* nova);

/**
 * @brief Carrega as antenas do ficheiro (ex.: "mapaAntenas.txt") para uma lista ligada.
 */
Antenas* CarregarMapaAntenas(const char *nomeFicheiro);

/**
 * @brief Modifica uma antena existente na lista.
 */
Antenas* ModificarAntena(Antenas* inicio, int x, int y, char novaFreq, int novoX, int novoY);

/**
 * @brief Calcula e retorna os pontos com efeito nefasto entre antenas com a mesma frequência.
 */
ListaEfeitoNefasto* CalcularEfeitoNefasto(Antenas* lista);

/**
 * @brief Insere um ponto na lista de efeito nefasto se ele ainda não existir.
 */
ListaEfeitoNefasto* InserirEfeitoSeNaoExiste(ListaEfeitoNefasto* lista, int x, int y);

/**
 * @brief Remove uma antena da lista e os efeitos nefastos associados.
 */
Antenas* RemoverAntena(Antenas* inicio, ListaEfeitoNefasto* inicioNefasto, int x, int y);

/**
 * @brief Remove efeitos nefastos relacionados a uma antena.
 */
ListaEfeitoNefasto* RemoverEfeitosNefastos(ListaEfeitoNefasto* inicio, int x, int y);

/**
 * @brief Cria uma tabela formatada com antenas e efeitos nefastos.
 */
char* CriarTabela(Antenas* listaAntenas, ListaEfeitoNefasto* listaNefasto);

/**
 * @brief Grava a lista de antenas num ficheiro binário.
 */
bool GravarListaFicheiro(Antenas* inicio, const char* nomeFicheiro);

/**
 * @brief Lê antenas de um ficheiro binário e devolve uma string formatada.
 */
char* LerListaFicheiro(const char* nomeFicheiro);





void MostrarLista(Antenas* inicio);

void MostrarListaNefasto(ListaEfeitoNefasto* inicio);

/**
 * @brief Liberta a memória alocada para a lista ligada de antenas.
 */
bool LimparMemoria(Antenas* inicio);

/**
 * @brief Liberta a memória alocada para a lista ligada do efeito nefasto.
 */
bool LimparMemoriaEfeito(ListaEfeitoNefasto* lista);
#endif