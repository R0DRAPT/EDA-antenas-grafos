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
  * @brief Lê o ficheiro "mapaGrafos.txt" e imprime o seu conteúdo no terminal.
*/
Grafos* ListarMapaGrafos(const char *nomeFicheiro);




/**
 * @brief Liberta a memória alocada para a lista ligada dos grafos
 */
bool LimparMemoriaGrafos(Grafos* grafo);



#endif
