#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "enemy.h"

Enemy *inicializarInimigos() {//Cria o vetor dinamico de inimigos mas so inicializa um deles (necessario para a fase 1)
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    Enemy *ptrAux = (Enemy *) malloc(sizeof(Enemy));//aloca um espaco usando um ponteiro auxiliar
    if (ptrAux == NULL) {//checa se o malloc retornou nulo
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    Enemy *inimigos = ptrAux;//guarda o endereco no ponteiro inimigos
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

Enemy *atualizarVetorInimigos(Enemy *inimigos, int *qtdInimigos) {
    Enemy *ptrAux = (Enemy *) realloc(inimigos, ((*qtdInimigos) + 1) * sizeof(Enemy));
    if (ptrAux == NULL) {
        free(inimigos);
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    inimigos = ptrAux;
    (*qtdInimigos)++;
    inimigos[(*qtdInimigos)-1].hitbox = (Rectangle) {
        inimigos[(*qtdInimigos)-1].coordenadas.x + 5,
        inimigos[(*qtdInimigos)-1].coordenadas.y,
        108,
        165,
    };
    return inimigos;
}
