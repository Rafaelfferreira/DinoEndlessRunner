#ifndef _GAMELIB_H_
#define _GAMELIB_H_

void rodajogo(int *dinoPosY, int *key, int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *existeTP, int *existeTG, int *existeAP, int *existeAG);
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel);
void interacao(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado, int *FLPulando, int *tempoPulo);
void pulando(int *dinoPosY, int *pronto, int *tempoPulo, int *FLPulando);
void abaixando(int *dinoPosY, int *abaicado);
void levantando(int *dinoPosY, int *abaixado);
void movimentaTG(int *iniPosx, int iniPosY, int *existeTG, int *inimigo);
void movimentaTP(int *iniPosx, int iniPosY, int *existeTP, int *inimigo);
void movimentaAG(int *iniPosx, int iniPosY, int *existeAG, int *inimigo);
void movimentaAP(int *iniPosx, int iniPosY, int *existeAP, int *inimigo);

#endif // _GAMELIB_H_
