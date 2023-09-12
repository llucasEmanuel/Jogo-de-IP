#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "collectable.h"


Collectable *inicializarBaterias(int *qtdBaterias) {
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Collectable *baterias = NULL;
    (*qtdBaterias) = (rand() % 5) + 1;//qtd de baterias que vao aparecer no mapa
    Collectable *ptrAux = (Collectable *) malloc((*qtdBaterias) * sizeof(Collectable));
    if (ptrAux == NULL) {//checa se a alocacao ocorreu
        for (int i = 0; i < *qtdBaterias; i++) {
           UnloadTexture(baterias[i].textura); 
        }
        free(baterias);
        CloseAudioDevice();
        CloseWindow();
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    baterias = ptrAux;
    for (int i = 0; i < *qtdBaterias; i++) {
        baterias[i].textura = LoadTexture("Sprites e Texturas/spriteBateria.png");
        //as coordenadas de cada bateria vao ser aleatorias mas dentro do limite da tela, posteriormente, do mapa
        baterias[i].coordenadas = (Vector2){(float) (rand() % (width - 45)), (float) (rand() % (height - 60))};
        baterias[i].hitbox = (Rectangle) {
            baterias[i].coordenadas.x,
            baterias[i].coordenadas.y,
            45,
            60,
        };
        baterias[i].colisao = 0;//nao sofreu colisao
    }
    return baterias;
}

Collectable inicializarChave() {
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Collectable chave;
    chave.textura = LoadTexture("Sprites e Texturas/spriteChave2.png");
    chave.coordenadas = (Vector2) {(float) (rand() % (width - 90)), (float) (rand() % (height - 36))};
    chave.hitbox = (Rectangle) {
        chave.coordenadas.x,
        chave.coordenadas.y,
        90,
        36,
    };
    chave.colisao = 0;
    return chave;
}

Collectable inicializarPorta() {
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Collectable porta;
    porta.textura = LoadTexture("Sprites e Texturas/porta.png");
    porta.coordenadas = (Vector2) {(float) (rand() % (width - (porta.textura.width * 2))), (float) (rand() % (height - (porta.textura.height * 2)))};
    porta.hitbox = (Rectangle) {
        porta.coordenadas.x + 31,
        porta.coordenadas.y + 50,
        36,
        55,
    };
    porta.colisao = 0;
    return porta;
}

Collectable inicializarVida() {
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Collectable vida;
    vida.textura = LoadTexture("Sprites e Texturas/lifeHeart.png");
    vida.coordenadas = (Vector2) {(float) (rand() % (width - (vida.textura.width * 2))), (float) (rand() % (height - (vida.textura.height * 2)))};
    vida.hitbox = (Rectangle) {
        vida.coordenadas.x + 10,
        vida.coordenadas.y,
        45,
        55,
    };
    vida.colisao = 0;
    return vida;
}

void InicializaColetavelContador(CollectableContador *mini){
    
    (*mini).textura = LoadTexture("Sprites e Texturas/spriteChave2.png");
}

void InicializaColetavelContador1(CollectableContador *mini1){
    
    (*mini1).textura = LoadTexture("Sprites e Texturas/spriteBateria.png");
}
