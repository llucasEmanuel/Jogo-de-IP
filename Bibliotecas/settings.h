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
void carregarSons(Sound *youDied, Sound *musicaPerseguicao, Sound *musicaEncerramento, Sound *miau, Sound *somScore, Sound *gameOverSound);
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

//PRINTAR A HUD FIXA EM RELACAO A CAMERA
void gerarHUD(Camera2D camera, Fase fase, int *deathCount, CollectableContador *chave, CollectableContador *bateria, Player jogador);

//FUNCOES DE COLISOES
void removerJogador(Enemy *inimigo, Player *jogador, int *perdeu, int *deathCount);
void pegarChave(Collectable *chave, Player *jogador);
void entrarNaPorta(Collectable *porta, Player *jogador, int *entrouNaPorta, Sound somScore);
void pegarBateria(Collectable *bateria, Player *jogador);
void pegarVida(Collectable *vida, Player *jogador, int *deathCount, Sound miau);

//FUNCOES DE CRIAR E RESETAR AS FASES
void criarFase(int numFase, Fase *fase, Player jogador);
void reiniciarFase(Player *jogador, Fase *fase);
