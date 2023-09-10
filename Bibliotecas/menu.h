#include <raylib.h>

typedef struct{
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

void iniciaMenu(Menu *menu);
void iniciaComando(Comando *comando);
Comando iniciaJogo(Comando comando);
Menu desenhaMenu(Menu menu);
