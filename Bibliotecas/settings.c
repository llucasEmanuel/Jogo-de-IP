#include <raylib.h>
#include "settings.h"
/* HITBOXES DO MAPA
Rectangle mesaG = {174, 885, 120, 196};
    Rectangle mesaP = {1610, 885, 123, 192};
    Rectangle bancada = {771, 382, 362, 108};
    Rectangle guardaRoupa = {174, 166, 481, 216};
    Rectangle estante = {1498, 166, 241, 188};
    Rectangle bancasE1 = {409, 626, 242, 115}; 
    Rectangle bancasE2 = {409, 866, 242, 115};
    Rectangle bancasC1 = {772, 626, 360, 115};
    Rectangle bancasC2 = {772, 866, 360, 115};
    Rectangle bancasD1 = {1250, 626, 242, 115};
    Rectangle bancasD2 = {1250, 866, 242, 115};
*/
Camera2D inicializarCamera(Player jogador) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    Camera2D camera = {0};
    camera.target = jogador.centro;
    camera.offset = (Vector2) {width/2, height/2};
    camera.rotation = 0;
    camera.zoom = 1;
    return camera;
}

void carregarMusicas(Music *musicasFase, Music *musicaMenu) {
    (*musicaMenu) = LoadMusicStream("Sons e Musica/Spooked - Mini Vandals.mp3");
    for (int i = 0; i < 5; i++) {
        musicasFase[i] = LoadMusicStream("Sons e Musica/musicaFase1.mp3");
    }
}

void carregarSons(Sound *youDied, Sound *musicaPerseguicao, Sound *musicaEncerramento, Sound *miau, Sound *somScore, Sound *gameOverSound) {
    (*youDied) = LoadSound("Sons e Musica/you_died_DS.mp3");
    (*musicaEncerramento) = LoadSound("Sons e Musica/Dramatic Series Theme - Freedom Trail Studio.mp3");
    (*musicaPerseguicao) = LoadSound("Sons e Musica/Funeral in Sinaloa - Jimena Contreras.mp3");
    (*miau) = LoadSound("Sons e Musica/gatoSFX.mp3");
    (*somScore) = LoadSound("Sons e Musica/highscore.mp3");
    (*gameOverSound) = LoadSound("Sons e Musica/gameOver.mp3");
}

void salvarScore(char *nome, int score) {
    FILE *file = fopen("highscore.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo highscore.txt\n");
        exit(1);
    }
    fprintf(file, "%s,%d\n", nome, score);
    fclose(file);
}

void printTelaEncerramento(Ranking *ranking, Menu *menu) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("PARABENS, VOCE SOBREVIVEU A UFPE...", width / 2 - MeasureText("PARABENS, VOCE SOBREVIVEU A UFPE...", 60) / 2, height / 2 - 450, 60, BLACK); 
    DrawText("POR ENQUANTO!", width / 2 - MeasureText("POR ENQUANTO!", 90) / 2, height / 2 - 350, 90, MAROON); 
    for(int i = 0; i < ranking[0].qtdPessoas && i < 10; i++){
        DrawText(TextFormat("%d. %s - %d", i + 1, ranking[i].nome, ranking[i].pontuacao), width/2 - 200, height / 2 + (50 * i) - 25, 40, BLACK);
    }
    EndDrawing();
    DrawText("RANKING", width / 2 - 150, height / 2 - 125, 50, MAROON);
    if (IsKeyPressed(KEY_SPACE)) {
        (*menu).reinicia = 1;
    }
}

