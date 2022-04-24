#include "tabelas.hpp"
#include "utils.hpp"

std::vector<std::string> get_palavras_scores(std::string stringPalavras){
    std::vector<std::string> palavras = {};
    std::vector<std::string> partes = dividir_string(stringPalavras,',');


    const std::string palavraInicial = partes[0].substr(1);
    palavras.push_back((palavraInicial.length()>0)?palavraInicial:"<nenhuma>");

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
        tamanhos[1] = (nome.length()+2>tamanhos[1])?nome.length()+2:tamanhos[1];
        tamanhos[2] = (tamanhoMaiorPalavra+2>tamanhos[2])?tamanhoMaiorPalavra+2:tamanhos[2];
        tamanhos[3] = (pontos.length()+1>tamanhos[3])?pontos.length()+1:tamanhos[3];
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
        const size_t descontoAcentos = (tem_caractere_especial(palavra) and palavra.find('<')==std::string::npos)?1:0;
        caracteresLinha += get_string_espacos(tamanhoColuna - caracteresLinha.length() + descontoAcentos); // Adiciona os espaços necessários
            
        std::cout << caracteresLinha << divisorDeCelulas;
    }   
}

void imprimir_linha_divisoria(const std::vector<size_t> &tamanhosColunas){
    const size_t quant_colunas = 4;

    for(size_t i=0;i<quant_colunas;i++){
        const char caractere_final = (i==quant_colunas-1)?'-':'+';
        const size_t tamanho_coluna = tamanhosColunas[i];

        for(size_t j=0;j<tamanho_coluna;j++){
            std::cout << "-";
        }
        std::cout << caractere_final;
    }
    std::cout << std::endl; // Quebra de linha
}

void imprimir_tabela_scores(std::vector<std::string> scores){
    const std::vector<size_t> tamanhosColunas = get_tamanhos_colunas(scores);

    std::vector<std::pair<std::string, size_t>> opcoesLinha = { // Definir o cabeçalho da tabela
        std::make_pair("Dificuldade", tamanhosColunas[0]), std::make_pair("Jogador", tamanhosColunas[1]), 
        std::make_pair("Palavras", tamanhosColunas[2]), std::make_pair("Pontos", tamanhosColunas[3])
    };

    imprimir_linha(opcoesLinha); // Imprimir o cabeçalho da tabela
    opcoesLinha = {}; // Redefinir as opções de linha

    for(size_t i=0;i<scores.size();i++){
        const std::vector<std::string> partes = dividir_string(scores[i],';');

        
        const std::vector<std::string> palavras = get_palavras_scores(partes[2]);
        const std::string pontos = partes[3].substr(1);

        for(size_t j=0;j<palavras.size();j++){
            const std::string dificuldade = (j==0)?partes[0]:"";
            const std::string nome = (j==0)?partes[1].substr(1):"";
            const std::string palavra = palavras[j];
            const std::string pontos = (j==0)?partes[3].substr(1):"";

            opcoesLinha = { // Definir as opções da linha
                std::make_pair(dificuldade, tamanhosColunas[0]), std::make_pair(nome, tamanhosColunas[1]), 
                std::make_pair(palavra, tamanhosColunas[2]), std::make_pair(pontos, tamanhosColunas[3])
            };

            imprimir_linha(opcoesLinha);
        }

        if(i!=scores.size()-1) // Se não for o último registro
            imprimir_linha_divisoria(tamanhosColunas);
    }
}