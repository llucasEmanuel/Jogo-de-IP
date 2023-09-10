#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"

void iniciaMenu(Menu *menu){ //funcao pra inicializar a struct menu
    (*menu).BG = LoadTexture("./Sprites e Texturas/bg_1.png");
    (*menu).continua = 0;
    (*menu).w = GetScreenWidth();
    (*menu).h = GetScreenHeight();
    strcpy((*menu).nome, "\0");
}

void iniciaComando(Comando *comando){ //funcao que inicializa a struct comando
        (*comando).w = LoadTexture("./Sprites e Texturas/W.png");
        (*comando).s = LoadTexture("./Sprites e Texturas/S.png");
        (*comando).a = LoadTexture("./Sprites e Texturas/A.png");
        (*comando).d = LoadTexture("./Sprites e Texturas/D.png"); //carregando as texturas dos comandos
        (*comando).continua = 0;
}

Menu desenhaMenu(Menu menu){
    
        
    menu.mouse = GetMousePosition(); //essa funcao devolve as coordenadas do mouse (X, Y)
        
    BeginDrawing(); //comeca a desenhar
       
    ClearBackground(BLACK); //limpa o plano de fundo
    DrawTexture(menu.BG, 0, 0, WHITE); //desenha o plano de fundo do menu (WHITE por que tira o PNG)
    DrawText("FIVE NIGHTS AT UFPE", 360, 200, 100, WHITE); 
    DrawText("Iniciar", 750, 825, 120, WHITE); //desenhando textos
    
    //Colocando opcao para digitar o nome do usuario
    DrawText(TextFormat("Digite seu nome: %s", menu.nome), menu.w - 1830, menu.h - 200, 35, WHITE);
    DrawText("_", menu.w - 1825 + MeasureText("Digite seu nome: ", 35) + MeasureText(menu.nome,35), menu.h - 200, 45, WHITE);
    
    //pegando nome do usuario
    if (IsKeyPressed(KEY_Q) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
        strcpy(menu.nome, "Q");
        }
        else{
           strcat(menu.nome, "Q"); 
        }
    }
    if (IsKeyPressed(KEY_W) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
        strcpy(menu.nome, "W");
        }
        else{
           strcat(menu.nome, "W"); 
        }
    }
    if (IsKeyPressed(KEY_E) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "E");
        }
        else{
           strcat(menu.nome, "E"); 
        }
    }
    if (IsKeyPressed(KEY_R) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
        strcpy(menu.nome, "R");
        }
        else{
           strcat(menu.nome, "R"); 
        }
    }
    if (IsKeyPressed(KEY_T) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "T");
        }
        else{
           strcat(menu.nome, "T"); 
        }
    }
    if (IsKeyPressed(KEY_Y) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "Y");
        }
        else{
           strcat(menu.nome, "Y"); 
        }
    }
    if (IsKeyPressed(KEY_U) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "U");
        }
        else{
           strcat(menu.nome, "U"); 
        }
    }
    if (IsKeyPressed(KEY_I) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "I");
        }
        else{
           strcat(menu.nome, "I"); 
        }
    }
    if (IsKeyPressed(KEY_O) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "O");
        }
        else{
           strcat(menu.nome, "O"); 
        }
    }
    if (IsKeyPressed(KEY_P) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "P");
        }
        else{
           strcat(menu.nome, "P"); 
        }
    }
    if (IsKeyPressed(KEY_A) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "A");
        }
        else{
           strcat(menu.nome, "A"); 
        }
    }
    if (IsKeyPressed(KEY_S) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "S");
        }
        else{
           strcat(menu.nome, "S"); 
        }
    }
    if (IsKeyPressed(KEY_D) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "D");
        }
        else{
           strcat(menu.nome, "D"); 
        }
    }
    if (IsKeyPressed(KEY_F) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "F");
        }
        else{
           strcat(menu.nome, "F"); 
        }
    }
    if (IsKeyPressed(KEY_G) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "G");
        }
        else{
           strcat(menu.nome, "G"); 
        }
    }
    if (IsKeyPressed(KEY_H) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "H");
        }
        else{
           strcat(menu.nome, "H"); 
        }
    }
    if (IsKeyPressed(KEY_J) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "J");
        }
        else{
           strcat(menu.nome, "J"); 
        }
    }
    if (IsKeyPressed(KEY_K) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "K");
        }
        else{
           strcat(menu.nome, "K"); 
        }
    }
    if (IsKeyPressed(KEY_L) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
           strcpy(menu.nome, "L");
        }
        else{
           strcat(menu.nome, "L"); 
        }
    }
    if (IsKeyPressed(KEY_Z) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "Z");
        }
        else{
           strcat(menu.nome, "Z"); 
        }
    }
    if (IsKeyPressed(KEY_X) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "X");
        }
        else{
           strcat(menu.nome, "X"); 
        }
    }
    if (IsKeyPressed(KEY_C) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "C");
        }
        else{
           strcat(menu.nome, "C"); 
        }
    }
    if (IsKeyPressed(KEY_V) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "V");
        }
        else{
           strcat(menu.nome, "V"); 
        }
    }
    if (IsKeyPressed(KEY_B) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "B");
        }
        else{
           strcat(menu.nome, "B"); 
        }
    }
    if (IsKeyPressed(KEY_N) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "N");
        }
        else{
           strcat(menu.nome, "N"); 
        }
    }
    if (IsKeyPressed(KEY_M) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, "M");
        }
        else{
           strcat(menu.nome, "M"); 
        }
    }
    if (IsKeyPressed(KEY_SPACE) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, " ");
        }
        else{
           strcat(menu.nome, " "); 
        }
    }
    if (IsKeyPressed(KEY_PERIOD) && strlen(menu.nome) < 12){
        if(strlen(menu.nome) == 0){
            strcpy(menu.nome, ".");
        }
        else{
           strcat(menu.nome, "."); 
        }
    }
    if(strlen(menu.nome) != 0 && IsKeyPressed(KEY_BACKSPACE)){
        menu.nome[strlen(menu.nome) - 1] = '\0';
    }
    
    
    if(menu.mouse.x >= 750 && menu.mouse.x <= 1120 && menu.mouse.y >= 825 && menu.mouse.y <= 925){ //se as coordenadas do mouse coincidirem com a palavra iniciar...
        DrawText("Iniciar", 750, 825, 120, MAROON); //sobrescreve com outra cor a palavra, pra destacar
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && strlen(menu.nome) != 0){ //se aperta o botao esquerto do mouse, 
            menu.continua = 1;
            UnloadTexture(menu.BG); //"descarregando" a textura carregada
        }
        else if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && strlen(menu.nome) == 0){
            DrawText("DIGITE UM NOME!", menu.w - 1850, menu.h - 260, 50, MAROON);
        }
    }
    DrawText("Aperte ESC para sair do jogo", 1350, 30, 35, GRAY); //apenas dizendo q se aperta esc, por padrao sai do jogo
       
    EndDrawing(); //fechando o desenho
    
  
    return menu;
}

