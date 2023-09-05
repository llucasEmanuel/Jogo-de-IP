#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
} Enemy;
//criar uma lista de strings com os paths para as texturas de cada inimigo
Enemy *inicializarInimigos();
Enemy *atualizarVetorInimigos(Enemy *inimigos, int *qtdInimigos);
