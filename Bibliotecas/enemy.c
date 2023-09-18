#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "enemy.h"
//#include "player.h"

Enemy *inicializarInimigos(int numFase, Enemy *inimigos) {
    if (numFase == 1) inimigos = NULL;
    Enemy *ptrAux = (Enemy *) realloc(inimigos, sizeof(Enemy) * numFase);
    if (ptrAux == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    inimigos = ptrAux;

    int limite = (numFase > 3) ? 3:numFase;
    for (int j = 0; j < limite; j++) {
        for (int i = 0; i < 4 && j == 0; i++) {//MARCIANO
            char file[20];
            sprintf(file, "Sprites e Texturas/mars/marsS%d.png", i+1);
            inimigos[j].textura[i] = LoadTexture(file);
        }
        for (int i = 0; i < 4 && j == 1; i++) {//SALTYPAUL
            char file[20];
            sprintf(file, "Sprites e Texturas/saltyPaul/saltyPaulS%d.png", i+1);
            inimigos[j].textura[i] = LoadTexture(file);
        }
        for (int i = 0; i < 4 && j == 2; i++) {//NIVAN
            char file[20];
            sprintf(file, "Sprites e Texturas/nivan/nivanS%d.png", i+1);
            inimigos[j].textura[i] = LoadTexture(file);
        }
    }
    
    for (int i = 0; i < numFase; i++) {//inicializar os atributos de cada inimigo
        inimigos[i].coordenadas = (Vector2) {(float) GetRandomValue(175, 1688), (float) GetRandomValue(281, 897)};
        inimigos[i].centro = (Vector2) {(2*inimigos[i].coordenadas.x + 8*inimigos[i].textura[0].width)/2, (2*inimigos[i].coordenadas.y + 8*inimigos[i].textura[0].height)/2};
        inimigos[i].detectouJogador = 0;
        inimigos[i].colisao = 0;
    }
    return inimigos;
}

void moveInimigoCirculos(Enemy *inimigo, int qtdInimigos) {//cria um padrao de movimentacao para o inimigo
    
    srand(time(NULL));
    int x;
    for(int i = 0; i < qtdInimigos; i++){
        int pode_direita = 1, pode_cima = 1, pode_baixo = 1, pode_esquerda = 1;
        x = (rand() % 4) + 1; //gera numero de 1 a 8 pra decidir onde o cara vai (dobrei o numero de opcoes pra ver se ele n fica rodando em um quadrado so)
        
        if(inimigo[i].coordenadas.x >= 1688){
            pode_direita = 0;
        }
        if(inimigo[i].coordenadas.x <= 174){
            pode_esquerda = 0;
        }
        if(inimigo[i].coordenadas.y >= 897){
            pode_baixo = 0;
        }
        if(inimigo[i].coordenadas.y <= 281){
            pode_cima = 0;
        }
        
        if((x == 1 ) && pode_direita == 1 ){ //direita
            inimigo[i].coordenadas.x += 1;
        }
        if((x == 2 ) && pode_esquerda == 1 ){
            inimigo[i].coordenadas.x -= 1;
        }
        if((x == 3 ) && pode_baixo == 1){
            inimigo[i].coordenadas.y += 1;
        }
        if((x == 4 ) && pode_cima == 1){
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
                    inimigos[i].coordenadas.x += 1.25 * sqrt(2);
                    inimigos[i].coordenadas.y += 1.25 * sqrt(2);
                }
                else if (deltaY < 0) {
                    inimigos[i].coordenadas.x += 1.25 * sqrt(2);
                    inimigos[i].coordenadas.y -= 1.25 * sqrt(2);
                }
                else inimigos[i].coordenadas.x += 2.5;
            }
            else if (deltaX < 0) {
                if (deltaY > 0) {
                    inimigos[i].coordenadas.x -= 1.25 * sqrt(2);
                    inimigos[i].coordenadas.y += 1.25 * sqrt(2);
                }
                else if (deltaY < 0) {
                    inimigos[i].coordenadas.x -= 1.25 * sqrt(2);
                    inimigos[i].coordenadas.y -= 1.25 * sqrt(2);
                }
                else inimigos[i].coordenadas.x -= 2.5;
            }
            else if (deltaY > 0) {
                if (deltaX > 0) {
                    inimigos[i].coordenadas.y += 1.25 * sqrt(2);
                    inimigos[i].coordenadas.x += 1.25 * sqrt(2);
                }
                else if (deltaX < 0) {
                    inimigos[i].coordenadas.y += 1.25 * sqrt(2);
                    inimigos[i].coordenadas.x -= 1.25 * sqrt(2);
                }
                else inimigos[i].coordenadas.y += 2.5;
            }
            else if (deltaY < 0) {
                if (deltaX > 0) {
                    inimigos[i].coordenadas.y -= 1.25 * sqrt(2);
                    inimigos[i].coordenadas.x += 1.25 * sqrt(2);
                }
                else if (deltaX < 0) {
                    inimigos[i].coordenadas.y -= 1.25 * sqrt(2);
                    inimigos[i].coordenadas.x -= 1.25 * sqrt(2);
                }
                else inimigos[i].coordenadas.y -= 2.5;
            }
        }
        else{
            moveInimigoCirculos(inimigos, qtdInimigos);
        }
    }
}

void atualizaInimigo(Enemy *inimigo) {
    inimigo->centro = (Vector2) {(2*inimigo->coordenadas.x + 8*inimigo->textura[0].width)/2, (2*inimigo->coordenadas.y + 8*inimigo->textura[0].height)/2};
    inimigo->hitbox = (Rectangle) {
        inimigo->coordenadas.x + 5,
        inimigo->coordenadas.y,
        108,
        165,
    };
}
