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
  * 
  * @param nomeFicheiro 
  * @return Antenas* 
  */
Antenas* ListarMapaAntenas(const char *nomeFicheiro);

/**
 * @brief 
 * 
 * @param freq 
 * @param x 
 * @param y 
 * @return Antenas* 
 */
Antenas* CriarAntena(char freq, int x, int y);

/**
 * @brief Cria uma nova antena e insere-a no fim da lista ligada.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param freq Frequência da nova antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Antenas* Retorna o ponteiro para o início da lista.
 */
Antenas* InserirAntenaFim(Antenas* inicio, Antenas* nova);

/**
 * @brief Cria uma nova antena e insere-a no inicio da lista ligada.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 * @param freq Frequência da nova antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Antenas* Retorna o ponteiro para o início da lista.
 */
Antenas* InserirAntenaInicio(Antenas* inicio, Antenas* nova);

/**
 * @brief Insere ordenadamente na lista ligada
 * 
 * @param inicio 
 * @param freq 
 * @param x 
 * @param y 
 * @return Antenas* 
 */
Antenas* InserirAntenasOrdenado(Antenas* inicio, Antenas* nova);

/**
 * @brief Carrega as antenas do ficheiro (ex.: "mapaAntenas.txt") para uma lista ligada.
 * 
 * Percorre o ficheiro linha a linha, coluna a coluna; se encontrar um caractere visível
 * (diferente de '.' e de '\n'), insere na lista como antena.
 * 
 * @param nomeFicheiro Caminho para o ficheiro (ex.: "FicheirosTexto/mapaAntenas.txt").
 * @return Antenas* Retorna a lista de antenas lida do ficheiro.
 */
Antenas* CarregarMapaAntenas(const char *nomeFicheiro);

void MostrarLista(Antenas* inicio);
#endif