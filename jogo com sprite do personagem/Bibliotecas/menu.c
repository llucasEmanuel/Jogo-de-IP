#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"

void iniciaMenu(Menu *menu){ //funcao que inicializa a struct menu (texturas e variaveis)
    (*menu).BG = LoadTexture("./Sprites e Texturas/bg_1.png"); 
    (*menu).creditos = LoadTexture("./Sprites e Texturas/theOneFromMars.png");
    (*menu).continua = 0;
    (*menu).w = GetScreenWidth();
    (*menu).h = GetScreenHeight();
    (*menu).creditosPos.x = (*menu).w - 550;
    (*menu).creditosPos.y = (*menu).h / 2 - (30*(*menu).creditos.height) / 2; // setando posicao do sprite do menu de creditos
    strcpy((*menu).nome, "\0"); // seta string do nome como '\0' para evitar caracteres indesejados
}


void iniciaComando(Comando *comando){ //funcao que inicializa a struct comando (texturas e variaveis
        (*comando).w = LoadTexture("./Sprites e Texturas/W.png");
        (*comando).s = LoadTexture("./Sprites e Texturas/S.png");
        (*comando).a = LoadTexture("./Sprites e Texturas/A.png");
        (*comando).d = LoadTexture("./Sprites e Texturas/D.png"); 
        (*comando).continua = 0;
}
int delay = 300;
Menu desenhaMenu(Menu menu, Music musica){ // funcao responsavel por desenhar a primeira parte do menu
    
    int liberaCreditos = 0;
    int apertouEspaco = 0; // auxiliares
    
    menu.mouse = GetMousePosition(); //essa funcao devolve as coordenadas do mouse (X, Y)
        
     Texture FNAU = LoadTexture("./Sprites e Texturas/FNAU.png");
    ;
     while (delay > 0) {
         delay--;
         BeginDrawing();
         ClearBackground(GRAY);
         DrawTextureEx(FNAU, (Vector2) {-450, 110} , 0, 1.6, WHITE);
         EndDrawing();
     }
        
    UnloadTexture(FNAU);
    
    BeginDrawing(); //comeca a desenhar
       
    ClearBackground(BLACK); //limpa o plano de fundo
    DrawTexture(menu.BG, 0, 0, WHITE); //desenha o plano de fundo do menu
    DrawText("FIVE NIGHTS AT UFPE", 125, 200, 140, MAROON); 
    DrawText("Iniciar", 750, 825, 120, WHITE); // desenhando textos
    
    //Colocando opcao para digitar o nome do usuario
    DrawText(TextFormat("Digite seu nome: %s", menu.nome), menu.w - 1830, menu.h - 200, 35, WHITE);
    DrawText("_", menu.w - 1825 + MeasureText("Digite seu nome: ", 35) + MeasureText(menu.nome,35), menu.h - 200, 45, WHITE);
    DrawText("Créditos", menu.w - MeasureText("Créditos", 50) - 125, menu.h - 200, 50, WHITE);
    
    //Configurando as letras do input do usuário
    if (IsKeyPressed(KEY_Q) && strlen(menu.nome) < 12){
   
       
           strcat(menu.nome, "Q"); 
        
    }
    if (IsKeyPressed(KEY_W) && strlen(menu.nome) < 12){
    
       
           strcat(menu.nome, "W"); 
        
    }
    if (IsKeyPressed(KEY_E) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "E"); 
        
    }
    if (IsKeyPressed(KEY_R) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "R"); 
        
    }
    if (IsKeyPressed(KEY_T) && strlen(menu.nome) < 12){
        
            strcat(menu.nome, "T"); 
        
    }
    if (IsKeyPressed(KEY_Y) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "Y"); 
        
    }
    if (IsKeyPressed(KEY_U) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "U"); 
        
    }
    if (IsKeyPressed(KEY_I) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "I"); 
        
    }
    if (IsKeyPressed(KEY_O) && strlen(menu.nome) < 12){
       
           strcat(menu.nome, "O"); 
        
    }
    if (IsKeyPressed(KEY_P) && strlen(menu.nome) < 12){
   
           strcat(menu.nome, "P"); 
        
    }
    if (IsKeyPressed(KEY_A) && strlen(menu.nome) < 12){
    
           strcat(menu.nome, "A"); 
        
    }
    if (IsKeyPressed(KEY_S) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "S"); 
        
    }
    if (IsKeyPressed(KEY_D) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "D"); 
        
    }
    if (IsKeyPressed(KEY_F) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "F"); 
        
    }
    if (IsKeyPressed(KEY_G) && strlen(menu.nome) < 12){
       
           strcat(menu.nome, "G"); 
        
    }
    if (IsKeyPressed(KEY_H) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "H"); 
        
    }
    if (IsKeyPressed(KEY_J) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "J"); 
        
    }
    if (IsKeyPressed(KEY_K) && strlen(menu.nome) < 12){
       
           strcat(menu.nome, "K"); 
        
    }
    if (IsKeyPressed(KEY_L) && strlen(menu.nome) < 12){
       
           strcat(menu.nome, "L"); 
        
    }
    if (IsKeyPressed(KEY_Z) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "Z"); 
        
    }
    if (IsKeyPressed(KEY_X) && strlen(menu.nome) < 12){
      
           strcat(menu.nome, "X"); 
        
    }
    if (IsKeyPressed(KEY_C) && strlen(menu.nome) < 12){
       
           strcat(menu.nome, "C"); 
        
    }
    if (IsKeyPressed(KEY_V) && strlen(menu.nome) < 12){
        
       
           strcat(menu.nome, "V"); 
        
    }
    if (IsKeyPressed(KEY_B) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "B"); 
        
    }
    if (IsKeyPressed(KEY_N) && strlen(menu.nome) < 12){
       
           strcat(menu.nome, "N"); 
        
    }
    if (IsKeyPressed(KEY_M) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "M"); 
        
    }
    if (IsKeyPressed(KEY_SPACE) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, " "); 
        
    }
    if (IsKeyPressed(KEY_PERIOD) && strlen(menu.nome) < 12){
        
           strcat(menu.nome, "."); 
        
    }
    if(strlen(menu.nome) != 0 && IsKeyPressed(KEY_BACKSPACE)){
        menu.nome[strlen(menu.nome) - 1] = '\0';
    } // quando aperta backspace, ultimo caracter eh substituido por '\0'
    
    // fim da configuracao de caracteres
    
    
    if(menu.mouse.x >= 750 && menu.mouse.x <= 1120 && menu.mouse.y >= 825 && menu.mouse.y <= 925){ //se as coordenadas do mouse coincidirem com a palavra iniciar...
        DrawText("Iniciar", 750, 825, 120, MAROON); //sobrescreve com outra cor a palavra, pra destacar
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && strlen(menu.nome) != 0){ //se aperta o botao esquerto do mouse 
            menu.continua = 1; // passa
            UnloadTexture(menu.creditos);
            UnloadTexture(menu.BG); //"descarregando" as texturas carregadas
        }
        else if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && strlen(menu.nome) == 0){
            DrawText("DIGITE UM NOME!", menu.w - 1850, menu.h - 260, 50, MAROON); //impede o usuario de iniciar o jogo sem colocar nome
        }
    }
    if(menu.mouse.x >= menu.w - MeasureText("Créditos", 50) - 125 && menu.mouse.x <= menu.w - 125 && menu.mouse.y >= menu.h - 200 && menu.mouse.y <= menu.h - 170){ //se as coordenadas do mouse coincidirem com a palavra créditos...
        DrawText("Créditos", menu.w - MeasureText("Créditos", 50) - 125, menu.h - 200, 50, MAROON); //sobrescreve com outra cor a palavra, pra destacar
        
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){ //se aperta o botao esquerto do mouse
            liberaCreditos = 1; // passa
        }
    }
    /* CHECAR */
    while(liberaCreditos == 1){ // enquanto os créditos estão liberados
        BeginDrawing(); // desenha por cima
        UpdateMusicStream(musica);
        ClearBackground(BLACK);
        DrawTextureEx(menu.creditos, menu.creditosPos, 0, 30, WHITE);
        DrawText("GRUPO 3", 100, 100, 60, MAROON);
        DrawText("MARCELO ARCOVERDE NEVES", 100, 600, 50, WHITE);
        DrawText("LUCAS EMANUEL SABINO", 100, 500, 50, WHITE);
        DrawText("KALANI RAFAEL VIEIRA", 100, 300, 50, WHITE);
        DrawText("LUANA GOMES LUCENA", 100, 400, 50, WHITE);
        DrawText("GABRIEL VALENCA MAYERHOFER", 100, 200, 50, WHITE);
        DrawText("PAULO VITOR BARBOSA SANTANA", 100, 700, 50, WHITE);
        DrawText("Pressione e solte [SPACE] para voltar para o menu", (menu.w / 2) - (MeasureText("Pressione e solte [SPACE] para voltar para o menu", 50) / 2), menu.h - 100, 50, GRAY);
        
        //Configurando para voltar pra o menu apos espaco ser apertado e soltado
        if(IsKeyDown(KEY_SPACE)){ 
            DrawText("Pressione e solte [SPACE] para voltar para o menu", (menu.w / 2) - (MeasureText("Pressione e solte [SPACE] para voltar para o menu", 50) / 2), menu.h - 100, 50, MAROON);
            apertouEspaco = 1;
            
        }
        if(IsKeyReleased(KEY_SPACE) && apertouEspaco == 1){
                liberaCreditos = 0;
        }
        
        // fim da cunfiguracao acima
        
        EndDrawing(); //fechando o desenho
    }
    DrawText("Aperte [ESC] para sair do jogo", 1350, 30, 35, GRAY); //apenas dizendo q se aperta esc, por padrao sai do jogo
       
    EndDrawing(); //fechando o desenho
    
    return menu;
}

