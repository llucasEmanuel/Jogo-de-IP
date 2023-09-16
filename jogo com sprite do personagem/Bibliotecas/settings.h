#include <raylib.h>
#include "menu.h"
//#include "player.h"
#include "collectable.h"
#include "enemy.h"

#define SILVER (Color) {192, 192, 192, 255}

typedef struct {
    Enemy *inimigos;
    Collectable chave;
    Collectable porta;
    Collectable *baterias;
    Collectable vida;
    Texture mapa;
    int qtdBaterias;
    int qtdInimigos;
    int faseAtual;
} Fase;

Camera2D inicializarCamera(Player jogador);

//CARREGAR E ARMAZENAR DADOS
void carregarMusicas(Music *musicasFase, Music *musicaMenu);
void carregarSons(Sound *youDied, Sound *musicaPerseguicao, Sound *musicaEncerramento);
void salvarScore(char *nome, int score);

//GERAR TELAS
void printTelaEncerramento(Ranking *ranking);
void printTelaPerdeu(int ind, Font fonteDS);
void printScore(int score);
void printGameOver();
Color definirCorFase(int faseAtual);

//DESENHAR TEXTURAS
void desenharPorta(Player jogador, Collectable porta, float *distCampoVisaoPortaC);
void desenharInimigo(Enemy *inimigo, Player jogador, float *acumulador, int *musicaTocando, int *musicaDelay, int *frameAtual, float *tempoFrame, Music *musicasFase, Sound musicaPerseguicao);
void desenharBateria(Collectable bateria, Player jogador);
void desenharChave(Collectable chave, Player jogador, float *distCampoVisaoChaveC);
void desenharVida(Collectable vida, Player jogador, float *distCampoVisaoVidaC);
void desenharJogador(Player jogador);

void gerarHUD(Camera2D camera, Fase fase, int *deathCount, CollectableContador *chave, CollectableContador *bateria, Player jogador);

//FUNCOES DE COLISOES
void removerJogador(Enemy *inimigo, Player *jogador, int *perdeu, int *deathCount, Color cor);
void pegarChave(Collectable *chave, Player *jogador, Color cor);
void entrarNaPorta(Collectable *porta, Player *jogador, int *entrouNaPorta, int numFase, Color cor);
void pegarBateria(Collectable *bateria, Player *jogador, Color cor);
void pegarVida(Collectable *vida, Player *jogador, int *deathCount, Color cor, int numFase);
