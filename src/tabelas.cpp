#include "tabelas.hpp"

std::string get_string_espacos(size_t tamanhoString){
    std::string espacos = "";

    for(size_t i=0;i<tamanhoString;i++){
        espacos+=" ";
    }

    return espacos;
}

void imprimir_linha(std::vector<std::pair<std::string, size_t>> &opcoes){
    std::string caracteresLinha = "";
    std::string divisorDeCelulas;

    for(size_t i=0;i<opcoes.size();i++){
        caracteresLinha = "";
        divisorDeCelulas = (i==opcoes.size()-1)?"\n":"|"; // Se for a última palavra termina com \n, se não termina com |

        const std::string palavra = opcoes[i].first;
        const size_t tamanhoColuna = opcoes[i].second;

        if(i>0){ // Se não for a primeira linha
            caracteresLinha = " ";
        }

        caracteresLinha += palavra; // Adiciona a palavra na linha a ser impressa
        caracteresLinha += get_string_espacos(tamanhoColuna - caracteresLinha.length()); // Adiciona os espaços necessários
            
        std::cout << caracteresLinha << divisorDeCelulas;
    }   
}