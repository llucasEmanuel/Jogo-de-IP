#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    Vector2 centro;
    int detectouJogador;
} Enemy;

Enemy *inicializarInimigos();
Enemy *atualizarVetorInimigos(Enemy *inimigos, int *qtdInimigos);
void moveInimigoCirculos(Enemy *inimigo, int qtdInimigos);
void perseguirJogador(Enemy *inimigo, Player jogador, int qtdInimigos);
