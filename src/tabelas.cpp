#include "tabelas.hpp"
#include "utils.hpp"

std::vector<std::string> get_palavras_scores(std::string stringPalavras){
    std::vector<std::string> palavras = {};
    std::vector<std::string> partes = dividir_string(stringPalavras,',');

    const std::string palavraInicial = (partes.size()>0)?partes[0].substr(1):"<nenhuma>";// Começa do 1 para eliminar o espaço
    palavras.push_back(palavraInicial);

    for(size_t i=1; i < partes.size(); i++){
        const std::string palavra = partes[i];

        palavras.push_back(palavra.substr(1)); // Adiciona a palavra sem o " " do começo na lista
    }

    return palavras;
}

std::vector<size_t> get_tamanhos_colunas(std::vector<std::string> linhas){
    std::string headerCol1 = "Dificuldade";
    std::string headerCol2 = "Jogador";
    std::string headerCol3 = "Palavras";
    std::string headerCol4 = "Pontos";


    std::vector<size_t> tamanhos = {headerCol1.length()+1, headerCol2.length()+2, headerCol3.length()+2, headerCol4.length()+1};

    for(size_t i=0;i<linhas.size();i++){
        std::vector<std::string> partes = dividir_string(linhas[i],';');
    
        const std::string dificuldade = partes[0];
        const std::string nome = partes[1].substr(1); // Pega começando do índice 1 para eliminar o " " do início
        const auto palavrasScores = get_palavras_scores(partes[2]);
        const size_t tamanhoMaiorPalavra = tamanho_maior_string(palavrasScores);
        const std::string pontos = partes[3].substr(1);
        
        // Verificação do maior e cálculo dos tamanhos
        tamanhos[0] = (dificuldade.length()>tamanhos[0])?dificuldade.length():tamanhos[0];
        tamanhos[1] = (nome.length()>tamanhos[1])?nome.length()+2:tamanhos[1];
        tamanhos[2] = (tamanhoMaiorPalavra>tamanhos[2])?tamanhoMaiorPalavra+2:tamanhos[2];
        tamanhos[3] = (pontos.length()>tamanhos[3])?pontos.length()+1:tamanhos[3];
    }

    return tamanhos;
}

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