#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "enemy.h"

Enemy *inicializarInimigos() {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Enemy *ptrAux = (Enemy *) malloc(sizeof(Enemy));
    if (ptrAux == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    Enemy *inimigos = ptrAux;
    inimigos[0].textura = LoadTexture("Sprites e Texturas/saltyPaul.png");
    inimigos[0].coordenadas = (Vector2) {(float) (rand() % (width - (inimigos[0].textura.width * 2))), (float) (rand() % (height - (inimigos[0].textura.height * 2)))};
    inimigos[0].hitbox = (Rectangle) {
        inimigos[0].coordenadas.x + 5,
        inimigos[0].coordenadas.y,
        108,
        165,
    };
    return inimigos;
}