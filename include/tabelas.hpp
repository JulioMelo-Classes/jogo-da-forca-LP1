#include <vector>
#include <iostream>
#include <string>

/**
 * @brief Obter as palavras acertadas do score
 * 
 * @param stringPalavras A Parte da string que armazena todas as palavras
 * @return Um std::vector de strings com cada palavra de um score específico 
 */
std::vector<std::string> get_palavras_scores(std::string stringPalavras);

/**
 * @brief Obter o tamanho que as colunas devem ter com base nas palavras
 * 
 * @param linhas Um std::vector<std::string> no formato "coluna1; coluna2; coluna3; coluna 4"
 * @return Um std::vector com o tamanho de cada coluna 
 */
std::vector<size_t> get_tamanhos_colunas(std::vector<std::string> linhas);

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