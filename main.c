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
    int velJogo = nivel * 250; //velocidade que o jogo vai rodar, deve ser sempre igual a ([VALOR PADRAO] - (250 * o nivel)) e será colocada dentro da função sleep
    int dinoPosY = 14, dinoCrouch = 0; //variaveis de posicao do dinossauro e variavel para determinar se o mesmo esta abaixado
    int pronto = 1, abaixado = 1; //variaveis para controlar se o dinossauro podera pular/se abaixar e se ele esta abaixado;
    char key; //tecla pressionada
    //variaveis para verificar se existem inimigos (pra saber se os mesmos devem ser carregados)
    int existeTP = 0, existeTG = 0, existeAP = 0, existeAG = 0; //T = terraqueo, A = aereo, P=pequeno, G=grande

    imprimeCenario(&dinoPosY,&vidas,&pontos,&nivel); //nao precisa verificar se esta abaixado pq sempre que carregar o cenario o jogador nao estara pressionando a tecla de se abaixar
    rodaJogo(&dinoPosY, &key, &pronto, &velJogo, &abaixado, &vidas, &pontos, &nivel, &gameOver, &pausado, &existeTP, &existeTG, &existeAP, &existeAG);

    //encerramento do programa
    gotoxy(1,21);
    return 0;
}
