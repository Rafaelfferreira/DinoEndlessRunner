#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "gamelib.h"
#define DINOPOSX 12
#define TLINHA 30 //tamanho maximo de uma linha de arquivo

//funcao a ser chamada quando sai do pause, inicia um jogo novo ou carrega outro jogo
void rodaJogo(int *dinoPosY, int *pronto,int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *countVida, char nomeJogador[21], int loadGame, int *nSaves)
{
    srand(time(NULL)); //inicializando a seed do rand
    char key;
    int FLPulando, tempoPulo = 0; //flag se o player esta pulando e var que determina quantos ciclos dura o pulo
    int ini1PosX = 90, ini1PosY = 0, inimigo = 0, ini2PosX = 90, ini2PosY = 0, ini1 = 0, ini2 = 0, levouDano = 0; //variaveis do inimigo, mudar iniposX para 100 e arrumar as bordas (mais pra frente no projeto)
    int countNivel = 0; //conta ate 100 e 500 respectivamente e incrementa a devida variavel
    int carregou = 0;

    if(loadGame == 1) //se esta carregando um save ao inves de come�ar um jogo novo
    {
        carregou = carregarJogo(nomeJogador, vidas, pontos, nivel, &ini1, &ini1PosX, &ini1PosY, &ini2, &ini2PosX, &ini2PosY, nSaves);
        if(carregou == 0)
        {
            clrscr();
            printf("falha ao carregar o save");
            printf("\npressione ENTER para voltar ao menu");
            scanf(stdin);
            menuInicial(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, &gameOver, pausado, countVida);
        }
        else
        {
            gotoxy(43,9);
            printf("Jogo carregado com sucesso!");
            gotoxy(50,11);
            printf("Comecando em:");
            gotoxy(56,13);
            printf("3 ");
            Sleep(600);
            gotoxy(56,13);
            printf("2 ");
            Sleep(600);
            gotoxy(56,13);
            printf("1 ");
            Sleep(600);
            clrscr();
        }
    }

    imprimeCenario(dinoPosY,vidas,pontos,nivel);

    *countVida = 0;

    while(*gameOver == 0 && *pausado == 0)
        {
        interacao(&key, dinoPosY, pronto, pausado,  abaixado, &FLPulando, &tempoPulo,vidas, pontos, nivel, &ini1, &ini2, &ini1PosX, &ini1PosY, &ini2PosX, &ini2PosY, countVida, nomeJogador, nSaves);

        //Se o jogador estiver pulando, carrega um frame novo do pulo a cada ciclo
        if(FLPulando == 1)
            pulando(dinoPosY, pronto, &tempoPulo, &FLPulando);

        //Se o inimigo 1 estiver na tela atualiza sua posicao
        if(ini1 != 0)
        {
            if(ini1 == 1)
            {
                ini1PosY = 14;
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
                movimentaTG(&ini1PosX, ini1PosY, &ini1, pontos, &countNivel, countVida);
            }
            else if(ini1 == 2)
            {
                movimentaAG(&ini1PosX, ini1PosY, &ini1, pontos, &countNivel, countVida);
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
            }
            else if(ini1 == 3)
            {
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
                movimentaAP(&ini1PosX, ini1PosY, &ini1, pontos, &countNivel, countVida);
            }
            else
            {
                ini1PosY = 14;
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
                movimentaTP(&ini1PosX, ini1PosY, &ini1, pontos, &countNivel, countVida);
            }
        }

        if(levouDano == 1) //confere se o inimigo 1 deu dano
        {
            perdeuVida(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, &levouDano, countVida, nomeJogador, nSaves);
            break; //sai do while caso gameOver vire 1 aqui;
        }

        //se o inimigo 2 estiver na tela atualiza sua posi��o
        if(ini2 != 0)
        {
            ini2 = 1;
            if(ini2 == 1)
            {
                ini2PosY = 14;
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
                movimentaTG(&ini2PosX, ini2PosY, &ini2, pontos, &countNivel, countVida);
            }
            else if(ini2 == 2)
            {
                movimentaAG(&ini2PosX, ini2PosY, &ini2, pontos, &countNivel, countVida);
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
            }
            else if(ini2 == 3)
            {
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
                movimentaAP(&ini2PosX, ini2PosY, &ini2, pontos, &countNivel, countVida);
            }
            else
            {
                ini2PosY = 14;
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
                movimentaTP(&ini2PosX, ini2PosY, &ini2, pontos, &countNivel, countVida);
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
                        ini1PosY = rand() % (13 + 1 - 12) + 12;
                    }

                    else if(ini2 == 0)
                    {
                        ini2 = 3;
                        ini2PosY = rand() % (13 + 1 - 12) + 12;
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

        if(levouDano == 1) //confere se o inimigo 2 deu dano
            perdeuVida(dinoPosY, pronto, abaixado, vidas, pontos, nivel, gameOver, pausado, &levouDano, countVida, nomeJogador, nSaves);

        //imprime os pontos atuais na tela, fazer com que talvez demore mais para ganhar cada ponto, pois os ciclos estao mto rapidos
        *pontos = *pontos + 1;
        gotoxy(9,2);
        printf("%d", *pontos);

        countNivel++;
        if(countNivel >= 100)
        {
            *nivel = *nivel + 1;
            countNivel = 0;
            gotoxy(8,3);
            printf("%d", *nivel);
        }
        *countVida = *countVida + 1;
        if(*countVida >= 500)
        {
            *vidas = *vidas + 1;
            *countVida = 0;
            gotoxy(8,1);
            printf("%d", *vidas);
        }

        if(*nivel < 5)
            Sleep(70 - (*nivel * 10));//controla a velocidade do jogo
        else
            Sleep(70 - 40 - ((*nivel-4) * 5));
    }

}
//Imprime na tela o cen�rio, a interface, e o dinnossauro em sua posi��o atual
//Essa fun��o deve ser chamada quando o jogo for iniciado(tanto do come�o quanto de um save) e quando o jogo sair do pause
////A fun��o ainda deve ser alterada para ler se o dinossauro esta abaixado na hora de come�ar para imprimilo corretamente
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel)
{
    //Imprime a interface
    gotoxy(1,1);
    printf("Vidas: %d", *vidas);
    printf("\nPontos: %d", *pontos);
    printf("\nNivel: %d", *nivel);

    //imprime o ch�o
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

//funcao que avalia que tipo de movimento � e chama a fun�ao adequada para executalo
//aqui passamos as variaveis dinoPosY e velJogo como um endere�o pois as fun�oes que executam os movimentos precisam usa-la como um ponteiro
void interacao(char *k, int dinoPosY, int *pronto, int *pausado, int *abaixado, int *FLPulando, int *tempoPulo, int *vidas, int *pontos, int *nivel, int *ini1, int *ini2, int *ini1PosX, int *ini1PosY, int *ini2PosX, int *ini2PosY, int *countVida, char nomeJogador[21], int *nSaves)
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
        else if(*k == 'c' || *k == 80) //80 � o numero que representa a seta para baixo
        {
            abaixando(dinoPosY, abaixado);
        }
        else if(*k == 'p')
            menuPause(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, pausado, ini1, ini2, ini1PosX, ini1PosY, ini2PosX, ini2PosY, countVida, nomeJogador, nSaves);
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

//As duas fun�oes abaixo apagam o dinossauro atual, imprimeme ele ou abaixado ou levantado e mudam a flag "abaixado"
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

void movimentaTG(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida)
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
        *pontos = *pontos + 10;
        *countNivel = *countNivel + 10;
        *countVida = *countVida + 10;
    }
}

