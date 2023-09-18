
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

void moverJogador(Player *jogador, int numFase) { //precisa do numero da fase pra definir as colisoes
    int pode_w = 1, pode_s = 1, pode_d = 1, pode_a = 1;
    //COLISOES DO MAPA
    if(jogador->coordenadas.x <= 10){ //quando passa de um certo ponto, limita o movimento para esquerda
        pode_a = 0;
    }
    if(jogador->coordenadas.x >= 1529){ // "" "" para direita
        pode_d = 0;
    }
    if(jogador->coordenadas.y <= 230){ //"" "" para cima
        pode_w = 0;
    }
    if(jogador->coordenadas.y >= 974){ //"" "" para baixo
        pode_s = 0;
    }
        
    colisaoJogadorMapa(jogador);

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

void colisaoJogadorMapa(Player *jogador) {
    //MESA COM O GLOBO
        Rectangle mesaG = {174, 875, 120, 206};
        //DrawRectangleRec(mesaG, PURPLE);
        if (CheckCollisionRecs(jogador->hitbox, mesaG)) {
            //CHECA SE APROXIMOU PELA DIREITA    
            if (jogador->coordenadas.x <= mesaG.x) {
                jogador->coordenadas.x += GetFrameTime() * 300;
            }
            //CHECA SE APROXIMOU POR CIMA
            if (jogador->coordenadas.y <= mesaG.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }   
        }

        //MESA COM PAPEL
        Rectangle mesaP = {1610, 875, 123, 202};
        //DrawRectangleRec(mesaP, YELLOW);
        if (CheckCollisionRecs(jogador->hitbox, mesaP)) {  
            if (jogador->coordenadas.x <= mesaP.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            if (jogador->coordenadas.y <= mesaP.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }   
        }
        
        //BANCADA PROFESSOR
        Rectangle bancada = {771, 382, 362, 108};
        //DrawRectangleRec(bancada, BLUE);
        if (CheckCollisionRecs(jogador->hitbox, bancada)) {   
            if (jogador->coordenadas.x <= bancada.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancada.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //GUARDA-ROUPA E MESA
        Rectangle guardaRoupa = {174, 166, 481, 216};
        //DrawRectangleRec(guardaRoupa, LIME);
        if (CheckCollisionRecs(jogador->hitbox, guardaRoupa)) {   
            if (jogador->coordenadas.x <= guardaRoupa.x) {
                if (jogador->coordenadas.x > 10) //evita que saia do mapa
                    jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= guardaRoupa.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //ESTANTE E ARMARIO
        Rectangle estante = {1498, 166, 241, 188};
        //DrawRectangleRec(estante, RED);
        if (CheckCollisionRecs(jogador->hitbox, estante)) {   
            if (jogador->coordenadas.x <= estante.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else if (jogador->coordenadas.x < 1529) {
                jogador->coordenadas.x += GetFrameTime() * 300;
            }
            
            if (jogador->coordenadas.y <= estante.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //BANCAS E1
        Rectangle bancasE1 = {409, 626, 242, 115};
        //DrawRectangleRec(bancasE1, SKYBLUE);
        if (CheckCollisionRecs(jogador->hitbox, bancasE1)) {   
            if (jogador->coordenadas.x <= bancasE1.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancasE1.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //BANCAS E2
        Rectangle bancasE2 = {409, 866, 242, 115};
        //DrawRectangleRec(bancasE2, BROWN);
        if (CheckCollisionRecs(jogador->hitbox, bancasE2)) {   
            if (jogador->coordenadas.x <= bancasE2.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancasE2.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //BANCAS C1
        Rectangle bancasC1 = {772, 626, 360, 115};
        //DrawRectangleRec(bancasC1, PINK);
        if (CheckCollisionRecs(jogador->hitbox, bancasC1)) {   
            if (jogador->coordenadas.x <= bancasC1.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancasC1.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //BANCAS C2
        Rectangle bancasC2 = {772, 866, 360, 115};
        //DrawRectangleRec(bancasC2, ORANGE);
        if (CheckCollisionRecs(jogador->hitbox, bancasC2)) {   
            if (jogador->coordenadas.x <= bancasC2.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancasC2.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //BANCAS D1
        Rectangle bancasD1 = {1250, 626, 242, 115};
        //DrawRectangleRec(bancasD1, GREEN);
        if (CheckCollisionRecs(jogador->hitbox, bancasD1)) {   
            if (jogador->coordenadas.x <= bancasD1.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancasD1.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
        
        //BANCAS D2
        Rectangle bancasD2 = {1250, 866, 242, 115};
        //DrawRectangleRec(bancasD2, GOLD);
        if (CheckCollisionRecs(jogador->hitbox, bancasD2)) {   
            if (jogador->coordenadas.x <= bancasD2.x) {
                jogador->coordenadas.x -= GetFrameTime() * 300;
            }
            else jogador->coordenadas.x += GetFrameTime() * 300;
            if (jogador->coordenadas.y <= bancasD2.y)  {
                jogador->coordenadas.y -= GetFrameTime() * 300;
            }  
            else jogador->coordenadas.y += GetFrameTime() * 300;
        }
}
