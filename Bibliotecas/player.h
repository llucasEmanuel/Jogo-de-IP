
#include <raylib.h>

typedef struct {
    Texture2D textura;
    Vector2 coordenadas;
    Rectangle hitbox;
    Vector2 centro;
    int temChave;//flag que indica se tem (1) ou nao (0) a chave
    int qtdBaterias;//qtd de baterias coletadas pelo jogador na fase
    int pegouVida;//detecta se o jogador pegou a vida
    int score;
    float timer;
    int frame;
    int maxFrames;
    float frameLargura;
    float campoVisao;//circulo de luz gerado pela lanterna (varia em funcao do jogador.qtdBaterias)
    int texturaCarregada;
} Player;

void moverJogador(Player *jogador, int numFase);
Player inicializarJogador();
void atualizaJogador(Player *jogador);
void colisaoJogadorMapa(Player *jogador);
