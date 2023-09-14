#include <raylib.h>
#include <stdio.h>

typedef struct{
    Texture FNAU;
    Texture BG;
    int h;
    int w;
    int continua;
    char nome[12];
    Vector2 mouse;
} Menu;

typedef struct{
    Texture w, a, s, d;
    int continua;
    
} Comando;

typedef struct{
    char nome[12];
    int pontuacao;
    int qtdPessoas;
} Ranking;

void iniciaMenu(Menu *menu);
void iniciaComando(Comando *comando);
Comando iniciaJogo(Comando comando);
Menu desenhaMenu(Menu menu);
Ranking *organizaRanking(FILE *arq);
