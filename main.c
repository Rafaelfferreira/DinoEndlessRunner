#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //incluimos essa biblioteca para usarmos a fun��o sleep, no UNIX essa fun��o se encontra na biblioteca <unistd.h>
#include "gamelib.h"
#define DINOPOSX 12 //definida aqui pois a posicao do dinossauro no eixo X � sempre a mesma
int main()
{
    int gameOver = 0, pausado = 0; //flags para se o jogo esta acabado ou pausado
    int vidas, pontos, nivel; //quantidade de vidas, pontos e nivel do jogador
    int dinoPosY = 14; //variaveis de posicao do dinossauro e variavel para determinar se o mesmo esta abaixado
    int pronto = 1, abaixado = 1; //variaveis para controlar se o dinossauro podera pular/se abaixar e se ele esta abaixado;
    int countVida = 0;

    menuInicial(&dinoPosY, &pronto, &abaixado, &vidas, &pontos, &nivel, &gameOver, &pausado, &countVida);

    //encerramento do programa
    gotoxy(1,21);
    return 0;
}
