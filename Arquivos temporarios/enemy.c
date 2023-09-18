#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "enemy.h"
//#include "player.h"

void atualizaSpriteInimigo(Enemy *inimigo, int qtdInimigos){
    for(int i=0; i<qtdInimigos; i++){
        inimigo[i].timer+=GetFrameTime();
        if(inimigo[i].timer>=0.2f){
            inimigo[i].timer=0.0f;
            inimigo[i].frame+=1;
        }
        inimigo[i].frame=(inimigo[i].frame)%(inimigo[i].maxFrames);
    }
}

Enemy *inicializarInimigos(int numFase, Enemy *inimigos) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    if (numFase == 1) inimigos = NULL;
    Enemy *ptrAux = (Enemy *) realloc(inimigos, sizeof(Enemy) * numFase);
    if (ptrAux == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    inimigos = ptrAux;
    //CARREGAR OS SPRITES DO MARCIANO
    int limite = (numFase > 3) ? 3:numFase;
    for (int j = 0; j < limite; j++) {
        if(j==0){
            //UnloadTexture(inimigos[j].textura);
            inimigos[j].textura = LoadTexture("Sprites e Texturas/mars/marsBaixo.png");
        }
        //SALTYPAUL
        else if(j==1){
            //UnloadTexture(inimigos[j].textura);
            inimigos[j].textura = LoadTexture("Sprites e Texturas/saltyPaul/pauloBaixo.png");
        }
        //NIVAN
        else if(j==2){
            //UnloadTexture(inimigos[j].textura);
            inimigos[j].textura = LoadTexture("Sprites e Texturas/nivan/nivanBaixo.png");
        }
    }
    
    for (int i = 0; i < numFase; i++) {//inicializar os atributos de cada inimigo
        inimigos[i].coordenadas = (Vector2) {(float) GetRandomValue(175, 1688), (float) GetRandomValue(281, 897)};        inimigos[i].centro = (Vector2) {(2*inimigos[i].coordenadas.x + 8*inimigos[i].textura.width)/2, (2*inimigos[i].coordenadas.y + 8*inimigos[i].textura.height)/2};
        inimigos[i].centro = (Vector2) {(2*inimigos[i].coordenadas.x + inimigos[i].textura.width)/2 - 512, (2*inimigos[i].coordenadas.y + inimigos[i].textura.height)/2 - 15};
        inimigos[i].detectouJogador = 0;
        inimigos[i].colisao = 0;
        inimigos[i].timer=0.0f;
        inimigos[i].frame=0;
        inimigos[i].frameLargura=(float)(inimigos[i].textura.width/9);
        inimigos[i].maxFrames=(int)(inimigos[i].textura.width/(int)inimigos[i].frameLargura);
        inimigos[i].texturaCarregada=0;
        
    }
    return inimigos;
}

void moveInimigoCirculos(Enemy *inimigo, int qtdInimigos) {//cria um padrao de movimentacao para o inimigo
    
    srand(time(NULL));
    int x;
    
    for(int i = 0; i < qtdInimigos; i++){
        int pode_direita = 1, pode_cima = 1, pode_baixo = 1, pode_esquerda = 1;
        x = (rand() % 4) + 1; //gera numero de 1 a 8 pra decidir onde o cara vai (dobrei o numero de opcoes pra ver se ele n fica rodando em um quadrado so)
        
        if(inimigo[i].coordenadas.x >= 1700){
            pode_direita = 0;
        }
        if(inimigo[i].coordenadas.x <= 30){
            pode_esquerda = 0;
        }
        if(inimigo[i].coordenadas.y >= 950){
            pode_baixo = 0;
        }
        if(inimigo[i].coordenadas.y <= 30){
            pode_cima = 0;
        }
        
        if((x == 1 ) && pode_direita == 1 ){ //direita
            if(i==0){
                if(inimigo[i].texturaCarregada!=1){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/mars/marsDireita.png");
                    inimigo[i].texturaCarregada=1;
                }
            }
            //SALTYPAUL
            else if(i==1){
                if(inimigo[i].texturaCarregada!=1){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/saltyPaul/pauloDireita.png");
                    inimigo[i].texturaCarregada=1;
                }
            }
            //NIVAN
            else if(i==2){
                if(inimigo[i].texturaCarregada!=1){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/nivan/nivanDireita.png");
                    inimigo[i].texturaCarregada=1;
                }
            }
            inimigo[i].coordenadas.x += 1;
        }
        else if((x == 2 ) && pode_esquerda == 1 ){
            if(i==0){
                if(inimigo[i].texturaCarregada!=2){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/mars/marsEsquerda.png");
                    inimigo[i].texturaCarregada=2;
                }
            }
            //SALTYPAUL
            else if(i==1){
                if(inimigo[i].texturaCarregada!=2){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/saltyPaul/pauloEsquerda.png");
                    inimigo[i].texturaCarregada=2;
                }
            }
            //NIVAN
            else if(i==2){
                if(inimigo[i].texturaCarregada!=2){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/nivan/nivanEsquerda.png");
                    inimigo[i].texturaCarregada=2;
                }
            }
            inimigo[i].coordenadas.x -= 1;
        }
        else if((x == 3 ) && pode_baixo == 1){
            if(i==0){
                if(inimigo[i].texturaCarregada!=3){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/mars/marsBaixo.png");
                    inimigo[i].texturaCarregada=3;
                }
            }
            //SALTYPAUL
            else if(i==1){
                if(inimigo[i].texturaCarregada!=3){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/saltyPaul/pauloBaixo.png");
                    inimigo[i].texturaCarregada=3;
                }
            }
            //NIVAN
            else if(i==2){
                if(inimigo[i].texturaCarregada!=3){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/nivan/nivanBaixo.png");
                    inimigo[i].texturaCarregada=3;
                }
            }
            inimigo[i].coordenadas.y += 1;
        }
        else if((x == 4 ) && pode_cima == 1){
            if(i==0){
                if(inimigo[i].texturaCarregada!=4){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/mars/marsFrente.png");
                    inimigo[i].texturaCarregada=4;
                }
            }
            //SALTYPAUL
            else if(i==1){
                if(inimigo[i].texturaCarregada!=4){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/saltyPaul/pauloFrente.png");
                    inimigo[i].texturaCarregada=4;
                }
            }
            //NIVAN
            else if(i==2){
                if(inimigo[i].texturaCarregada!=4){
                    UnloadTexture(inimigo[i].textura);
                    inimigo[i].textura = LoadTexture("Sprites e Texturas/nivan/nivanFrente.png");
                    inimigo[i].texturaCarregada=4;
                }
            }
            inimigo[i].coordenadas.y -= 1;
        }
    }
    
} 

