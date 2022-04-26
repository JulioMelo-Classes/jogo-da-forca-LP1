#include <iostream>
#include "Forca.hpp"
#include "tabelas.hpp"

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
        case Forca::Dificuldade::FACIL: return "fácil";
        case Forca::Dificuldade::MEDIO: return "médio";
        case Forca::Dificuldade::DIFICIL: return "difícil";
    }

    return "<dificuldade_não_reconhecida>";
}

void exibe_interface_jogo(Forca &forca,std::string mensagem){
    std::cout << "-----------------------------------------------------------" << std::endl;
    std::cout << mensagem << std::endl;
    std::cout << "\n\n";
    std::cout << "Tentativas restantes: " << forca.get_tentativas_restantes() << std::endl;
    std::cout << forca.get_palavra_jogada() << std::endl << std::endl;
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

            while(true){ //
                string p = forca.proxima_palavra();
                forca.reset_rodada();

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
                    std::cout << "Parabéns! Você acertou, a palavra era"<< forca.get_palavra_atual() << std::endl;
                    const unsigned int opcao = exibe_parar_continuar();

                    if (opcao!=1) // Se não escolheu continuar
                        break;
                    else
                        forca.reset_rodada();
                }
                else{ /*perdeu*/
                    /*imprime gameover e a palavra que estava sendo jogada*/
                    std::cout << "Game Over! A palavra era " << forca.get_palavra_atual() << "!\n";
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