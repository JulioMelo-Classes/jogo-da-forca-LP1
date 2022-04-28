# Jogo da Forca com Interface Textual
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Avaliação e Feeback

- Implementação do carregamento dos arquivos |  10 / 10 pontos
    - Vou considerar mas você precisa deixar claro no readme que o arquivo de palavras precisa separar o número com \t.

- Implementação de parte da validação | 10 / 10 pontos

- Implementação de um main funcional com parte da UI | 5 / 5 pontos

- Implementação de parte da lógica de sorteio de palavras | 10 / 10 pontos
    - Muito boa usar a função uniform_distribution, você também poderia usar algo parecido para embaralhar o vetor de palavras e apenas pegar os
    primeiros elementos!

- Estrutura básica dos arquivos e processo de compilação definido | 5 / 5 pontos

- Observações gerais
    - Muito boa a modularicação!

# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing).



## 1. Como Compilar e Executar o Projeto

Para a compilação do projeto é possível utilizar a ferramenta de compilação **cmake** (Caso não possua o cmake precisará instalá-lo). Assim, siga o conjunto de passos:

Crie a pasta `/build` para manter o projeto organizado quando o **cmake** buildar o projeto. Para isso, execute os comandos de dentro da pasta raiz do projeto:

```bash
mkdir build/
cd build/
cmake ..
```

Dessa forma, diversos arquivos do cmake serão criados dentro da pasta `/build`. 

Agora execute o seguinte comando, dentro da pasta `/build` para compilar o projeto com o cmake (Os configurações de compilação já estão presentes no arquivo `CMakeLists.txt` no diretório raiz do projeto):

```bash
cmake --build . 
```

Agora, um arquivo executável será criado em `/build` com o nome de `forca`. Para executar o jogo em sí execute o seguinte comando:

```bash
./forca ../data/palavras_forca.txt ../data/scores.txt
```

O `../data/palavras_forca.txt`  e `../data/scores.txt` referem-se, respectivamente, ao arquivo de palavras e scores bases utilizados no jogo que estão dentro da pasta  `/data`. 

## 2. Funcionalidades não implementadas

Para esta versão do jogo ainda não foram implementadas as seguintes funcionalidades básicas: 

* Sorteio de consoantes para as palavras ao iniciar o jogo;
* Contagem de pontos;
*  Salvamento dos scores no arquivo `score.txt`. 
