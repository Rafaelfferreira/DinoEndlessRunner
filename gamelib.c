#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "gamelib.h"
#define DINOPOSX 12

//funcao a ser chamada quando sai do pause, inicia um jogo novo ou carrega outro jogo
void rodaJogo(int *dinoPosY, int *key, int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *existeTP, int *existeTG, int *existeAP, int *existeAG)
{
    srand(time(NULL)); //inicializando a seed do rand
    int FLPulando, tempoPulo; //flag se o player esta pulando e var que determina quantos ciclos dura o pulo
    int ini1PosX = 90, ini1PosY, inimigo = 0, ini2PosX = 90, ini2PosY, ini1 = 0, ini2 = 0; //variaveis do inimigo, mudar iniposX para 100 e arrumar as bordas (mais pra frente no projeto)

    while(*gameOver == 0 && *pausado == 0)
    {
        interacao(key, dinoPosY, pronto, velJogo, abaixado, &FLPulando, &tempoPulo);

        //Se o jogador estiver pulando, carrega um frame novo do pulo a cada ciclo
        if(FLPulando == 1)
            pulando(dinoPosY, pronto, &tempoPulo, &FLPulando);

        //Se o inimigo 1 estiver na tela atualiza sua posicao
        if(ini1 != 0)
        {
            if(ini1 == 1)
            {
                ini1PosY = 14;
                movimentaTG(&ini1PosX, ini1PosY, &ini1);
            }
            else if(ini1 == 2)
            {
                movimentaAG(&ini1PosX, ini1PosY, &ini1);
            }
            else if(ini1 == 3)
            {
                movimentaAP(&ini1PosX, ini1PosY, &ini1);
            }
            else
            {
                ini1PosY = 14;
                movimentaTP(&ini1PosX, ini1PosY, &ini1);
            }
        }

        //se o inimigo 2 estiver na tela atualiza sua posição
        if(ini2 != 0)
        {
            if(ini2 == 1)
            {
                ini2PosY = 14;
                movimentaTG(&ini2PosX, ini2PosY, &ini2);
            }
            else if(ini2 == 2)
            {
                movimentaAG(&ini2PosX, ini2PosY, &ini2);
            }
            else if(ini2 == 3)
            {
                movimentaAP(&ini2PosX, ini2PosY, &ini2);
            }
            else
            {
                ini2PosY = 14;
                movimentaTP(&ini2PosX, ini2PosY, &ini2);
            }
        }

        if(ini1 == 0 || ini2 == 0) //cria um inimigo aleatorio caso nao hajam 2 inimigos na tela
        {
            if((ini1 != 0 && ini1PosX < 30) || (ini2 != 0 && ini2PosX < 30) || (ini1 == 0 && ini2 == 0))
            {
                inimigo = rand() % (4 + 1 - 1) + 1;
                if(inimigo == 1)
                {
                    if(ini1 == 0)
                        ini1 = 1;

                    else if(ini2 == 0)
                        ini2 = 1;

                }
                else if(inimigo == 2)
                {
                    if(ini1 == 0)
                    {
                        ini1 = 2;
                        ini1PosY = rand() % (13 + 1 - 11) + 11;
                    }

                    else if(ini2 == 0)
                    {
                        ini2 = 2;
                        ini2PosY = rand() % (13 + 1 - 11) + 11;
                    }
                }
                else if(inimigo == 3)
                {
                    if(ini1 == 0)
                    {
                        ini1 = 3;
                        ini1PosY = rand() % (13 + 1 - 11) + 11;
                    }

                    else if(ini2 == 0)
                    {
                        ini2 = 3;
                        ini2PosY = rand() % (13 + 1 - 11) + 11;
                    }
                }
                else
                {
                    if(ini1 == 0)
                        ini1 = 4;

                    else if(ini2 == 0)
                        ini2 = 4;
                }
            }
        }

        Sleep(300 - *velJogo);//controla a velocidade do jogo
    }

}
//Imprime na tela o cenário, a interface, e o dinnossauro em sua posição atual
//Essa função deve ser chamada quando o jogo for iniciado(tanto do começo quanto de um save) e quando o jogo sair do pause
////A função ainda deve ser alterada para ler se o dinossauro esta abaixado na hora de começar para imprimilo corretamente
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel)
{
    //Imprime a interface
    printf("Vidas: %d", *vidas);
    printf("\nPontos: %d", *pontos);
    printf("\nNivel: %d", *nivel);

    //imprime o chão
    gotoxy(1,18);
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    gotoxy(1,19);
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    gotoxy(1,20);
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

        //Imprime o dinossauro
        gotoxy(DINOPOSX,*dinoPosY);
        printf("  TT");
        gotoxy(DINOPOSX,*dinoPosY+1);
        printf("TTT");
        gotoxy(DINOPOSX,*dinoPosY+2);
        printf("TTT");
        gotoxy(DINOPOSX,*dinoPosY+3);
        printf("TTT");
}

