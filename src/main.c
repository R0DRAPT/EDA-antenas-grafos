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
 #include <stdbool.h>
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
  // Cria a antena e depois insere-a no inicio da lista ligada
  printf("\n");
  Antenas* a1 = CriarAntena('A', 2, 2);
  ListaAntenasAux = InserirAntenaInicio(ListaAntenasAux, a1);

  // Cria a antena e depois insere-a no fim da lista principal
  Antenas* a2 = CriarAntena('C', 7, 7);
  ListaAntenasAux = InserirAntenaFim(ListaAntenasAux, a2);

  // Cria a antena e depois insere-a lista principal ordenadamente
  Antenas* a3 = CriarAntena('H', 1, 1);
  ListaAntenasAux = InserirAntenasOrdenado(ListaAntenasAux, a3);

  MostrarLista(ListaAntenasAux);
  #pragma endregion

  #pragma region Modifica_Antena
  //Modifica uma antena criada previamente
  printf("\nAntena Modificada\n");
  ListaAntenasAux = ModificarAntena(ListaAntenasAux, 7, 7, 'I', 3, 6);
  #pragma endregion

  #pragma region Calcular_Efeito_Nefasto
  //Chama a funcao "EfeitoNefasto" onde e calculado o efeito nefasto das antenas na lista ligada
  printf("\nEfeito nefasto calculado\n");
  listaNefasto = CalcularEfeitoNefasto(ListaAntenasAux);
  printf("\n");
  MostrarListaNefasto(listaNefasto);
  #pragma endregion

  #pragma region Remover_Antena
  ListaAntenasAux = RemoverAntena(ListaAntenasAux, listaNefasto, 2, 2);

  //Liberta a memória da lista de efeitos antiga
  LimparMemoriaEfeito(listaNefasto);

  //Volta a chamar a função "CalcularEfeitoNefasto" para voltar a calcular 
  listaNefasto = CalcularEfeitoNefasto(ListaAntenasAux);

  // MostrarLista(ListaAntenasAux);
  // printf("\n");
  // printf("Nefastoooo ----------------\n");
  // MostrarListaNefasto(listaNefasto);
  #pragma endregion

  #pragma region Limpar_Memorias
  // Liberta a memória alocada da lista ligada de antenas
  LimparMemoria(ListaAntenasAux);
  // Liberta a memória alocada da lista ligada do efeito nefasto
  LimparMemoriaEfeito(listaNefasto);
  #pragma endregion

  return 0; // Retorna 0 em caso de sucesso.
}