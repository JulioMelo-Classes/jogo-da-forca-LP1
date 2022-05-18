# Jogo da Forca com Interface Textual
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1

# Avaliação e Feedback

## Geral

- Implementção da Classe forca ou similar | 10 / 10 pontos
	- ok

- Implementação da Interface textual | 10 / 10 pontos
	- ok

- Execução completa do jogo | 15 / 15 pontos
	- Sorteio correto de paralavras para o jogo: cp1
	- Configuração correta da palavra jogada, dependendo da dificuldade:  5 / 5 
	- Execução correta do jogo (não pode repetir palpites, contabilização correta dos pontos e loop): 3 / 3
	- Salvamento correto do score: 2 / 2
	- Exibição correta dos scores: 5 / 5

- Validação dos arquivos de texto | 5 / 5 pontos
	- ok

- Arquivos de teste de validação dos casos de erro | 5 / 5 pontos
	- ok

## Código

- Documentação do código e readme | 10 / 10 pontos
	- muito bom o readme!

- Organização e indentação do código | 10 / 10 pontos
	- ok

- Compilação automatizada | 5 / 5 pontos
	- ok
	
## Comentários
- Embora você tenha feito várias funções no main, talvez valesse a pena movê-las para seu próprio .h. Na maioria das vezes o main não tem funções a
menos que tenham a ver com a configuração inicial do programa.

# Documento de Especificação

Leia o documento de especificação contido em [Especificação do Trabalho 1](https://docs.google.com/document/d/1aa51VNLQ_jpZaEuGkMz2KE8feAkE48-TENZ9eqn48nk/edit?usp=sharing).



## 1. :hammer_and_wrench: Como Compilar e Executar o Projeto

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

## 2. :file_folder: Arquivo de Palavras e de Scores

###### O arquivo de palavras (`palavras_forca.txt`) e de scores (`scores.txt`) se encontram dentro da pasta `/data` no diretório raiz do projeto e devem possuir uma formatações específicas.

### 2.1 `palavras_forca.txt`

O arquivo de palavras possui, em cada linha, uma palavra com a sua respectiva frequência de aparição separadas por um **tab** (tabulação, `\t`). Exemplo fictício:

```
coracao	16
sorte 14
coragem 10

```

As palavras não podem possuir caracteres especiais (ç, @ etc) e devem possuir um tamanho mínimo de 5 letras.

### 2.2 `scores.txt`

O arquivo de scores por sua vez possui em cada linha informações da dificuldade do jogo, nome do jogador, palavras acertadas por ele e pontos obtidos por ele. Todas essas informações são separadas por ponto e vírgula (`;`) e as palavras acertadas são separadas por vírgula (`,`). Exemplo:

```
Fácil; Hugo Santos; CORACAO, SORTE; 10
Médio; Maria Silva; CORACAO, SORTE, CORAGEM; 20
Difícil; Joao Souza; ; 0
```



## 3. :exclamation: Testes de Validação de Arquivos

Iremos testar os seguintes casos de validação de arquivos:

* **Palavras**
  * Arquivo não encontrado;
  * A linha não está com a formatação correta;
  * Alguma palavra possui caractere especial;
  * Alguma palavra não tem a frequência correspondente válida;
  * Alguma palavra não possui o tamanho mínimo de 5 letras.
* **Scores**
  * Arquivo não encontrado;
  * Presença de mais ou menos 3 pontos e vírgulas (`;`) ;
  * A pontuação do jogador não é um número inteiro;
  * Se o campo de nome ou dificuldade estão vazios.

### 3.1 Testes de palavras

Para testar o caso de arquivo não encontrado basta passarmos como argumento um arquivo que não existe. Exemplo

```bash
 ./forca palavras.txt ../data/scores.txt
```

**Saída Esperada:** Arquivo 'palavras.txt' não encontrado!

---

Testando o caso de alguma linha não estar com a formatação correta:

```bash
./forca ../data/palavras_formatacao.txt ../data/scores.txt
```

**Saída Esperada:** A linha 3 não está com a formatação correta!

---

Caso alguma palavra possua algum caractere especial:

```bash
./forca ../data/palavras_caractere.txt ../data/scores.txt
```

**Saída Esperada:** A palavra 'CORAÇÃO' na linha 3 possui algum caracter especial (ç, @ etc).

---

Caso de alguma palavra não ter a frequência correspondente válida:

```bash
./forca ../data/palavras_frequencia.txt ../data/scores.txt
```

**Saída Esperada:** A palavra 'ADEUS' na linha 4 possui uma frequência correspondente inválida!

---

Caso de alguma palavra ter tamanho menor do que 5:

```bash
./forca ../data/palavras_tamanho.txt ../data/scores.txt
```

**Saída Esperada:** A palavra 'AMOR' na linha 4 possui um tamanho menor do que 5

### 3.2 Teste de scores

Testando o caso de arquivo de scores não encontrado passando um arquivo de scores inexistente:

```bash
./forca ../data/palavras_forca.txt scores.txt
```

**Saída Esperada:** Arquivo 'scores.txt' não encontrado

---

Testando arquivos com alguma linha com mais ou menos 3 pontos e vírgulas:

```bash
./forca ../data/palavras_forca.txt ../data/scores_formatacao.txt
```

**Saída Esperada:** Presença de mais ou menos 3 ';' na linha 2

---

Testando o caso de ter alguma pontuação sem ser um número inteiro:

```
./forca ../data/palavras_forca.txt ../data/scores_pontuacao.txt
```

**Saída Esperada:** A pontuação não é um número inteiro na linha 3 do arquivo de scores

---

Testando o caso do campo nome ou dificuldade vazios:

```bash
./forca ../data/palavras_forca.txt ../data/scores_vazios.txt
```

**Saída Esperada:** Algum dos campos (Nome ou dificuldade) estão vazios na linha 3
