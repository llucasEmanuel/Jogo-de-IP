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
void perseguirJogador(Enemy *inimigo, Player jogador);
