#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <raylib.h>
#include "menu.h"
//#include "player.h"
#include "collectable.h"
#include "enemy.h"

typedef struct {
    Enemy *inimigos;
    Collectable chave;
    Collectable porta;
    Collectable *baterias;
    int qtdBaterias;
    int qtdInimigos;
} Fase;

Fase criarFase();

int main() {
    
    srand(time(NULL));
    
    InitWindow(1920, 1080, "Jogo de IP");
    //if (!IsWindowFullscreen()) ToggleFullscreen();
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    Player jogador = inicializarJogador();//inicializa jogador fora do criarFase para manter o score para as outras fases
    Fase fase = criarFase();
    fase.qtdInimigos = 1;
    
    //INICIALIZACAO DOS SONS
    InitAudioDevice();
    Sound musica = LoadSound("Sons e Musica/Spooked - Mini Vandals.mp3");
    //PlaySound(musica);
    
    SetTargetFPS(60);
    
    
    //FLAGS PARA CONTROLE DOS EVENTOS DA FASE
    int entrouNaPorta = 0;
    int perdeu = 0;
    
    //AUXILIAR MENU
    int continua = 0, continua1 = 0;
    
    //INICIALIZA A CAMERA
    Camera2D camera = {0};
    camera.target = jogador.centro;
    camera.offset = (Vector2) {width/2, height/2};
    camera.rotation = 0;
    camera.zoom = 1;

    //INICIO DO LOOP EM QUE RODA O JOGO
    while(!WindowShouldClose()) {       

        while (perdeu) {//
            
            BeginDrawing();
            ClearBackground(WHITE);

            DrawText("PAULO SALGADO NÃO IRÁ... NÃO IRÁ NOS SALVAR", width / 2 - MeasureText("PAULO SALGADO NÃO IRÁ... NÃO IRA NOS SALVAR", 70) / 2, height / 2 - 70, 70, BLACK);

            EndDrawing();
            
            if (IsKeyPressed(KEY_ESCAPE)) {//MUDAR PRA KEY_SPACE DPS
                perdeu = 0;
                //Reiniciar a fase
            }
        }
        
        if(continua == 0 && continua1 == 0){ //Chama a primeira parte do menu
           continua = geraMenu();
        }
       
        if(continua == 1 && continua1 == 0){ //Chama a parte dos comandos
           continua1 = iniciaJogo();
        }
       
        if(continua1 == 1 && continua == 1){ //Inicia Jogo
        
            //atualiza a camera
            camera.target = jogador.centro;
            
            while (entrouNaPorta) {
                
                BeginDrawing();
                ClearBackground(WHITE);
                DrawText(TextFormat("HIGHSCORE : %d", jogador.score), width / 2 - MeasureText("HIGHSCORE : ", 75) / 2, height / 2 - 75, 75, BLACK);
                EndDrawing();
             
                if (IsKeyPressed(KEY_ESCAPE)) {//MUDAR PRA KEY_SPACE DPS
                    entrouNaPorta = 0;
                }
            } 
            
          
            BeginDrawing();
            
            jogador.campoVisao = 150 + (35 * jogador.qtdBaterias);//raio do campo de visao
            //DrawCircle(camera.target.x, camera.target.y, jogador.campoVisao, WHITE);//campo de visao
            //atualiza o centro do jogador
            jogador.centro = (Vector2) {(2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2, (2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2};
            //atualiza o centro do inimigo
            fase.inimigos[0].centro = (Vector2) {(2*fase.inimigos[0].coordenadas.x + 8*fase.inimigos[0].textura.width)/2, (2*fase.inimigos[0].coordenadas.y + 8*fase.inimigos[0].textura.height)/2};
            ClearBackground(BLACK);
            
            
            BeginMode2D(camera);//ativa a camera
            DrawCircle(jogador.centro.x, jogador.centro.y, jogador.campoVisao, WHITE);
        
            DrawText("FASE 1", width / 2 - MeasureText("FASE 1", 40) / 2, height / 2 - 40, 40, BLACK);
          
            //DESENHA INIMIGOS
            if (!perdeu) {
                float distCampoVisaoinimigoC = sqrt(pow(jogador.centro.x - fase.inimigos[0].centro.x, 2) + pow(jogador.centro.y - fase.inimigos[0].centro.y, 2));
                if (distCampoVisaoinimigoC < jogador.campoVisao) {//se tiver dentro do campo de visao
                    DrawTextureEx(fase.inimigos[0].textura, fase.inimigos[0].coordenadas, 0, 8, WHITE);
                }
                else DrawTextureEx(fase.inimigos[0].textura, fase.inimigos[0].coordenadas, 0, 8, WHITE);
                
                DrawRectangle(fase.inimigos[0].hitbox.x, fase.inimigos[0].hitbox.y, fase.inimigos[0].hitbox.width, fase.inimigos[0].hitbox.height, BLANK);
            }
           
            //DESENHA A TEXTURA DAS BATERIAS 
            for (int i = 0; i < fase.qtdBaterias; i++) {
                if (fase.baterias[i].colisao == 0) {
                    float distCampoVisaoBateriaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.baterias[i].coordenadas.x + 3*fase.baterias[i].textura.width)/2, 2)
                    + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.baterias[i].coordenadas.y + 3*fase.baterias[i].textura.height)/2, 2));
                    if (distCampoVisaoBateriaC < jogador.campoVisao) {
                        DrawTextureEx(fase.baterias[i].textura, fase.baterias[i].coordenadas, 0, 3, WHITE);
                    }
                    else DrawTextureEx(fase.baterias[i].textura, fase.baterias[i].coordenadas, 0, 3, BLACK);
                    
                    DrawRectangle(fase.baterias[i].hitbox.x, fase.baterias[i].hitbox.y, fase.baterias[i].hitbox.width, fase.baterias[i].hitbox.height, BLANK);
                }
            }
            
            //DESENHA A TEXTURA DA CHAVE
            float distCampoVisaoChaveC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.chave.coordenadas.x + 2.5*fase.chave.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.chave.coordenadas.y + 2.5*fase.chave.textura.height)/2, 2));
            if (!jogador.temChave) {
                if (distCampoVisaoChaveC < jogador.campoVisao) {
                    DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, WHITE);
                }
                else DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, BLACK);
                
                DrawRectangle(fase.chave.hitbox.x, fase.chave.hitbox.y, fase.chave.hitbox.width, fase.chave.hitbox.height, BLANK);
            }
           
            //hitbox dinamica que se move conforme o sprite do jogador
            jogador.hitbox = (Rectangle) {
                jogador.coordenadas.x + 18,
                jogador.coordenadas.y + 40,
                96,
                90,
            };
          
            //hitbox dinamica para o inimigo
            fase.inimigos[0].hitbox = (Rectangle) {
                fase.inimigos[0].coordenadas.x + 5,
                fase.inimigos[0].coordenadas.y,
                108,
                165,
            };
          
            float distCampoVisaoPortaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.porta.coordenadas.x + 2.2*fase.porta.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.porta.coordenadas.y + 2.2*fase.porta.textura.height)/2, 2));
            if (!jogador.temChave) {//desenha antes se o jogador nao tiver a chave
                if (distCampoVisaoPortaC < jogador.campoVisao) {
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, WHITE);
                }
                else DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2,  BLACK);
                
                DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
            }
                
            //DESENHA A TEXTURA DO JOGADOR
            if (!perdeu) {
                DrawTextureEx(jogador.textura, jogador.coordenadas, 0, 0.33, WHITE);
                DrawRectangle(jogador.hitbox.x, jogador.hitbox.y, jogador.hitbox.width, jogador.hitbox.height, BLANK);
            }
            
            if (jogador.temChave) {//desenha depois se tiver a chave
                if (distCampoVisaoPortaC < jogador.campoVisao) {
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, WHITE);
                }
                else DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, BLACK);
                
                DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
            }

            moverJogador(&jogador);
            perseguirJogador(fase.inimigos, jogador);
            
            if (CheckCollisionRecs(jogador.hitbox, fase.inimigos[0].hitbox)) {
                printf("Colisao INIMIGO");
                UnloadTexture(jogador.textura);
                jogador.hitbox = (Rectangle) {0, 0, 0, 0};
                perdeu = 1;
            }
           
            //CHECA SE HOUVE COLISAO COM A CHAVE
            if (CheckCollisionRecs(jogador.hitbox, fase.chave.hitbox)) {
                fase.chave.colisao = 1;
                printf("Colisao CHAVE\n");
                UnloadTexture(fase.chave.textura);//apaga a textura
                fase.chave.hitbox = (Rectangle) {0, 0, 0, 0};//remove a hitbox
                jogador.temChave = 1;//atualiza a flag do jogador
                jogador.score += 200;
            }
         
            //CHECA SE HOUVE COLISAO COM A PORTA
            if (CheckCollisionRecs(jogador.hitbox, fase.porta.hitbox)) {
                if (jogador.temChave) {
                    fase.porta.colisao = 1;
                    printf("Colisao PORTA\n");
                    UnloadTexture(fase.porta.textura);
                    fase.porta.hitbox = (Rectangle) {0, 0, 0, 0};
                    jogador.score += 500;
                    entrouNaPorta = 1;
                }
                else {
                    DrawText("PORTA TRANCADA", fase.porta.coordenadas.x - 3*fase.porta.textura.width, fase.porta.coordenadas.y - 50, 40, RED);

                }
            }
           
            //CHECA SE HOUVE COLISAO COM UMA DAS BATERIAS
            int indColisoes[fase.qtdBaterias];//armazena os indices das baterias colididas
            int qtdColisoes = 0;//qtd de baterias obtidas
            for (int i = 0; i < fase.qtdBaterias; i++) {
                if (CheckCollisionRecs(jogador.hitbox, fase.baterias[i].hitbox)) {
                    indColisoes[qtdColisoes] = i;//guarda os indices
                    qtdColisoes++;
                }
            }
                
            //REMOVER BATERIAS
            for (int i = 0 ; i < qtdColisoes; i++) { 
                int ind = indColisoes[i];
                //checa a flag da bateria daquele indice, se o indice estiver dentro da lista e flag for 0,
                //entao tem que apagar a bateria
                if (fase.baterias[ind].colisao == 0) {
                    fase.baterias[ind].colisao = 1;
                    printf("Colisao BATERIA\n");
                    UnloadTexture(fase.baterias[ind].textura);
                    fase.baterias[ind].hitbox = (Rectangle){0, 0, 0, 0};
                    jogador.qtdBaterias++; 
                    jogador.score += 50;
                }
            }

            //GUARDAR CADA STRING EM UMA VARIAVEL DIFERENTE E SÓ SOMAR 1 NO CHAR DO DIGITO
            DrawText(TextFormat("SCORE : %d", jogador.score), camera.target.x - 900, camera.target.y - 500, 40, GRAY);
            DrawText(TextFormat("CHAVES : %d", jogador.temChave), camera.target.x - 900, camera.target.y - 450, 40, GRAY);
            DrawText(TextFormat("BATERIAS : %d", jogador.qtdBaterias), camera.target.x - 900, camera.target.y - 400, 40, GRAY);

            EndMode2D();
            EndDrawing();  
            
        }
    }

    //DESALOCA OS PONTEIROS, APAGA AS TEXTURAS E DESATIVA AS FUNCOES DE AUDIO
    UnloadTexture(jogador.textura);
    UnloadTexture(fase.chave.textura);
    UnloadTexture(fase.porta.textura);
    for (int i = 0; i < fase.qtdInimigos; i++) {
       UnloadTexture(fase.inimigos[i].textura); 
    }
    for (int i = 0; i < fase.qtdBaterias; i++) {
       UnloadTexture(fase.baterias[i].textura); 
    }
    free(fase.baterias);
    CloseAudioDevice();
    CloseWindow();

    return 0; 
}

Fase criarFase() {//usa o endereco do jogador para poder alterar a posicao e outros fatores
    
    int height = GetScreenHeight();
    int width = GetScreenWidth();

    Fase fase;
    //INICIALIZACAO DOS INIMIGOS
    fase.inimigos = inicializarInimigos();
 
    //INICIALIZACAO DAS BATERIAS
    fase.qtdBaterias = 0;
    fase.baterias = inicializarBaterias(&fase.qtdBaterias);
    
    //INICIALIZACAO DA CHAVE
    fase.chave = inicializarChave();
    
    //INICIALIZACAO DA PORTA DE SAIDA
    fase.porta = inicializarPorta();
    
    return fase;
}
