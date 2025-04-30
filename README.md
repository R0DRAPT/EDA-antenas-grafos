## Descrição do Projeto

Este projeto foi desenvolvido no âmbito da unidade curricular de **Estruturas de Dados Avançadas (EDA)**, lecionada pelo professor Luís Ferreira, no 2º semestre do 1º ano. O seu principal objetivo é reforçar e aplicar os conhecimentos adquiridos ao longo do semestre.

O projeto foca-se na modelação e análise da distribuição de antenas de transmissão numa cidade representada por uma matriz bidimensional. Cada antena possui uma frequência de ressonância, identificada por um caractere. O objetivo é processar esses dados, identificar padrões de interferência e estruturar as informações de forma eficiente, utilizando listas l0«igadas e grafos.

## Organização

- **`src/`**: Código da solução desenvolvida
- **`doxdoc/`**: Documentação com o relatório gerado pela ferramenta Doxygen

## Como Executar o Código

### Pré-requisitos

Certifique-se de que as seguintes ferramentas estão instaladas no sistema:
- [gcc](https://gcc.gnu.org/install/) 
- [make](https://www.gnu.org/software/make/)
- [Doxygen](https://www.doxygen.nl/index.html)

### Passos para Compilar e Executar

1. **Compilar o Código**

   Abra o terminal e navegue até a pasta onde o `Makefile` está localizado. Para compilar o código, execute o comando:
   ```[bash]
   make
   ```

2. **Executar o Programa**

   Após a compilação bem-sucedida, você pode executar o programa com o seguinte comando:
   ```[bash]
   make run
   ```

3. **Limpar Arquivos Gerados**

   Para remover os arquivos objetos e o executável gerado, execute:
   ```[bash]
   make clean
   ```
## Como Criar a Documentação com Doxygen

1. **Criar o Arquivo `Doxyfile`**

    No terminal, dentro do diretório do seu projeto, execute o seguinte comando para criar um arquivo de configuração `Doxyfile`:
    ```[bash]   
    doxygen -g
    ```
2. **Criar a Documentação**

    Após configurar o `Doxyfile`, execute o seguinte comando para criar a documentação:
    ```[bash]   
    doxygen Doxyfile
    ```