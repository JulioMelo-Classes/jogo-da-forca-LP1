#include <fstream>
#include <iostream>

#include "Forca.hpp"
#include "utils.hpp"
#include <random>

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
            mensagem = "A palavra '"+par.first+"' na linha " + std::to_string(numero_da_linha) + " possui algum caracter especial (ç, @ etc).";
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
            mensagem = "A pontuação não é um número inteiro na linha "+std::to_string(numero_da_linha) +" do arquivo de scores";
            return std::make_pair(false, mensagem);
        }if(dificuldade.empty() or nome.empty()){ // Se o nome ou a dificuldade estão vazios
            mensagem = "Algum dos campos (Nome ou dificuldade) estão vazios na linha " + std::to_string(numero_da_linha);
            return std::make_pair(false, mensagem);
        }

        numero_da_linha++;
    }
    
    return std::make_pair(true, ""); 
}

void Forca::carregar_palavras_base(){

    for(auto par: this->m_palavras){
        const std::string palavra = par.first;
        const int ocorrencias = par.second;

        if(ocorrencias>=this->media_ocorrencias){
            this->palavras_populares.push_back(palavra);
            
            if(ocorrencias==this->media_ocorrencias)
                this->palavras_na_media.push_back(palavra);

            continue;
        }
            
        palavras_nao_populares.push_back(palavra);
    }
}

void Forca::set_dificuldade(Forca::Dificuldade d){
    this->m_palavras_do_jogo = {}; // Reinicia as palavras do jogo
    this->m_dificuldade = d;

    switch(d){
        case Forca::Dificuldade::FACIL: // Dificuldade fácil escolhida

            while(this->m_palavras_do_jogo.size()<10){ // Enquanto não forem sorteadas 10 palavras
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_int_distribution<int> distr(0, this->palavras_populares.size()-1);
                
                const int indice_gerado = distr(eng); // Numero gerado entre 0 e a quantidade de palavras
                std::string palavra = this->palavras_populares[indice_gerado];
            
                const bool eh_igual_a_media = esta_no_vetor(palavra ,palavras_na_media);
                const bool foi_sorteada = esta_no_vetor(palavra, this->m_palavras_do_jogo);

                if(!eh_igual_a_media and !foi_sorteada)
                    this->m_palavras_do_jogo.push_back(palavra);
                    
            }

            break;
        case Forca::Dificuldade::MEDIO: // Dificuldade médio escolhida
            while(this->m_palavras_do_jogo.size()<6){ // Gera as 6 palavras com frequência menor do que a média
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_int_distribution<int> distr(0, this->palavras_nao_populares.size()-1);
                
                const int indice_gerado = distr(eng);
                std::string palavra = this->palavras_nao_populares[indice_gerado];
                const bool foi_sorteada = esta_no_vetor(palavra, this->m_palavras_do_jogo);

                if(!foi_sorteada)
                    this->m_palavras_do_jogo.push_back(palavra);
            }

            while(this->m_palavras_do_jogo.size()<20){
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_int_distribution<int> distr(0, this->palavras_populares.size()-1);

                const int indice_gerado = distr(eng);
                std::string palavra = this->palavras_populares[indice_gerado];
                const bool foi_sorteada = esta_no_vetor(palavra, this->m_palavras_do_jogo);

                if(!foi_sorteada)
                    this->m_palavras_do_jogo.push_back(palavra);
            }

            break;
        
        case Forca::Dificuldade::DIFICIL: // Dificuldade difícil escolhida
            while(this->m_palavras_do_jogo.size()<22){
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_int_distribution<int> distr(0, this->palavras_nao_populares.size()-1);

                const int indice_gerado = distr(eng);
                std::string palavra = this->palavras_nao_populares[indice_gerado];
                const bool foi_sorteada = esta_no_vetor(palavra, this->m_palavras_do_jogo);

                if(!foi_sorteada)
                    this->m_palavras_do_jogo.push_back(palavra);
            }
            
            while(this->m_palavras_do_jogo.size()<30){
                std::random_device rd;
                std::default_random_engine eng(rd());
                std::uniform_int_distribution<int> distr(0, this->palavras_populares.size()-1);

                const int indice_gerado = distr(eng);
                std::string palavra = this->palavras_populares[indice_gerado];
                const bool foi_sorteada = esta_no_vetor(palavra, this->m_palavras_do_jogo);

                if(!foi_sorteada)
                    this->m_palavras_do_jogo.push_back(palavra);
            }
    }
}

std::string Forca::proxima_palavra(){
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(0, this->m_palavras_do_jogo.size()-1);

    const int indice_gerado = distr(eng);
    std::string palavra_maiusculo = to_upper_case(this->m_palavras_do_jogo[indice_gerado]);
    this->m_palavra_atual = palavra_maiusculo;
    apagar_por_indice(indice_gerado, this->m_palavras_do_jogo);
    this->m_palavra_jogada = palavra_formato_secreto(palavra_maiusculo);

    return this->m_palavra_jogada;
}

