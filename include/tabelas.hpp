#include <vector>
#include <iostream>
#include <string>

/**
 * @brief Função para obter uma string que só tem espaços
 * 
 * @param tamanhoString O tamanho da string com espaços vazios
 * @return Uma std::string cujo conteúdo só tem espaços vazios
 */
std::string get_string_espacos(size_t tamanhoString);

/**
 * @brief Imprime uma linha da tabela com base nas palavras a serem imprimidas em cada coluna e no tamanho dessas colunas
 * 
 * @param opcoes Um vetor de pares em que o primeiro elemento de cada par corresponde a palavra e o segundo o tamanho da coluna
 */
void imprimir_linha(std::vector<std::pair<std::string, size_t>> &opcoes);