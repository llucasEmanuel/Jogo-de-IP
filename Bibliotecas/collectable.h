#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    int colisao;//flag que indica se houve (1) ou nao (0) colisao com aquele coletavel
} Collectable;//baterias, chave, ...

typedef struct {
    Texture textura;
    Vector2 coordenadas;
} CollectableContador;

Collectable inicializarChave(int numFase);
Collectable *inicializarBaterias(int *qtdBaterias, int numFase);
Collectable inicializarPorta(int numFase);
Collectable inicializarVida(int numFase);
void InicializaColetavelContador(CollectableContador *mini);
void InicializaColetavelContador1(CollectableContador *mini1);