int delayTempo = 0;//CORRIGIR A FLAG DE DELAY
void perseguirJogador(Enemy *inimigos, Player jogador, int qtdInimigos) {//inimigo tbm anda na diagonal


    for (int i = 0 ; i < qtdInimigos; i++) {
        float deltaX = jogador.centro.x - inimigos[i].centro.x;//variacao em x
        float deltaY = jogador.centro.y - inimigos[i].centro.y;//variacao em y
        float distInimigoJogador = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
        //DrawText("A", deltaX, deltaY, 30, RED);
        if (distInimigoJogador <= jogador.campoVisao) {//so ativa quando o inimigo ta dentro do campo de visao
            inimigos[i].detectouJogador = 1;
        }
        else {
            inimigos[i].detectouJogador = 0;      
        }
       
        if (inimigos[i].detectouJogador) {
        
            if (deltaX > 0) {
                if (deltaY > 0) {
                    inimigos[i].coordenadas.x += 1.5 * sqrt(2);
                    inimigos[i].coordenadas.y += 1.5 * sqrt(2);
                }
                else if (deltaY < 0) {
                    inimigos[i].coordenadas.x += 1.5 * sqrt(2);
                    inimigos[i].coordenadas.y -= 1.5 * sqrt(2);
                }
                else inimigos[i].coordenadas.x += 3;
            }
            else if (deltaX < 0) {
                if (deltaY > 0) {
                    inimigos[i].coordenadas.x -= 1.5 * sqrt(2);
                    inimigos[i].coordenadas.y += 1.5 * sqrt(2);
                }
                else if (deltaY < 0) {
                    inimigos[i].coordenadas.x -= 1.5 * sqrt(2);
                    inimigos[i].coordenadas.y -= 1.5 * sqrt(2);
                }
                else inimigos[i].coordenadas.x -= 3;
            }
            else if (deltaY > 0) {
                if (deltaX > 0) {
                    inimigos[i].coordenadas.y += 1.5 * sqrt(2);
                    inimigos[i].coordenadas.x += 1.5 * sqrt(2);
                }
                else if (deltaX < 0) {
                    inimigos[i].coordenadas.y += 1.5 * sqrt(2);
                    inimigos[i].coordenadas.x -= 1.5 * sqrt(2);
                }
                else inimigos[i].coordenadas.y += 3;
            }
            else if (deltaY < 0) {
                if (deltaX > 0) {
                    inimigos[i].coordenadas.y -= 1.5 * sqrt(2);
                    inimigos[i].coordenadas.x += 1.5 * sqrt(2);
                }
                else if (deltaX < 0) {
                    inimigos[i].coordenadas.y -= 1.5 * sqrt(2);
                    inimigos[i].coordenadas.x -= 1.5 * sqrt(2);
                }
                else inimigos[i].coordenadas.y -= 3;
            }
        }
        else{
            moveInimigoCirculos(inimigos, qtdInimigos);
            atualizaSpriteInimigo(inimigos, qtdInimigos);
        }
    }
}

void atualizaInimigo(Enemy *inimigo) {
    inimigo->centro = (Vector2) {(2*inimigo->coordenadas.x + inimigo->textura.width)/2 - 512, (2*inimigo->coordenadas.y + inimigo->textura.height)/2 - 15};
    inimigo->hitbox = (Rectangle) {
        inimigo->coordenadas.x + 40,
        inimigo->coordenadas.y + 17,
        55,
        88,
    };
}   