Comando iniciaJogo(Comando comando){
    int flag = 0;
        
        BeginDrawing(); 
        ClearBackground(BLACK);
        if(IsKeyDown(KEY_SPACE)){
            flag = 1;
        } // se apertar espaço, a flag muda de valor pra iniciar o jogo
        
        if(flag == 0){
            DrawTexture(comando.w, 150, 150, WHITE);
            DrawText("- ANDAR PARA CIMA", 240, 160, 50, WHITE);
            DrawTexture(comando.a, 150, 300, WHITE);
            DrawText("- ANDAR ESQUERDA", 240, 310, 50, WHITE);
            DrawTexture(comando.s, 150, 450, WHITE);
            DrawText("- ANDAR PARA BAIXO", 240, 460, 50, WHITE);
            DrawTexture(comando.d, 150, 600, WHITE);
            DrawText("- ANDAR PARA DIREITA", 240, 610, 50, WHITE);
            DrawText("APERTE ESPAÇO PARA CONTINUAR", 295, 850, 75, GRAY); //desenha as teclas e o que elas fazem
            
            DrawText("Você deve procurar", 1200, 200, 40, GRAY);
            DrawText("pela chave do GRAD05 na", 1200, 250, 40, GRAY);
            DrawText("escuridão do CIN.", 1200, 300, 40, GRAY);
            DrawText("Baterias ajudam sua lanterna.", 1200, 375, 40, GRAY);
            DrawText("Cuidado com Paulo!", 1200, 450, 40, GRAY);
        }
        else{ //inicia o jogo
            comando.continua = 1;
            UnloadTexture(comando.w);
            UnloadTexture(comando.a);
            UnloadTexture(comando.s);
            UnloadTexture(comando.d);
        }
        
    EndDrawing();
    
    return comando;
}