void movimentaTP(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida)
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
        *pontos = *pontos + 10;
        *countNivel = *countNivel + 10;
        *countVida = *countVida + 10;
    }
}

void movimentaAG(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida)
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
        *pontos = *pontos + 10;
        *countNivel = *countNivel + 10;
        *countVida = *countVida + 10;
    }
}

void movimentaAP(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida)
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
        *pontos = *pontos + 10;
        *countNivel = *countNivel + 10;
        *countVida = *countVida + 10;
    }
}

int testaDano(int dinoPosY,int nIni, int iniPosY, int iniPosX, int abaixado, int tempoPulo)
{
    int bateu = 0;
    if(abaixado == 0)
    {
        //avalia qual tipo de inimigo � e avalia se deu dano
        switch(nIni)
        {
            case 1: //Terrestre Grande
                //O if e o else a seguir testam se houve colis�o quando o dinossauro esta na frente dos cactus
                if((DINOPOSX+3) == (iniPosX-1)) //testa se o dinossauro vai bater a cabe�a nos "bra�os" dos cactus
                {
                    if(dinoPosY == iniPosY)
                    {
                        bateu = 1;
                    }
                }
                else if((DINOPOSX+2) == (iniPosX-1))
                {
                    if((iniPosY > dinoPosY && iniPosY < dinoPosY+4) || (iniPosY+1 > dinoPosY && iniPosY+1 < dinoPosY+4)) //testa se a frente do corpo do dino bate nos bra�os dos cactus
                    {
                        bateu = 1;
                    }
                }
                //esse if testa se o dinossauro cair� em cima dos cactus
                if(tempoPulo < 5 && tempoPulo > 0)
                {
                    if((DINOPOSX >= iniPosX && DINOPOSX < iniPosX+7) || (DINOPOSX+1 >= iniPosX && DINOPOSX+1 < iniPosX+7) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+7))
                    {
                        bateu = 1;
                    }
                }

            break;

            case 2://Aereo Grande
                if((dinoPosY == iniPosY+2) || (dinoPosY == iniPosY+1) || (dinoPosY == iniPosY)) //testa se a cabe�a esta na mesma altura do aerolito
                {
                    if((DINOPOSX+3 >= iniPosX && DINOPOSX+3 < iniPosX+7) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+7)) //testa se a cabe�a esta na mesma posicao que o aerolito
                    {
                        bateu = 1;
                    }
                }
                else if(dinoPosY+1 == iniPosY || dinoPosY+1 == iniPosY+1 || dinoPosY+1 == iniPosY+2 || dinoPosY+2 == iniPosY || dinoPosY+2 == iniPosY+1 || dinoPosY+2 == iniPosY+2 || dinoPosY+3 == iniPosY || dinoPosY+3 == iniPosY+1 || dinoPosY+3 == iniPosY+2)
                {
                    //if testa se a frente e a traseira do corpo do dinossauro estao encostando na nuvem
                    if((DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+6) || (DINOPOSX >= iniPosX && DINOPOSX < iniPosX+6) || (DINOPOSX >= iniPosX && DINOPOSX < iniPosX+6))
                    {
                        bateu = 1;
                    }
                }
            break;

            case 3: //Aereo Pequeno
                if((dinoPosY == iniPosY+1) || (dinoPosY == iniPosY)) //testa se a cabe�a esta na mesma altura do aerolito
                {
                    if((DINOPOSX+3 >= iniPosX && DINOPOSX+3 < iniPosX+6) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+6)) //testa se a cabe�a esta na mesma posicao que o aerolito
                    {
                        bateu = 1;
                    }
                }
                //else abaixo testa se o corpo do dinossauro esta na mesma altura do aerolito
                else if((dinoPosY+1 == iniPosY+1) || (dinoPosY+1 == iniPosY) || (dinoPosY+2 == iniPosY+1) || (dinoPosY+2 == iniPosY) || (dinoPosY+3 == iniPosY+1) || (dinoPosY+3 == iniPosY))
                {
                    //if testa se a frente e a traseira do corpo do dinossauro estao encostando na nuvem
                    if((DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+6) || (DINOPOSX+1 >= iniPosX && DINOPOSX < iniPosX+6) || (DINOPOSX >= iniPosX && DINOPOSX < iniPosX+6))
                    {
                        bateu = 1;
                    }
                }
            break;

            case 4: //Terrestre pequeno
                if((DINOPOSX+3) == (iniPosX)) //testa se o dinossauro vai bater a cabe�a nos "bra�os" dos cactus
                {
                    if(dinoPosY == iniPosY)
                    {
                        bateu = 1;
                    }
                }
                else if((DINOPOSX+2) == (iniPosX))
                {
                    //testa se o corpo do dinossauro bate contra o cactus
                    if((iniPosY > dinoPosY && iniPosY < dinoPosY+4) || (iniPosY+1 > dinoPosY && iniPosY+1 < dinoPosY+4) || (iniPosY+2 > dinoPosY && iniPosY+2 < dinoPosY+4) || (iniPosY+3 > dinoPosY && iniPosY+3 < dinoPosY+4)) //testa se a frente do corpo do dino bate nos bra�os dos cactus
                    {
                        bateu = 1;
                    }
                }

                //esse if testa se o dinossauro cair� em cima dos cactus
                if(tempoPulo < 5 && tempoPulo > 0)
                {
                    if((DINOPOSX >= iniPosX && DINOPOSX < iniPosX+2) || (DINOPOSX+1 >= iniPosX && DINOPOSX+1 < iniPosX+2) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+2))
                    {
                        bateu = 1;
                    }
                }

            break;


        }
    }
    else if (abaixado == 1)
    {
        switch(nIni)
        {
            case 1:
                if(DINOPOSX+6 == iniPosX+2) //testa se a cabeca do dinossauro bate no corpo dos cactus
                {
                    bateu = 1;
                }
                break;

            case 4:
                if(DINOPOSX+4 == iniPosX)
                {
                    bateu = 1;
                }
                break;

        }
    }
    return bateu;

}

