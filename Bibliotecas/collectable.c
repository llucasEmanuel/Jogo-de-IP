#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "collectable.h"

Collectable inicializarChave(int numFase) {

    Collectable chave;
    chave.textura = LoadTexture("Sprites e Texturas/spriteChave.png");
    switch (numFase) {//posiciona a chave
        case 1:
            chave.coordenadas = (Vector2) {310, 1012};
            break;
        case 2:
            chave.coordenadas = (Vector2) {1625, 397};
            break;
        case 3:
            chave.coordenadas = (Vector2) {1050, 1010};  
            break;
        case 4:
            chave.coordenadas = (Vector2) {1000, 320};
            break;
        case 5:
            chave.coordenadas = (Vector2) {1620, 474};
            break;
        default:
            break;
    }
    
    chave.hitbox = (Rectangle) {
        chave.coordenadas.x,
        chave.coordenadas.y,
        90,
        36,
    };
    chave.colisao = 0;
    return chave;
}

Collectable *inicializarBaterias(int *qtdBaterias, int numFase) {
    
    Collectable *baterias = NULL;
    (*qtdBaterias) = GetRandomValue(1, 5);//qtd de baterias que vao aparecer no mapa
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
    
    Vector2 configBat[5];
    configBat[0] = (Vector2) {GetRandomValue(300, 1527), 799};
    configBat[1] = (Vector2) {709, GetRandomValue(379, 1011)};
    configBat[2] = (Vector2) {GetRandomValue(233, 1662), 568};
    configBat[3] = (Vector2) {1190, GetRandomValue(335, 977)};
    configBat[4] = (Vector2) {GetRandomValue(270, 700) , 455};
    for (int i = 0; i < *qtdBaterias; i++) {
        baterias[i].textura = LoadTexture("Sprites e Texturas/spriteBateria.png");
        //as coordenadas de cada bateria vao ser aleatorias mas dentro do limite da tela, posteriormente, do mapa
        baterias[i].coordenadas = configBat[i];
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

Collectable inicializarPorta(int numFase) {
    
    Collectable porta;
    porta.textura = LoadTexture("Sprites e Texturas/porta.png");
    switch (numFase) {
        case 1:
            porta.coordenadas = (Vector2) {1625, 355};
            break;
        case 2:
            porta.coordenadas = (Vector2) {310, 911};
            break;
        case 3:
            porta.coordenadas = (Vector2) {200, 712};  
            break;
        case 4:
            porta.coordenadas = (Vector2) {1150, 910};
            break;
        case 5:
            porta.coordenadas = (Vector2) {200, 712}; 
            break;
        default:
            break;
    }
    porta.hitbox = (Rectangle) {
        porta.coordenadas.x + 31,
        porta.coordenadas.y + 50,
        36,
        55,
    };
    porta.colisao = 0;
    return porta;
}

Collectable inicializarVida(int numFase) {
    
    Collectable vida;
    vida.textura = LoadTexture("Sprites e Texturas/gatoArea2.png");
    switch (numFase) {
        case 1:
            vida.coordenadas = (Vector2) {200, 700};
            break;
        case 2:
            vida.coordenadas = (Vector2) {1380, 612}; 
            break;
        case 3:
            vida.coordenadas = (Vector2) {409, 612}; 
            break;
        case 4:
            vida.coordenadas = (Vector2) {1600, 400}; 
            break;
        case 5:
            vida.coordenadas = (Vector2) {930, 314};
            break;
        default:
            break;
    }
    //vida.coordenadas = (Vector2) {(float) (rand() % (width - (vida.textura.width * 2))), (float) (rand() % (height - (vida.textura.height * 2)))};
    vida.hitbox = (Rectangle) {
        vida.coordenadas.x + 8,
        vida.coordenadas.y + 3,
        45,
        55,
    };
    vida.colisao = 0;
    return vida;
}

void InicializaColetavelContador(CollectableContador *mini){
    
    (*mini).textura = LoadTexture("Sprites e Texturas/spriteChave.png");
}

void InicializaColetavelContador1(CollectableContador *mini1){
    
    (*mini1).textura = LoadTexture("Sprites e Texturas/spriteBateria.png");
}