//funcao que avalia que tipo de movimento é e chama a funçao adequada para executalo
//aqui passamos as variaveis dinoPosY e velJogo como um endereço pois as funçoes que executam os movimentos precisam usa-la como um ponteiro
void interacao(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado, int *FLPulando, int *tempoPulo)
{ //flag se o dinossauro esta pulando
    if(*pronto == 1 && kbhit()) //Determina se o usuario pressionou uma tecla sem ter que parar o programa
    {
        *k = getch();
        if(*k == ' ' && *abaixado == 0)
        {
            *pronto = 0;
            *tempoPulo = 20;
            *FLPulando = 1;
        }
        else if(*k == 'c' || *k == 80) //80 é o numero que representa a seta para baixo
        {
            abaixando(dinoPosY, abaixado);
        }
    }
    //Esse if executa se o jogador nao estiver pressionando a tecla 'c' e se o dinossauro estiver abaixado
    //0x43 e 0x28 sao os KeyCodes das teclas C e da seta para baixo
    if(!(GetKeyState(0x43) & 0x80) && !(GetKeyState(0x28) & 0x80) && *abaixado == 1)
    {
        levantando(dinoPosY, abaixado);
    }
}

//Faz o dinossauro pular e, ao fim do pulo, limpa o buffer de qualquer outra tecla que o jogador tenha pressionado durante o pulo
void pulando(int *dinoPosY, int *pronto, int *tempoPulo, int *FLPulando)
{
        //dinossauro subindo
        if(*tempoPulo > 16)
        {
            *dinoPosY = *dinoPosY -1;
            gotoxy(DINOPOSX,*dinoPosY);
            printf("  TT");
            gotoxy(DINOPOSX,*dinoPosY+1);
            printf("TTT ");
            gotoxy(DINOPOSX,*dinoPosY+2);
            printf("TTT");
            gotoxy(DINOPOSX,*dinoPosY+3);
            printf("TTT");
            gotoxy(DINOPOSX,*dinoPosY+4);
            printf("   ");
            *tempoPulo = *tempoPulo-1;
        }
        //tempo que o dinossauro fica parado no ar
        else if(*tempoPulo > 4 && *tempoPulo < 17)
            *tempoPulo = *tempoPulo-1;

        //dinossauro descendo
        else if(*tempoPulo < 5 && *tempoPulo > 0)
        {
            *dinoPosY = *dinoPosY + 1;
            gotoxy(DINOPOSX,*dinoPosY-1);
            printf("    ");
            gotoxy(DINOPOSX,*dinoPosY);
            printf("  TT");
            gotoxy(DINOPOSX,*dinoPosY+1);
            printf("TTT");
            gotoxy(DINOPOSX,*dinoPosY+2);
            printf("TTT");
            gotoxy(DINOPOSX,*dinoPosY+3);
            printf("TTT");
            *tempoPulo = *tempoPulo-1;
        }
        else if(*tempoPulo == 0)
        {
            *FLPulando = 0; //faz com que o dinossauro pare de pular

            //Limpa o buffer do teclado de teclas que foram pressionadas durante o pulo
            while(kbhit())
            getch();
            *pronto = 1;
        }

}

