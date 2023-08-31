#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <raylib.h>

typedef struct {
    Texture textura;
    Vector2 coordenadas;// {x, y}
    Rectangle hitbox;
    int temChave;//flag
    int qtdBaterias;
} Player;//relacionar tudo oq foi criado com o player

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    int colisao;
} Collectable;//Pilhas, chave, ...

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
} Enemy;

void moverJogador(Player *jogador);
//fazer um que detecta colisao entre jogador e inimigo
int main() {
    
    srand(time(NULL));
    InitWindow(1280, 720, "Jogo de IP");
    InitAudioDevice();
    //if (!IsWindowFullscreen()) ToggleFullscreen();
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    
    //INICIALIZACAO DO JOGADOR
    Player jogador;
    jogador.qtdBaterias = 0;
    jogador.temChave = 0;
    jogador.textura = LoadTexture("sprite1.png");
    jogador.coordenadas = (Vector2){width/2, height/2};
    //
    //INICIALIZACAO DAS BATERIAS
    Collectable *baterias;
    int qtdBaterias = (rand() % 3) + 1;//qtd de baterias que vao spawnar no mapa
    Collectable *ptrAux = (Collectable *) malloc(qtdBaterias * sizeof(Collectable));
    if (ptrAux == NULL) {//checa se a alocacao ocorreu
        UnloadTexture(jogador.textura);
        for (int i = 0; i < qtdBaterias; i++) {
           UnloadTexture(baterias[i].textura); 
        }
        free(baterias);
        CloseAudioDevice();
        CloseWindow();
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    baterias = ptrAux;
    for (int i = 0; i < qtdBaterias; i++) {
        baterias[i].textura = LoadTexture("sprite2.png");
        baterias[i].coordenadas = (Vector2){(float) (rand() % width), (float) (rand() % height)};
        baterias[i].hitbox = (Rectangle) {
            baterias[i].coordenadas.x,
            baterias[i].coordenadas.y,
            30, 75,
            //baterias[i].textura.width,
            //baterias[i].textura.height,
        };
        baterias[i].colisao = 0;//nao sofreu colisao
    }
    //
    //INICIALIZACAO DOS SONS
    Sound musica = LoadSound("Sons e Musica/Spooked - Mini Vandals.mp3");
    PlaySound(musica);
    //
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
  
        BeginDrawing();
        
        ClearBackground(WHITE);
       
        //PRECISA CONVERTER ESSES VALORES EM INT PRA PODER ATUALIZAR
        //GUARDAR CADA STRING EM UMA VARIAVEL DIFERENTE E SÓ SOMAR 1 NO CHAR DO DIGITO
        DrawText("SCORE : 0", 30, 30, 40, BLACK);
        DrawText("CHAVES : 0", 30, 80, 40, BLACK);
        DrawText("BATERIAS : 0", 30, 130, 40, BLACK);
        for (int i = 0; i < qtdBaterias && baterias[i].colisao == 0; i++) {
            DrawTextureEx(baterias[i].textura, baterias[i].coordenadas, 0, 0.1f, WHITE);
        }
        
        DrawText("JOGO DE IP", width / 2 - MeasureText("JOGO DE IP", 40) / 2, height / 2 - 40, 40, BLACK);
        DrawTextureEx(jogador.textura, jogador.coordenadas, 0, 0.33f, WHITE);
        //as texturas que sao desenhadas depois ficam por cima das de antes
        
        //atualiza a hitbox do jogador a cada iteracao
        jogador.hitbox = (Rectangle) {
            jogador.coordenadas.x,
            jogador.coordenadas.y,
            //talvez seja preciso reduzir essas medidas de width e height na hitbox
            80, 120,
            //jogador.textura.width,
            //jogador.textura.height,
        };
        //DrawRectangle(jogador.coordenadas.x, jogador.coordenadas.y, 120, 200, GREEN);
        moverJogador(&jogador);
        
        //CHECA SE HOUVE COLISAO COM UMA DAS PILHAS
        int ind = -1;
        int achou = 0;
        int i;
        for (i = 0; i < qtdBaterias && achou == 0; i++) {
            if (CheckCollisionRecs(jogador.hitbox, baterias[i].hitbox)) {
                ind = i;
                achou = 1;
            }
            
            if (ind == i) {
                baterias[ind].colisao = 1;
                printf("Colisao\n");
                UnloadTexture(baterias[ind].textura);
                jogador.qtdBaterias++; 
            }
            else {
                ind = -1;
                achou = 0;
            }
        }
        
        
        // for (int i = 0; i < qtdBaterias && CheckCollisionRecs(jogador.hitbox, baterias[i].hitbox); i++) {
            // //DrawRectangle(baterias[i].coordenadas.x, baterias[i].coordenadas.y, 50, 100, BLUE);
                // //DrawRectangle(baterias[i].coordenadas.x, baterias[i].coordenadas.y, 50, 100, WHITE);
            // if (baterias[i].colisao == 1) {
                // UnloadTexture(baterias[i].textura);
                // jogador.qtdBaterias++; 
            // }
            
        // }
        //DrawRectangle(jogador.coordenadas.x, jogador.coordenadas.y, 120, 200, GREEN);
        EndDrawing();
       // DrawRectangle(jogador.coordenadas.x, jogador.coordenadas.y, 120, 200, GREEN);
            
    }
    
    UnloadTexture(jogador.textura);
    for (int i = 0; i < qtdBaterias; i++) {
       UnloadTexture(baterias[i].textura); 
    }
    free(baterias);
    CloseAudioDevice();
    CloseWindow();
    return 0; 
}

void moverJogador(Player *jogador) {
    //Movimentacao do personagem
    //Velocidade diagonal equilibrada
    if (IsKeyDown(KEY_W)) {
        if (IsKeyDown(KEY_D)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x += GetFrameTime() * (125.f * sqrt(2.f));
        }
        else if (IsKeyDown(KEY_A)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x -= GetFrameTime() * (125.f * sqrt(2.f));
        }
        else {
            (*jogador).coordenadas.y -= GetFrameTime() * 250.f;
        }  
    }
    else if (IsKeyDown(KEY_S)) {
        if (IsKeyDown(KEY_D)) {
            (*jogador).coordenadas.y += GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x += GetFrameTime() * (125.f * sqrt(2.f));
        }
        else if (IsKeyDown(KEY_A)) {
            (*jogador).coordenadas.y += GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x -= GetFrameTime() * (125.f * sqrt(2.f));
        }
        else {
            (*jogador).coordenadas.y += GetFrameTime() * 250.f;
        }  
    }
    else if (IsKeyDown(KEY_A)) {
        if (IsKeyDown(KEY_W)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x -= GetFrameTime() * (125.f * sqrt(2.f));
        }
        else if (IsKeyDown(KEY_S)) {
            (*jogador).coordenadas.y += GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x -= GetFrameTime() * (125.f * sqrt(2.f));
        }
        else {
            (*jogador).coordenadas.x -= GetFrameTime() * 250.f;
        } 
    }
    else if (IsKeyDown(KEY_D)) {
        if (IsKeyDown(KEY_W)) {
            (*jogador).coordenadas.y -= GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x += GetFrameTime() * (125.f * sqrt(2.f));
        }
        else if (IsKeyDown(KEY_S)) {
            (*jogador).coordenadas.y += GetFrameTime() * (125.f * sqrt(2.f));
            (*jogador).coordenadas.x += GetFrameTime() * (125.f * sqrt(2.f));
        }
        else {
            (*jogador).coordenadas.x += GetFrameTime() * 250.f;
        } 
    }
}

