#include "utils.hpp"

size_t tamanho_maior_string(std::vector<std::string> strings){
    size_t maiorTamanho = (strings.size()>0)?strings[0].length():0;

    for(size_t i=1; i<strings.size();i++){
        const size_t tamanho = strings[i].length();

        if(tamanho > maiorTamanho)
            maiorTamanho = tamanho;
            
    }

    return maiorTamanho;
}

std::string to_upper_case(std::string texto){
    std::string maiusculo = "";

    
    for(size_t i=0; i<texto.length();i++){
        maiusculo += toupper(texto[i]);
    }

    return maiusculo;
}

std::string palavra_formato_secreto(std::string palavra){
    std::string separador = " ";
    std::string secreta = "";

    for(size_t i=0; i<palavra.length();i++){
        if(i==palavra.length()-1)
            separador = "";
        
        secreta+="_"+separador;
    }

    return secreta;
}

std::vector<std::string> dividir_string(std::string &texto, char separador){
    std::vector<std::string> partes = {};
    size_t comeco = 0;
    size_t fim = texto.find(separador, comeco);

    if(texto.compare("")==0)
        return partes;

    while(fim !=std::string::npos){ // Enquanto encontrar o caractere separador na string.
        partes.push_back(texto.substr(comeco, fim-comeco));
        comeco = fim+1;

        fim = texto.find(separador, comeco);
    }
    partes.push_back(texto.substr(comeco));

    return partes;
}

bool tem_caractere_especial(const std::string &texto){
    for(size_t i=0;i<texto.size();i++){
        const bool entre_a_z = texto[i]>='a' and texto[i]<='z';
        const bool entre_A_Z = texto[i]>='A' and texto[i]<='Z';

        if(!(entre_a_z or entre_A_Z) and texto[i]!=' ' and texto[i]!='-')
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