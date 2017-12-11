#ifndef _GAMELIB_H_
#define _GAMELIB_H_

void rodajogo(int *dinoPosY, int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado);
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel);
void interacao(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado, int *FLPulando, int *tempoPulo);
void pulando(int *dinoPosY, int *pronto, int *tempoPulo, int *FLPulando);
void abaixando(int *dinoPosY, int *abaicado);
void levantando(int *dinoPosY, int *abaixado);
void movimentaTG(int *iniPosx, int iniPosY, int *nIni);
void movimentaTP(int *iniPosx, int iniPosY, int *nIni);
void movimentaAG(int *iniPosx, int iniPosY, int *nIni);
void movimentaAP(int *iniPosx, int iniPosY, int *nIni);
int testaDano(int dinoPosY, int nIni, int iniPosY, int iniPosX, int abaixado, int tempoPulo);
void perdeuVida(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano);
void recomeca(int *dinoPosY,int *pronto, int *velJogo, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano);

#endif // _GAMELIB_H_