Comando iniciaJogo(Comando comando){ // funcao que desenha o menu de comandos
    
    int flag = 0;
        
    BeginDrawing(); 
    ClearBackground(BLACK);
    if(IsKeyDown(KEY_SPACE)){
        flag = 1;
    } // se apertar espaço, a flag muda de valor pra iniciar o jogo
        
    if(flag == 0){ // desenhando texturas
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
        DrawText("pela chave do GRAD 05 na", 1200, 250, 40, GRAY);
        DrawText("escuridão do CIN.", 1200, 300, 40, GRAY);
        DrawText("Baterias ajudam sua lanterna.", 1200, 375, 40, GRAY);
        DrawText("Cuidado com os Paulo!", 1200, 450, 40, GRAY);
        }
        else{ //inicia o jogo
            comando.continua = 1;
            UnloadTexture(comando.w);
            UnloadTexture(comando.a);
            UnloadTexture(comando.s);
            UnloadTexture(comando.d);
        }
        
    EndDrawing(); //fechando o desenho
    
    return comando;
}

Ranking* organizaRanking(FILE *arq){ // funcao que le o arquivo do ranking e organiza em ordem de pontuacao
    
    char nomeTemp[12];
    int pontuacaoTemp;
    int qtd = 0; // variaveis de auxilio de leitura do arquivo
    Ranking *ranking = NULL, *temp, troca;
    
    while(!feof(arq)){ // le ate o fim do arquivo
        
        fscanf(arq, " %[^,],%d ", nomeTemp, &pontuacaoTemp); // escaneia no formato que escrevemos "nome,pontuacao"
        temp = ranking;
        ranking = (Ranking *) realloc(temp, (qtd + 1) * sizeof(Ranking)); // aloca o necessário
        if(ranking == NULL){
            printf("Falha na alocacao de memoria\n");
            free(temp);
            exit(1);
        } // se !NULL passa dos auxiliares para o vetor
        strcpy(ranking[qtd].nome, nomeTemp);
        ranking[qtd].pontuacao = pontuacaoTemp;
        qtd++;
    }
    
    for(int i = 0; i < qtd; i++){
        for(int j = i + 1; j < qtd; j++){
            if(ranking[i].pontuacao < ranking[j].pontuacao){
                troca = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = troca;
            }
            else if (ranking[i].pontuacao == ranking[j].pontuacao) {
                if (strcmp(ranking[i].nome, ranking[j].nome) > 0) {
                    troca = ranking[i];
                    ranking[i] = ranking[j];
                    ranking[j] = troca;
                }
            }
        }
    } //bubble sort
    
    ranking[0].qtdPessoas = qtd; // passando a quantidade de pessoas em um parametro "aleatorio" para auxiliar o controle
    
    return ranking;
}
