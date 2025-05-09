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
 #include "funcoesFase2.h"
 
 /**
  * @brief Função principal do programa.
  *     
  */
 int main() {
    #pragma region FASE_1

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
        printf("\n\nLista Antenas         Efeitos Nefastos\n");
        printf("--------------------- -------------------\n");
        printf("Freq    X    Y        | X    Y\n");

        Antenas* ant = ListaAntenasAux;
        ListaEfeitoNefasto* nef = listaNefasto;

        char freq;
        int xA, yA, xN, yN;

        while (ProximaLinhaTabular(&ant, &nef, &freq, &xA, &yA, &xN, &yN)) {
            if (freq != '\0') {
                printf(" %-6c %-4d %-4d     |", freq, xA, yA);
            } else {
                printf("                      |");
            }

            if (xN != 0 || yN != 0) {
                printf(" %-4d %-4d\n", xN, yN);
            } else {
                printf("\n");
            }
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
        printf("Conteudo do ficheiro:\n%s", conteudo);
        free(conteudo);
    } else {
        printf("Erro ao ler ficheiro '%s'\n", ficheiro);
    }
    #pragma endregion

    printf("\n----------------------------------------------\n\n");
    #pragma endregion
    
    #pragma region FASE_2

    #pragma region Declaração_Variaveis
    // Ponteiros para listas ligadas
    Grafos* listaGrafos = NULL; // Lista principal.
    Grafos* ListaGrafosAux = NULL; // Lista auxiliar 
    Vertices* ListaVerticesAux = NULL; //Lista Vertices
    #pragma endregion

    #pragma region Lista_mapaVertices.txt
    // Lista o mapa das antenas disponíveis
    ListarMapaVertices("Ficheiros/mapaVertices.txt");
    printf("\n\n");
    #pragma endregion

    #pragma region Carrega_Vertices_Do_mapaGrafo
    // Carrega os vertices a partir de um ficheiro de texto
    ListaVerticesAux = CarregarMapaVertices("Ficheiros/mapaVertices.txt");
    if (ListaVerticesAux == NULL) {
        return 1; // Retorna 1 em caso de erro.
    }
    #pragma endregion

    #pragma region Cria_&_Insere_Vertices
    // Cria o vertice e depois insere-o no inicio da lista ligada
    Vertices* g1 = CriarVertice('A', 2, 2);
    ListaVerticesAux = InserirVerticeInicio(ListaVerticesAux, g1);

    // Cria o vertice e depois insere-o no fim da lista principal
    Vertices* g2 = CriarVertice('C', 7, 7);
    ListaVerticesAux = InserirVerticeFim(ListaVerticesAux, g2);

    // Cria o vertice e depois insere-o lista principal ordenadamente
    Vertices* g3 = CriarVertice('H', 1, 1);
    ListaVerticesAux = InserirVerticeOrdenado(ListaVerticesAux, g3);

    // Cria o vertice e depois insere-o lista principal ordenadamente
    // Vertices* g4 = CriarVertice('H', 9, 4);
    // ListaVerticesAux = InserirVerticeOrdenado(ListaVerticesAux, g4);

    MostrarListaVertices(ListaVerticesAux);
    #pragma endregion

    #pragma region Cria_&_Insere_Arestas
    // Cria adjacencias bidirecionais entre vértices com a mesma frequência
    if (CriarArestasMesmoFreq(ListaVerticesAux)) {
        printf("\nAdjacencias criadas com sucesso entre vertices com mesma frequencia.\n");
    } else {
        printf("\nErro ao criar as adjacencias.\n");
    }

    // Mostra os vértices com suas adjacências
    printf("\nLista de vertices com suas adjacencias:\n");
    MostrarAdjacencias(ListaVerticesAux);
    #pragma endregion

    #pragma region Criar_Grafo
    if (ListaVerticesAux == NULL) {
        printf("Erro: Lista de vértices vazia.\n");
        return 1;
    }

    Grafos* grafoFinal = CriarGrafo(ListaVerticesAux);
    if (grafoFinal != NULL) {
        printf("Grafo criado com %d vértices e %d arestas.\n", grafoFinal->numVertices, grafoFinal->numArestas);
    }
    #pragma endregion

    #pragma region Procura_Em_Profundidade
    if (ListaVerticesAux == NULL) {
        printf("Erro: Lista de vértices vazia.\n");
        return 1;
    }

    Visitados* resultado = ProcuraProfundidade(ListaVerticesAux, 3, 7);
    Visitados* aux = resultado;

    printf("\n");
    while (aux != NULL) {
        printf("Visitado: %c (%d, %d)\n", aux->vertice->freq, aux->vertice->x, aux->vertice->y);
        aux = aux->prox;
    }
    printf("\n");
    #pragma endregion

    #pragma region Procura_Em_Largura 
    Visitados* resultadoLargura = ProcuraLargura(ListaVerticesAux, 2, 2);
    Visitados* temp = resultadoLargura;
    
    while (temp != NULL) {
        printf("Antena alcançada: (%d, %d)\n", temp->vertice->x, temp->vertice->y);
        temp = temp->prox;
    }
    #pragma endregion

    #pragma region Encontrar_Caminhos
    // Encontra e mostra o caminho entre dois vértices no grafo
    Caminho* caminhoEncontrado = ListarTodosCaminhos(grafoFinal, 2, 2, 6, 8);

    if (caminhoEncontrado != NULL) {
        printf("\nCaminho(s) encontrado(s):\n");
        int n = 1;
        for (Caminho* atual = caminhoEncontrado; atual != NULL; atual = atual->prox) {
            printf("Caminho %d: ", n++);
            Visitados* v = atual->vertices;
            while (v != NULL) {
                printf("(%c - %d,%d)", v->vertice->freq, v->vertice->x, v->vertice->y);
                if (v->prox != NULL) printf(" -> ");
                v = v->prox;
            }
            printf("\n");
        }
    } else {
        printf("\nNenhum caminho encontrado");
    }
    printf("\n");
    #pragma endregion

    #pragma region Listar_Intersecoes_Por_Freq
    ListaPares lista = ObterParesEntreFrequencias(grafoFinal, 'A', '0');

    printf("Pares entre antenas 'A' e '0':\n");
    for (int i = 0; i < lista.tamanho; i++) {
        printf("(%c - %d,%d) <-> (%c - %d,%d)\n",
               lista.pares[i].a->freq, lista.pares[i].a->x, lista.pares[i].a->y,
               lista.pares[i].b->freq, lista.pares[i].b->x, lista.pares[i].b->y);
    }
    
    #pragma endregion

    #pragma endregion


    #pragma region Limpar_Memorias
    // Liberta a memória alocada da lista ligada de antenas
    LimparMemoria(ListaAntenasAux);
    // Liberta a memória alocada da lista ligada do efeito nefasto
    LimparMemoriaEfeito(listaNefasto);
    // Liberta listas auxiliares e grafos
    LimparMemoriaGrafos(grafoFinal);
    #pragma endregion

    return 0; 
}