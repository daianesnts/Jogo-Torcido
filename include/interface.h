#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include <string>
#include "pilha.h"
using namespace std;

TPilha palavrasAcertadas,palavasDoDicionario;
string palavraEmFormacao = "";
string palavraSorteada = "";
string letrasEmbaralhadas = "";
string nomeArquivoDicionario = "";
string arquivoScore = "";
int tempo;
int pontuacao;
int maiorPontuacao;
Music musicaFundo;
Sound somTempoEsgotado;
Sound somHover;

bool hoverAnteriorGeral[10] = {false};

void inicializarJanela(int largura, int altura, const char* titulo) {
    InitWindow(largura, altura, titulo);
    InitAudioDevice();
    musicaFundo = LoadMusicStream("assets/audio/musicajogo.mp3");
    SetMusicVolume(musicaFundo, 0.25f);
    somTempoEsgotado = LoadSound("assets/audio/tempo.wav");
    somHover = LoadSound("assets/audio/hover.wav");
}

void desenharBotaoComHover(Rectangle botao, const char* texto, int indiceHover, int tamanhoFonte) {
    bool hoverAtual = CheckCollisionPointRec(GetMousePosition(), botao);
    if (hoverAtual && !hoverAnteriorGeral[indiceHover]) {
        PlaySound(somHover);
    }
    hoverAnteriorGeral[indiceHover] = hoverAtual;

    DrawRectangleRec(botao, hoverAtual ? GRAY : LIGHTGRAY);
    int textWidth = MeasureText(texto, tamanhoFonte);
    DrawText(texto, botao.x + (botao.width - textWidth)/2, botao.y + 15, tamanhoFonte, BLACK);
}

void desenharMenuPrincipal() {
    ClearBackground(RAYWHITE);
    int tamanhoText = MeasureText("JOGO TORCIDO", 40);
    int textX = (800 - tamanhoText)/2;
    DrawText("JOGO TORCIDO", textX, 70, 40, DARKBLUE);

    desenharBotaoComHover({300, 180, 200, 50}, "JOGAR", 0, 30);
    desenharBotaoComHover({300, 260, 200, 50}, "AJUDA", 1, 30);
    desenharBotaoComHover({300, 340, 200, 50}, "CRIADORES", 2, 30);
    desenharBotaoComHover({300, 420, 200, 50}, "SAIR", 3, 30);
}

void desenharJanelaAjuda() {
    ClearBackground(RAYWHITE);
    DrawText("Como jogar:", 60, 60, 30, DARKBLUE);
    DrawText("- Forme palavras com as letras embaralhadas.", 60, 120, 30, BLACK);
    DrawText("- Use apenas as letras disponíveis.", 60, 160, 30, BLACK);
    DrawText("- Pontue com palavras válidas do dicionário.", 60, 200, 30, BLACK);
    DrawText("- Descubra a palavra original para avançar.", 60, 240, 30, BLACK);
    desenharBotaoComHover({300, 400, 200, 50}, "VOLTAR", 4, 30);
}

void desenharJanelaCriadores(){
    ClearBackground(RAYWHITE);
    DrawText("Criadores:", 60, 60, 30, DARKBLUE);
    DrawText("- Daiane da Silva Santos;", 60, 120, 30, BLACK);
    DrawText("- Guilherme;", 60, 160, 30, BLACK);
    DrawText("- Igor Santos Dias;", 60, 200, 30, BLACK);
    DrawText("- Yasmim Passos Alves de Araújo", 60, 240, 30, BLACK);
    desenharBotaoComHover({300, 400, 200, 50}, "VOLTAR", 5, 30);
}

void desenharEscolhaDicionario() {
    ClearBackground(RAYWHITE);
    int tamanhoText = MeasureText("Escolha o dicionário:", 30);
    int textX = (800 - tamanhoText)/2;
    DrawText("Escolha o dicionário:", textX, 100, 30, DARKBLUE);

    desenharBotaoComHover({190, 200, 200, 60}, "PORTUGUÊS", 6, 25);
    desenharBotaoComHover({410, 200, 200, 60}, "INGLÊS", 7, 25);
    desenharBotaoComHover({300, 400, 200, 50}, "VOLTAR", 8, 30);
}

void desenharTelaJogo() {
    DrawText(TextFormat("Tempo: %d", tempo), 50, 50, 20, BLACK);
    int tamanhoText = MeasureText("Jogo Torcido", 30);
    int textX = (800 - tamanhoText)/2;
    DrawText("Jogo Torcido", textX, 50, 30, DARKBLUE);
    DrawText(TextFormat("Pontuação: %d", pontuacao), 600, 50, 20, BLACK);
    //tamanhoText = MeasureText(palavraEmFormacao.c_str(), 36);
    //textX = (400 - tamanhoText / 2);
    DrawText(palavraEmFormacao.c_str(), 200, 220, 36, BLACK);

    DrawText(TextFormat("Maior pontuação: %d", maiorPontuacao), 70, 520, 20, DARKBLUE);
    DrawText(letrasEmbaralhadas.c_str(), 340, 520, 32, BLACK);

    DrawText("Palavras acertadas", 500, 160, 18, DARKBLUE);
    int y = 190, x = 500, cont = 0;
    for (int i = 0; i <= palavrasAcertadas.Topo; i++) {
        DrawText(palavrasAcertadas.Item[i].palavra.c_str(), x, y, 18, BLACK);
        y += 28;
        cont += 1;
        //cria nova coluna depois de 11 palavras
        if (cont == 11) {
            x += 110;
            y = 190;
            cont = 0;
        }
    }
}

void desenharTelaTempoEsgotado() {
    ClearBackground(RAYWHITE);
    int tamanhoText = MeasureText("TEMPO ESGOTADO!", 48);
    int textX = (800 - tamanhoText)/2;
    DrawText("TEMPO ESGOTADO!", textX, 180, 48, RED);
    tamanhoText = MeasureText(TextFormat("Pontuação final: %d", pontuacao), 36);
    textX = (800 - tamanhoText)/2;
    DrawText(TextFormat("Pontuação final: %d", pontuacao), textX, 260, 36, DARKBLUE);
    tamanhoText = MeasureText(TextFormat("A palavra era: %s", palavraSorteada.c_str()), 36);
    textX = (800 - tamanhoText)/2;
    DrawText(TextFormat("A palavra era: %s", palavraSorteada.c_str()), textX, 300, 36, DARKBLUE);

    desenharBotaoComHover({250, 400, 300, 50}, "VOLTAR AO MENU", 9, 30);
}

#endif