void Forca::gerar_letras_aleatorias(){
    std::vector<char> letras = {};
    int qnt_letras_sorteio;

    if(this->m_dificuldade== Forca::Dificuldade::FACIL){
        letras = get_consoantes(this->m_palavra_atual);
        int tamanho_sobre_5 = (int) this->m_palavra_atual.length()/5;
        qnt_letras_sorteio = (tamanho_sobre_5>1)?tamanho_sobre_5:1;

        while(qnt_letras_sorteio>0 and letras.size()>0){
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_int_distribution<int> distr(0, letras.size()-1);

            const int indice_gerado = distr(eng);
            const char letra = letras[indice_gerado];

            for(size_t i=0;i<this->m_palavra_atual.length();i++){
                if(letra == this->m_palavra_atual[i]){
                    this->m_palavra_jogada[i*2] = toupper(letra);
                    this->m_letras_palpitadas.push_back(toupper(letra));
                } 

            }

            apagar_por_indice(indice_gerado, letras); // Apaga a letra gerada do vetor de letras
            qnt_letras_sorteio-=1; // Decrementa em 1 a quantidade de letras a serem geradas no sorteio
        }
    }else if(this->m_dificuldade == Forca::Dificuldade::MEDIO){
        letras = get_vogais(this->m_palavra_atual);
        qnt_letras_sorteio = 1;

        if(letras.size()>0){
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_int_distribution<int> distr(0, letras.size()-1);

            const int indice_gerado = distr(eng);
            const char letra = letras[indice_gerado];

            for(size_t i=0;i<this->m_palavra_atual.length();i++){
                if(letra == this->m_palavra_atual[i]){
                    this->m_palavra_jogada[i*2] = toupper(letra);
                    this->m_letras_palpitadas.push_back(toupper(letra));
                }
            }

            apagar_por_indice(indice_gerado, letras); // Apaga a letra gerada do vetor de letras
            qnt_letras_sorteio-=1;
        }
    }

}

std::pair<bool, bool> Forca::palpite(std::string palpite){
    const char letra_palpite = toupper(palpite.at(0)); // A letra será a primeira letra da string em maiúsculo
    const bool foi_palpitada = esta_no_vetor(letra_palpite, this->m_letras_palpitadas);

    if(!foi_palpitada){
        unsigned int aparicoes_da_letra = 0;
        this->m_letras_palpitadas.push_back(letra_palpite); // Adiciona o palpite no vetor de letras palpitadas

        for(size_t l=0;l < this->m_palavra_atual.length();l++){
            if(letra_palpite==this->m_palavra_atual[l]){
                this->m_palavra_jogada[l*2] = letra_palpite;
                aparicoes_da_letra++;
                this->pontos_jogador += 1; // Incrementa em 1 os pontos do jogador
            }
        }

        if(aparicoes_da_letra>0)
            return std::make_pair(true, true); // Pertence a palavra e é um palpite novo

        this->pontos_jogador -=1; // Tira 1 ponto do jogador
        this->m_tentativas_restantes-=1;
        return std::make_pair(false, true); // Não pertence a palavra mas é um palpite novo
    }

    return std::make_pair(false, false);
}

bool Forca::acertou_palavra(){
    for(size_t l=0;l<this->m_palavra_jogada.length();l+=2){ // Pula de 2 em 2 índices pois os índices ímpares são só underlines
        if(this->m_palavra_jogada.at(l) == '_'){ // Se ainda tiver alguma letra não encontrada
            return false;
        }  
    }

    return (this->m_palavra_jogada.length()>0)?true:false;
}

bool Forca::rodada_terminada(){
    bool const tentativas_acabadas = this->m_tentativas_restantes == 0;
    const bool palavra_acertada = this->acertou_palavra();

    if(tentativas_acabadas or palavra_acertada) // Se acabaram as tentativas ou a palavra foi acertada
        return true;
    
    return false;
}

void Forca::reset_rodada(){
    this->m_tentativas_restantes = 6;
    this->m_letras_palpitadas = {};
}

void Forca::add_linha_score(std::string linha){
    this->linhas_scores.push_back(linha);
}

// ------------------------------------------------ Getters ---------------------------------------------------------------------

double Forca::get_media_ocorrencias(){
    return this->media_ocorrencias;
}

std::vector<std::string> Forca::get_linhas_scores(){
    return this->linhas_scores;
}

std::string Forca::get_palavra_jogada(){
    return this->m_palavra_jogada;
}

std::string Forca::get_palavra_atual(){
    return this->m_palavra_atual;
}

std::vector<std::string> Forca::get_palavras_do_jogo(){
    return this->m_palavras_do_jogo;
}

int Forca::get_tentativas_restantes(){
    return this->m_tentativas_restantes;
}

