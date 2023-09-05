#include <raylib.h>
#include <math.h>
#include "player.h"

void moverJogador(Player *jogador) { //TUDO CONFIGURADO LEVANDO EM CONSIDERACAO A TELA CHEIA
    int pode_w = 1, pode_s = 1, pode_d = 1, pode_a = 1;
    
    if(jogador->coordenadas.x <= -20){ //quando passa de um certo ponto, limita o movimento para esquerda
        pode_a = 0;
    }
    if(jogador->coordenadas.x >= 1810){ // "" "" para direita
        pode_d = 0;
    }
    if(jogador->coordenadas.y <= -22){ //"" "" para cima
        pode_w = 0;
    }
    if(jogador->coordenadas.y >= 951.34){ //"" "" para baixo
        pode_s = 0;
    }
    
    if (IsKeyDown(KEY_W) && pode_w == 1) {
        if (IsKeyDown(KEY_D) && pode_d == 1) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_A) && pode_a == 1) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else{
            jogador->coordenadas.y -= GetFrameTime() * 300;
        }  
    }
    else if (IsKeyDown(KEY_S) && pode_s == 1) {
        if (IsKeyDown(KEY_D) && pode_d == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_A) && pode_a == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            jogador->coordenadas.y += GetFrameTime() * 300;
        }  
    }
    else if (IsKeyDown(KEY_A) && pode_a == 1) {
        if (IsKeyDown(KEY_W) && pode_w == 1) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_S) && pode_s == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            jogador->coordenadas.x -= GetFrameTime() * 300;
        } 
    }
    else if (IsKeyDown(KEY_D) && pode_d == 1) {
        if (IsKeyDown(KEY_W) && pode_w) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_S) && pode_s == 1) {
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
