
#include "raylib.h"
int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Texture foto1=LoadTexture("alunoescada.png");
    Texture foto2=LoadTexture("alunosala.png");
    Texture foto3=LoadTexture("corredor1.png");
    Texture foto4=LoadTexture("alunobiblioteca.png");
    Texture foto5=LoadTexture("alunoestante2.png");
    Texture foto6=LoadTexture("alunoestante1.png");
    Texture foto7=LoadTexture("estante03.3.png");
    Texture foto8=LoadTexture("estantebilhete.png");
    Texture foto9=LoadTexture("leuobilhete.png");
    Texture foto10=LoadTexture("estantefim.png");
    Texture foto12=LoadTexture("idap.png");
    Texture foto13=LoadTexture("ritual.png");
    Texture foto14=LoadTexture("voltaapg.png");
    Texture foto15=LoadTexture("voltaac.png");
    Texture foto16=LoadTexture("corredorb.png");
    Texture foto17=LoadTexture("salab.png");
    Texture foto18=LoadTexture("corredor2.png");
    Texture foto19=LoadTexture("fim2.png");
    

    const char legendas[25][100]= {"''Estou ansioso para o fim do período''", 
                                   "''agora o que resta são as provas''",
                                   "''Ah não, mais uma nota baixa!''", "''Desse jeito eu vou reprovar.",
                                    "''preciso estudar para a final, rápido!''",
                                    "''São tantos conteudos...''", "...", "...","...",
                                     "''Parece que alguem esqueceu esse bilhete''", "...",
                                     "''Como aprender o que quiser, por cinco dias?''",
                                     "''Vá para uma floresta com esses objetos?''", 
                                    "''Isso tá parecendo um ritual...''", "''os passos são tão simples...''",
                                    "''por que não tentar?''",
                                    "''Tudo Pronto!''", "'' Agora é só esperar.''",
                                    "''Acho que não deu certo..''", "''Já ta no horário de voltar mesmo...''",
                                    "''Onde está todo mundo?''", "''Ah não...isso é tudo culpa minha''", 
                                    "''Eu não devia ter feito isso''", "''Preciso ir embora!''", 
                                    "''Tenho que sair daqui antes que seja tarde demais...''"};
                                    
                                   
    int framesCounter=4;
    int numpalavra=25; 
    int palavraatual=0;
    Texture fotos[29]= {foto1,foto3,foto2, foto2,foto18,foto4,foto5,foto6,
                        foto7, foto8,foto9,foto9,foto9,foto9,foto9,foto10,foto12,
                        foto13, foto14,foto15,foto16,foto17,foto17,foto17,foto19};
    int indice=0;
    int i=0;

    SetTargetFPS(60);             
    
    int apertouenter=0; 
    
    while (!WindowShouldClose())    
    {
        
        if(IsKeyPressed(KEY_SPACE))
        {
            apertouenter=1;
            
            if (palavraatual < numpalavra)
            {
                framesCounter=0;
                palavraatual++;
            }
             apertouenter=1;
             
                if(apertouenter){
                    indice=(indice +1);
                    apertouenter=0;
                    i=(i+1);
                    framesCounter+=4;
                }
        }
        else framesCounter++;
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTextureEx(fotos[indice],(Vector2){0.5, 0.5},0, 0.2, WHITE);
            DrawText(TextSubtext(legendas[palavraatual],0, framesCounter), 200, 400, 27,GOLD);
            

        
    }
    
    
    UnloadTexture(foto1);
    UnloadTexture(foto2);
    UnloadTexture(foto3);
    UnloadTexture(foto4);
    UnloadTexture(foto5);
    UnloadTexture(foto6);
    UnloadTexture(foto7);
    UnloadTexture(foto8);
    UnloadTexture(foto9);
    UnloadTexture(foto10);
    UnloadTexture(foto13);
    UnloadTexture(foto14);
    UnloadTexture(foto15);
    UnloadTexture(foto16);
    UnloadTexture(foto17);
    UnloadTexture(foto18);
    UnloadTexture(foto19);
    UnloadTexture(foto12);

    
    CloseWindow();        
    return 0;
}