void perdeuVida(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano, int *countVida, char nomeJogador[21], int *nSaves)
{
    Sleep(250); //tempo para o jogador ver que ele morreu
    clrscr();
    *vidas = *vidas - 1;

    if(*vidas == 0)
    {
        morreu(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, levouDano, countVida, nomeJogador);
    }
    else
    {
        recomeca(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, levouDano, countVida, nomeJogador, nSaves);
    }
}

//recomeca eh a funcao que exibe a tela de morte do jogo
void recomeca(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano, int *countVida, char nomeJogador[21], int *nSaves)
{
    int existeSave = 0; //flag que serve para mostrar que nao esta carregando um jogo salvo

    *dinoPosY = 14;
    *pronto = 1;
    *nivel = 1;
    *abaixado = 0;
    *gameOver = 0;
    *pausado = 0;
    *levouDano = 0;

    gotoxy(48,10);
    printf("Vidas Restantes: %d ", *vidas);
    Sleep(1000);
    //Imprime um contador para quando o jogo voltara
    gotoxy(50,12);
    printf("recomecando em:");
    gotoxy(56,13);
    printf("3 ");
    Sleep(600);
    gotoxy(56,13);
    printf("2 ");
    Sleep(600);
    gotoxy(56,13);
    printf("1 ");
    Sleep(600);

    gotoxy(48,10);
    printf("                   ");
    gotoxy(50,12);
    printf("               ");
    gotoxy(56,13);
    printf(" ");

    while(kbhit()) //Limpa o buffer caso o jogador aperte espa�o na tela de morte
            getch();

    imprimeCenario(dinoPosY, vidas, pontos, nivel);
    rodaJogo(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, countVida, nomeJogador, existeSave, nSaves);

}

