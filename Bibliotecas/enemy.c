#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "enemy.h"
//#include "player.h"

Enemy *inicializarInimigos() {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Enemy *ptrAux = (Enemy *) malloc(sizeof(Enemy));
    if (ptrAux == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    Enemy *inimigos = ptrAux;
    inimigos[0].textura = LoadTexture("Sprites e Texturas/saltyPaul.png");
    inimigos[0].coordenadas = (Vector2) {(float) (rand() % (width - (inimigos[0].textura.width * 8))), (float) (rand() % (height - (inimigos[0].textura.height * 8)))};
    inimigos[0].centro = (Vector2) {(2*inimigos[0].coordenadas.x + 8*inimigos[0].textura.width)/2, (2*inimigos[0].coordenadas.y + 8*inimigos[0].textura.height)/2};
    inimigos[0].detectouJogador = 0;
    return inimigos;
}

void perseguirJogador(Enemy *inimigos, Player jogador) {//inimigo tbm anda na diagonal

    float deltaX = jogador.centro.x - inimigos[0].centro.x;//variacao em x
    float deltaY = jogador.centro.y - inimigos[0].centro.y;//variacao em y
    float distInimigoJogador = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    
    if (distInimigoJogador <= jogador.campoVisao) {//so ativa quando o inimigo ta dentro do campo de visao
        inimigos[0].detectouJogador = 1;
    }
    
    if (inimigos[0].detectouJogador) {
        int moveX = 1, moveY = 1;
        //margem para se movimentar (evita que o sprite fique tremendo quando fabs(deltaX ou deltaY) tende a 0)
        if (fabs(deltaX) <= 50) moveX = 0;
        if (fabs(deltaY) <= 50) moveY = 0;
    
        if (deltaX > 0 && moveX) {
            if (deltaY > 0) {
                inimigos[0].coordenadas.x += 1.5 * sqrt(2);
                inimigos[0].coordenadas.y += 1.5 * sqrt(2);
            }
            else if (deltaY < 0) {
                inimigos[0].coordenadas.x += 1.5 * sqrt(2);
                inimigos[0].coordenadas.y -= 1.5 * sqrt(2);
            }
            else inimigos[0].coordenadas.x += 3;
        }
        else if (deltaX < 0 && moveX) {
            if (deltaY > 0) {
                inimigos[0].coordenadas.x -= 1.5 * sqrt(2);
                inimigos[0].coordenadas.y += 1.5 * sqrt(2);
            }
            else if (deltaY < 0) {
                inimigos[0].coordenadas.x -= 1.5 * sqrt(2);
                inimigos[0].coordenadas.y -= 1.5 * sqrt(2);
            }
            else inimigos[0].coordenadas.x -= 3;
        }
        else if (deltaY > 0 && moveY) {
            if (deltaX > 0) {
                inimigos[0].coordenadas.y += 1.5 * sqrt(2);
                inimigos[0].coordenadas.x += 1.5 * sqrt(2);
            }
            else if (deltaX < 0) {
                inimigos[0].coordenadas.y += 1.5 * sqrt(2);
                inimigos[0].coordenadas.x -= 1.5 * sqrt(2);
            }
            else inimigos[0].coordenadas.y += 3;
        }
        else if (deltaY < 0 && moveY) {
            if (deltaX > 0) {
                inimigos[0].coordenadas.y -= 1.5 * sqrt(2);
                inimigos[0].coordenadas.x += 1.5 * sqrt(2);
            }
            else if (deltaX < 0) {
                inimigos[0].coordenadas.y -= 1.5 * sqrt(2);
                inimigos[0].coordenadas.x -= 1.5 * sqrt(2);
            }
            else inimigos[0].coordenadas.y -= 3;
        }
    }
}
// void moveInimigoCirculos(Enemy *inimigo) {//cria um padrao de movimentacao para o inimigo 
// } //opcional
