#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

typedef struct {
    Texture textura[4];//sprites do inimigo
    Vector2 coordenadas;
    Rectangle hitbox;
    Vector2 centro;
    int detectouJogador;
    int colisao;
} Enemy;

Enemy *inicializarInimigos(int numFase);
//Enemy *atualizarVetorInimigos(Enemy *inimigos, int *qtdInimigos);
void moveInimigoCirculos(Enemy *inimigo, int qtdInimigos);
void perseguirJogador(Enemy *inimigos, Player jogador, int qtdInimigos);
