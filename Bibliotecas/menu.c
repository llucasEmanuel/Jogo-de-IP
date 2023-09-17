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
     
     // while (delay > 0) {
          // delay--;
          // BeginDrawing();
          // ClearBackground(GRAY);
          // DrawTextureEx(FNAU, (Vector2) {-450, 110} , 0, 1.6, WHITE);
          // EndDrawing();
      // }
        
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
    char letra[2];
    letra[0] = GetKeyPressed();
    letra[1] = '\0';
    
    if(letra[0] >= 65 && letra[0] <= 90 && strlen(menu.nome) < 11){
        strcat(menu.nome, letra);
    }
    if(letra[0] == ' ' && strlen(menu.nome) < 11){
        strcat(menu.nome, letra);
    }
    if(letra[0] == '.' && strlen(menu.nome) < 11){
        strcat(menu.nome, letra);
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
