#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

typedef struct {
    Texture2D textura;
    int texturaCarregada;
    Vector2 coordenadas;
    Rectangle hitbox;
    Vector2 centro;
    int detectouJogador;
    int colisao;
    float timer;
    int frame;
    int maxFrames;
    float frameLargura;
} Enemy;

Enemy *inicializarInimigos(int numFase, Enemy *inimigos);
void moveInimigoCirculos(Enemy *inimigo, int qtdInimigos);
void perseguirJogador(Enemy *inimigos, Player jogador, int qtdInimigos);
void atualizaInimigo(Enemy *inimigo);
