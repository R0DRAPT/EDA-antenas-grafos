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
  printf("\nRemover a Antena A - (2, 2)\n");
  ListaAntenasAux = RemoverAntena(ListaAntenasAux, listaNefasto, 2, 2);

  //Liberta a memória da lista de efeitos antiga
  LimparMemoriaEfeito(listaNefasto);

  //Volta a chamar a função "CalcularEfeitoNefasto" para voltar a calcular 
  listaNefasto = CalcularEfeitoNefasto(ListaAntenasAux);

  printf("\nLista apos remover a antena\n\n");
  MostrarLista(ListaAntenasAux);

  printf("\nEfeitos nefastos apos remover a antena\n\n");
  MostrarListaNefasto(listaNefasto);
  #pragma endregion

  #pragma region Listagem_Tabular
  //Listagem de forma tabular na consola das antenas e localizações com efeito nefasto.
  char* tabela = CriarTabela(ListaAntenasAux, listaNefasto);
    if (tabela) {
        printf("%s", tabela);
    } else {
        printf("Erro ao criar a tabela.\n");
    }
  #pragma endregion

  #pragma region Grava_E_Imprime_ListaAntena_Ficheiro_Bin
  const char* ficheiro = "Ficheiros/Bin_mapaAntenas";

  // Grava
  if (GravarListaFicheiro(ListaAntenasAux, ficheiro)) {
      printf("\nGravado com sucesso em '%s'\n", ficheiro);
  } else {
      printf("Erro ao gravar em '%s'\n", ficheiro);
  }

  // Lê
  char* conteudo = LerListaFicheiro(ficheiro);
  if (conteudo) {
      printf("Conteúdo do ficheiro:\n%s", conteudo);
      free(conteudo);
  } else {
      printf("Erro ao ler ficheiro '%s'\n", ficheiro);
  }

  #pragma endregion

  #pragma region Limpar_Memorias
  // Liberta a memória alocada da lista ligada de antenas
  LimparMemoria(ListaAntenasAux);
  // Liberta a memória alocada da lista ligada do efeito nefasto
  LimparMemoriaEfeito(listaNefasto);
  #pragma endregion

  return 0; // Retorna 0 em caso de sucesso.
}