void morreu(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano, int *countVida, char nomeJogador[21])
{
    char opcao;

    *gameOver = 1;

    gotoxy(48,7);
    printf("GAME OVER");
    gotoxy(48,11);
    printf("Score: %d", *pontos);
    gotoxy(44,13);
    printf("Selecione uma opcao: ");
    gotoxy(39,14);
    printf("1 - Voltar ao menu inicial");
    gotoxy(48,15);
    printf("2 - Sair");

    scores(nomeJogador, *pontos);

    gotoxy(1,18);
    while(opcao != '1' && opcao != '2') //faz com que o programa nao aceite outras entradas se nao 1 ou 2
        opcao = getch();

    if(opcao == '2')
        exit(0); //termina a aplica��o
    else if(opcao == '1')
        menuInicial(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, countVida);

}

void menuInicial(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *countVida)
{
    int saiuDoJogo = 0, existeSave = 0, nSaves = 0;
    clrscr();
    fflush(stdin);

    *dinoPosY = 14;
    *pontos = 0;
    *pronto = 1;
    *nivel = 1;
    *vidas = 3;
    *abaixado = 0;
    *gameOver = 0;
    *pausado = 0;
    *gameOver = 0;

    char opcao = ' ';
    char nomeJogador[21] = " ";

    gotoxy(47,7);
    printf("T-REX RUNNER");
    gotoxy(45, 11);
    printf("(n) - Novo Jogo");
    gotoxy(43,12);
    printf("(c) - Carregar Jogo");
    gotoxy(46,13);
    printf("(t) - Top 10");
    gotoxy(47,14);
    printf("(r) - Sair");
    gotoxy(1,20);

    while(saiuDoJogo == 0)
    {
        while(opcao != 'n' && opcao != 'c' && opcao != 't' && opcao != 'r') //faz com que o programa nao aceite outras entradas se nao 1 ou 2
        opcao = getch();

            if(opcao == 'n')
            {
                clrscr();
                gotoxy(35,7);
                printf("Insira o nome do jogador: ");
                gets(nomeJogador);

                clrscr();
                rodaJogo(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, countVida, nomeJogador, existeSave, &nSaves);
            }
            else if(opcao == 't')
            {
                ranking(&opcao);
                menuInicial(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, countVida);
            }
            else if(opcao == 'c')
            {
                existeSave = 1;
                rodaJogo(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, gameOver, pausado, countVida, nomeJogador, existeSave, &nSaves);
            }
            else if(opcao == 'r')
            {
                saiuDoJogo = 1;
                exit(0);
            }
        }
}

