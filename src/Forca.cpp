#include "Forca.hpp"
#include <fstream>
#include <iostream>
#include <utils.hpp>

Forca::Forca(std::string palavras, std::string scores){
    this->m_arquivo_palavras = palavras;
    this->m_arquivo_scores = scores;
}

void Forca::carregar_arquivos(){
    std::ifstream palavras_stream(this->m_arquivo_palavras);
    std::ifstream score_stream(this->m_arquivo_scores);
    std::string linha = "";

    // Processar o arquivo de palavras
    if(palavras_stream.is_open()){
        while(linha!="\n" or !palavras_stream.eof()){
            getline(std::cin, linha);
            const std::vector<std::string> partes = dividirString(linha,'\t');
            
            if(partes.size()==2){ // Se a string separada resultou em duas partes
                const std::string palavra = partes[0];
                const int ocorrencias = pode_ser_int(partes[1])?std::stoi(partes[1]):-2;
                
                std::pair<std::string, int> par;
                par.first = palavra;
                par.second = ocorrencias;

                this->m_palavras.push_back(par);
            }
        }
    }else{
        std::pair<std::string, int> par;
        par.first = "file_not_find";
        par.second = -1;

        this->m_palavras.push_back(par);
    }
    palavras_stream.close();

    // Processar o arquivo de scores
    if(score_stream.is_open()){
        linha = "";
        while(!score_stream.eof()){
            getline(std::cin, linha);
            this->linhas_scores.push_back(linha);
        }

    }else{
        this->linhas_scores.push_back("file_not_found");
    }

}


