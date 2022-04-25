#include <vector>
#include <string>
#include <iostream>

template <typename Type>
/**
 * @brief Verifica se um determinado elemento está em um vetor específico
 * 
 * @param elemento O elemento que que será buscado no vetor
 * @param vetor O vetor que servirá como base para a busca
 * @return true se o elemento está no vetor e false caso contrário
 */
bool esta_no_vetor(Type elemento, std::vector<Type> vetor){
    for(size_t i=0;i<vetor.size();i++){
        if(elemento == vetor[i])
            return true;
    }
    
    return false;
}

/**
 * @brief Calcula o tamanho da maior string de uma lista
 * 
 * @param strings Uma lista com as strings
 * @return size_t O tamanho da maior string
 */
size_t tamanho_maior_string(std::vector<std::string> strings);

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
bool tem_caractere_especial(const std::string &texto);

/**
 * @brief Verifica se uma determinada string pode ser convertida em inteiro.
 * 
 * @param texto String a ser verificada
 * @return true se a string puder ser convertida em inteiro e false caso contrário.
 */
bool pode_ser_int(std::string texto);