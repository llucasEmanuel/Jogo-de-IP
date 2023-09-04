#include <raylib.h>

typedef struct {
    Texture textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    int temChave;//flag que indica se tem (1) ou nao (0) a chave
    int qtdBaterias;//qtd de baterias coletadas pelo jogador na fase
    int score;
    float campoVisao;//circulo de luz gerado pela lanterna (varia em funcao do jogador.qtdBaterias)
} Player;

void moverJogador(Player *jogador);
Player inicializarJogador();