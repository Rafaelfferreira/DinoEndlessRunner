#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "gamelib.h"
#define DINOPOSX 12

//funcao a ser chamada quando sai do pause, inicia um jogo novo ou carrega outro jogo
void rodaJogo(int *dinoPosY, int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado)
{
    srand(time(NULL)); //inicializando a seed do rand
    char key;
    int FLPulando, tempoPulo = 0; //flag se o player esta pulando e var que determina quantos ciclos dura o pulo
    int ini1PosX = 90, ini1PosY, inimigo = 0, ini2PosX = 90, ini2PosY, ini1 = 0, ini2 = 0, levouDano = 0; //variaveis do inimigo, mudar iniposX para 100 e arrumar as bordas (mais pra frente no projeto)0

    while(*gameOver == 0 && *pausado == 0)
    {
        interacao(&key, dinoPosY, pronto, pausado, velJogo, abaixado, &FLPulando, &tempoPulo,vidas, pontos, nivel, &ini1, &ini2, &ini1PosX, &ini1PosY, &ini2PosX, &ini2PosY);

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
                movimentaTG(&ini1PosX, ini1PosY, &ini1);
            }
            else if(ini1 == 2)
            {
                movimentaAG(&ini1PosX, ini1PosY, &ini1);
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
            }
            else if(ini1 == 3)
            {
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
                movimentaAP(&ini1PosX, ini1PosY, &ini1);
            }
            else
            {
                ini1PosY = 14;
                levouDano = testaDano(*dinoPosY, ini1, ini1PosY, ini1PosX, *abaixado, tempoPulo);
                movimentaTP(&ini1PosX, ini1PosY, &ini1);
            }
        }

        if(levouDano == 1) //confere se o inimigo 1 deu dano
        {
            perdeuVida(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado, &levouDano);
            break; //sai do while caso gameOver vire 1 aqui;
        }

        //se o inimigo 2 estiver na tela atualiza sua posição
        if(ini2 != 0)
        {
            ini2 = 1;
            if(ini2 == 1)
            {
                ini2PosY = 14;
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
                movimentaTG(&ini2PosX, ini2PosY, &ini2);
            }
            else if(ini2 == 2)
            {
                movimentaAG(&ini2PosX, ini2PosY, &ini2);
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
            }
            else if(ini2 == 3)
            {
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
                movimentaAP(&ini2PosX, ini2PosY, &ini2);
            }
            else
            {
                ini2PosY = 14;
                levouDano = testaDano(*dinoPosY, ini2, ini2PosY, ini2PosX, *abaixado, tempoPulo);
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
            perdeuVida(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado, &levouDano);

        Sleep(300 - *velJogo);//controla a velocidade do jogo
    }

}
//Imprime na tela o cenário, a interface, e o dinnossauro em sua posição atual
//Essa função deve ser chamada quando o jogo for iniciado(tanto do começo quanto de um save) e quando o jogo sair do pause
////A função ainda deve ser alterada para ler se o dinossauro esta abaixado na hora de começar para imprimilo corretamente
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel)
{
    //Imprime a interface
    gotoxy(1,1);
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
void interacao(char *k, int dinoPosY, int *pronto, int *pausado, int velJogo, int *abaixado, int *FLPulando, int *tempoPulo, int *vidas, int *pontos, int *nivel, int *ini1, int *ini2, int *ini1PosX, int *ini1PosY, int *ini2PosX, int *ini2PosY)
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
        else if(*k == 'p')
            menuPause(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, pausado, ini1, ini2, ini1PosX, ini1PosY, ini2PosX, ini2PosY);
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

int testaDano(int dinoPosY,int nIni, int iniPosY, int iniPosX, int abaixado, int tempoPulo)
{
    int bateu = 0;
    if(abaixado == 0)
    {
        //TUDO UM TESTE
        //AVALIA QUE TIPO DE INIMIGO É E PROCESSA OS DADOS DE FORMA DIFERENTE
        switch(nIni)
        {
            case 1:
                //O if e o else a seguir testam se houve colisão quando o dinossauro esta na frente dos cactus
                if((DINOPOSX+3) == (iniPosX-1)) //testa se o dinossauro vai bater a cabeça nos "braços" dos cactus
                {
                    if(dinoPosY == iniPosY)
                    {
                        bateu = 1;
                    }
                }
                else if((DINOPOSX+2) == (iniPosX-1))
                {
                    if((iniPosY > dinoPosY && iniPosY < dinoPosY+4) || (iniPosY+1 > dinoPosY && iniPosY+1 < dinoPosY+4)) //testa se a frente do corpo do dino bate nos braços dos cactus
                    {
                        bateu = 1;
                    }
                }
                //esse if testa se o dinossauro cairá em cima dos cactus
                if(tempoPulo < 5 && tempoPulo > 0)
                {
                    if((DINOPOSX >= iniPosX && DINOPOSX < iniPosX+7) || (DINOPOSX+1 >= iniPosX && DINOPOSX+1 < iniPosX+7) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+7))
                    {
                        bateu = 1;
                    }
                }

            break;

            case 2:
                if((dinoPosY == iniPosY+2) || (dinoPosY == iniPosY+1) || (dinoPosY == iniPosY)) //testa se a cabeça esta na mesma altura do aerolito
                {
                    if((DINOPOSX+3 >= iniPosX && DINOPOSX+3 < iniPosX+7) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+7)) //testa se a cabeça esta na mesma posicao que o aerolito
                    {
                        bateu = 1;
                    }
                }
                else if(dinoPosY+1 == iniPosY || dinoPosY+1 == iniPosY+1 || iniPosX+1 == iniPosY+2 || dinoPosY+2 == iniPosY || dinoPosY+2 == iniPosY+1 || iniPosX+2 == iniPosY+2 || dinoPosY+3 == iniPosY || dinoPosY+3 == iniPosY+1 || iniPosX+3 == iniPosY+2)
                {
                    //if testa se a frente e a traseira do corpo do dinossauro estao encostando na nuvem
                    if((DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+6) || (DINOPOSX >= iniPosX && DINOPOSX < iniPosX+6) || (DINOPOSX >= iniPosX && DINOPOSX < iniPosX+6))
                    {
                        bateu = 1;
                    }
                }
            break;

            case 3:
                if((dinoPosY == iniPosY+1) || (dinoPosY == iniPosY)) //testa se a cabeça esta na mesma altura do aerolito
                {
                    if((DINOPOSX+3 >= iniPosX && DINOPOSX+3 < iniPosX+6) || (DINOPOSX+2 >= iniPosX && DINOPOSX+2 < iniPosX+6)) //testa se a cabeça esta na mesma posicao que o aerolito
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

            case 4:
                if((DINOPOSX+3) == (iniPosX)) //testa se o dinossauro vai bater a cabeça nos "braços" dos cactus
                {
                    if(dinoPosY == iniPosY)
                    {
                        bateu = 1;
                    }
                }
                else if((DINOPOSX+2) == (iniPosX))
                {
                    //testa se o corpo do dinossauro bate contra o cactus
                    if((iniPosY > dinoPosY && iniPosY < dinoPosY+4) || (iniPosY+1 > dinoPosY && iniPosY+1 < dinoPosY+4) || (iniPosY+2 > dinoPosY && iniPosY+2 < dinoPosY+4) || (iniPosY+3 > dinoPosY && iniPosY+3 < dinoPosY+4)) //testa se a frente do corpo do dino bate nos braços dos cactus
                    {
                        bateu = 1;
                    }
                }

                //esse if testa se o dinossauro cairá em cima dos cactus
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

void perdeuVida(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano)
{
    Sleep(250); //tempo para o jogador ver que ele morreu
    clrscr();
    *vidas = *vidas - 1;

    if(*vidas == 0)
    {
        morreu(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado, levouDano);
    }
    else
    {
        recomeca(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado, levouDano);
    }
}

//recomeca eh a funcao que exibe a tela de morte do jogo
void recomeca(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano)
{
    *dinoPosY = 14;
    *pronto = 1;
    *nivel = 1;
    *velJogo = *nivel * 250;
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

    while(kbhit()) //Limpa o buffer caso o jogador aperte espaço na tela de morte
            getch();

    imprimeCenario(dinoPosY, vidas, pontos, nivel);
    rodaJogo(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado);

}

void morreu(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano)
{
    char opcao;

    *gameOver = 1;

    gotoxy(48,7);
    printf("GAME OVER");
    gotoxy(44,12);
    printf("Selecione uma opcao: ");
    gotoxy(39,13);
    printf("1 - Voltar ao menu inicial");
    gotoxy(48,14);
    printf("2 - Sair");

    gotoxy(1,18);
    while(opcao != '1' && opcao != '2') //faz com que o programa nao aceite outras entradas se nao 1 ou 2
        opcao = getch();

    if(opcao == '2')
        exit(0); //termina a aplicação
    else if(opcao == '1')
        menuInicial(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado);
}

void menuInicial(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado)
{
    clrscr();

    *dinoPosY = 14;
    *pronto = 1;
    *nivel = 1;
    *vidas = 3;
    *velJogo = *nivel * 250;
    *abaixado = 0;
    *gameOver = 0;
    *pausado = 0;
    *gameOver = 0;

    char opcao;

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

    while(opcao != 'n' && opcao != 'c' && opcao != 't' && opcao != 'r') //faz com que o programa nao aceite outras entradas se nao 1 ou 2
        opcao = getch();

    if(opcao == 'n')
    {
        clrscr();
        imprimeCenario(dinoPosY,vidas,pontos,nivel);
        rodaJogo(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, gameOver, pausado);
    }

    else if(opcao == 'r')
        exit(0); //termina o programa e retorna 0;
}

void menuPause(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *pausado, int ini1, int ini2, int ini1PosX, int ini1PosY, int ini2PosX, int ini2PosY)
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
        menuInicial(dinoPosY, pronto, velJogo, abaixado, vidas, pontos, nivel, &gameOver, pausado);
    }

}