void printTelaPerdeu(int ind, Font fonteDS) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    BeginDrawing();
    ClearBackground(BLACK);
    if (ind != -1) {
        switch (ind) {
            case 0://MS
                DrawTextEx(fonteDS, "VOCE CHEGOU 2 MINUTOS ATRASADO", (Vector2) {width / 2 - MeasureText("VOCE CHEGOU 2 MINUTOS ATRASADO", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                break;
            case 1://PS
                DrawTextEx(fonteDS, "PAULO SALGADO NAO IRA... NAO IRA NOS SALVAR", (Vector2) {width / 2 - MeasureText("PAULO SALGADO NAO IRA... NAO IRA NOS SALVAR", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                break;
            case 2://NV
                DrawTextEx(fonteDS, "ISSO ERA TRIVIAL", (Vector2) {width / 2 - MeasureText("ISSO ERA TRIVIAL", 70)/ 2 + 25, height / 2 - 70}, 70, 3, MAROON);
                break;
            default:
                break;
        }
    }
    DrawText("Aperte [SPACE] para continuar", width/2 - MeasureText("Aperte [SPACE] para continuar", 50)/2, 980, 50, GRAY);
    EndDrawing();
}

void printScore(int score) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    BeginDrawing();
    ClearBackground(GRAY);
    DrawText(TextFormat("SCORE ATUAL: %d", score), width / 2 - MeasureText("SCORE ATUAL: ", 75) / 2, height / 2 - 75, 75, BLACK);
    EndDrawing();
}

void printGameOver(Menu *menu) {
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("VOCE FOI REPROVADO!", width/2 - MeasureText("VOCE FOI REPROVADO!", 120)/2, height/2 - 220, 120, MAROON);
    DrawText("GAME OVER", width/2 - MeasureText("GAME OVER", 150)/2, height/2 - 80, 150, RED);
    DrawText("Aperte [SPACE] para continuar", width/2 - MeasureText("Aperte [SPACE] para continuar", 50)/2, 980, 50, GRAY);
    EndDrawing();
    if (IsKeyPressed(KEY_SPACE)) {
        (*menu).reinicia = 1;
    }
}

void desenharPorta(Player jogador, Collectable porta, float *distCampoVisaoPortaC) {
    *distCampoVisaoPortaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*porta.coordenadas.x + 2.2*porta.textura.width)/2, 2)
    + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*porta.coordenadas.y + 2.2*porta.textura.height)/2, 2));
    if (*distCampoVisaoPortaC < jogador.campoVisao) {
        DrawTextureEx(porta.textura, porta.coordenadas, 0, 2.2, WHITE);
    }
    else DrawTextureEx(porta.textura, porta.coordenadas, 0, 2.2,  BLACK);
  
    DrawRectangle(porta.hitbox.x, porta.hitbox.y, porta.hitbox.width, porta.hitbox.height, BLANK);
}

void desenharInimigo(Enemy *inimigo, Player jogador, float *acumulador, int *musicaTocando, int *musicaDelay, int *frameAtual, float *tempoFrame, Music *musicasFase, Sound musicaPerseguicao) {
    float distCampoVisaoinimigoC = sqrt(pow(jogador.centro.x - inimigo->centro.x, 2) + pow(jogador.centro.y - inimigo->centro.y, 2));
    if (distCampoVisaoinimigoC < jogador.campoVisao) {//se tiver dentro do campo de visao
        if (!(*musicaTocando)) {
            PauseMusicStream(musicasFase[0]);
            PlaySound(musicaPerseguicao);
            SetSoundVolume(musicaPerseguicao, 0.6);
            (*musicaTocando) = 1;
            (*musicaDelay) = 120;
        }
        DrawTextureRec(inimigo->textura, (Rectangle){((inimigo->frameLargura) * (inimigo->frame)), 0, inimigo->frameLargura, inimigo->textura.height}, (Vector2) {inimigo->coordenadas.x, inimigo->coordenadas.y}, RAYWHITE);

    }
    else { 
        if (*musicaTocando) {
            if ((*musicaDelay) > 0) {
                (*musicaDelay)--;
            }
            else {   
                ResumeMusicStream(musicasFase[0]);//continua de onde parou
                StopSound(musicaPerseguicao);
                (*musicaTocando) = 0;
            }
        }
        DrawTextureRec(inimigo->textura, (Rectangle){((inimigo->frameLargura) * (inimigo->frame)), 0, inimigo->frameLargura, inimigo->textura.height}, (Vector2) {inimigo->coordenadas.x, inimigo->coordenadas.y}, BLACK);

    }
    DrawRectangle(inimigo->hitbox.x, inimigo->hitbox.y, inimigo->hitbox.width, inimigo->hitbox.height, BLANK);
    //DrawTextureRec(inimigo->textura, (Rectangle){((inimigo->frameLargura) * (inimigo->frame)), 0, inimigo->frameLargura, inimigo->textura.height}, (Vector2) {inimigo->coordenadas.x, inimigo->coordenadas.y}, RAYWHITE);
}

void desenharBateria(Collectable bateria, Player jogador) {
    float distCampoVisaoBateriaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*bateria.coordenadas.x + 3*bateria.textura.width)/2, 2)
    + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*bateria.coordenadas.y + 3*bateria.textura.height)/2, 2));
    if (distCampoVisaoBateriaC < jogador.campoVisao) {
        DrawTextureEx(bateria.textura, bateria.coordenadas, 0, 3, WHITE);
    }
    else DrawTextureEx(bateria.textura, bateria.coordenadas, 0, 3, BLACK);

    DrawRectangle(bateria.hitbox.x, bateria.hitbox.y, bateria.hitbox.width, bateria.hitbox.height, BLANK);
}

