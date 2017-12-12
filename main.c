#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //incluimos essa biblioteca para usarmos a função sleep, no UNIX essa função se encontra na biblioteca <unistd.h>
#include "gamelib.h"
#define DINOPOSX 12 //definida aqui pois a posicao do dinossauro no eixo X é sempre a mesma
int main()
{
    int gameOver = 0, pausado = 0;
    int vidas = 1, pontos = 0, nivel = 1;
    int velJogo = 250; //velocidade que o jogo vai rodar, deve ser sempre igual a ([VALOR PADRAO] - (250 * o nivel)) e será colocada dentro da função sleep
    int dinoPosY = 14, dinoCrouch = 0; //variaveis de posicao do dinossauro e variavel para determinar se o mesmo esta abaixado
    int pronto = 1, abaixado = 1; //variaveis para controlar se o dinossauro podera pular/se abaixar e se ele esta abaixado;
    int countVida = 0;

    menuInicial(&dinoPosY, &pronto, &velJogo, &abaixado, &vidas, &pontos, &nivel, &gameOver, &pausado, &countVida);

    //encerramento do programa
    gotoxy(1,21);
    return 0;
}
