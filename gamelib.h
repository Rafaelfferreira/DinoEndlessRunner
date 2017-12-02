#ifndef _GAMELIB_H_
#define _GAMELIB_H_

void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel);
void movimento(char *k, int dinoPosY, int *pronto, int velJogo, int *abaixado);
void pulando(int *dinoPosY, int *velJogo, int *pronto);
void abaixando(int *dinoPosY, int *abaicado);
void levantando(int *dinoPosY, int *abaixado);

#endif // _GAMELIB_H_