void desenharChave(Collectable chave, Player jogador, float *distCampoVisaoChaveC) {
    *distCampoVisaoChaveC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*chave.coordenadas.x + 2.5*chave.textura.width)/2, 2)
    + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*chave.coordenadas.y + 2.5*chave.textura.height)/2, 2));
    if (*distCampoVisaoChaveC < jogador.campoVisao) {
        DrawTextureEx(chave.textura, chave.coordenadas, 0, 2.5, WHITE);
    }
    else DrawTextureEx(chave.textura, chave.coordenadas, 0, 2.5, BLACK);

    DrawRectangle(chave.hitbox.x, chave.hitbox.y, chave.hitbox.width, chave.hitbox.height, BLANK);
}

void desenharVida(Collectable vida, Player jogador, float *distCampoVisaoVidaC) {
    *distCampoVisaoVidaC = sqrt(pow((2*jogador.coordenadas.x + 0.33*jogador.textura.width)/2 - (2*vida.coordenadas.x + 2.2*vida.textura.width)/2, 2)
    + pow((2*jogador.coordenadas.y + 0.33*jogador.textura.height)/2 - (2*vida.coordenadas.y + 2.2*vida.textura.height)/2, 2));
    if (*distCampoVisaoVidaC < jogador.campoVisao) {
        DrawTextureEx(vida.textura, vida.coordenadas, 0, 2.2, WHITE);
    }
    else DrawTextureEx(vida.textura, vida.coordenadas, 0, 2.2, BLACK);
 
    DrawRectangle(vida.hitbox.x, vida.hitbox.y, vida.hitbox.width, vida.hitbox.height, BLANK);
}

void desenharJogador(Player jogador) {
    DrawTextureRec(jogador.textura, (Rectangle){((jogador.frameLargura) * (jogador.frame)), 0, jogador.frameLargura, jogador.textura.height}, (Vector2) {jogador.coordenadas.x+jogador.frameLargura-10, jogador.coordenadas.y-10}, RAYWHITE);
    DrawRectangle(jogador.hitbox.x, jogador.hitbox.y, jogador.hitbox.width, jogador.hitbox.height, BLANK);
}

void gerarHUD(Camera2D camera, Fase fase, int *deathCount, CollectableContador *chave, CollectableContador *bateria, Player jogador) {
    //DESENHAR BARRA DE SANIDADE (A CADA MORTE ELA DIMINUI 1/3)
    DrawText("SANIDADE", camera.target.x - MeasureText("SANIDADE", 35)/2, camera.target.y - 500, 35, SILVER);
    DrawRectangle(camera.target.x - 125, camera.target.y - 450, 250, 40, SILVER);
    DrawRectangle(camera.target.x - 120, camera.target.y - 446, 240 - 80*(*deathCount), 32, RED);
    DrawRectangle(camera.target.x - 120 + 240 - (80*(*deathCount)), camera.target.y - 446, 80*(*deathCount), 32, BLACK);

    //DESENHAR OS ICONES, SCORE E QTD DE COLETAVEIS
    DrawText(TextFormat("NOITE %d", fase.faseAtual), camera.target.x - MeasureText("NOITE 1", 40) / 2, camera.target.y + 400, 40, SILVER);
    DrawText(TextFormat("SCORE : %d", jogador.score), camera.target.x - 900, camera.target.y - 500, 40, SILVER);
    chave->coordenadas.x = camera.target.x - 900;
    chave->coordenadas.y = camera.target.y - 450;
    DrawTextureEx(chave->textura, chave->coordenadas, 0, 2.5, WHITE);
    DrawText(TextFormat(" x %d", jogador.temChave), camera.target.x - 900 + (2.5 * chave->textura.width), camera.target.y - 450, 40, SILVER);
    bateria->coordenadas.x = camera.target.x - 900;
    bateria->coordenadas.y = camera.target.y - 400;
    DrawTextureEx(bateria->textura, bateria->coordenadas, 0, 3, WHITE);
    DrawText(TextFormat(" x %d", jogador.qtdBaterias), camera.target.x - 900 + (3 * bateria->textura.width), camera.target.y - 390, 40, SILVER);
}

void removerJogador(Enemy *inimigo, Player *jogador, int *perdeu, int *deathCount) {
    DrawTextureEx(jogador->textura, jogador->coordenadas, 0, 0.33, BLANK);
    printf("Colisao INIMIGO\n");
    //UnloadTexture(jogador->textura);
    jogador->hitbox = (Rectangle) {0, 0, 0, 0};
    inimigo->colisao = 1;
    *perdeu = 1;
    (*deathCount)++;
}

void pegarChave(Collectable *chave, Player *jogador) {
    DrawTextureEx(chave->textura, chave->coordenadas, 0, 2.5, BLANK);
    chave->colisao = 1;
    printf("Colisao CHAVE\n");
    //UnloadTexture(chave->textura);//apaga a textura
    chave->hitbox = (Rectangle) {0, 0, 0, 0};//remove a hitbox
    jogador->temChave = 1;//atualiza a flag do jogador
    jogador->score += 200;
}

