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

//CRIAR UM "settings.h" que vai ter as funcoes de inicializar musicas, camera, ...
#define SILVER (Color) {192, 192, 192, 255}
#define BRANCO (Color) {255, 255, 255, 180}

typedef struct {
    Enemy *inimigos;
    Collectable chave;
    Collectable porta;
    Collectable *baterias;
    Collectable vida;
    Texture mapa;
    int qtdBaterias;
    int qtdInimigos;
    int faseAtual;
} Fase;

Camera2D inicializarCamera(Player jogador);
void carregarMusicas(Music *musicasFase, Music *musicaMenu);
void carregarSons(Sound *youDied, Sound *musicaPerseguicao, Sound *musicaEncerramento);
void salvarScore(char *nome, int score);
void printTelaEncerramento(Ranking *ranking);
Fase criarFase(int numFase);
void reiniciarFase(Player *jogador, Fase *fase);

int main() {
    
    srand(time(NULL));
    
    InitWindow(1920, 1080, "FNAU");
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    SetTargetFPS(60);
    
    Player jogador = inicializarJogador();//inicializa jogador fora do criarFase para manter o score para as outras fases
    Fase fase = criarFase(1);
    fase.qtdInimigos = 1;
    fase.mapa = LoadTexture("Sprites e Texturas/mapa.png");
    
    //INICIALIZACAO DOS SONS E MUSICAS
    InitAudioDevice();
    
    Music musicasFase[5], musica;
    carregarMusicas(musicasFase, &musica);
    
    Sound youDied, musicaPerseguicao, musicaEncerramento;
    carregarSons(&youDied, &musicaPerseguicao, &musicaEncerramento);
    
    PlayMusicStream(musica);
    //flags de controle dos sons
    int musicaTocando = 0;//musica de perseguicao
    int musicaDelay = 0;
    //
    
    Font fonteDS = LoadFont("OptimusPrinceps.ttf");
    //FLAGS PARA CONTROLE DOS EVENTOS DA FASE
    //colocar as flags dentro das structs
    int entrouNaPorta = 0;
    int perdeu = 0;
    int deathCount = 0;
    int gameOver = 0;
    int musicaFaseTocando = 0;
    
    //AUXILIAR MENU
    Menu menu;
    Comando comando;
    iniciaMenu(&menu);
    iniciaComando(&comando);
    
    //INICIALIZA A CAMERA
    Camera2D camera = inicializarCamera(jogador);
    
    //AUXILIAR RANKING
    Ranking *ranking = NULL;
    
    //INICIALIZAR COLETAVEIS CONTADOREs
    CollectableContador chave, bateria;
    InicializaColetavelContador(&chave);
    InicializaColetavelContador1(&bateria);

    int frameAtual = 0;
    float tempoFrame = 0.1;
    float acumulador = 0;

    //INICIO DO LOOP EM QUE RODA O JOGO
    while(!WindowShouldClose()) { 
        
        UpdateMusicStream(musica);
        
        int tamBarra = 240 - 80*deathCount;
        
        int gravouScore = 0;//garante que nao vai gravar o score varias vezes no loop
        
        //TELA DE ENCERRAMENTO
        while (fase.faseAtual > 5 && !IsKeyDown(KEY_ESCAPE)) {
            
            //SALVAR A PONTUACAO DO JOGADOR
            if (!gravouScore) {
                StopMusicStream(musicasFase[0]);
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
                PlaySound(musicaEncerramento);
                SetSoundVolume(musicaEncerramento, 0.8);
                
                salvarScore(menu.nome, jogador.score);   
                //organizar o ranking
                FILE *file = fopen("highscore.txt", "r");
                if(file == NULL){
                    printf("falha na leitura do arquivo.\n");
                    exit(1);
                }
                ranking = organizaRanking(file);
                fclose(file);

                gravouScore = 1;
            }

            printTelaEncerramento(ranking);
        }
        //

        if (perdeu) {  
            StopMusicStream(musicasFase[0]);
            SetSoundVolume(youDied, 2.5);
            PlaySound(youDied);
            
            if (jogador.score >= 200) jogador.score -= 200;//perde 200 pontos toda vez que morre
            else (jogador.score) = 0;
            
            int ind = -1;
            for (int i = 0; i < fase.qtdInimigos && ind != i; i++) {
                if (fase.inimigos[i].colisao == 1) ind = i;
            }
            
            while (perdeu) {
               
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
               
                BeginDrawing();
                ClearBackground(BLACK);
                
                if (ind != -1) {
                    switch (ind) {
                        case 0://MS
                            DrawTextEx(fonteDS, "VOCE CHEGOU 2 MINUTOS ATRASADO", (Vector2) {width / 2 - MeasureText("VOCE CHEGOU 2 MINUTOS ATRASADO", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                            break;
                        case 1://PS
                            DrawTextEx(fonteDS, "PAULO SALGADO NAO IRA... NAO IRA NOS SALVAR", (Vector2) {width / 2 - MeasureText("PAULO SALGADO NAO IRA... NAO IRA NOS SALVAR", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                            break;
                        case 2://NV
                            DrawTextEx(fonteDS, "ISSO ERA TRIVIAL", (Vector2) {width / 2 - MeasureText("ISSO ERA TRIVIAL", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                            break;
                        default:
                            break;
                    }
                }
               
                DrawText("Aperte [SPACE] para continuar", width/2 - MeasureText("Aperte [SPACE] para continuar", 50)/2, 980, 50, GRAY);
                EndDrawing();
                
                if (IsKeyPressed(KEY_SPACE)) {
                    StopSound(youDied);
                    perdeu = 0;
                    fase.inimigos[ind].colisao = 0;
                    //Reiniciar a fase
                    reiniciarFase(&jogador, &fase);
                    if (fase.faseAtual <= 3)    
                        fase.qtdInimigos = fase.faseAtual;
                    PlayMusicStream(musicasFase[0]);
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
            if (!musicaFaseTocando) {//CRIAR UM VETOR E TOCAR A MUSICA DE (IND_FASE + 1)
                StopMusicStream(musica);
                PlayMusicStream(musicasFase[0]);
                musicaFaseTocando = 1;
                musicaTocando = 0; 
            }
            
            UpdateMusicStream(musicasFase[0]);
            
            while (entrouNaPorta) {
                
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
                
                BeginDrawing();
                ClearBackground(WHITE);
                DrawText(TextFormat("HIGHSCORE : %d", jogador.score), width / 2 - MeasureText("HIGHSCORE : ", 75) / 2, height / 2 - 75, 75, BLACK);
                EndDrawing();
                if (IsKeyPressed(KEY_SPACE)) {
 
                    //qtdInimigos++;
                    reiniciarFase(&jogador, &fase);
                    PlayMusicStream(musicasFase[0]);
                    //fase.inimigos = inicializarInimigos();
                    entrouNaPorta = 0;    
                    fase.faseAtual++;
                    if (fase.faseAtual <= 3)    
                        fase.qtdInimigos = fase.faseAtual;
                    //fase.inimigos = atualizarVetorInimigos(fase.inimigos, &qtdInimigos);
                    //fase.qtdInimigos = qtdInimigos;
                    //printf("QTD INIMIGOS = %d\n", qtdInimigos);
                }
            } 
            
            //TELA DE GAME OVER
            if (tamBarra <= 0) gameOver = 1; 
            while (gameOver) { 
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("VOCE FOI REPROVADO!", width/2 - MeasureText("VOCE FOI REPROVADO!", 120)/2, height/2 - 220, 120, MAROON);
                DrawText("GAME OVER", width/2 - MeasureText("GAME OVER", 150)/2, height/2 - 80, 150, RED);
                EndDrawing();
                if (IsKeyDown(KEY_ESCAPE)) {
                    gameOver = 0;
                    deathCount = 0;
                    // menu.continua = 0;
                    // comando.continua = 0;
                }
            }  

            BeginDrawing();
            
            jogador.campoVisao = 150 + (35 * jogador.qtdBaterias);//raio do campo de visao
            jogador.centro = (Vector2) {(2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2, (2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2};
            //atualiza o centro do inimigo
            for (int i = 0; i < fase.qtdInimigos; i++) {
                fase.inimigos[i].centro = (Vector2) {(2*fase.inimigos[i].coordenadas.x + 8*fase.inimigos[i].textura[0].width)/2, (2*fase.inimigos[i].coordenadas.y + 8*fase.inimigos[i].textura[0].height)/2};
            }
            ClearBackground(BLACK);
            
            BeginMode2D(camera);//ativa a camera
            //DrawTextureEx(mapa, (Vector2) {0, 0}, 0, 1, WHITE);
            
            //DrawTextureEx(fase.mapa, (Vector2){0, 0}, 0, 1, BRANCO);
            //DEFINE A COR BASE DE CADA FASE
            Color cores[5] = {WHITE, MAROON, SKYBLUE, ORANGE, GRAY};
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
            //DESENHA O CAMPO DE VISAO DO PERSONAGEM
            DrawCircle(jogador.centro.x, jogador.centro.y, jogador.campoVisao, cor);
            
            //MARCADORES DOS LIMITES DA FASE
            DrawLine(0, 0, width, 0, BLACK);
            DrawLine(width, 0, width, height, BLACK);
            DrawLine(width, height, 0, height, BLACK);
            DrawLine(0, height, 0, 0, BLACK);
            
            //DESENHA DE TEXTURA DA PORTA
            float distCampoVisaoPortaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.porta.coordenadas.x + 2.2*fase.porta.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.porta.coordenadas.y + 2.2*fase.porta.textura.height)/2, 2));
            if (!jogador.temChave) {//desenha antes se o jogador nao tiver a chave
                if (distCampoVisaoPortaC < jogador.campoVisao) {
                    DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, WHITE);
                }
                else DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2,  WHITE);
                
                DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
            }
           
            if (!perdeu) {
                for (int i = 0; i < fase.qtdInimigos; i++) {
                    
                    float deltaT = GetFrameTime();
                    acumulador += deltaT;
                    
                    if (acumulador >= tempoFrame) {
                        frameAtual = ((frameAtual + 1) % 4);
                        acumulador -= tempoFrame;
                    }
                    
                    float distCampoVisaoinimigoC = sqrt(pow(jogador.centro.x - fase.inimigos[i].centro.x, 2) + pow(jogador.centro.y - fase.inimigos[i].centro.y, 2));
                    if (distCampoVisaoinimigoC < jogador.campoVisao) {//se tiver dentro do campo de visao
                        if (!musicaTocando) {
                            PauseMusicStream(musicasFase[0]);
                            PlaySound(musicaPerseguicao);
                            SetSoundVolume(musicaPerseguicao, 0.6);
                            musicaTocando = 1;
                            musicaDelay = 300;//num de frames (5 segundos)
                        }
                        DrawTextureEx(fase.inimigos[i].textura[frameAtual], fase.inimigos[i].coordenadas, 0, 8, WHITE);
                    }
                    else { 
                        if (musicaTocando) {
                            if (musicaDelay > 0) {
                                musicaDelay--;
                            }
                            else {   
                                ResumeMusicStream(musicasFase[0]);//continua de onde parou
                                StopSound(musicaPerseguicao);
                                musicaTocando = 0;
                            }
                        }
                        DrawTextureEx(fase.inimigos[i].textura[frameAtual], fase.inimigos[i].coordenadas, 0, 8, WHITE);
                    }
                    
                    DrawRectangle(fase.inimigos[i].hitbox.x, fase.inimigos[i].hitbox.y, fase.inimigos[i].hitbox.width, fase.inimigos[i].hitbox.height, BLANK);
                }
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
            for (int i = 0; i < fase.qtdInimigos; i++) {
                fase.inimigos[i].hitbox = (Rectangle) {
                    fase.inimigos[i].coordenadas.x + 5,
                    fase.inimigos[i].coordenadas.y,
                    108,
                    165,
                };
            }
            
            //DESENHA TEXTURA DA CHAVE
            float distCampoVisaoChaveC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.chave.coordenadas.x + 2.5*fase.chave.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.chave.coordenadas.y + 2.5*fase.chave.textura.height)/2, 2));
            if (!jogador.temChave) {
                if (distCampoVisaoChaveC < jogador.campoVisao) {
                    DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, WHITE);
                }
                else DrawTextureEx(fase.chave.textura, fase.chave.coordenadas, 0, 2.5, WHITE);
                
                DrawRectangle(fase.chave.hitbox.x, fase.chave.hitbox.y, fase.chave.hitbox.width, fase.chave.hitbox.height, BLANK);
            }
            
            //DESENHA A TEXTURA DA VIDA
            float distCampoVisaoVidaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*fase.vida.coordenadas.x + 5*fase.vida.textura.width)/2, 2)
            + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*fase.vida.coordenadas.y + 5*fase.vida.textura.height)/2, 2));
            if (fase.vida.colisao == 0) {
                if (distCampoVisaoVidaC < jogador.campoVisao) {
                    DrawTextureEx(fase.vida.textura, fase.vida.coordenadas, 0, 5, WHITE);
                }
                else DrawTextureEx(fase.vida.textura, fase.vida.coordenadas, 0, 5, BLACK);
                
                DrawRectangle(fase.vida.hitbox.x, fase.vida.hitbox.y, fase.vida.hitbox.width, fase.vida.hitbox.height, BLANK);
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
                else DrawTextureEx(fase.porta.textura, fase.porta.coordenadas, 0, 2.2, WHITE);
                
                DrawRectangle(fase.porta.hitbox.x, fase.porta.hitbox.y, fase.porta.hitbox.width, fase.porta.hitbox.height, BLANK);
            }

            moverJogador(&jogador);
            perseguirJogador(fase.inimigos, jogador, fase.qtdInimigos);
          
            //CHECA SE HOUVE COLISAO COM O INIMIGO
            for (int i = 0; i < fase.qtdInimigos; i++) {
                if (CheckCollisionRecs(jogador.hitbox, fase.inimigos[i].hitbox)) {
                    DrawTextureEx(jogador.textura, jogador.coordenadas, 0, 0.33, cor);
                    printf("Colisao INIMIGO\n");
                    UnloadTexture(jogador.textura);
                    jogador.hitbox = (Rectangle) {0, 0, 0, 0};
                    fase.inimigos[i].colisao = 1;
                    perdeu = 1;
                    deathCount++;
                }
            }
           
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
            
            //CHECA SE HOUVE COLISAO COM A VIDA
            if (CheckCollisionRecs(jogador.hitbox, fase.vida.hitbox)) {
                DrawTextureEx(fase.vida.textura, fase.vida.coordenadas, 0, 5, cor);
                fase.vida.colisao = 1;
                jogador.pegouVida = 1;
                printf("Colisao VIDA\n");
                UnloadTexture(fase.vida.textura);
                fase.vida.hitbox = (Rectangle) {0, 0, 0, 0};
                jogador.score += 100;
                if (deathCount != 0) deathCount--;//aumenta a barra de sanidade 
            }

            //DESENHAR BARRA DE SANIDADE (A CADA MORTE ELA DIMINUI 1/3)
            DrawText("SANIDADE", camera.target.x - MeasureText("SANIDADE", 35)/2, camera.target.y - 500, 35, SILVER);
            DrawRectangle(camera.target.x - 125, camera.target.y - 450, 250, 40, SILVER);
            DrawRectangle(camera.target.x - 120, camera.target.y - 446, tamBarra, 32, RED);
            DrawRectangle(camera.target.x - 120 + 240 - (80*deathCount), camera.target.y - 446, 80*deathCount, 32, BLACK);
            //
            
            DrawText(TextFormat("NOITE %d", fase.faseAtual), camera.target.x - MeasureText("NOITE 1", 40) / 2, camera.target.y + 400, 40, SILVER);
            DrawText(TextFormat("SCORE : %d", jogador.score), camera.target.x - 900, camera.target.y - 500, 40, SILVER);
            chave.coordenadas.x = camera.target.x - 900;
            chave.coordenadas.y = camera.target.y - 450;
            DrawTextureEx(chave.textura, chave.coordenadas, 0, 2.5, WHITE);
            DrawText(TextFormat(" x %d", jogador.temChave), camera.target.x - 900 + (2.5 * chave.textura.width), camera.target.y - 450, 40, SILVER);
            bateria.coordenadas.x = camera.target.x - 900;
            bateria.coordenadas.y = camera.target.y - 400;
            DrawTextureEx(bateria.textura, bateria.coordenadas, 0, 3, WHITE);
            DrawText(TextFormat(" x %d", jogador.qtdBaterias), camera.target.x - 900 + (3 * bateria.textura.width), camera.target.y - 390, 40, SILVER);

            EndMode2D();
            EndDrawing();  
        }
    }

    //DA UNLOAD NAS MUSICAS E SONS
    UnloadMusicStream(musica);
    UnloadSound(musicaEncerramento);
    UnloadSound(musicaPerseguicao);
    UnloadSound(youDied);
    
    //DA UNLOAD NAS TEXTURAS
    UnloadTexture(jogador.textura);
    UnloadTexture(fase.chave.textura);
    UnloadTexture(fase.porta.textura);
    UnloadTexture(chave.textura);
    UnloadTexture(bateria.textura);
    UnloadTexture(fase.vida.textura);
    UnloadTexture(fase.mapa);
    for (int i = 0; i < fase.qtdInimigos; i++) {
        for (int j = 0; j < 4; j++)
            UnloadTexture(fase.inimigos[i].textura[j]); 
    }
    for (int i = 0; i < fase.qtdBaterias; i++) {
       UnloadTexture(fase.baterias[i].textura); 
    }
    UnloadFont(fonteDS);
    
    //DESALOCA OS PONTEIROS
    free(fase.inimigos);
    free(fase.baterias);
    CloseAudioDevice();
    CloseWindow();

    return 0; 
}

