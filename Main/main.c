#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <raylib.h>
#include "menu.h"
#include "player.h"
#include "collectable.h"
#include "enemy.h"

void criarFase(Player *jogador);

int main() {
    
    srand(time(NULL));
    InitWindow(1920, 1080, "Jogo de IP");
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    Player jogador = inicializarJogador();
    //Enemy *inimigos = NULL;
    //int qtdInimigos = 0;
    criarFase(&jogador);

    return 0; 
}

void criarFase(Player *jogador) {
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    //AUXILIAR MENU
    int continua = 0, continua1 = 0;
    
    InitAudioDevice();
    //if (!IsWindowFullscreen()) ToggleFullscreen();
    
    //INICIALIZACAO DOS INIMIGOS
    Enemy *inimigos = inicializarInimigos();
    
    //INICIALIZACAO DAS BATERIAS
    int qtdBaterias = 0;//qtd baterias que irao aparecer na tela (a qtd eh aleatorio e definida na funcao)
    Collectable *baterias = inicializarBaterias(&qtdBaterias);
    
    //INICIALIZACAO DA CHAVE
    Collectable chave = inicializarChave();
    
    //INICIALIZACAO DA PORTA DE SAIDA
    Collectable porta = inicializarPorta();
    
    //INICIALIZACAO DOS SONS
    Sound musica = LoadSound("Sons e Musica/Spooked - Mini Vandals.mp3");
    PlaySound(musica);
    
    SetTargetFPS(60);
    
    char bateriasStr[] = "BATERIAS : 0";//11 == ind do char do digito
    char chavesStr[] = "CHAVES : 0";//9 == ind do char do digito
    
    int entrouNaPorta = 0;
    

    //INICIO DO LOOP EM QUE RODA O JOGO
    while(!WindowShouldClose()) {
                
        
        if(continua == 0 && continua1 == 0){ //Chama a primeira parte do menu
           continua = geraMenu();
        }
       
        if(continua == 1 && continua1 == 0){ //Chama a parte dos comandos
           continua1 = iniciaJogo();
        }
       
        
        if(continua1 == 1 && continua == 1){ //Inicia Jogo
                while (entrouNaPorta) {
                    BeginDrawing();
                    ClearBackground(WHITE);

                    DrawText(TextFormat("HIGHSCORE : %d", jogador->score), width / 2 - MeasureText("HIGHSCORE : ", 75) / 2, height / 2 - 75, 75, BLACK);

                    EndDrawing();
                    
                    if (IsKeyPressed(KEY_ESCAPE)) {//mudar a tecla para KEY_SPACE depois
                        entrouNaPorta = 0;
                    }
                }
            
            
            BeginDrawing();
            
            // jogador->campoVisao = 150 + (25 * jogador->qtdBaterias);
            // DrawCircle(jogador->hitbox.x + 46, jogador->hitbox.y + 40, jogador->campoVisao, WHITE);//campo de visao
            ClearBackground(WHITE);
     
            DrawText("FASE 1", width / 2 - MeasureText("FASE 1", 40) / 2, height / 2 - 40, 40, BLACK);
            
            //DESENHA INIMIGOS
            DrawTextureEx(inimigos[0].textura, inimigos[0].coordenadas, 0, 8, WHITE);
            DrawRectangle(inimigos[0].hitbox.x, inimigos[0].hitbox.y, inimigos[0].hitbox.width, inimigos[0].hitbox.height, BLANK);
            
            //DESENHA A TEXTURA DAS BATERIAS 
            for (int i = 0; i < qtdBaterias; i++) {
                if (baterias[i].colisao == 0) {
                    DrawTextureEx(baterias[i].textura, (Vector2) {baterias[i].coordenadas.x, baterias[i].coordenadas.y}, 0, 3, WHITE);
                    DrawRectangle(baterias[i].hitbox.x, baterias[i].hitbox.y, baterias[i].hitbox.width, baterias[i].hitbox.height, BLANK);
                }
            }
            
            //DESENHA A TEXTURA DA CHAVE
            DrawTextureEx(chave.textura, (Vector2) {chave.coordenadas.x, chave.coordenadas.y}, 0, 2.5, WHITE);
            DrawRectangle(chave.hitbox.x, chave.hitbox.y, chave.hitbox.width, chave.hitbox.height, BLANK);
            
            //hitbox dinamica que se move conforme o sprite do jogador
            jogador->hitbox = (Rectangle) {
                jogador->coordenadas.x + 18,
                jogador->coordenadas.y + 40,
                96,
                90,
            };
            
            if (!jogador->temChave) {//desenha antes se o jogador nao tiver a chave
                DrawTextureEx(porta.textura, porta.coordenadas, 0, 2.2, WHITE);
                DrawRectangle(porta.hitbox.x, porta.hitbox.y, porta.hitbox.width, porta.hitbox.height, BLANK);
            }
            
            //DESENHA A TEXTURA DO JOGADOR
            DrawTextureEx(jogador->textura, jogador->coordenadas, 0, 0.33, WHITE);
            DrawRectangle(jogador->hitbox.x, jogador->hitbox.y, jogador->hitbox.width, jogador->hitbox.height, BLANK);
            
            if (jogador->temChave) {//desenha depois se tiver a chave
                DrawTextureEx(porta.textura, porta.coordenadas, 0, 2.2, WHITE);
                DrawRectangle(porta.hitbox.x, porta.hitbox.y, porta.hitbox.width, porta.hitbox.height, BLANK);
            }

            moverJogador(jogador);
            
            //CHECA SE HOUVE COLISAO COM A CHAVE
            if (CheckCollisionRecs(jogador->hitbox, chave.hitbox)) {
                chave.colisao = 1;
                printf("Colisao CHAVE\n");
                UnloadTexture(chave.textura);//apaga a textura
                chave.hitbox = (Rectangle) {0, 0, 0, 0};//remove a hitbox
                jogador->temChave = 1;//atualiza a flag do jogador
                chavesStr[9]++;//atualiza a qtd chaves na tela
                jogador->score += 200;
            }
            
            //CHECA SE HOUVE COLISAO COM A PORTA
            if (CheckCollisionRecs(jogador->hitbox, porta.hitbox)) {
                if (jogador->temChave) {
                    porta.colisao = 1;
                    printf("Colisao PORTA\n");
                    UnloadTexture(porta.textura);
                    porta.hitbox = (Rectangle) {0, 0 , 0 , 0};
                    jogador->score += 500;
                    entrouNaPorta = 1;
                    //return;//Sai da funcao
                }
                else {
                    DrawText("PORTA TRANCADA", width/2 - MeasureText("PORTA TRANCADA", 30), 30, 40, RED);
                }
            }
            
            //CHECA SE HOUVE COLISAO COM UMA DAS BATERIAS
            int indColisoes[qtdBaterias];//armazena os indices das baterias colididas
            int qtdColisoes = 0;//qtd de baterias obtidas
            for (int i = 0; i < qtdBaterias; i++) {
                if (CheckCollisionRecs(jogador->hitbox, baterias[i].hitbox)) {
                    indColisoes[qtdColisoes] = i;//guarda os indices
                    qtdColisoes++;
                    bateriasStr[11]++;//atualiza a qtd baterias na tela
                }
            }
            
            //REMOVER BATERIAS
            for (int i = 0 ; i < qtdColisoes; i++) { 
                int ind = indColisoes[i];
                //checa a flag da bateria daquele indice, se o indice estiver dentro da lista e flag for 0,
                //entao tem que apagar a bateria
                if (baterias[ind].colisao == 0) {
                    baterias[ind].colisao = 1;
                    printf("Colisao BATERIA\n");
                    UnloadTexture(baterias[ind].textura);
                    baterias[ind].hitbox = (Rectangle){0, 0, 0, 0};
                    jogador->qtdBaterias++; 
                    jogador->score += 50;
                }
            }

            //GUARDAR CADA STRING EM UMA VARIAVEL DIFERENTE E SÓ SOMAR 1 NO CHAR DO DIGITO
            DrawText(TextFormat("SCORE : %d", jogador->score), 30, 30, 40, GRAY);
            DrawText(chavesStr, 30, 80, 40, GRAY);
            DrawText(bateriasStr, 30, 130, 40, GRAY);

            EndDrawing();  
        }
    }

    //DESALOCA OS PONTEIROS, APAGA AS TEXTURAS E DESATIVA AS FUNCOES DE AUDIO
    UnloadTexture(jogador->textura);
    UnloadTexture(chave.textura);
    UnloadTexture(porta.textura);
    for (int i = 0; i < qtdBaterias; i++) {
       UnloadTexture(baterias[i].textura); 
    }
    free(baterias);
    CloseAudioDevice();
    CloseWindow();
}
