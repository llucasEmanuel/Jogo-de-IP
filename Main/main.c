#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <raylib.h>
#include "settings.h"

#define BRANCO (Color) {255, 255, 255, 180}

void printTelaEncerramento(Ranking *ranking);
Fase criarFase(int numFase);
void reiniciarFase(Player *jogador, Fase *fase);

int main() {
    
/* INICIALIZACAO DAS CONFIGURACOES BASICAS --------------------- */
    srand(time(NULL));
    
    InitWindow(1920, 1080, "FNAU");
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    SetTargetFPS(60);
    
    Player jogador = inicializarJogador();
    Fase fase = criarFase(1);
    fase.qtdInimigos = 1;
    //fase.mapa = LoadTexture("Sprites e Texturas/mapa.png");
    
    //INICIALIZACAO DOS SONS E MUSICAS
    InitAudioDevice();
    
    Music musicasFase[5], musica;
    carregarMusicas(musicasFase, &musica);
    
    Sound youDied, musicaPerseguicao, musicaEncerramento;
    carregarSons(&youDied, &musicaPerseguicao, &musicaEncerramento);
    
    PlayMusicStream(musica);
    //flags de controle dos sons //colocar dentro da struct Fase
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
/* ------------------------------------------------------------- */

    while(!WindowShouldClose()) {//INICIO DO LOOP EM QUE RODA O JOGO
        
        UpdateMusicStream(musica);
        
        int tamBarra = 240 - 80*deathCount;//calcula o tamanho da barra de sanidade
        
        int gravouScore = 0;//garante que nao vai gravar o score varias vezes no loop
        
    /* TELA DE ENCERRAMENTO ------------------------------------------- */
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
                perdeu = 0;
            }
            printTelaEncerramento(ranking);
        }
    /* --------------------------------------------------------------- */

    /* TELA QUANDO O JOGADOR É PEGO POR ALGUM INIMIGO ----------------------------------------------------------------------- */
        if (perdeu) {  
            StopMusicStream(musicasFase[0]);
            SetSoundVolume(youDied, 2.5);
            PlaySound(youDied);
            
            if (jogador.score >= 200) jogador.score -= 200;//perde 200 pontos toda vez que morre
            else (jogador.score) = 0;
            
            int ind = -1;
            for (int i = 0; i < fase.qtdInimigos && ind != i; i++) {//checa se existe algum inimigo que colidiu com o jogador
                if (fase.inimigos[i].colisao == 1) ind = i;
            }
            
            while (perdeu) {
               
                printTelaPerdeu(ind, fonteDS);
               
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
               
                if (IsKeyPressed(KEY_SPACE)) {
                    StopSound(youDied);
                    perdeu = 0;
                    fase.inimigos[ind].colisao = 0;
                    reiniciarFase(&jogador, &fase);
                    if (fase.faseAtual <= 3) fase.qtdInimigos = fase.faseAtual;
                    PlayMusicStream(musicasFase[0]);
                }
            }
        }
    /* ---------------------------------------------------------------------------------------------------------------------- */
        
    /* MENU ------------------------------------------------------------------------------- */
        if(menu.continua == 0 && comando.continua == 0){ //Chama a primeira parte do menu       
           menu = desenhaMenu(menu);                                                            
        }
        if(menu.continua == 1 && comando.continua == 0){ //Chama a parte dos comandos
           comando = iniciaJogo(comando);
        }
    /* ------------------------------------------------------------------------------------ */
        
        if(menu.continua == 1 && comando.continua == 1){ //Inicia Jogo
            camera.target = jogador.centro;//atualiza a camera
            
            if (!musicaFaseTocando) {
                StopMusicStream(musica);
                PlayMusicStream(musicasFase[0]);
                musicaFaseTocando = 1;
                musicaTocando = 0; 
            }
            
            UpdateMusicStream(musicasFase[0]);
            
        /* PASSAR DE FASE -------------------------------------------------- */
            while (entrouNaPorta) {
                
                if (musicaTocando) {
                    StopSound(musicaPerseguicao);
                    musicaTocando = 0;
                }
                
                printScore(jogador.score);
                
                if (IsKeyPressed(KEY_SPACE)) {
                    reiniciarFase(&jogador, &fase);
                    PlayMusicStream(musicasFase[0]);
                    entrouNaPorta = 0;    
                    fase.faseAtual++;
                    if (fase.faseAtual <= 3) fase.qtdInimigos = fase.faseAtual;
                }
            } 
        /* ----------------------------------------------------------------- */
            
        /* TELA DE GAME OVER --------------------------------------- */
            if (tamBarra <= 0) gameOver = 1; 
            while (gameOver) { 
                printGameOver();
                if (IsKeyDown(KEY_ESCAPE)) {
                    gameOver = 0;
                    deathCount = 0;
                }
            }  
        /* ---------------------------------------------------------- */

        /* ATUALIZA COORDENADAS E HITBOXES DO JOGADOR E DOS INIMIGOS ------------ */
            atualizaJogador(&jogador);
            for (int i = 0; i < fase.qtdInimigos; i++) {
                atualizaInimigo(&fase.inimigos[i]);
            }
        /* ---------------------------------------------------------------------- */
            
            BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(camera);//ativa a camera
            
            //DEFINE A COR BASE DE CADA FASE
            Color cor = definirCorFase(fase.faseAtual);
            
            //DESENHA O CAMPO DE VISAO DO PERSONAGEM
            DrawCircle(jogador.centro.x, jogador.centro.y, jogador.campoVisao, cor);
            
            //MARCADORES DOS LIMITES DA FASE
            DrawLine(0, 0, width, 0, BLACK);
            DrawLine(width, 0, width, height, BLACK);
            DrawLine(width, height, 0, height, BLACK);
            DrawLine(0, height, 0, 0, BLACK);
            
        /* DESENHA AS TEXTURAS ------------------------------------------------------------------------------------------------------------- */
            
            //PORTA (ANTES DE TER A CHAVE)
            float distCampoVisaoPortaC;
            if (!jogador.temChave) desenharPorta(jogador, fase.porta, &distCampoVisaoPortaC);//deteccao do campo de visao embutida na funcao
  
            //INIMIGOS
            if (!perdeu) {
                for (int i = 0; i < fase.qtdInimigos; i++) {
                    desenharInimigo(&fase.inimigos[i], jogador, &acumulador, &musicaTocando, &musicaDelay, &frameAtual, &tempoFrame, musicasFase, musicaPerseguicao);
                }
            }
           
            //BATERIAS
            for (int i = 0; i < fase.qtdBaterias; i++) {
                if (fase.baterias[i].colisao == 0) {
                    desenharBateria(fase.baterias[i], jogador);
                }
            }

            //CHAVE
            float distCampoVisaoChaveC;
            if (!jogador.temChave) desenharChave(fase.chave, jogador, &distCampoVisaoChaveC);
 
            //VIDA //substituir coracao pelo gato da area2
            float distCampoVisaoVidaC;
            if (fase.vida.colisao == 0) desenharVida(fase.vida, jogador, &distCampoVisaoVidaC);

            //JOGADOR
            if (!perdeu) desenharJogador(jogador);
            
            //PORTA (DEPOIS QUE TEM A CHAVE)
            if (jogador.temChave) desenharPorta(jogador, fase.porta, &distCampoVisaoPortaC);
            
        /* --------------------------------------------------------------------------------------------------------------------------------- */

        /* MOVIMENTACAO DO JOGADOR E DOS INIMIGOS --------------------- */
            moverJogador(&jogador);
            perseguirJogador(fase.inimigos, jogador, fase.qtdInimigos);
        /* ------------------------------------------------------------ */
            
        /* COLISOES ----------------------------------------------------------------------------------------------------------------------------------- */
          
            //INIMIGO
            for (int i = 0; i < fase.qtdInimigos; i++) {
                if (CheckCollisionRecs(jogador.hitbox, fase.inimigos[i].hitbox)) removerJogador(&fase.inimigos[i], &jogador, &perdeu, &deathCount, cor);
            }
           
            //CHAVE
            if (CheckCollisionRecs(jogador.hitbox, fase.chave.hitbox)) pegarChave(&fase.chave, &jogador, cor);
            
            //PORTA
            if (CheckCollisionRecs(jogador.hitbox, fase.porta.hitbox)) entrarNaPorta(&fase.porta, &jogador, &entrouNaPorta, fase.faseAtual, cor);

            //BATERIAS
            for (int i = 0; i < fase.qtdBaterias; i++) {
                if (CheckCollisionRecs(jogador.hitbox, fase.baterias[i].hitbox)) pegarBateria(&fase.baterias[i], &jogador, cor); 
            }
            
            //VIDA
            if (CheckCollisionRecs(jogador.hitbox, fase.vida.hitbox)) pegarVida(&fase.chave, &jogador, &deathCount, cor); 
        /* -------------------------------------------------------------------------------------------------------------------------------------------- */

        /* GERA A HUD ---------------- */
            gerarHUD(camera, fase, &deathCount, &chave, &bateria, jogador);
        /* --------------------------- */
        
            EndMode2D();
            EndDrawing();  
        }
    }

    /* LIBERA TODA A MEMORIA UTILIZADA --------------------- */
    UnloadMusicStream(musica);
    for (int i = 0; i < 5; i++) {
        UnloadMusicStream(musicasFase[i]);
    }
    UnloadSound(musicaEncerramento);
    UnloadSound(musicaPerseguicao);
    UnloadSound(youDied);
    
    UnloadTexture(jogador.textura);
    UnloadTexture(fase.chave.textura);
    UnloadTexture(fase.porta.textura);
    UnloadTexture(chave.textura);
    UnloadTexture(bateria.textura);
    UnloadTexture(fase.vida.textura);
    //UnloadTexture(fase.mapa);
    for (int i = 0; i < fase.qtdInimigos; i++) {
        for (int j = 0; j < 4; j++)
            UnloadTexture(fase.inimigos[i].textura[j]); 
    }
    for (int i = 0; i < fase.qtdBaterias; i++) {
       UnloadTexture(fase.baterias[i].textura); 
    }
    UnloadFont(fonteDS);
    
    free(fase.inimigos);
    free(fase.baterias);
    CloseAudioDevice();
    CloseWindow();
    /* ----------------------------------------------------- */
    return 0; 
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
