#include <iostream>
#include "raylib.h"
#include "pilha.h"
#include "nucleo_jogo.h"
#include "interface.h"

using namespace std;

// Estados das telas
enum EstadoTela {MENU, AJUDA, CRIADORES, ESCOLHA_DIC, JOGO, TEMPO_ESGOTADO};

int main() {
    inicializarJanela(800, 600, "Jogo Torcido");

    EstadoTela estado = MENU;

    // Inicializa a vari�vel que armazena o tempo do �ltimo frame em que o cron�metro foi atualizado
    double tempoUltimoFrame = GetTime();

    bool musicaTocando = false;

    while (!WindowShouldClose()) {

        if (estado == JOGO && tempo > 0) {
            int key = GetCharPressed();
            while (key > 0) {
                for(char letra : palavraSorteada) {
                    if (letra == (char)key) {
                        palavraEmFormacao += (char)key;
                        break;
                    }
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && !palavraEmFormacao.empty()) {
                palavraEmFormacao.pop_back();
            }

            if (IsKeyPressed(KEY_ENTER) && !palavraEmFormacao.empty()) {
                TInfo item;
                if (verificarPalavraValida(palavraEmFormacao, nomeArquivoDicionario,
                                           palavraSorteada, palavrasAcertadas)) {
                    item.palavra = palavraEmFormacao;
                    Empilha(palavrasAcertadas, item);
                }
                palavraEmFormacao = "";
            }

            double tempoAtual = GetTime();
            if (tempoAtual - tempoUltimoFrame >= 1.0) {
                tempo--;
                tempoUltimoFrame = tempoAtual;
            }
            if (tempo == 0) {
                StopMusicStream(musicaFundo);
                musicaTocando = false;
                PlaySound(somTempoEsgotado);
                estado = TEMPO_ESGOTADO;
            }

            if (!musicaTocando) { // acabou de entrar na tela JOGO
                PlayMusicStream(musicaFundo); // come�a (ou retoma) a trilha
                musicaTocando = true;
            }
            else {
                UpdateMusicStream(musicaFundo);
            }
        }

        // Desenho das telas
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mouse = GetMousePosition();

        if (estado == MENU) {
            desenharMenuPrincipal();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, {300, 180, 200, 50}))
                    estado = ESCOLHA_DIC;
                if (CheckCollisionPointRec(mouse, {300, 260, 200, 50}))
                    estado = AJUDA;
                if (CheckCollisionPointRec(mouse, {300, 340, 200, 50}))
                    estado = CRIADORES;
                if (CheckCollisionPointRec(mouse, {300, 420, 200, 50}))
                    break;
            }
        } else if (estado == AJUDA) {
            desenharJanelaAjuda();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, {300, 400, 200, 50}))
                    estado = MENU;
            }
        } else if (estado == CRIADORES){
            desenharJanelaCriadores();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, {300, 400, 200, 50}))
                    estado = MENU;
            }
        } else if (estado == ESCOLHA_DIC) {
            desenharEscolhaDicionario();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, {190, 200, 200, 60})) {
                    arquivoScore = "data/scores/maiorpontuacao.txt";
                    carregarHighScore(arquivoScore);
                    nomeArquivoDicionario = selecionarLingua(1);
                    Cria(palavasDoDicionario);
                    carregarDicionario(nomeArquivoDicionario,palavasDoDicionario);
                    palavraSorteada = selecionarPalavraAleatoria(palavasDoDicionario);
                    letrasEmbaralhadas = embaralhaPalavra(palavraSorteada);
                    Cria(palavrasAcertadas);
                    tempo = 15;
                    pontuacao = 0;
                    palavraEmFormacao = "";
                    estado = JOGO;
                    tempoUltimoFrame = GetTime();
                }
                if (CheckCollisionPointRec(mouse, {410, 200, 200, 60})) {
                    arquivoScore = "data/scores/highscore.txt";
                    carregarHighScore(arquivoScore);
                    nomeArquivoDicionario = selecionarLingua(2);
                    Cria(palavasDoDicionario);
                    carregarDicionario(nomeArquivoDicionario,palavasDoDicionario);
                    palavraSorteada = selecionarPalavraAleatoria(palavasDoDicionario);
                    letrasEmbaralhadas = embaralhaPalavra(palavraSorteada);
                    Cria(palavrasAcertadas);
                    tempo = 15;
                    pontuacao = 0;
                    palavraEmFormacao = "";
                    estado = JOGO;
                    tempoUltimoFrame = GetTime();
                }
                if (CheckCollisionPointRec(mouse, {300, 400, 200, 50}))
                    estado = MENU;
            }
        } else if (estado == JOGO) {
            desenharTelaJogo();
        } else if (estado == TEMPO_ESGOTADO){
            if (pontuacao > maiorPontuacao)
                salvarHighScore(arquivoScore);
            desenharTelaTempoEsgotado();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, {250, 400, 300, 50})) {
                    estado = MENU;
                }
            }
        }
        EndDrawing();
    } // Fechamento do while principal

    // Libera��o de recursos
    UnloadSound(somTempoEsgotado);
    UnloadSound(somHover);
    UnloadMusicStream(musicaFundo);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
