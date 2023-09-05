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

typedef struct {//Fazer a funcao criarFase() retornar a fase inicializada
    //Player jogador;//Jogador vai ser independente da fase, talvez n precise disso
    Enemy *inimigos;
    Collectable chave;
    Collectable porta;
    Collectable *baterias;
    int qtdBaterias;
    int qtdInimigos;
} Fase;

Fase criarFase();
void gameOver();

int main() {
    
    srand(time(NULL));
    InitWindow(1920, 1080, "Jogo de IP");
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    Player jogador = inicializarJogador();//inicializa jogador fora do criarFase para manter o score para as outras fases
    Fase fase = criarFase();
    fase.qtdInimigos = 1;
    
    //INICIALIZACAO DOS SONS
    InitAudioDevice();
    Sound musica = LoadSound("Sons e Musica/Spooked - Mini Vandals.mp3");
    PlaySound(musica);
    //if (!IsWindowFullscreen()) ToggleFullscreen();
    SetTargetFPS(60);
    
    //AUXILIAR MENU
    int continua = 0, continua1 = 0;
    
    char bateriasStr[] = "BATERIAS : 0";//11 == ind do char do digito
    char chavesStr[] = "CHAVES : 0";//9 == ind do char do digito
    
    int entrouNaPorta = 0;
    int perdeu = 0;
    

    //INICIO DO LOOP EM QUE RODA O JOGO
    while(!WindowShouldClose()) {       

        while (perdeu) {
            
            BeginDrawing();
            ClearBackground(WHITE);

            DrawText("PAULO SALGADO NÃO... NÃO IRA NOS SALVAR", width / 2 - MeasureText("PAULO SALGADO NÃO... NÃO IRA NOS SALVAR", 75) / 2, height / 2 - 75, 75, BLACK);

            EndDrawing();
            
            if (IsKeyPressed(KEY_ESCAPE)) {//mudar a tecla para KEY_SPACE depois
                perdeu = 0;
            }
        }
        
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

                DrawText(TextFormat("HIGHSCORE : %d", jogador.score), width / 2 - MeasureText("HIGHSCORE : ", 75) / 2, height / 2 - 75, 75, BLACK);
   

                EndDrawing();
             
                if (IsKeyPressed(KEY_ESCAPE)) {
                    entrouNaPorta = 0;
                }
            }

                BeginDrawing();
                
                jogador.campoVisao = 150 + (35 * jogador.qtdBaterias);
                DrawCircle(jogador.hitbox.x + 46, jogador.hitbox.y + 40, jogador.campoVisao, WHITE);//campo de visao
                ClearBackground(BLACK);
        
                DrawText("FASE 1", width / 2 - MeasureText("FASE 1", 40) / 2, height / 2 - 40, 40, BLACK);
                
                //DESENHA INIMIGOS
                if (!perdeu) {
                    DrawTextureEx(fase.inimigos[0].textura, fase.inimigos[0].coordenadas, 0, 8, BLACK);
                    DrawRectangle(fase.inimigos[0].hitbox.x, fase.inimigos[0].hitbox.y, fase.inimigos[0].hitbox.width, fase.inimigos[0].hitbox.height, BLANK);
                }
                
                //DESENHA A TEXTURA DAS BATERIAS 
                for (int i = 0; i < fase.qtdBaterias; i++) {
                    if (fase.baterias[i].colisao == 0) {
                        DrawTextureEx(fase.baterias[i].textura, fase.baterias[i].coordenadas, 0, 3, BLACK);
                        DrawRectangle(fase.baterias[i].hitbox.x, fase.baterias[i].hitbox.y, fase.baterias[i].hitbox.width, fase.baterias[i].hitbox.height, BLANK);
                    }
                }
                
                //DESENHA A TEXTURA DA CHAVE
                if (!jogador.temChave) {
                    DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, BLACK);
                    DrawRectangle(fase.chave.hitbox.x, fase.chave.hitbox.y, fase.chave.hitbox.width, fase.chave.hitbox.height, BLANK);
                }
                
                //hitbox dinamica que se move conforme o sprite do jogador
                jogador.hitbox = (Rectangle) {
                    jogador.coordenadas.x + 18,
                    jogador.coordenadas.y + 40,
                    96,
                    90,
                };
                
                if (!jogador.temChave) {//desenha antes se o jogador nao tiver a chave
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, BLACK);
                    DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
                }
                
                //DESENHA A TEXTURA DO JOGADOR
                if (!perdeu) {
                    DrawTextureEx(jogador.textura, jogador.coordenadas, 0, 0.33, WHITE);
                    DrawRectangle(jogador.hitbox.x, jogador.hitbox.y, jogador.hitbox.width, jogador.hitbox.height, BLANK);
                }
                
                if (jogador.temChave) {//desenha depois se tiver a chave
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, BLACK);
                    DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
                }

                moverJogador(&jogador);
                
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
                    chavesStr[9]++;//atualiza a qtd chaves na tela
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
                        DrawText("PORTA TRANCADA", width/2 - MeasureText("PORTA TRANCADA", 30), 50, 40, RED);
                    }
                }
                
                //CHECA SE HOUVE COLISAO COM UMA DAS BATERIAS
                int indColisoes[fase.qtdBaterias];//armazena os indices das baterias colididas
                int qtdColisoes = 0;//qtd de baterias obtidas
                for (int i = 0; i < fase.qtdBaterias; i++) {
                    if (CheckCollisionRecs(jogador.hitbox, fase.baterias[i].hitbox)) {
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
                DrawText(TextFormat("SCORE : %d", jogador.score), 30, 30, 40, GRAY);
                DrawText(chavesStr, 30, 80, 40, GRAY);
                DrawText(bateriasStr, 30, 130, 40, GRAY);

                EndDrawing();  
            
        }
    }

    //DESALOCA OS PONTEIROS, APAGA AS TEXTURAS E DESATIVA AS FUNCOES DE AUDIO
    UnloadTexture(jogador.textura);
    UnloadTexture(fase.chave.textura);
    UnloadTexture(fase.porta.textura);
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

    
