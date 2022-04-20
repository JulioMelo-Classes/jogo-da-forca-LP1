#include "utils.hpp"

std::vector<std::string> dividir_string(std::string &texto, char separador){
    std::vector<std::string> partes = {};
    size_t comeco = 0;
    size_t fim = texto.find(separador, comeco);

    while(fim !=std::string::npos){ // Enquanto encontrar o caractere separador na string.
        partes.push_back(texto.substr(comeco, fim-comeco));
        comeco = fim+1;

        fim = texto.find(separador, comeco);
    }
    partes.push_back(texto.substr(comeco));

    return partes;
}

bool tem_caractere_especial(std::string &texto){
    for(size_t i=0;i<texto.size();i++){
        const bool entre_a_z = texto[i]>='a' and texto[i]<='z';
        const bool entre_A_Z = texto[i]>='A' and texto[i]<='Z';

        if(!(entre_a_z or entre_A_Z))
            return true;
    }

    return false;
}

bool pode_ser_int(std::string texto){
    try{
        int number = std::stoi(texto);

        return true;
    }catch(std::invalid_argument const &e){
        return false;
    }

    return false;
}