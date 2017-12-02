#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "gamelib.h"
#define DINOPOSX 12

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
void movimento(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado)
{
    if(*pronto == 1 && kbhit()) //Determina se o usuario pressionou uma tecla sem ter que parar o programa
    {
        *k = getch();
        if(*k == ' ' && *abaixado == 0)
        {
            *pronto = 0;
            pulando(dinoPosY, velJogo, pronto);
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
void pulando(int *dinoPosY, int *velJogo, int *pronto)
{
    int i, tempoPulo = 12;

    //Ajustar quanto tempo ele fica no ar
    for(i = 0; i < tempoPulo; i++) //7 é quantos ciclos demora um pulo, 1 para subir, 5 no ar e 1 para descer
    {
        //dinossauro descendo
        if(i > (tempoPulo - 5))
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

            //Limpa o buffer do teclado de teclas que foram pressionadas durante o pulo
            while(kbhit())
            getch();
            *pronto = 1;
        }

        //dinossauro subindo
        else if(i < 4)
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
        }

        Sleep(*velJogo/2);
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