Camera2D inicializarCamera(Player jogador) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Camera2D camera = {0};
    camera.target = jogador.centro;
    camera.offset = (Vector2) {width/2, height/2};
    camera.rotation = 0;
    camera.zoom = 1;
    return camera;
}

void carregarMusicas(Music *musicasFase, Music *musicaMenu) {
    (*musicaMenu) = LoadMusicStream("Sons e Musica/Spooked - Mini Vandals.mp3");
    for (int i = 0; i < 5; i++) {
        musicasFase[i] = LoadMusicStream("Sons e Musica/musicaFase1.mp3");
    }
}

void carregarSons(Sound *youDied, Sound *musicaPerseguicao, Sound *musicaEncerramento) {
    (*youDied) = LoadSound("Sons e Musica/you_died_DS.mp3");
    (*musicaEncerramento) = LoadSound("Sons e Musica/Dramatic Series Theme - Freedom Trail Studio.mp3");
    (*musicaPerseguicao) = LoadSound("Sons e Musica/Funeral in Sinaloa - Jimena Contreras.mp3");
}

void salvarScore(char *nome, int score) {
    FILE *file = fopen("highscore.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo highscore.txt\n");
        exit(1);
    }
    fprintf(file, "%s,%d\n", nome, score);
    fclose(file);
}

