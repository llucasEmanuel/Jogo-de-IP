#include <raylib.h>
#include <math.h>
#include "player.h"

void moverJogador(Player *jogador) {
    if (IsKeyDown(KEY_W)) {
        if (IsKeyDown(KEY_D)) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_A)) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            jogador->coordenadas.y -= GetFrameTime() * 300;
        }  
    }
    else if (IsKeyDown(KEY_S)) {
        if (IsKeyDown(KEY_D)) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_A)) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            jogador->coordenadas.y += GetFrameTime() * 300;
        }  
    }
    else if (IsKeyDown(KEY_A)) {
        if (IsKeyDown(KEY_W)) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_S)) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            jogador->coordenadas.x -= GetFrameTime() * 300;
        } 
    }
    else if (IsKeyDown(KEY_D)) {
        if (IsKeyDown(KEY_W)) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_S)) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else {
            jogador->coordenadas.x += GetFrameTime() * 300;
        } 
    }
}

Player inicializarJogador() {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Player jogador;
    jogador.qtdBaterias = 0;
    jogador.temChave = 0;//flag
    jogador.textura = LoadTexture("Sprites e Texturas/sprite1.png");
    jogador.coordenadas = (Vector2) {width/2, height/2};
    jogador.score = 0;
    //jogador.campoVisao = 150 + (50 * jogador.qtdBaterias);//raio = 1;
    return jogador;
}
