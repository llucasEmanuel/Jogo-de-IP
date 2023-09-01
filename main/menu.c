#include <raylib.h>

void iniciaJogo();

void geraMenu();

int main(void){
    InitWindow(1920, 1080, "jogo ip"); //inicializando a janela com a resolucao e o nome dela
    SetTargetFPS(60); //setando FPS como 60
   
    geraMenu(); //chamando funcao de gerar o menu
 
    return 0;
}

void geraMenu(){
   
    InitAudioDevice(); //inicializando dispositivo de audio para tocar a musica do menu
   
    Music musica = LoadMusicStream("./trilhaMenu.mp3"); //dando load no arquivo mp3
   
    Texture BG, COMANDOS;
    COMANDOS = LoadTexture("./bloco_comando.png");
    BG = LoadTexture("./bg_1.png"); //load nas texturas
    Vector2 mouse; //criando um vetor pro mouse, pra armazenar as coordenadas dele a cada vez que percorre o while
   
    ToggleFullscreen(); //colocando em tela cheia
    while(!WindowShouldClose()){

        UpdateMusicStream(musica); //dar update de onde a musica parou
        PlayMusicStream(musica); //dar play na musica carregada
       
        SetMasterVolume(100.0); //tentei aumentar volume mas deu em muita coisa nao
       
        mouse = GetMousePosition(); //essa funcao devolve as coordenadas do mouse (X, Y)
       
        BeginDrawing(); //comeca a desenhar
       
        ClearBackground(BLACK); //limpa o plano de fundo
        DrawTexture(BG, 0, 0, WHITE); //desenha o plano de fundo do menu (WHITE por que tira o PNG)
        DrawText("NOME DO JOGO", 380, 200, 150, WHITE);
        DrawText("Iniciar", 750, 825, 120, WHITE); //desenhando textos
        if(mouse.x >= 750 && mouse.x <= 1120 && mouse.y >= 825 && mouse.y <= 925){ //se as coordenadas do mouse coincidirem com a palavra iniciar...
            DrawText("Iniciar", 750, 825, 120, MAROON); //sobrescreve com outra cor a palavra, pra destacar
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                iniciaJogo(musica);//se o botao esquerdo for apertado, chama a funcao inicia jogo
            }
        }
        DrawText("Aperte ESC para sair do jogo", 1350, 30, 35, GRAY); //apenas dizendo q se aperta esc, por padrao sai do jogo
       
        EndDrawing(); //fechando o desenho
    }
   
    UnloadMusicStream(musica); //"descarregando" a musica
    UnloadTexture(BG); //"descarregando" a textura carregada
    CloseAudioDevice(); //fechar dispositivo de audio
   
}

void iniciaJogo(Music musica){ //passei musica como parametro pra continuar tocando
    int flag = 0;
    Texture w, s, a, d;
    w = LoadTexture("./W.png");
    s = LoadTexture("./S.png");
    a = LoadTexture("./A.png");
    d = LoadTexture("./D.png"); //carregando as texturas dos comandos
    while(!WindowShouldClose()){
       
        UpdateMusicStream(musica); //continua tocando
       
        BeginDrawing();
        ClearBackground(BLACK);
        if(IsKeyDown(KEY_SPACE)){
            flag = 1;
        } // se apertar espaço, a flag muda de valor, teoricamente pra iniciar o jogo
       
        if(flag == 0){
            DrawTexture(w, 150, 150, WHITE);
            DrawText("- ANDAR PARA FRENTE", 240, 160, 50, WHITE);
            DrawTexture(a, 150, 300, WHITE);
            DrawText("- ANDAR ESQUERDA", 240, 310, 50, WHITE);
            DrawTexture(s, 150, 450, WHITE);
            DrawText("- ANDAR PARA DIREITA", 240, 460, 50, WHITE);
            DrawTexture(d, 150, 600, WHITE);
            DrawText("- ANDAR PARA TRAS", 240, 610, 50, WHITE);
            DrawText("APERTE ESPAÇO PARA CONTINUAR", 295, 850, 75, GRAY); //desenha as teclas e o que elas fazem
        }
        else{ //inicia o jogo
            StopMusicStream(musica); //para pra trocar de musica caso queiram
            DrawText("OI", 10, 10, 50, WHITE);  
        }
       
        EndDrawing();
    }
    UnloadTexture(w);
    UnloadTexture(a);
    UnloadTexture(s);
    UnloadTexture(d);
}
