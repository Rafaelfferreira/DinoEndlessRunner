#ifndef _GAMELIB_H_
#define _GAMELIB_H_

typedef struct struct_pontuacao
{
    char nome[21];
    int score;
}str_pontuacao;

typedef struct struct_save
{
    char nome[25];
    int vidas, pontos, nivel, ini1, ini1PosX, ini1PosY, ini2, ini2PosX, ini2PosY, nSave;
}str_save;

void rodajogo(int *dinoPosY, int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *countVida, char nomeJogador[21], int loadGame, int *nSaves);
void imprimeCenario(int *dinoPosY, int *vidas, int *pontos, int *nivel);
//A funcao interacao precisa de tantas informacoes pois ela talvez precise referencias as posicoes dos inimigos e status do jogador a funcao de pause e de salvar jogo
void interacao(char *k, int dinoPosY, int *pronto, int *pausado, int *abaixado, int *FLPulando, int *tempoPulo, int *vidas, int *pontos, int *nivel, int *ini1, int *ini2, int *ini1PosX, int *ini1PosY, int *ini2PosX, int *ini2PosY, int *countVida, char nomeJogador[21], int *nSaves);
void pulando(int *dinoPosY, int *pronto, int *tempoPulo, int *FLPulando);
void abaixando(int *dinoPosY, int *abaicado);
void levantando(int *dinoPosY, int *abaixado);
void movimentaTG(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida);
void movimentaTP(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida);
void movimentaAG(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida);
void movimentaAP(int *iniPosx, int iniPosY, int *nIni, int *pontos, int *countNivel, int *countVida);
int testaDano(int dinoPosY, int nIni, int iniPosY, int iniPosX, int abaixado, int tempoPulo);
void perdeuVida(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano, int *countVida, char nomeJogador[21], int *nSaves);
void recomeca(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano, int *countVida, char nomeJogador[21], int *nSaves);
void morreu(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *levouDano, int *countVida, char nomeJogador[21]);
void menuInicial(int *dinoPosY,int *pronto,int *abaixado, int *vidas, int *pontos, int *nivel, int *gameOver, int *pausado, int *countVida);
void menuPause(int *dinoPosY,int *pronto, int *abaixado, int *vidas, int *pontos, int *nivel, int *pausado, int ini1, int ini2, int ini1PosX, int ini1PosY, int ini2PosX, int ini2PosY, int *countVida, char nomeJogador[21], int *nSaves);
void scores(char nomeJogador[21], int pontos);
void ranking(char *opcao);
void salvarJogo(int *vidas, int *pontos, int *nivel, int *ini1, int *ini1PosX, int *ini1PosY, int *ini2, int *ini2PosX, int *ini2PosY, char nomeJogador[21], int *nSaves);
int testaCarregaJogo();
int carregarJogo(char nomeJogador[21], int *vidas, int *pontos, int *nivel, int *ini1, int *ini1PosX,  int *ini1PosY, int *ini2, int *ini2PosX, int *ini2PosY, int *nSaves);

#endif // _GAMELIB_H_
