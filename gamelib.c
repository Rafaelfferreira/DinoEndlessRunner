#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "gamelib.h"
#define DINOPOSX 12

void rodaJogo(int *dinoPosY, int *key, int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *existeTP, int *existeTG, int *existeAP, int *existeAG)
{
    srand(time(NULL));
    while(*gameOver == 0 && *pausado == 0)
    {
        interacao(key, dinoPosY, pronto, velJogo, abaixado);
        int iniPosX = 90, iniPosY, inimigo;

        //5 flags para controlar os inimigos: "inimigo" diz se tem um inimigo na tela e as outras sao flags especificas
        if(*existeAG == 1 || *existeAP == 1 || *existeTG == 1 || existeTP == 1) //movimenta o inimigo
        {
            if(*existeTG == 1)
            {
                iniPosY = 14;
                movimentaTG(&iniPosX, iniPosY, &existeTG, &inimigo);
            }
            else if(*existeAG == 1)
            {

            }
            else if(*existeAP == 1)
            {

            }
            else
            {

            }
        }

        if(*existeAG == 0 && *existeAP == 0 && *existeTG == 0 && *existeTP == 0) //cria um inimigo aleatorio
        {
            //inimigo = rand() % (4 + 1 - 1) + 1;
            inimigo = 1;

            if(inimigo == 1)
            {
                *existeTG = 1;
            }
            else if(inimigo == 2)
            {
                *existeAG == 1;
            }
            else if(inimigo == 3)
            {
                *existeAP == 1;
            }
            else
            {
                *existeTP == 1;
            }
        }
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
void interacao(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado)
{
    int FLPulando, tempoPulo; //flag se o dinossauro esta pulando
    if(*pronto == 1 && kbhit()) //Determina se o usuario pressionou uma tecla sem ter que parar o programa
    {
        *k = getch();
        if(*k == ' ' && *abaixado == 0)
        {
            *pronto = 0;
            tempoPulo = 12;
            FLPulando = 1;
            pulando(dinoPosY, velJogo, pronto, &tempoPulo, &FLPulando);
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
    if(FLPulando == 1)
        pulando(dinoPosY, velJogo, pronto, &tempoPulo, &FLPulando);
}

//Faz o dinossauro pular e, ao fim do pulo, limpa o buffer de qualquer outra tecla que o jogador tenha pressionado durante o pulo
void pulando(int *dinoPosY, int *velJogo, int *pronto, int *tempoPulo, int *FLPulando)
{
        gotoxy(20,10);
        printf("entrou %d, %d", *tempoPulo, *FLPulando);
        Sleep(500);
        //dinossauro descendo
        if(*tempoPulo > 8)
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
        else if(*tempoPulo > 4 && *tempoPulo < 9)
            *tempoPulo = *tempoPulo-1;

        //dinossauro subindo
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

            //Limpa o buffer do teclado de teclas que foram pressionadas durante o pulo
            while(kbhit())
            getch();
            *pronto = 1;
        }
        else if(*tempoPulo == 0)
            *FLPulando = 0;


        //Sleep(*velJogo/2);
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

void movimentaTG(int *iniPosx, int iniPosY, int *existeTG, int *inimigo)
{
    gotoxy(*iniPosx, iniPosY);
    printf("YY   YY ");
    gotoxy(*iniPosx, iniPosY+1);
    printf("YYYYYYY ");
    gotoxy(*iniPosx, iniPosY+2);
    printf("  YYY ");
    gotoxy(*iniPosx, iniPosY+3);
    printf("  YYY ");
}
