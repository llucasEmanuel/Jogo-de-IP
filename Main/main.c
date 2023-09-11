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
    int faseAtual;
} Fase;

Fase criarFase(int numFase);
void reiniciarFase(Player *jogador, Fase *fase);

int main() {
    
    srand(time(NULL));
    
    InitWindow(1920, 1080, "FNAU");
    //if (!IsWindowFullscreen()) ToggleFullscreen();
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    Player jogador = inicializarJogador();//inicializa jogador fora do criarFase para manter o score para as outras fases
    Fase fase = criarFase(1);
    //INICIALIZACAO DOS INIMIGOS FORA DO DOMINIO DA FASE
    //Enemy *vetorInimigos = inicializarInimigos();//guarda os inimigos
    int qtdInimigos = 1;
    
    //fase.inimigos = vetorInimigos;
    //Texture mapa = LoadTexture("Sprites e Texturas/mapa.png");
    fase.qtdInimigos = qtdInimigos;
    
    //INICIALIZACAO DOS SONS
    InitAudioDevice();
    Music musica = LoadMusicStream("Sons e Musica/Spooked - Mini Vandals.mp3");
    Sound youDied = LoadSound("Sons e Musica/you_died_DS.mp3");
    Sound musicaEncerramento = LoadSound("Sons e Musica/Dramatic Series Theme - Freedom Trail Studio.mp3");
    Sound musicaPerseguicao = LoadSound("Sons e Musica/Funeral in Sinaloa - Jimena Contreras.mp3");
    PlayMusicStream(musica);
    int musicaTocando = 0;//musica de perseguicao
    int musicaDelay = 0;
    
    SetTargetFPS(60);
    
    //
    Font fonteDS = LoadFont("OptimusPrinceps.ttf");
    //FLAGS PARA CONTROLE DOS EVENTOS DA FASE
    int entrouNaPorta = 0;
    int perdeu = 0;
    int deathCount = 0;
    
    //AUXILIAR MENU
    Menu menu;
    Comando comando;
    iniciaMenu(&menu);
    iniciaComando(&comando);
    
    //INICIALIZA A CAMERA
    Camera2D camera = {0};
    camera.target = jogador.centro;
    camera.offset = (Vector2) {width/2, height/2};
    camera.rotation = 0;
    camera.zoom = 1;
    
    //AUXILIAR RANKING
    Ranking *ranking = NULL;
    
    //INICIALIZAR COLETAVEIS CONTADOREs
    CollectableContador chave, bateria;
    InicializaColetavelContador(&chave);
    InicializaColetavelContador1(&bateria);


    //INICIO DO LOOP EM QUE RODA O JOGO
    while(!WindowShouldClose()) { 
        
        UpdateMusicStream(musica);

        int gravouScore = 0;//garante que nao vai gravar o score varias vezes no loop
        while (fase.faseAtual > 5 && !IsKeyDown(KEY_ESCAPE)) {
            
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("PARABENS, VOCE SOBREVIVEU A UFPE...", width / 2 - MeasureText("PARABENS, VOCE SOBREVIVEU A UFPE...", 60) / 2, height / 2 - 450, 60, BLACK); 
            DrawText("POR ENQUANTO!", width / 2 - MeasureText("POR ENQUANTO!", 90) / 2, height / 2 - 350, 90, MAROON); 

            DrawText("RANKING", width / 2 - 150, height / 2 - 125, 50, MAROON);
           
            //SALVAR A PONTUACAO DO JOGADOR
            if (!gravouScore) {
                StopMusicStream(musica);
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
                PlaySound(musicaEncerramento);
                SetSoundVolume(musicaEncerramento, 0.8);
                FILE *file = fopen("highscore.txt", "a");
                if (file == NULL) {
                    printf("Erro ao abrir o arquivo highscore.txt\n");
                    exit(1);
                }
                fprintf(file, "%s,%d\n", menu.nome, jogador.score);
                fclose(file);
                
                //organizar o ranking
                file = fopen("highscore.txt", "r");
                if(file == NULL){
                    printf("falha na leitura do arquivo.\n");
                    exit(1);
                }
                ranking = organizaRanking(file);
                fclose(file);
                gravouScore = 1;
            }

            for(int i = 0; i < ranking[0].qtdPessoas && i < 10; i++){
                DrawText(TextFormat("%d. %s - %d", i + 1, ranking[i].nome, ranking[i].pontuacao), width/2 - 200, height / 2 + (50 * i) - 25, 40, BLACK);
            }
            EndDrawing();

        }
        

        if (perdeu) {  
            StopMusicStream(musica);
            SetSoundVolume(youDied, 2.5);
            PlaySound(youDied);
            
            if (jogador.score >= 200) jogador.score -= 200;//perde 200 pontos toda vez que morre
            else (jogador.score) = 0;
            
            while (perdeu) {
               
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
               
                BeginDrawing();
                ClearBackground(BLACK);
          
                DrawTextEx(fonteDS, "PAULO SALGADO NAO IRA ... NAO IRA NOS SALVAR", (Vector2) {width / 2 - MeasureText("PAULO SALGADO NAO IRA ... NAO IRA NOS SALVAR", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                //else if (fase.faseAtual == 2)
                   // DrawTextEx(fonteDS, "NIVAN NAO IRA ... NAO IRA NOS SALVAR", (Vector2) {width / 2 - MeasureText("NIVAN NAO IRA ... NAO IRA NOS SALVAR", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);

                DrawText("Aperte [SPACE] para continuar", width/2 - MeasureText("Aperte [SPACE] para continuar", 50)/2, 980, 50, GRAY);
                
                EndDrawing();
                
                if (IsKeyPressed(KEY_SPACE)) {
                    StopSound(youDied);
                    perdeu = 0;
                    
                    //Reiniciar a fase
                    reiniciarFase(&jogador, &fase);
                    PlayMusicStream(musica);
                    //fase.inimigos = inicializarInimigos();
                }
            }
        }
        
        if(menu.continua == 0 && comando.continua == 0){ //Chama a primeira parte do menu
           menu = desenhaMenu(menu);
        }
       
        if(menu.continua == 1 && comando.continua == 0){ //Chama a parte dos comandos
           comando = iniciaJogo(comando);
        }
       
        if(menu.continua == 1 && comando.continua == 1){ //Inicia Jogo
        
            //atualiza a camera
            camera.target = jogador.centro;
            
            int tamBarra = 240 - 80*deathCount;
            
            while (entrouNaPorta) {
                
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
                
                BeginDrawing();
                ClearBackground(WHITE);
                DrawText(TextFormat("HIGHSCORE : %d", jogador.score), width / 2 - MeasureText("HIGHSCORE : ", 75) / 2, height / 2 - 75, 75, BLACK);
                EndDrawing();
                if (IsKeyPressed(KEY_SPACE)) {//MUDAR PRA KEY_SPACE DPS
 
                    //qtdInimigos++;
                    reiniciarFase(&jogador, &fase);
                    PlayMusicStream(musica);
                    //fase.inimigos = inicializarInimigos();
                    entrouNaPorta = 0;    
                    fase.faseAtual++;
                    //fase.inimigos = atualizarVetorInimigos(fase.inimigos, &qtdInimigos);
                    //fase.qtdInimigos = qtdInimigos;
                    //printf("QTD INIMIGOS = %d\n", qtdInimigos);
                }
            } 

            BeginDrawing();
            
            jogador.campoVisao = 150 + (35 * jogador.qtdBaterias);//raio do campo de visao
            //DrawCircle(camera.target.x, camera.target.y, jogador.campoVisao, WHITE);//campo de visao
            //atualiza o centro do jogador
            jogador.centro = (Vector2) {(2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2, (2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2};
            //atualiza o centro do inimigo
            //for (int i = 0; i < fase.qtdInimigos; i++) {
                fase.inimigos[0].centro = (Vector2) {(2*fase.inimigos[0].coordenadas.x + 8*fase.inimigos[0].textura.width)/2, (2*fase.inimigos[0].coordenadas.y + 8*fase.inimigos[0].textura.height)/2};
            //}
            ClearBackground(BLACK);
            
            
            BeginMode2D(camera);//ativa a camera
            //DrawTextureEx(mapa, (Vector2) {0, 0}, 0, 1, WHITE);
            
            //DEFINE A COR BASE DE CADA FASE
            Color cores[5] = {WHITE, RED, SKYBLUE, ORANGE, GRAY};
            Color cor;
            switch (fase.faseAtual) {
                case 1:
                    cor = cores[0];
                    break;
                case 2:
                    cor = cores[1];
                    break;
                case 3:
                    cor = cores[2];
                    break;
                case 4:
                    cor = cores[3];
                    break;
                case 5:
                    cor = cores[4];
                    break;
                default:
                    cor = BLACK;
                    break;
            }
            
            DrawCircle(jogador.centro.x, jogador.centro.y, jogador.campoVisao, cor);
            
            
            //MARCADORES DOS LIMITES DA FASE
            DrawLine(0, 0, width, 0, BLACK);
            DrawLine(width, 0, width, height, BLACK);
            DrawLine(width, height, 0, height, BLACK);
            DrawLine(0, height, 0, 0, BLACK);
          
            //DESENHA INIMIGOS
            if (!perdeu) {
                //for (int i = 0; i < fase.qtdInimigos; i++) {
                    float distCampoVisaoinimigoC = sqrt(pow(jogador.centro.x - fase.inimigos[0].centro.x, 2) + pow(jogador.centro.y - fase.inimigos[0].centro.y, 2));
                    if (distCampoVisaoinimigoC < jogador.campoVisao) {//se tiver dentro do campo de visao
                        if (!musicaTocando) {
                            PauseMusicStream(musica);
                            PlaySound(musicaPerseguicao);
                            SetSoundVolume(musicaPerseguicao, 0.6);
                            musicaTocando = 1;
                            musicaDelay = 300;//num de frames (5 segundos)
                        }
                        DrawTextureEx(fase.inimigos[0].textura, fase.inimigos[0].coordenadas, 0, 8, WHITE);
                    }
                    else { 
                        if (musicaTocando) {
                            if (musicaDelay > 0) musicaDelay--;
                            else {   
                                ResumeMusicStream(musica);//continua de onde parou
                                StopSound(musicaPerseguicao);
                                musicaTocando = 0;
                            }
                        }
                        DrawTextureEx(fase.inimigos[0].textura, fase.inimigos[0].coordenadas, 0, 8, WHITE);
                    }
                    
                    DrawRectangle(fase.inimigos[0].hitbox.x, fase.inimigos[0].hitbox.y, fase.inimigos[0].hitbox.width, fase.inimigos[0].hitbox.height, BLANK);
                //}
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
            
            //hitbox dinamica que se move conforme o sprite do jogador
            jogador.hitbox = (Rectangle) {
                jogador.coordenadas.x + 18,
                jogador.coordenadas.y + 40,
                96,
                90,
            };
          
            //hitbox dinamica para o inimigo
            //for (int i = 0; i < fase.qtdInimigos; i++) {
                fase.inimigos[0].hitbox = (Rectangle) {
                    fase.inimigos[0].coordenadas.x + 5,
                    fase.inimigos[0].coordenadas.y,
                    108,
                    165,
                };
            //}
            
            //DESENHA DE TEXTURA DA PORTA
            float distCampoVisaoPortaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.porta.coordenadas.x + 2.2*fase.porta.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.porta.coordenadas.y + 2.2*fase.porta.textura.height)/2, 2));
            if (!jogador.temChave) {//desenha antes se o jogador nao tiver a chave
                if (distCampoVisaoPortaC < jogador.campoVisao) {
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, WHITE);
                }
                else DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2,  BLACK);
                
                DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
            }
            
            //DESENHA TEXTURA DA CHAVE
            float distCampoVisaoChaveC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.chave.coordenadas.x + 2.5*fase.chave.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.chave.coordenadas.y + 2.5*fase.chave.textura.height)/2, 2));
            if (!jogador.temChave) {
                if (distCampoVisaoChaveC < jogador.campoVisao) {
                    DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, WHITE);
                }
                else DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, BLACK);
                
                DrawRectangle(fase.chave.hitbox.x, fase.chave.hitbox.y, fase.chave.hitbox.width, fase.chave.hitbox.height, BLANK);
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
            perseguirJogador(fase.inimigos, jogador, fase.qtdInimigos);
          
            
            //for (int i = 0; i < fase.qtdInimigos; i++) {
                if (CheckCollisionRecs(jogador.hitbox, fase.inimigos[0].hitbox)) {
                    DrawTextureEx(jogador.textura, jogador.coordenadas, 0, 0.33, cor);
                    printf("Colisao INIMIGO\n");
                    UnloadTexture(jogador.textura);
                    jogador.hitbox = (Rectangle) {0, 0, 0, 0};
                    perdeu = 1;
                    deathCount++;
                    // if (tamBarra == 0) {
                        // gameOver();
                    // }
                }
            //}
           
            //CHECA SE HOUVE COLISAO COM A CHAVE
            if (CheckCollisionRecs(jogador.hitbox, fase.chave.hitbox)) {
                DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, cor);
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
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, cor);
                    fase.porta.colisao = 1;
                    printf("Colisao PORTA\n");
                    UnloadTexture(fase.porta.textura);
                    fase.porta.hitbox = (Rectangle) {0, 0, 0, 0};
                    jogador.score += 500;
                    entrouNaPorta = 1;
                }
                else {
                    if (fase.faseAtual != 2)
                        DrawText("PORTA TRANCADA", fase.porta.coordenadas.x - 3*fase.porta.textura.width, fase.porta.coordenadas.y - 50, 40, RED);
                    else 
                        DrawText("PORTA TRANCADA", fase.porta.coordenadas.x - 3*fase.porta.textura.width, fase.porta.coordenadas.y - 50, 40, RAYWHITE);
                }
            }
           
            //CHECA SE HOUVE COLISAO COM UMA DAS BATERIAS
            int indColisoes[fase.qtdBaterias];//armazena os indices das baterias colididas
            int qtdColisoes = 0;//qtd de baterias obtidas
            for (int i = 0; i < fase.qtdBaterias; i++) {
                if (CheckCollisionRecs(jogador.hitbox, fase.baterias[i].hitbox)) {
                    DrawTextureEx(fase.baterias[i].textura, fase.baterias[i].coordenadas, 0, 3, cor);
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

            //DESENHAR BARRA DE SANIDADE (A CADA MORTE ELA AUMENTA 1/3)
            DrawRectangle(camera.target.x - 120, camera.target.y - 450, 250, 40, GRAY);
            DrawRectangle(camera.target.x - 115, camera.target.y - 446, tamBarra, 32, RED);
            //


            
            DrawText(TextFormat("NOITE %d", fase.faseAtual), camera.target.x - MeasureText("NOITE 1", 40) / 2, camera.target.y + 400, 40, GRAY);
            DrawText(TextFormat("SCORE : %d", jogador.score), camera.target.x - 900, camera.target.y - 500, 40, GRAY);
            chave.coordenadas.x = camera.target.x - 900;
            chave.coordenadas.y = camera.target.y - 450;
            DrawTextureEx(chave.textura, chave.coordenadas, 0, 2.5, WHITE);
            DrawText(TextFormat(" x %d", jogador.temChave), camera.target.x - 900 + (2.5 * chave.textura.width), camera.target.y - 450, 40, GRAY);
            bateria.coordenadas.x = camera.target.x - 900;
            bateria.coordenadas.y = camera.target.y - 400;
            DrawTextureEx(bateria.textura, bateria.coordenadas, 0, 3, WHITE);
            DrawText(TextFormat(" x %d", jogador.qtdBaterias), camera.target.x - 900 + (3 * bateria.textura.width), camera.target.y - 390, 40, GRAY);

            EndMode2D();
            EndDrawing();  
        }
    }

    //DESALOCA OS PONTEIROS, APAGA AS TEXTURAS E DESATIVA AS FUNCOES DE AUDIO
    UnloadMusicStream(musica);
    UnloadSound(musicaEncerramento);
    UnloadSound(musicaPerseguicao);
    UnloadSound(youDied);
    
    UnloadTexture(jogador.textura);
    UnloadTexture(fase.chave.textura);
    UnloadTexture(fase.porta.textura);
    UnloadTexture(chave.textura);
    UnloadTexture(bateria.textura);
    //UnloadTexture(mapa);
    for (int i = 0; i < qtdInimigos; i++) {
       UnloadTexture(fase.inimigos[i].textura); 
    }
    for (int i = 0; i < fase.qtdBaterias; i++) {
       UnloadTexture(fase.baterias[i].textura); 
    }
    free(fase.inimigos);
    UnloadFont(fonteDS);
    free(fase.baterias);
    CloseAudioDevice();
    CloseWindow();

    return 0; 
}

Fase criarFase(int numFase) {//usa o endereco do jogador para poder alterar a posicao e outros fatores
    

    Fase fase;
    
    fase.inimigos = inicializarInimigos();
 
    //INICIALIZACAO DAS BATERIAS
    fase.qtdBaterias = 0;
    fase.baterias = inicializarBaterias(&fase.qtdBaterias);
    
    //INICIALIZACAO DA CHAVE
    fase.chave = inicializarChave();
    
    //INICIALIZACAO DA PORTA DE SAIDA
    fase.porta = inicializarPorta();
    fase.faseAtual = numFase;
    
    return fase;
}

void reiniciarFase(Player *jogador, Fase *fase) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    jogador->textura = LoadTexture("Sprites e Texturas/sprite1.png");
    jogador->coordenadas = (Vector2){width/2, height/2};
    jogador->qtdBaterias = 0;
    jogador->temChave = 0;
    // Redefina a fase para o estado inicial
    (*fase) = criarFase(fase->faseAtual);
}