void menuPause(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *pausado, int ini1, int ini2, int ini1PosX, int ini1PosY, int ini2PosX, int ini2PosY, int *countVida, char nomeJogador[21], int *nSaves)
{
    clrscr();
    char opcao;

    gotoxy(47,7);
    printf("PAUSADO");
    gotoxy(42, 11);
    printf("(s) - Salvar Jogo");
    gotoxy(40,12);
    printf("(r) - voltar ao menu");

    while(opcao != 's' && opcao != 'r' && opcao != 'p') //faz com que o programa nao aceite outras entradas se nao 1 ou 2
        opcao = getch();

    if(opcao == 'p')
    {
        clrscr();
        imprimeCenario(dinoPosY,vidas,pontos,nivel);
    }
    else if(opcao == 'r')
    {
        int gameOver = 0;
        scores(nomeJogador, *pontos);
        menuInicial(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, &gameOver, pausado, countVida);
    }
    else if(opcao == 's')
    {
        salvarJogo(vidas, pontos, nivel, ini1, ini1PosX, ini1PosY, ini2, ini2PosX, ini2PosY, nomeJogador, nSaves);
        menuPause(dinoPosY, pronto,  abaixado, vidas, pontos, nivel, pausado, ini1, ini2, ini1PosX, ini1PosY, ini2PosX, ini2PosY, countVida, nomeJogador, nSaves);
    }

}

