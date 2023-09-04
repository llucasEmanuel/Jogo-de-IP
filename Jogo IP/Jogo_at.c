#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <raylib.h>
#include "menu.h"

//CRIAR BIBLIOTECAS ESPECIFICAS PARA PLAYER, INIMIGOS, COLETAVEIS, ...
typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    int temChave;//flag que indica se tem (1) ou nao (0) a chave
    int qtdBaterias;//qtd de baterias coletadas pelo jogador na fase
    int score;
} Player;

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    int colisao;//flag que indica se houve (1) ou nao (0) colisao com aquele coletavel
} Collectable;//baterias, chave, ...

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
} Enemy;

typedef struct {
    int width;
    int height;
} Window;

void moverJogador(Player *jogador);
void criarFase(Player *jogador, Window janela);
Player inicializarJogador(Window janela);
Collectable inicializarChave(Window janela);
Collectable *inicializarBaterias(Window janela, int *qtdBaterias);
Collectable inicializarPorta(Window janela);
//Criar funcoes de inicializar jogador, baterias e chave e colocar na de inicializar fase
//Depois criar a funcao de inicializar fase, que add inimigos e reseta os objetos e o jogador
int main() {
    
    srand(time(NULL));
    Window janela;
    InitWindow(1920, 1080, "Jogo de IP");
    janela.height = GetScreenHeight();
    janela.width = GetScreenWidth();
    //INICIALIZACAO DO JOGADOR
    Player jogador = inicializarJogador(janela);
    criarFase(&jogador, janela);
    

    return 0; 
}

void criarFase(Player *jogador, Window janela) {
    
    //AUXILIAR MENU
    int continua = 0, continua1 = 0;
    
    InitAudioDevice();
    //if (!IsWindowFullscreen()) ToggleFullscreen();
    
    //INICIALIZACAO DAS BATERIAS
    int qtdBaterias = 0;//qtd baterias que irao aparecer na tela (a qtd eh aleatorio e definida na funcao)
    Collectable *baterias = inicializarBaterias(janela, &qtdBaterias);
    
    //INICIALIZACAO DA CHAVE
    Collectable chave = inicializarChave(janela);
    
    //INICIALIZACAO DA PORTA DE SAIDA
    Collectable porta = inicializarPorta(janela);
    
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

                DrawText(TextFormat("HIGHSCORE : %d", jogador->score), janela.width / 2 - MeasureText("HIGHSCORE : ", 75) / 2, janela.height / 2 - 75, 75, BLACK);

                EndDrawing();
                
                if (IsKeyPressed(KEY_ESCAPE)) {//mudar a tecla para KEY_SPACE depois
                    entrouNaPorta = 0;
                }
            }
            
            BeginDrawing();
            
            ClearBackground(WHITE);
     
            DrawText("FASE 1", janela.width / 2 - MeasureText("FASE 1", 40) / 2, janela.height / 2 - 40, 40, BLACK);
            
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
            
            jogador->hitbox = (Rectangle) {//hitbox dinamica que se move conforme o sprite do jogador
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
            DrawTextureEx(jogador->textura, jogador->coordenadas, 0, 0.33f, WHITE);
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
                    DrawText("PORTA TRANCADA", janela.width/2 - MeasureText("PORTA TRANCADA", 30), 30, 40, RED);
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
                    jogador->score+= 50;
                }
            }

            //GUARDAR CADA STRING EM UMA VARIAVEL DIFERENTE E SÓ SOMAR 1 NO CHAR DO DIGITO
            DrawText(TextFormat("SCORE : %d", jogador->score), 30, 30, 40, BLACK);
            DrawText(chavesStr, 30, 80, 40, BLACK);
            DrawText(bateriasStr, 30, 130, 40, BLACK);

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

Player inicializarJogador(Window janela) {
    Player jogador;
    jogador.qtdBaterias = 0;
    jogador.temChave = 0;//flag
    jogador.textura = LoadTexture("Sprites e Texturas/sprite1.png");
    jogador.coordenadas = (Vector2) {janela.width/2, janela.height/2};
    jogador.score = 0;
    return jogador;
}

Collectable *inicializarBaterias(Window janela, int *qtdBaterias) {
    Collectable *baterias = NULL;
    (*qtdBaterias) = (rand() % 5) + 1;//qtd de baterias que vao aparecer no mapa
    Collectable *ptrAux = (Collectable *) malloc((*qtdBaterias) * sizeof(Collectable));
    if (ptrAux == NULL) {//checa se a alocacao ocorreu
        for (int i = 0; i < *qtdBaterias; i++) {
           UnloadTexture(baterias[i].textura); 
        }
        free(baterias);
        CloseAudioDevice();
        CloseWindow();
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    baterias = ptrAux;
    for (int i = 0; i < *qtdBaterias; i++) {
        baterias[i].textura = LoadTexture("Sprites e Texturas/spriteBateria.png");
        //as coordenadas de cada bateria vao ser aleatorias mas dentro do limite da tela, posteriormente, do mapa
        baterias[i].coordenadas = (Vector2){(float) (rand() % (janela.width - 45)), (float) (rand() % (janela.height - 60))};
        baterias[i].hitbox = (Rectangle) {
            baterias[i].coordenadas.x,
            baterias[i].coordenadas.y,
            45,
            60,
        };
        baterias[i].colisao = 0;//nao sofreu colisao
    }
    return baterias;
}

Collectable inicializarChave(Window janela) {
    Collectable chave;
    chave.textura = LoadTexture("Sprites e Texturas/spriteChave2.png");
    chave.coordenadas = (Vector2) {(float) (rand() % (janela.width - 90)), (float) (rand() % (janela.height - 36))};
    chave.hitbox = (Rectangle) {
        chave.coordenadas.x,
        chave.coordenadas.y,
        90,
        36,
    };
    chave.colisao = 0;
    return chave;
}

Collectable inicializarPorta(Window janela) {
    Collectable porta;
    porta.textura = LoadTexture("Sprites e Texturas/porta.png");
    porta.coordenadas = (Vector2) {(float) (rand() % (janela.width - (porta.textura.width * 2))), (float) (rand() % (janela.height - (porta.textura.height * 2)))};
    porta.hitbox = (Rectangle) {
        porta.coordenadas.x + 31,
        porta.coordenadas.y + 50,
        36,
        55,
    };
    porta.colisao = 0;
    return porta;
}

void moverJogador(Player *jogador) {
    if (IsKeyDown(KEY_W)) {
        if (IsKeyDown(KEY_D)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_A)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            (*jogador).coordenadas.y -= GetFrameTime() * 300;
        }  
    }
    else if (IsKeyDown(KEY_S)) {
        if (IsKeyDown(KEY_D)) {
            (*jogador).coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_A)) {
            (*jogador).coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            (*jogador).coordenadas.y += GetFrameTime() * 300;
        }  
    }
    else if (IsKeyDown(KEY_A)) {
        if (IsKeyDown(KEY_W)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_S)) {
            (*jogador).coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x -= GetFrameTime() * (150 * sqrt(2));
        }
        else {
            (*jogador).coordenadas.x -= GetFrameTime() * 300;
        } 
    }
    else if (IsKeyDown(KEY_D)) {
        if (IsKeyDown(KEY_W)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else if (IsKeyDown(KEY_S)) {
            (*jogador).coordenadas.y += GetFrameTime() * (150 * sqrt(2));
            (*jogador).coordenadas.x += GetFrameTime() * (150 * sqrt(2));
        }
        else {
            (*jogador).coordenadas.x += GetFrameTime() * 300;
        } 
    }
}
