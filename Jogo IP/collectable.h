#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    int colisao;//flag que indica se houve (1) ou nao (0) colisao com aquele coletavel
} Collectable;//baterias, chave, ...

Collectable inicializarChave();
Collectable *inicializarBaterias(int *qtdBaterias);
Collectable inicializarPorta();