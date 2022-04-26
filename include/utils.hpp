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

template <typename Type>
/**
 * @brief Apaga um elemento de um vetor apartir do índice
 * 
 * @param indice O índice do elemento que pretende remover do vetor
 * @param vetor vetor do qual deseja apagar o elemento
 */
void apagar_por_indice(int indice, std::vector<Type> &vetor){
    auto iterator = vetor.begin();

    vetor.erase(iterator+indice);
}

/**
 * @brief Calcula o tamanho da maior string de uma lista
 * 
 * @param strings Uma lista com as strings
 * @return size_t O tamanho da maior string
 */
size_t tamanho_maior_string(std::vector<std::string> strings);

/**
 * @brief Deixar em maiúsculo uma string sem acentos.
 * 
 * @param texto string a ser convertida
 * @return a string passada convertida para maiúsculo
 */
std::string to_upper_case(std::string texto);

/**
 * @brief Gera uma palavra no formato "_ _ _ ... _" a partir de outra palavra
 * 
 * @param palavra Palavra a ser convertida no formato
 * @return Uma std::string no formato "_ _ _ ... _"
 */
std::string palavra_formato_secreto(std::string palavra);

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