#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "enemy.h"
//#include "player.h"


Enemy *inicializarInimigos(int numFase) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Enemy *inimigos = NULL;
    Enemy *ptrAux = (Enemy *) realloc(inimigos, sizeof(Enemy) * numFase);
    if (ptrAux == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    inimigos = ptrAux;
    //CARREGAR OS SPRITES DO MARCIANO
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
        inimigos[i].coordenadas = (Vector2) {(float) (rand() % (width - (inimigos[i].textura[0].width * 8))), (float) (rand() % (height - (inimigos[i].textura[0].height * 8)))};
        inimigos[i].centro = (Vector2) {(2*inimigos[i].coordenadas.x + 8*inimigos[i].textura[0].width)/2, (2*inimigos[i].coordenadas.y + 8*inimigos[i].textura[0].height)/2};
        inimigos[i].detectouJogador = 0;
        inimigos[i].colisao = 0;
    }
    return inimigos;
}

void moveInimigoCirculos(Enemy *inimigo, int qtdInimigos) {//cria um padrao de movimentacao para o inimigo
    
    srand(time(NULL));
    int x;
    //for(int i = 0; i < qtdInimigos; i++){
        int pode_direita = 1, pode_cima = 1, pode_baixo = 1, pode_esquerda = 1;
        x = (rand() % 8) + 1; //gera numero de 1 a 8 pra decidir onde o cara vai (dobrei o numero de opcoes pra ver se ele n fica rodando em um quadrado so)
        
        
        
        if(inimigo->coordenadas.x >= 1700){
            pode_direita = 0;
        }
        if(inimigo->coordenadas.x <= 30){
            pode_esquerda = 0;
        }
        if(inimigo->coordenadas.y >= 950){
            pode_baixo = 0;
        }
        if(inimigo->coordenadas.y <= 30){
            pode_cima = 0;
        }
        
        if((x == 1 || x == 5) && pode_direita == 1 ){ //direita
            inimigo->coordenadas.x += sqrt(2);
        }
        if((x == 2 || x == 6) && pode_esquerda == 1 ){
            inimigo->coordenadas.x -= sqrt(2);
        }
        if((x == 3 || x == 7) && pode_baixo == 1){
            inimigo->coordenadas.y += sqrt(2);
        }
        if((x == 4 || x == 8) && pode_cima == 1){
            inimigo->coordenadas.y -= sqrt(2);
        }
    //}
    
} 

void perseguirJogador(Enemy *inimigos, Player jogador, int qtdInimigos) {//inimigo tbm anda na diagonal


    for (int i = 0 ; i < qtdInimigos; i++) {
        float deltaX = jogador.centro.x - inimigos[i].centro.x;//variacao em x
        float deltaY = jogador.centro.y - inimigos[i].centro.y;//variacao em y
        float distInimigoJogador = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
        
        if (distInimigoJogador <= jogador.campoVisao) {//so ativa quando o inimigo ta dentro do campo de visao
            inimigos[i].detectouJogador = 1;
        }
       
        if (inimigos[i].detectouJogador) {
            int moveX = 1, moveY = 1;
            //margem para se movimentar (evita que o sprite fique tremendo quando fabs(deltaX ou deltaY) tende a 0)
            if (fabs(deltaX) <= 50) moveX = 0;
            if (fabs(deltaY) <= 50) moveY = 0;
        
            if (deltaX > 0 && moveX) {
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
            else if (deltaX < 0 && moveX) {
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
            else if (deltaY > 0 && moveY) {
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
            else if (deltaY < 0 && moveY) {
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
            moveInimigoCirculos(&inimigos[i], qtdInimigos);
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
