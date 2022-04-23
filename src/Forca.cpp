#include <fstream>
#include <iostream>

#include "Forca.hpp"
#include "utils.hpp"

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
        getline(palavras_stream, linha);

        while(linha!="\n" and !palavras_stream.eof()){
            const std::vector<std::string> partes = dividir_string(linha,'\t');
            std::pair<std::string, int> par;

            if(partes.size()==2){ // Se a string separada resultou em duas partes
                const std::string palavra = partes[0];
                const int ocorrencias = pode_ser_int(partes[1])?std::stoi(partes[1]):-2;

                par.first = palavra;
                par.second = ocorrencias;

                this->m_palavras.push_back(par);
            }else{
                par.first = "invalid_format";
                par.second = -1;
                
                this->m_palavras.push_back(par);
                break;
            }

            getline(palavras_stream, linha);
        }
        palavras_stream.close();

    }else{
        std::pair<std::string, int> par;
        par.first = "file_not_found";
        par.second = -1;

        this->m_palavras.push_back(par);
    }

    // Processar o arquivo de scores
    if(score_stream.is_open()){
        getline(score_stream, linha);
        while(linha!="\n" and !score_stream.eof()){
            this->linhas_scores.push_back(linha);

            getline(score_stream, linha);
        }
        score_stream.close();
    }else{
        this->linhas_scores.push_back("file_not_found");
    }

}

std::pair<bool, std::string> Forca::eh_valido(){
    this->media_ocorrencias = 0;
    std::string mensagem = "";

    size_t numero_da_linha = 1;
    size_t quant_palavras = this->m_palavras.size();

    for(std::pair<std::string, int> par: this->m_palavras){ // Percorre o vetor com as palavras e ocorrências

        if(par.first.compare("file_not_found")==0 and par.second==-1){ // Arquivo não encontrado
            mensagem = "Arquivo '" + this->m_arquivo_palavras + "' não encontrado!";
            return std::make_pair(false, mensagem); 
        }if(par.first.compare("invalid_format")==0 and par.second<0){ // Se a linha possui o formato inválido
            mensagem = "A linha " + std::to_string(numero_da_linha) + " não está com a formatação correta!";
            return std::make_pair(false, mensagem);
        }if(tem_caractere_especial(par.first)){// Se a palavra tem algum caractere especial
            mensagem = "A palavra '"+par.first+"' na linha " + std::to_string(numero_da_linha) + " possui algum caracter especial (Espaço, @ etc).";
            return std::make_pair(false, mensagem);
        }if(par.second<0){ // Ocorrências negativas ou não possui ocorrências correspondentes
            mensagem = "A palavra '"+par.first+"' na linha "+std::to_string(numero_da_linha)+" possui uma frequência correspondente inválida!";
            return std::make_pair(false, mensagem);
        }if(par.first.length()<5){
            mensagem = "A palavra '"+par.first+"' na linha "+std::to_string(numero_da_linha)+" possui um tamanho menor do que 5";
            return std::make_pair(false, mensagem);
        }

        numero_da_linha++;
        this->media_ocorrencias += ((double) par.second)/quant_palavras;
    }

    numero_da_linha = 1; // Reinicia a contagem da linha

    for(std::string linha: this->linhas_scores){ // Percorre as linhas dos scores
        const std::vector<std::string> partes = dividir_string(linha,';');
        
        std::string mensagem = "";

        if(linha.compare("file_not_found")==0){
            mensagem = "Arquivo '" + this->m_arquivo_scores +"' não encontrado";
            return std::make_pair(false, mensagem);
        }if(partes.size()!=4){ // Se ao dividir a linha por ; não resultou em 4 partes
            mensagem = "Presença de mais ou menos 3 ';' na linha " + std::to_string(numero_da_linha);
            return std::make_pair(false, mensagem);
        }
        

        const std::string dificuldade = partes[0];
        const std::string nome = partes[1].substr(1); // Inicia do índice 1 para eliminar o " "
        const std::string pontuacao = partes[3].substr(1);
        
        if(!pode_ser_int(pontuacao)){
            mensagem = "A pontuação não é um número inteiro na linha "+std::to_string(numero_da_linha);
            return std::make_pair(false, mensagem);
        }if(dificuldade.empty() or nome.empty()){ // Se o nome ou a dificuldade estão vazios
            mensagem = "Algum dos campos (Nome ou dificuldade) estão vazios na linha " + std::to_string(numero_da_linha);
            return std::make_pair(false, mensagem);
        }

        numero_da_linha++;
    }
    
    return std::make_pair(true, ""); 
}

// ------------------------------------------------ Getters ---------------------------------------------------------------------

double Forca::get_media_ocorrencias(){
    return this->media_ocorrencias;
}

std::vector<std::string> Forca::get_linhas_scores(){
    return this->linhas_scores;
}

