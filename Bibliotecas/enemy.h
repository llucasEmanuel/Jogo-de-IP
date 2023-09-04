#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
} Enemy;

Enemy *inicializarInimigos();