/*
J = jogador
S = Saída
K = Chave (Key)
P = Pilha
E = Inmigo(Enemy)

A movimentacao do jogo é baseada na leitura
de caracteres pelo scanf, em que w vai pra cima,
a vai pra esquerda, s vai pra baixo e d vai pra direita

o objetivo é pegar a chave (K) e abrir a abrir a porta da saída (S)
Se enconstar no inimigo (E) você perde.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define PI 3.14

typedef struct {
    int qtdPilhas;
    float campoDeVisao;//area de um circulo
    int temChave;//flag que indica se tem a chave (1) ou nao (0)
} Player;

typedef struct {  
} Enemy;

typedef struct {
    char simbolo;//representacao grafica daquele espaco;
    int temPilha;//1 == sim, 0 == nao
    int temChave;//1 == sim, 0 == nao;
} MatrizDaFase;

typedef struct {
    Enemy *inimigos;
    Player jogador;
    MatrizDaFase **matriz;
    int largura;
    int comprimento;
} Fase;

typedef struct {
    int xPilha;
    int yPilha;
} Pilha;

typedef struct {
    int x;
    int y;
} Coordenadas;

void atualizarVetorInimigos(Enemy **inimigos, int *qtdInimigos);
Fase criarFase(Enemy *inimigos, Player jogador);
int calcularDimensao();
void posicionarChave(Fase fase);
void posicionarPilhas(Fase fase);
void posicionarJogador(Fase fase);
void poisicionarInmigo(Fase fase);
void posicionarSaida(Fase fase);
void ampliarCampoVisao(float *campoDeVisao);
void moverPersonagem(Fase *fase, char direcao);//direcao == 'w' 'a' 's' 'd'

int main() {

    srand(time(NULL));
    Player jogador;
    jogador.qtdPilhas = 0;
    jogador.campoDeVisao = PI;
    jogador.temChave = 0;

    Enemy *inimigos = NULL;
    int qtdInimigos = 0;
    Fase fase = criarFase(inimigos, jogador);
    atualizarVetorInimigos(&fase.inimigos, &qtdInimigos);//ir adicionando um inimigo a cada fase

    for (int i = 0; i < fase.largura; i++) {
        for (int j = 0; j < fase.comprimento; j++) {
            printf("%2c", fase.matriz[i][j].simbolo);
        }
        printf("\n");
    }

    char comando = 'q';
    while (comando != '.') {
        scanf(" %c", &comando);
        moverPersonagem(&fase, comando);
        for (int i = 0; i < fase.largura; i++) {
            for (int j = 0; j < fase.comprimento; j++) {
                printf("%2c", fase.matriz[i][j].simbolo);
            }
            printf("\n");
        }
    }
    
    free(fase.inimigos);
    free(fase.matriz);
    for (int i = 0; i < fase.largura; i++) {
        free(fase.matriz[i]);
    }
    //dar free nos ponteiros da fase tbm
    return 0;
}

Fase criarFase(Enemy *inimigos, Player jogador) {

    Fase fase;
    fase.inimigos = inimigos;
    fase.jogador = jogador;
    
    //a fase vai ser representada por uma matriz dinamica de até 20x20 e no minimo 10x10
    //as dimensoes dela serao geradas aleatoriamente
    fase.matriz = NULL;
    int largura = calcularDimensao();
    MatrizDaFase **ptrAux1 = (MatrizDaFase **) malloc(largura * sizeof(MatrizDaFase *));
    if (ptrAux1 == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    fase.matriz = ptrAux1;
    fase.largura = largura;
    int comprimento = calcularDimensao();
    for (int i = 0; i < largura; i++) {
        MatrizDaFase *ptrAux2 = (MatrizDaFase *) malloc(comprimento * sizeof(MatrizDaFase));
        if (ptrAux2 == NULL) {
            for (int j = 0; j < i; j++) {
                free(fase.matriz[j]);
            }
            printf("Problema de alocacao de memoria.\n");
            exit(1);
        }
        fase.matriz[i] = ptrAux2;
        fase.comprimento = comprimento;
    }

    for (int i = 0; i < fase.largura; i++) {
        for (int j = 0; j < fase.comprimento; j++) {
            fase.matriz[i][j].simbolo = '*';
        }
    }
    //depois de ja ter preenchido a matriz, tem que preencher alguns espacos com a chave e com as pilhas
    posicionarChave(fase);
    posicionarPilhas(fase);
    posicionarJogador(fase);
    poisicionarInmigo(fase);
    posicionarSaida(fase);
    return fase;
}

int calcularDimensao() {

    int dimensao = 0;
    while (dimensao < 10) {
        dimensao = (rand() % 20) + 1;
    }
    return dimensao;
}

void atualizarVetorInimigos(Enemy **inimigos, int *qtdInimigos) {

    Enemy *ptrAux = (Enemy *) realloc((*inimigos), ((*qtdInimigos) + 1) * sizeof(Enemy));
    if (ptrAux == NULL) {
        printf("Problema de alocacao de memoria.\n");
        exit(1);
    }
    (*inimigos) = ptrAux;
    (*qtdInimigos)++;
}

void posicionarChave(Fase fase) {

    int xChave = rand() % fase.largura;
    int yChave = rand() % fase.comprimento;

    fase.matriz[xChave][yChave].simbolo = 'K';
    fase.matriz[xChave][yChave].temChave = 1;
}

void posicionarPilhas(Fase fase) {
    
    int qtdPilhas = 0;//no maximo 5 pilhas
    while (qtdPilhas < 3) {//minimo de 3 pilhas
        qtdPilhas = (rand() % 5) + 1;
    }
    Pilha pilhas[qtdPilhas];
    for (int i = 0; i < qtdPilhas; i++) {//posicionar cada pilha
        pilhas[i].xPilha = -1;
        pilhas[i].yPilha = -1;

        if (pilhas[i].xPilha < 0 || pilhas[i].yPilha < 0) {
            pilhas[i].xPilha = rand() % fase.largura;
            pilhas[i].yPilha = rand() % fase.comprimento;
            while (fase.matriz[pilhas[i].xPilha][pilhas[i].yPilha].simbolo != '*') {
                pilhas[i].xPilha = rand() % fase.largura;
                pilhas[i].yPilha = rand() % fase.comprimento;
            }
        }
 

        fase.matriz[pilhas[i].xPilha][pilhas[i].yPilha].simbolo = 'P';
        fase.matriz[pilhas[i].xPilha][pilhas[i].yPilha].temPilha = 1;
    }
}

void posicionarJogador(Fase fase) {

    int xJog = -1;
    int yJog = -1;
    if (xJog < 0 || yJog < 0) {
        xJog = rand() % fase.largura;
        yJog = rand() % fase.comprimento;
        while (fase.matriz[xJog][yJog].simbolo != '*') {
            xJog = rand() % fase.largura;
            yJog = rand() % fase.comprimento;
        }
    }

    fase.matriz[xJog][yJog].simbolo = 'J';
}

void poisicionarInmigo(Fase fase) {

    int xEnemy = -1;
    int yEnemy = -1;
    if (xEnemy < 0 || yEnemy < 0) {
        xEnemy = rand() % fase.largura;
        yEnemy = rand() % fase.comprimento;
        while (fase.matriz[xEnemy][yEnemy].simbolo != '*') {
            xEnemy = rand() % fase.largura;
            yEnemy = rand() % fase.comprimento;
        }
    }

    fase.matriz[xEnemy][yEnemy].simbolo = 'E';
}

void posicionarSaida(Fase fase) {

    int xSaida = -1;
    int ySaida = -1;
    if (xSaida < 0 || ySaida < 0) {
        xSaida = rand() % fase.largura;
        ySaida = rand() % fase.comprimento;
        while (fase.matriz[xSaida][ySaida].simbolo != '*') {
            xSaida = rand() % fase.largura;
            ySaida = rand() % fase.comprimento;
        }
    }

    fase.matriz[xSaida][ySaida].simbolo = 'S';
}

void ampliarCampoVisao(float *campoDeVisao) {
    (*campoDeVisao) += PI;
}

Coordenadas encontrarElemento(Fase fase, char elemento) {
    Coordenadas cord;
    cord.x = -1;
    cord.y = -1;
    for (int i = 0; i < fase.largura; i++) {
        for (int j = 0; j < fase.comprimento; j++) {
            if (fase.matriz[i][j].simbolo == elemento) {
                cord.x = i;
                cord.y = j;
            }
        }
    }
    return cord;
}

void moverPersonagem(Fase *fase, char direcao) {
    Coordenadas cord = encontrarElemento(*fase, 'J');
    if (cord.x < 0 || cord.y < 0) return;
    if ((*fase).matriz[cord.x-1][cord.y].simbolo == 'E' || (*fase).matriz[cord.x+1][cord.y].simbolo == 'E' || (*fase).matriz[cord.x][cord.y-1].simbolo == 'E' || (*fase).matriz[cord.x][cord.y+1].simbolo == 'E') {
        printf("GAME OVER!!!!\n");
        exit(1);
    }
    
    if (((*fase).matriz[cord.x-1][cord.y].simbolo == 'K' || (*fase).matriz[cord.x+1][cord.y].simbolo == 'K' || (*fase).matriz[cord.x][cord.y-1].simbolo == 'K' || (*fase).matriz[cord.x][cord.y+1].simbolo == 'K')) {
        (*fase).jogador.temChave = 1;
    } 

    if ((((*fase).matriz[cord.x-1][cord.y].simbolo == 'S' || (*fase).matriz[cord.x+1][cord.y].simbolo == 'S' || (*fase).matriz[cord.x][cord.y-1].simbolo == 'S' || (*fase).matriz[cord.x][cord.y+1].simbolo == 'S') && (*fase).jogador.temChave == 1)) {
        printf("YOU WIN!!!!\n");
        exit(1);
    }
    switch (direcao) {
        case 'w':
            if (cord.y > 0) {
                (*fase).matriz[cord.x][cord.y].simbolo = '*';
                (*fase).matriz[cord.x-1][cord.y].simbolo = 'J';
            }
            break;
        case 'a':
            if (cord.x > 0) {
                (*fase).matriz[cord.x][cord.y].simbolo = '*';
                (*fase).matriz[cord.x][cord.y-1].simbolo = 'J';
            }
            break;
        case 's':
            if (cord.y < (*fase).comprimento) {
                (*fase).matriz[cord.x][cord.y].simbolo = '*';
                (*fase).matriz[cord.x+1][cord.y].simbolo = 'J';
            }
            break;
        case 'd':
            if (cord.x < (*fase).largura) {
                (*fase).matriz[cord.x][cord.y].simbolo = '*';
                (*fase).matriz[cord.x][cord.y+1].simbolo = 'J';
            }
            break;
        default:
            break;
    }   
}
