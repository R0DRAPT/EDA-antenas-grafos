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
 * @brief Cria uma nova antena
 * 
 * @param freq 
 * @param x 
 * @param y 
 * @return Antenas* 
 */
Antenas* CriarAntena(char freq, int x, int y);

/**
 * @brief Insere antena no fim da lista ligada.
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
 * @param inicio Ponteiro para o início da lista ligada.
 * @param freq Frequência da nova antena.
 * @param x Coordenada X da antena.
 * @param y Coordenada Y da antena.
 * @return Antenas* Retorna o ponteiro para o início da lista.
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

/**
 * @brief Modifica as propriedades de uma antena existente na lista encadeada.
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
Antenas* ModificarAntena(Antenas* inicio, int x, int y, char novaFreq, int novoX, int novoY);

/**
 * @brief Calcula o efeito nefasto entre as antenas com a mesma frequência.
 * 
 * @param lista Lista ligada de antenas.
 * @return ListaEfeitoNefasto* Retorna uma lista ligada com os pontos calculados do efeito nefasto.
 */
ListaEfeitoNefasto* CalcularEfeitoNefasto(Antenas* lista);

/**
 * @brief Insere um novo ponto na lista de efeito nefasto, se ele não existir ainda.
 * 
 * @param lista Lista ligada de pontos do efeito nefasto.
 * @param x Coordenada X do ponto a ser inserido.
 * @param y Coordenada Y do ponto a ser inserido.
 * @return ListaEfeitoNefasto* Retorna a lista com o ponto inserido, caso ele não existisse.
 */
ListaEfeitoNefasto* InserirEfeitoSeNaoExiste(ListaEfeitoNefasto* lista, int x, int y);

/**
 * @brief Remove uma antena da lista ligada e também remove os efeitos nefastos relacionados.
 * 
 * @param inicio Ponteiro para o início da lista ligada de antenas.
 * @param inicioNefasto Ponteiro para o início da lista de efeitos nefastos.
 * @param x Coordenada X da antena a remover.
 * @param y Coordenada Y da antena a remover.
 * @return Antenas* Retorna o ponteiro para o início da lista ligada após a remoção da antena.
 * @return ListaEfeitoNefasto* Retorna o ponteiro para o início da lista de efeitos nefastos após a remoção dos efeitos relacionados.
 */
Antenas* RemoverAntena(Antenas* inicio, ListaEfeitoNefasto* inicioNefasto, int x, int y);

/**
 * @brief Remove os efeitos nefastos gerados por uma antena específica.
 * 
 * @param inicio Ponteiro para o início da lista de efeitos nefastos.
 * @param x Coordenada X da antena cujos efeitos nefastos serão removidos.
 * @param y Coordenada Y da antena cujos efeitos nefastos serão removidos.
 * @return ListaEfeitoNefasto* Retorna o ponteiro para o início da lista de efeitos nefastos após a remoção.
 */
ListaEfeitoNefasto* RemoverEfeitosNefastos(ListaEfeitoNefasto* inicio, int x, int y);






void MostrarLista(Antenas* inicio);

void MostrarListaNefasto(ListaEfeitoNefasto* inicio);

/**
 * @brief Liberta a memória alocada para a lista ligada de antenas.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 */
bool LimparMemoria(Antenas* inicio);

/**
 * @brief Liberta a memória alocada para a lista ligada do efeito nefasto.
 * 
 * @param inicio Ponteiro para o início da lista ligada.
 */
bool LimparMemoriaEfeito(ListaEfeitoNefasto* lista);
#endif