void printTelaEncerramento(Ranking *ranking) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("PARABENS, VOCE SOBREVIVEU A UFPE...", width / 2 - MeasureText("PARABENS, VOCE SOBREVIVEU A UFPE...", 60) / 2, height / 2 - 450, 60, BLACK); 
    DrawText("POR ENQUANTO!", width / 2 - MeasureText("POR ENQUANTO!", 90) / 2, height / 2 - 350, 90, MAROON); 
    for(int i = 0; i < ranking[0].qtdPessoas && i < 10; i++){
        DrawText(TextFormat("%d. %s - %d", i + 1, ranking[i].nome, ranking[i].pontuacao), width/2 - 200, height / 2 + (50 * i) - 25, 40, BLACK);
    }
    EndDrawing();
    DrawText("RANKING", width / 2 - 150, height / 2 - 125, 50, MAROON);
}

Fase criarFase(int numFase) {
    
    Fase fase;
    
    //INICIALIZAR INIMIGOS
    fase.inimigos = inicializarInimigos(numFase);
    if (numFase <= 3) fase.qtdInimigos = numFase; 
    else fase.qtdInimigos = 3;
 
    //INICIALIZACAO DAS BATERIAS
    fase.qtdBaterias = 0;
    fase.baterias = inicializarBaterias(&fase.qtdBaterias);
    
    //INICIALIZACAO DA CHAVE
    fase.chave = inicializarChave();
    
    //INICIALIZACAO DA PORTA DE SAIDA
    fase.porta = inicializarPorta();
    
    int spawnVida = rand() % 2;//50% de chance de spawnar e 50% de nao spawnar
    if (spawnVida) {
        fase.vida = inicializarVida();
    }
    
    fase.faseAtual = numFase;
    
    return fase;
}

void reiniciarFase(Player *jogador, Fase *fase) {//usa o endereco do jogador para poder alterar a posicao e outros fatores
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    jogador->textura = LoadTexture("Sprites e Texturas/sprite1.png");
    jogador->coordenadas = (Vector2){width/2, height/2};
    jogador->qtdBaterias = 0;
    jogador->temChave = 0;
    // Redefina a fase para o estado inicial
    (*fase) = criarFase(fase->faseAtual);
}
