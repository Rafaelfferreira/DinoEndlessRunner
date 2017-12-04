#ifndef _GAMELIB_H_
#define _GAMELIB_H_

void rodajogo(int *dinoPosY, int *key, int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *existeTP, int *existeTG, int *existeAP, int *existeAG);
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel);
void interacao(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado);
void pulando(int *dinoPosY, int *velJogo, int *pronto);
void abaixando(int *dinoPosY, int *abaicado);
void levantando(int *dinoPosY, int *abaixado);
void movimentaTG(int *iniPosx, int iniPosY, int *existeTG, int *inimigo);

#endif // _GAMELIB_H_