void entrarNaPorta(Collectable *porta, Player *jogador, int *entrouNaPorta, Sound somScore) {
    if (jogador->temChave) {
        DrawTextureEx(porta->textura, porta->coordenadas, 0, 2.2, BLANK);
        porta->colisao = 1;
        printf("Colisao PORTA\n");
        //UnloadTexture(porta->textura);
        porta->hitbox = (Rectangle) {0, 0, 0, 0};
        jogador->score += 500;
        (*entrouNaPorta) = 1;
        PlaySound(somScore);
    }
    else {
        DrawText("PORTA TRANCADA", porta->coordenadas.x - 3*porta->textura.width, porta->coordenadas.y - 50, 40, RED);
    }
}

void pegarBateria(Collectable *bateria, Player *jogador) {
    if (bateria->colisao == 0) {
        DrawTextureEx(bateria->textura, bateria->coordenadas, 0, 3, BLANK);
        bateria->colisao = 1;
        printf("Colisao BATERIA\n");
        //UnloadTexture(bateria->textura);
        bateria->hitbox = (Rectangle){0, 0, 0, 0};
        jogador->qtdBaterias++; 
        jogador->score += 50;
    }
}

void pegarVida(Collectable *vida, Player *jogador, int *deathCount, Sound miau) {
    if ((*deathCount)) {
        DrawTextureEx(vida->textura, vida->coordenadas, 0, 5, BLANK);
        vida->colisao = 1;
        jogador->pegouVida = 1;
        printf("Colisao VIDA\n");
        //UnloadTexture(vida->textura);
        vida->hitbox = (Rectangle) {0, 0, 0, 0};
        jogador->score += 100;
        if (*deathCount != 0) (*deathCount)--;//aumenta a barra de sanidade 
        PlaySound(miau);
    }
    else {
        DrawText("SANIDADE EM DIA", vida->coordenadas.x - 160, vida->coordenadas.y - 50, 40, RED);
    }
}

void criarFase(int numFase, Fase *fase, Player jogador) {
    //INICIALIZAR INIMIGOS
    if (numFase == 1) {
        fase->inimigos = NULL;
    }
    fase->inimigos = inicializarInimigos(numFase, fase->inimigos);
    if (numFase <= 3) fase->qtdInimigos = numFase; 
    else fase->qtdInimigos = 3;
   
    for (int i = 0; i < fase->qtdInimigos; i++) {
        fase->inimigos = inicializarInimigos(numFase, fase->inimigos);   
    }
 
    //INICIALIZACAO DAS BATERIAS
    fase->qtdBaterias = 0;
    fase->baterias = inicializarBaterias(&fase->qtdBaterias, numFase);
    
    //INICIALIZACAO DA CHAVE
    fase->chave = inicializarChave(numFase);
    
    //INICIALIZACAO DA PORTA DE SAIDA
    fase->porta = inicializarPorta(numFase);
    
    //INICIALIZACAO DA VIDA/GATO
    fase->vida = inicializarVida(numFase);
    int spawnGato = rand() % 2;//50% de chance de spawnar em um local inacessivel
    if (spawnGato) {
        fase->vida.coordenadas = (Vector2) {479, 282};
        fase->vida.hitbox = (Rectangle) {0, 0, 0, 0};
    }
    
    fase->faseAtual = numFase;
}

void reiniciarFase(Player *jogador, Fase *fase) {//usa o endereco do jogador para poder alterar a posicao e outros fatores
    int height = GetScreenHeight();
    int width = GetScreenWidth();
    jogador->textura = LoadTexture("Sprites e Texturas/spritebaixo.png");
    UnloadTexture(fase->vida.textura);
    UnloadTexture(fase->chave.textura);
    UnloadTexture(fase->porta.textura);
    for (int i = 0; i < fase->qtdBaterias; i++) {
        UnloadTexture(fase->baterias[i].textura);
    }
    switch (fase->faseAtual) {//posicao do jogador
        case 1:
            jogador->coordenadas = (Vector2) {width/2, height/2};
            break;
        case 2:
            jogador->coordenadas = (Vector2) {150, 400};
            break;
        case 3:
            jogador->coordenadas = (Vector2) {1300, 400};
            break;
        case 4:
            jogador->coordenadas = (Vector2) {523, 807};
            break;
        case 5:
            jogador->coordenadas = (Vector2) {89, 520};
            break;
        default:
            break;
    }
    
    jogador->qtdBaterias = 0;
    jogador->temChave = 0;
    // Redefina a fase para o estado inicial
    criarFase(fase->faseAtual, fase, *jogador);
}
