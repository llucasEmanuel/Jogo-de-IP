
#include <raylib.h>
#include <math.h>
#include "player.h"

void atualizaSprite(Player *jogador){
    jogador->timer+=GetFrameTime();
    if(jogador->timer>=0.2f){
        jogador->timer=0.0f;
        jogador->frame+=1;
    }
    jogador->frame=(jogador->frame)%(jogador->maxFrames);
}

void moverJogador(Player *jogador) { //TUDO CONFIGURADO LEVANDO EM CONSIDERACAO A TELA CHEIA
    int pode_w = 1, pode_s = 1, pode_d = 1, pode_a = 1;
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    //medir limites do mapa
    if(jogador->coordenadas.x <= -160){ //quando passa de um certo ponto, limita o movimento para esquerda
        pode_a = 0;
    }
    if(jogador->coordenadas.x >= width - 210){ // "" "" para direita
        pode_d = 0;
    }
    if(jogador->coordenadas.y <= -22){ //"" "" para cima
        pode_w = 0;
    }
    if(jogador->coordenadas.y >= height - 110){ //"" "" para baixo
        pode_s = 0;
    }
    
    
    if (IsKeyDown(KEY_W) && pode_w == 1) {
        jogador->textura = LoadTexture("Sprites e Texturas/spritefrente.png");
        if (IsKeyDown(KEY_D) && pode_d == 1) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else if (IsKeyDown(KEY_A) && pode_a == 1) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else{
            jogador->coordenadas.y -= GetFrameTime() * 300;
            atualizaSprite(jogador);
        }  
    }
    else if (IsKeyDown(KEY_S) && pode_s == 1) {
        jogador->textura = LoadTexture("Sprites e Texturas/spritebaixo.png");
        if (IsKeyDown(KEY_D) && pode_d == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else if (IsKeyDown(KEY_A) && pode_a == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else {
            jogador->coordenadas.y += GetFrameTime() * 300;
            atualizaSprite(jogador);
        }  
    }
    else if (IsKeyDown(KEY_A) && pode_a == 1) {
        jogador->textura = LoadTexture("Sprites e Texturas/spriteesquerda.png");
        if (IsKeyDown(KEY_W) && pode_w == 1) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else if (IsKeyDown(KEY_S) && pode_s == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else {
            jogador->coordenadas.x -= GetFrameTime() * 300;
            atualizaSprite(jogador);
        } 
    }
    else if (IsKeyDown(KEY_D) && pode_d == 1) {
        jogador->textura = LoadTexture("Sprites e Texturas/spritedireita.png");
        if (IsKeyDown(KEY_W) && pode_w) {
            jogador->coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else if (IsKeyDown(KEY_S) && pode_s == 1) {
            jogador->coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            jogador->coordenadas.x += GetFrameTime() * (150 * sqrt(2));
            atualizaSprite(jogador);
        }
        else {
            jogador->coordenadas.x += GetFrameTime() * 300;
            atualizaSprite(jogador);
        } 
    }
}

Player inicializarJogador() {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Player jogador;
    jogador.qtdBaterias = 0;
    jogador.temChave = 0;//flag
    jogador.pegouVida = 0;
    jogador.textura = LoadTexture("Sprites e Texturas/spritebaixo.png");
    jogador.coordenadas = (Vector2) {width/2, height/2};
    jogador.score = 0;
    jogador.centro = (Vector2) {(2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2, (2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2};
    jogador.timer=0.0f;
    jogador.frame=0;
    jogador.frameLargura=(float)(jogador.textura.width/9);
    jogador.maxFrames=(int)(jogador.textura.width/(int)jogador.frameLargura);
    //jogador.campoVisao = 150 + (50 * jogador.qtdBaterias);//raio = 1;
    return jogador;
}

void atualizaJogador(Player *jogador) {
    jogador->campoVisao = 150 + (35 * jogador->qtdBaterias);//raio do campo de visao
    jogador->centro = (Vector2) {(2*jogador->coordenadas.x + 0.33*jogador->textura.width)/2, (2*jogador->coordenadas.y + 0.33*jogador->textura.height)/2};
    //hitbox dinamica que se move conforme o sprite do jogador
    jogador->hitbox = (Rectangle) {
        jogador->coordenadas.x + 155,
        jogador->coordenadas.y + 15,
        56,
        70,
    };
}