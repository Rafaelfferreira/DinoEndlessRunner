#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //incluimos essa biblioteca para usarmos a função sleep, no UNIX essa função se encontra na biblioteca <unistd.h>
#include "gamelib.h"
#define DINOPOSX 12 //definida aqui pois a posicao do dinossauro no eixo X é sempre a mesma


int main()
{
    int gameOver = 0, pausado = 0;
    int vidas = 3, pontos = 0, nivel = 1;
    int velJogo = nivel * 250; //velocidade que o jogo vai rodar, deve ser sempre igual a (250 * o nivel) e será colocada dentro da função sleep
    int posX = 50,posY = 10; //variaveis de teste, as posicoes devem ficar dentro das estruturas
    int dinoPosY = 14, dinoCrouch = 0; //variaveis de posicao do dinossauro e variavel para determinar se o mesmo esta abaixado
    int pronto = 1, abaixado = 0; //variaveis para controlar se o dinossauro podera pular/se abaixar e se ele esta abaixado;
    char key; //tecla pressionada

    imprimeCenario(&dinoPosY,&vidas,&pontos,&nivel); //modificar a função para receber se o dinossauro está abaixado ou não

    while(gameOver == 0 && pausado == 0)
    {
        movimento(&key, &dinoPosY, &pronto, &velJogo, &abaixado);
    }

    //encerramento do programa
    gotoxy(1,21);
    return 0;
}
