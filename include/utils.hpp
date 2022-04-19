#include <vector>
#include <string>
#include <iostream>

/**
 * Divide uma string com base em um caractere separador.
 * 
 * @param texto string que será dividida 
 * @param separador caractere que será considerado para separar as partes da string
 * @return Um std::vector de strings com as partes da string separada 
 */
std::vector<std::string> dividir_string(std::string &texto, char separador);

/**
 * @brief Verifica se uma string possui algum caractere que não está entre a e z (Maiúsculo ou minúsculo).
 * 
 * @param texto String a ser verificada
 * @return true se a string possui algum caractere que não esteja entre a e z (Ou A e Z) e false caso contrário.
 */
bool tem_caractere_especial(std::string &texto);

/**
 * @brief Verifica se uma determinada string pode ser convertida em inteiro.
 * 
 * @param texto String a ser verificada
 * @return true se a string puder ser convertida em inteiro e false caso contrário.
 */
bool pode_ser_int(std::string texto);