/**
 * @file main.c
 * @author Rodrigo Miranda (a31509@alunos.ipca.pt)
 * @brief Ficheiro principal do programa para gerir antenas.
 * @version 0.1
 * @date 2025-03-18
 * 
 * @copyright Copyright (c) 2025
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "funcoes.h"
 
 /**
  * @brief Função principal do programa.
  *     
  */
 int main() {
  #pragma region Declaração_Variaveis
  // Ponteiros para listas ligadas de antenas
  Antenas* listaAntenas = NULL; // Lista principal de antenas.
  ListaEfeitoNefasto* listaNefasto = NULL; //Lista principal do efeito nefasto
  Antenas* ListaAntenasAux = NULL; // Lista auxiliar
  #pragma endregion
  
  #pragma region Lista_mapaAntena.txt
  // Lista o mapa das antenas disponíveis
  ListarMapaAntenas("Ficheiros/mapaAntenas.txt");
  printf("\n");
  #pragma endregion

  #pragma region Carrega_Antenas_Do_mapaAntena
  // Carrega as antenas a partir de um ficheiro de texto
  ListaAntenasAux = CarregarMapaAntenas("Ficheiros/mapaAntenas.txt");
  if (ListaAntenasAux == NULL) {
    return 1; // Retorna 1 em caso de erro.
  }
  #pragma endregion

  #pragma region Cria_&_Insere_Antena
  // Criação e inserção de antenas no início da lista principal
  Antenas* a1 = CriarAntena('A', 1, 1);
  ListaAntenasAux = InserirAntenaInicio(ListaAntenasAux, a1);

  // Criação e inserção de antenas no fim da lista principal
  Antenas* a2 = CriarAntena('C', 7, 7);
  ListaAntenasAux = InserirAntenaFim(ListaAntenasAux, a2);

  // Criação e inserção de antenas na lista principal ordenadamente
  Antenas* a3 = CriarAntena('J', 6, 6);
  ListaAntenasAux = InserirAntenasOrdenado(ListaAntenasAux, a3);

  MostrarLista(ListaAntenasAux);
  #pragma endregion

  

  return 0; // Retorna 0 em caso de sucesso.
}