#ifndef NUCLEO_JOGO_H
#define NUCLEO_JOGO_H

#include <fstream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <algorithm>
#include "pilha.h"
#include "interface.h"

void carregarHighScore(string nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo >> maiorPontuacao;
        arquivo.close();
    } else {
        maiorPontuacao = 0;
    }
}

void salvarHighScore(string nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo.c_str(), "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "%d", pontuacao);
        fclose(arquivo);
    }
}

string selecionarLingua(int escolhaIdioma) {
    if (escolhaIdioma == 1) {
        return "data/dictionaries/portugues.txt";
    } else if (escolhaIdioma == 2) {
        return "data/dictionaries/ingles.txt";
    }
    return "data/dictionaries/portugues.txt";
}

void carregarDicionario(string nomeArquivo,TPilha& pilhaPalavras){
    TInfo item;
    ifstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        string linha;
        while (getline(arquivo, linha)) {
            item.palavra = linha;
            Empilha(pilhaPalavras,item);
        }
        arquivo.close();
    }
}

string selecionarPalavraAleatoria(TPilha palavras) {
    static mt19937 gerador([]() {
        random_device rd;
        return rd() ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    }());

    uniform_int_distribution<int> distribuicao(0, palavras.Topo);

    int rnd = distribuicao(gerador);
    return palavras.Item[rnd].palavra;
}

string embaralhaPalavra(string palavra) {
    random_device rd;
    default_random_engine engine(rd());

    shuffle(palavra.begin(), palavra.end(), engine);

    while(palavra == palavraSorteada)
        shuffle(palavra.begin(), palavra.end(), engine);
    return palavra;
}

bool verificarPalavraValida(string palavra, string nomeArquivo, string& palavraSorteada,TPilha palavrasAcertadas) {

    // verifica se a palavra digitada j� � a palavra sorteada
    // se for a palavra sorteada: pontua��o m�xima, reinicia tempo e sorteia nova palavra
    if (palavra == palavraSorteada) {
        pontuacao += 100;
        tempo = 15;
        palavraSorteada = selecionarPalavraAleatoria(palavasDoDicionario);
        letrasEmbaralhadas = embaralhaPalavra(palavraSorteada);
        return true;
    }
    // Percorre a pilha de palavras j� acertadas
    // Se a palavra j� foi digitada antes, n�o pontua novamente
    for (int aux = 0; aux <= palavrasAcertadas.Topo; aux++) {
        if (palavrasAcertadas.Item[aux].palavra == palavra)
            return false;
    }

    // Verifica��o no dicion�rio
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
        return false;
    // Se est� no dicion�rio: pontua��o e tempo extra.
    // Se n�o est� no dicion�rio: n�o pontua, retorna falso
    string linha;
    while (getline(arquivo, linha)) {
        if (linha == palavra) {
            arquivo.close();
            tempo += 2;
            pontuacao += 10;
            return true;
        }
    }
    arquivo.close();
    return false;
}

#endif
