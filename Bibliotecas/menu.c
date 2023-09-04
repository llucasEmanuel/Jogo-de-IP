#include <raylib.h>
#include "menu.h"

int geraMenu(){
    int continua = 0; //variavel que a funcao vai retornar
  
    Texture BG, COMANDOS; 
    COMANDOS = LoadTexture("./Sprites e Texturas/bloco_comando.png");
    BG = LoadTexture("./Sprites e Texturas/bg_1.png"); //load nas texturas
    Vector2 mouse; //criando um vetor pro mouse, pra armazenar as coordenadas dele a cada vez que percorre o while
        
    mouse = GetMousePosition(); //essa funcao devolve as coordenadas do mouse (X, Y)
        
    BeginDrawing(); //comeca a desenhar
       
    ClearBackground(BLACK); //limpa o plano de fundo
    DrawTexture(BG, 0, 0, WHITE); //desenha o plano de fundo do menu (WHITE por que tira o PNG)
    DrawText("NOME DO JOGO", 380, 200, 150, WHITE); 
    DrawText("Iniciar", 750, 825, 120, WHITE); //desenhando textos
    if(mouse.x >= 750 && mouse.x <= 1120 && mouse.y >= 825 && mouse.y <= 925){ //se as coordenadas do mouse coincidirem com a palavra iniciar...
        DrawText("Iniciar", 750, 825, 120, MAROON); //sobrescreve com outra cor a palavra, pra destacar
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ //se aperta o botao esquerto do mouse, 
            continua = 1;
        }
    }
    DrawText("Aperte ESC para sair do jogo", 1350, 30, 35, GRAY); //apenas dizendo q se aperta esc, por padrao sai do jogo
       
    EndDrawing(); //fechando o desenho
    
    UnloadTexture(BG); //"descarregando" a textura carregada
    
  
    return continua;
}

int iniciaJogo(){
    int flag = 0;
    int continua = 0; //variavel que a funcao retorna
    
    Texture w, s, a, d;
    w = LoadTexture("./Sprites e Texturas/W.png");
    s = LoadTexture("./Sprites e Texturas/S.png");
    a = LoadTexture("./Sprites e Texturas/A.png");
    d = LoadTexture("./Sprites e Texturas/D.png"); //carregando as texturas dos comandos
        
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
            continua = 1;
        }
        
    EndDrawing();
    
    UnloadTexture(w);
    UnloadTexture(a);
    UnloadTexture(s);
    UnloadTexture(d);
    return continua;
}