void scores(char nomeJogador[21], int pontos)
{
    FILE *arqScores, *arqRank;
    str_pontuacao varbuffer, temporario[10], auxiliar; //temporario � onde armazenaremos o ranking para ordena-lo e auxiliar � a variavel que usaremos para fazer o bubble sort
    char ch; //variavel usada para procurar quantos '\n' tem no ranking (e consequentemente, quantos jogadores)
    char linha[TLINHA], linhaNova[TLINHA];
    int erro = 0, escreveu = 0, cont = 0, i, j;

    strcpy(varbuffer.nome, nomeJogador);
    varbuffer.score = pontos;

    //adiciona o score ao arquivo scores.txt
    arqScores = fopen("scores.txt", "a");
    if(arqScores == NULL)
    {
        clrscr();
        gotoxy(45,10);
        printf("Erro no arquivo scores.txt");
    }
    else
        fprintf(arqScores, "%s,%d\n", varbuffer.nome, varbuffer.score);

    fclose(arqScores);

    //monta o arquivo do ranking de melhores scores
    arqRank = fopen("hiscore.txt", "r"); //abre em modo de leitura para ver se ja tem 10 entradas
    if(arqRank == NULL)
    {
        arqRank = fopen("hiscore.txt", "w"); //abre em modo de escrita caso nao tenha conseguido abrir no modo de leitura (pois nao existia o arquivo)
        if(arqRank == NULL)
        {
            clrscr();
            gotoxy(45,10);
            printf("Erro no arquivo hiscore.txt");
            erro = 1;
        }
        else
        {
            fprintf(arqRank, "%s,%d\n", varbuffer.nome, varbuffer.score); //escreve na primeira linha do arquivo
            escreveu = 1;
            fclose(arqRank);
        }
    }

    fclose(arqRank);


    if(erro == 0 && escreveu == 0)
    {
        arqRank = fopen("hiscore.txt", "a+");

            //pega ate 10 items do ranking e salva no array de pontuacoes "temporario"
            while(!feof(arqRank) && cont < 10)
            {
                if(fgets(linha,TLINHA,arqRank)!=NULL) //le uma linha do arquivo
                {
                    strcpy(temporario[cont].nome,strtok(linha,","));
                    temporario[cont].score = atoi(strtok(NULL,",")); //copia a linha lida para a variavel temporaria
                    cont++;
                }
            }
            //se a nova pontuacao for maior do que a ultima no ranking, coloca a nova pontuacao em ultimo
            if(cont == 10 && varbuffer.score > temporario[cont-1].score)
            {
                strcpy(temporario[cont-1].nome, varbuffer.nome);
                temporario[cont-1].score = varbuffer.score;
            }
            else if(cont < 10) //se tem menos de 10 jogadores no ranking coloca a nova pontuacao em ultimo
            {
                strcpy(temporario[cont].nome, varbuffer.nome);
                temporario[cont].score = varbuffer.score;
                cont++;
            }

            //ordena o array temporario
            for(j=0;j<cont;j++)
            {
                for(i=0;i<(cont-1);i++)
                {
                    if(temporario[i].score < temporario[i+1].score)
                    {
                        strcpy(auxiliar.nome,temporario[i].nome);
                        auxiliar.score = temporario[i].score;

                        strcpy(temporario[i].nome, temporario[i+1].nome);
                        temporario[i].score = temporario[i+1].score;

                        strcpy(temporario[i+1].nome, auxiliar.nome);
                        temporario[i+1].score = auxiliar.score;
                    }
                }
            }

            //cria o novo ranking
            arqRank = fopen("hiscore.txt", "w");
            if(arqRank == NULL)
            {
                clrscr();
                gotoxy(45,10);
                printf("Erro no arquivo hiscore.txt");
            }
            else
            {
                for(i=0;i<cont;i++)
                    fprintf(arqRank, "%s,%d\n", temporario[i].nome, temporario[i].score); //escreve na primeira linha do arquivo
            }
    }
    fclose(arqRank);
}

