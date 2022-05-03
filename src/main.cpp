#include <iostream>
#include "Forca.hpp"
#include "tabelas.hpp"
#include <fstream>

/**
 * @brief Imprime uma confirmação de que os arquivos foram lidos sem problemas
 * 
 */
void exibe_confirmacao_arquivos(){
    std::cout << "--------------------------------------" << std::endl;
    std::cout << ">>> Arquivos OK!" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

/**
 * @brief Exibe o menu principal e lê a escolha do usuário
 * 
 * @return Um valor referente ao número digitado pelo usuário 
 */
unsigned int exibe_menu_principal(){
    unsigned int opcao = -1;

    std::cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << std::endl;
    std::cout << "1 - Iniciar o Jogo" << std::endl;
    std::cout << "2 - Ver Scores Anteriores" << std::endl;
    std::cout << "3 - Sair do Jogo" << std::endl;

    std::cout << "Sua escolha: " << std::endl;
    std::cin >> opcao;

    return opcao;
}

Forca::Dificuldade exibe_menu_dificuldades(){
    unsigned int opcao = -1;

    std::cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade" << std::endl;
    std::cout << "1 - Fácil" << std::endl;
    std::cout << "2 - Médio" << std::endl;
    std::cout << "3 - Difícil" << std::endl;
    
    std::cout << "Sua escolha: " << std::endl;
    std::cin >> opcao;

    switch(opcao){
        case 2: return Forca::Dificuldade::MEDIO;
        case 3: return Forca::Dificuldade::DIFICIL;
    }

    return Forca::Dificuldade::FACIL;
}

std::string nome_da_dificuldade(Forca::Dificuldade d){
    switch(d){
        case Forca::Dificuldade::FACIL: return "Fácil";
        case Forca::Dificuldade::MEDIO: return "Médio";
        case Forca::Dificuldade::DIFICIL: return "Difícil";
    }

    return "<dificuldade_não_reconhecida>";
}

std::string str_palavras_acertadas(std::vector<std::string> palavras_acertadas){
    std::string str_palavras = "";
    std::string separador = ",";

    for(size_t i=0;i<palavras_acertadas.size();i++){
        if(i==palavras_acertadas.size()-1) // Se for a última palavra
            separador = "";
        
        str_palavras+=" " + palavras_acertadas[i] + separador;
    }

    return (palavras_acertadas.size()!=0)?str_palavras:" ";
}

/**
 * @brief Atualiza o arquivo de scores com base nas informações
 * 
 * @param dificuldade Dificuldade do jogo em string (Fácil, Médio ou Difícil)
 * @param palavras_acertadas Um vetor de strings com as palavras acertadas pelo jogador
 * @param pontos Pontos obtidos pelo jogador
 */
void atualizar_score(Forca &forca, std::string dificuldade, std::vector<std::string> palavras_acertadas, int pontos, std::string arquivo_scores){
    std::ofstream score_stream(arquivo_scores, std::ios::app);

    std::string str_palavras = str_palavras_acertadas(palavras_acertadas);
    std::string jogador;

    std::cout << "Informe o nome do jogador: " << std::endl;
    std::cin.ignore();

    std::getline(std::cin, jogador);

    std::string linha_score = dificuldade + "; " + jogador + ";" + str_palavras + "; " + std::to_string(pontos);

    score_stream << linha_score << std::endl; // Adiciona a linha no arquivo score
    forca.add_linha_score(linha_score); // Adiciona a linha no vetor de linhas da forca

    score_stream.close();
}

/**
 * @brief Desenha a figura do boneco da forca com base na quantidade de erros
 * 
 * @param qntErros A quantidade de erros do usuário
 */
void desenhar_forca(int qntErros){
    switch(qntErros){
        case 0: 
            std::cout << "\n\n\n\n";
            break;
        case 1:
            std::cout << " o" << std::endl;
            std::cout << "\n\n\n";
            break;
        case 2:
            std::cout << " o" << std::endl;
            std::cout << " |" << std::endl;
            std::cout << "\n\n";
            break;
        case 3:
            std::cout << " o" << std::endl;
            std::cout << "/|" << std::endl;
            std::cout << "\n\n";
            break;
        case 4:
            std::cout << " o" << std::endl;
            std::cout << "/|\\" << std::endl;
            std::cout << "\n\n";
            break;
        case 5:
            std::cout << " o" << std::endl;
            std::cout << "/|\\" << std::endl;
            std::cout << "/" << std::endl;
            std::cout << "\n";
            break;
        case 6:
            std::cout << " o" << std::endl;
            std::cout << "/|\\" << std::endl;
            std::cout << "/ \\" << std::endl;
            std::cout << "\n";
            break;
    }
}

void exibe_interface_jogo(Forca &forca,std::string mensagem){
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << mensagem << std::endl;
    desenhar_forca(6 - forca.get_tentativas_restantes());
    std::cout << forca.get_palavra_jogada() << std::endl << std::endl;
    std::cout << "Pontos: " << forca.pontos_jogador << std::endl;
}

unsigned int exibe_parar_continuar(){
    unsigned int opcao = -1;

    std::cout << "Deseja continuar?" << std::endl;
    std::cout << "1 - Sim" << std::endl;
    std::cout << "2 - Não" << std::endl;

    std::cin >> opcao;
    return opcao;
}

using namespace std;
int main(int argc, char *argv[]){
    Forca forca(argv[1], argv[2]);

    std::cout << "Carregando arquivos de palavras [" << argv[1] <<"] e de scores [" << argv[2] << "]..." << std::endl;
    forca.carregar_arquivos();
    auto valid = forca.eh_valido();

    if(!valid.first){ //sai do programa ao encontrar um erro
        cout<< valid.second<<endl;
        exit(-1);
    }
    
    exibe_confirmacao_arquivos();
    while(true){
        /*imprime o menu principal e a escolha do usuário*/
        const unsigned int opcao = exibe_menu_principal();

        if(opcao==1){
            /*Seleciona dificuldade*/
            Forca::Dificuldade d = exibe_menu_dificuldades();

            forca.carregar_palavras_base();
            forca.set_dificuldade(d);

            std::vector<std::string> palavras_acertadas = {};

            while(true){
                string p = forca.proxima_palavra();
                forca.reset_rodada();
                forca.gerar_letras_aleatorias();

                /*exibe interface do jogo*/
                std::string msg = "Iniciando o Jogo no nível "+nome_da_dificuldade(d)+", será que você conhece essa palavra?";
                exibe_interface_jogo(forca, msg);

                while (!forca.rodada_terminada()){ //loop da rodada
                    /*ler palpite*/
                    string palpite;
                    std::cout << "Palpite: ";
                    std::cin >> palpite;

                    auto result = forca.palpite(palpite);
                    const std::string letra = palpite.substr(0, 1);

                    /*testa palpite e atualiza a interface dependendo do resultado*/

                    if(result.second==false){
                        msg = "Você já tentou a letra " + letra +" antes!";
                        exibe_interface_jogo(forca, msg);
                    }else if(result.first){
                        msg = "Muito bem! A palavra contém a letra " +letra+ "!";
                        exibe_interface_jogo(forca, msg);
                    }else{
                        msg = "não achei a letra "+letra+"!";
                        exibe_interface_jogo(forca, msg);
                    }

                }

                if(forca.acertou_palavra()){ // Se o jogador acertou a palavra
                    /*imprime interface de continuar / parar*/
                    forca.pontos_jogador +=2;

                    std::cout << "Parabéns! Você acertou, a palavra era "<< forca.get_palavra_atual() << std::endl;
                    std::cout << "Pontos: " << forca.pontos_jogador << std::endl;
                    palavras_acertadas.push_back(forca.get_palavra_atual());    

                    const unsigned int opcao = exibe_parar_continuar();

                    if (opcao!=1){ // Se não escolheu continuar
                        atualizar_score(forca, nome_da_dificuldade(d), palavras_acertadas, forca.pontos_jogador, argv[2]);
                        break;
                    }
                    else{
                        forca.reset_rodada();

                        if(forca.get_palavras_do_jogo().size()==0){ // Se o usuário acertar todas as palavras sorteadas inicialmente
                            forca.carregar_palavras_base();
                            forca.set_dificuldade(d);
                        }

                    }
                }
                else{ /*perdeu*/
                    /*imprime gameover e a palavra que estava sendo jogada*/
                    std::cout << "Game Over! A palavra era " << forca.get_palavra_atual() << "!\n";
                    atualizar_score(forca, nome_da_dificuldade(d),palavras_acertadas, forca.pontos_jogador, argv[2]);
                    forca.pontos_jogador = 0;
                    break;
                }
            }
            /*ler informações do jogador para o score e gravar no arquivo*/
        }
        else if(opcao==2){
            std::cout << std::endl;
            imprimir_tabela_scores(forca.get_linhas_scores());
            std::cout << std::endl;
        }else{ //qualquer outro número sai do jogo
            break;
        }
    }
    return 0;
}