//As duas funçoes abaixo apagam o dinossauro atual, imprimeme ele ou abaixado ou levantado e mudam a flag "abaixado"
void abaixando(int *dinoPosY, int *abaixado)
{
    if(*abaixado == 0)
    {
        gotoxy(DINOPOSX,*dinoPosY);
        printf("    ");
        gotoxy(DINOPOSX,*dinoPosY+1);
        printf("   ");
        gotoxy(DINOPOSX,*dinoPosY+2);
        printf("TTTTT");
        gotoxy(DINOPOSX,*dinoPosY+3);
        printf("TTT");
        *abaixado = 1;
    }
}

void levantando(int *dinoPosY, int *abaixado)
{
    gotoxy(DINOPOSX,*dinoPosY);
    printf("  TT");
    gotoxy(DINOPOSX,*dinoPosY+1);
    printf("TTT");
    gotoxy(DINOPOSX,*dinoPosY+2);
    printf("TTT  ");
    gotoxy(DINOPOSX,*dinoPosY+3);
    printf("TTT");
    *abaixado = 0;
}

void movimentaTG(int *iniPosx, int iniPosY, int *nIni)
{
    if(*iniPosx > 0)
    {
        gotoxy(*iniPosx, iniPosY);
        printf("YY   YY ");
        gotoxy(*iniPosx, iniPosY+1);
        printf("YYYYYYY ");
        gotoxy(*iniPosx, iniPosY+2);
        printf("  YYY ");
        gotoxy(*iniPosx, iniPosY+3);
        printf("  YYY ");
        *iniPosx = *iniPosx - 1;
    }
    else if (*iniPosx == 0)
    {
        gotoxy(*iniPosx+1, iniPosY);
        printf("       ");
        gotoxy(*iniPosx+1, iniPosY+1);
        printf("       ");
        gotoxy(*iniPosx+1, iniPosY+2);
        printf("     ");
        gotoxy(*iniPosx+1, iniPosY+3);
        printf("     ");
        *nIni = 0;
        *iniPosx = 90;
    }
}

void movimentaTP(int *iniPosx, int iniPosY, int *nIni)
{
    if(*iniPosx > 0)
    {
        gotoxy(*iniPosx, iniPosY);
        printf("### ");
        gotoxy(*iniPosx, iniPosY+1);
        printf("### ");
        gotoxy(*iniPosx, iniPosY+2);
        printf("### ");
        gotoxy(*iniPosx, iniPosY+3);
        printf("### ");
        *iniPosx = *iniPosx - 1;
    }
    else if(*iniPosx == 0)
    {
        gotoxy(*iniPosx+1, iniPosY);
        printf("   ");
        gotoxy(*iniPosx+1, iniPosY+1);
        printf("   ");
        gotoxy(*iniPosx+1, iniPosY+2);
        printf("   ");
        gotoxy(*iniPosx+1, iniPosY+3);
        printf("    ");
        *nIni = 0;
        *iniPosx = 90;
    }
}

void movimentaAG(int *iniPosx, int iniPosY, int *nIni)
{
    if(*iniPosx > 0)
    {
        gotoxy(*iniPosx, iniPosY);
        printf(" %%%%%%%%%%%% ");
        gotoxy(*iniPosx, iniPosY+1);
        printf("%%%%%%%% ");
        gotoxy(*iniPosx, iniPosY+2);
        printf(" %%%%%%%%%%%% ");
        *iniPosx = *iniPosx - 1;
    }
    else if(*iniPosx == 0)
    {
        gotoxy(*iniPosx+1, iniPosY);
        printf("       ");
        gotoxy(*iniPosx+1, iniPosY+1);
        printf("    ");
        gotoxy(*iniPosx+1, iniPosY+2);
        printf("       ");
        *nIni = 0;
        *iniPosx = 90;
    }
}

void movimentaAP(int *iniPosx, int iniPosY, int *nIni)
{
    if(*iniPosx > 0)
    {
        gotoxy(*iniPosx, iniPosY);
        printf("%%%%%%%%%%%%%% ");
        gotoxy(*iniPosx, iniPosY+1);
        printf("%%%%%%%%%%%%%% ");
        *iniPosx = *iniPosx - 1;
    }
    else if(*iniPosx == 0)
    {
        gotoxy(*iniPosx+1, iniPosY);
        printf("       ");
        gotoxy(*iniPosx+1, iniPosY+1);
        printf("       ");
        *nIni = 0;
        *iniPosx = 90;
    }
}