void ranking(char *opcao)
{
    FILE *arqRank;
    str_pontuacao top10[10];
    char linha[TLINHA], key;
    int contador = 0, i, posY = 7, posXScore = 83, posXNome = 20;

    clrscr();

    arqRank = fopen("hiscore.txt", "r");
    if(arqRank == NULL)
    {
        gotoxy(35,9);
        printf("Nao existem pontuacoes cadastradas no ranking");
        gotoxy(40,10);
        printf("Pressione enter para voltar ao menu");
        scanf(stdin);
    }
    else
    {
        while(!feof(arqRank))
        {
            //le todas as linhas dentro do ranking
            if(fgets(linha, TLINHA, arqRank) != NULL)
            {
                strcpy(top10[contador].nome, strtok(linha,","));
                top10[contador].score = atoi(strtok(NULL, ","));
                contador++;
            }
        }

        gotoxy(48,2);
        printf("TOP 10 SCORES");
        gotoxy(20,4);
        printf("JOGADOR");
        gotoxy(80,4);
        printf("PONTUACAO");

        //imprime todos os nomes no ranking
        for(i = 0;i<contador;i++)
        {
            gotoxy(posXNome, posY);
            printf("%d. %s", (i+1), top10[i].nome);
            gotoxy(posXScore, posY);
            printf("%d", top10[i].score);
            posY += 2;
        }

        gotoxy(38,posY + 2);
        printf("pressione \"r\" para voltar ao menu\n");

        while(key != 'r')
            key = getch();
    }

    *opcao = 'q';
    fclose(arqRank);
}

salvarJogo(int *vidas, int *pontos, int *nivel, int *ini1, int *ini1PosX, int *ini1PosY, int *ini2, int *ini2PosX, int *ini2PosY, char nomeJogador[21], int *nSaves)
{
    FILE *arq1;
    str_save arquivoSave;
    char nomeArquivo[25];

    *nSaves = *nSaves+1;
    sprintf(nomeArquivo, "%s%d.bin", nomeJogador, *nSaves); //faz com que nomeArquivo receba o valor NomeJogador + nSaves  .txt

    strcpy(arquivoSave.nome, nomeJogador);
    arquivoSave.vidas = *vidas;
    arquivoSave.pontos = *pontos;
    arquivoSave.nivel = *nivel;
    arquivoSave.ini1 = *ini1;
    arquivoSave.ini1PosX = *ini1PosX;
    arquivoSave.ini1PosY = *ini1PosY;
    arquivoSave.ini2 = *ini2;
    arquivoSave.ini2PosX = *ini2PosX;
    arquivoSave.ini2PosY = *ini2PosY;
    arquivoSave.nSave = *nSaves;


    arq1 = fopen(nomeArquivo,"wb");
    if(arq1 == NULL)
        printf("Erro ao salvar o jogo");
    else
    {
        if(fwrite(&arquivoSave, sizeof(str_save), 1, arq1) != 1)
            printf("erro no save");
    }

    fclose(arq1);

    gotoxy(43,9);
    printf("salvando jogo...");
    Sleep(600);
}

int carregarJogo(char nomeJogador[21], int *vidas, int *pontos, int *nivel, int *ini1, int *ini1PosX, int *ini1PosY, int *ini2, int *ini2PosX, int *ini2PosY, int *nSaves)
{
    FILE *arq1;
    char nomeArquivo[25], key;
    str_save saveFile;
    int ret = 1;

    clrscr();
    gotoxy(35,7);
    printf("Digite o nome do arquivo que deseja carregar: ");
    gotoxy(50,8);
    gets(nomeArquivo);

    arq1 = fopen(nomeArquivo, "rb");
    if(arq1 == NULL)
    {
        ret = 0;
    }
    else
    {
        fread(&saveFile, sizeof(str_save), 1, arq1);
        strcpy(nomeJogador, saveFile.nome);
        *vidas = saveFile.vidas;
        *pontos = saveFile.pontos;
        *nivel = saveFile.nivel;
        *ini1 = saveFile.ini1;
        *ini1PosX = saveFile.ini1PosX;
        *ini1PosY = saveFile.ini1PosY;
        *ini2 = saveFile.ini2;
        *ini2PosX = saveFile.ini2PosX;
        *ini2PosY = saveFile.ini2PosY;
        *nSaves = saveFile.nSave;
    }

    clrscr();
    fclose(arq1);
    return ret;
}
