#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <limits.h>
#include <stdlib.h>

#include <algorithm>
//#include "BCommandLine.h"

#define DEFAULTINTLIMITLOWER                     INT_MIN
#define DEFAULTINTLIMITUPPER                     INT_MAX


#define VAZIO                          0
#define JOGBRANCO                      1
#define JOGPRETO                       2
#define FASEINSERCAOPECAS              0
#define FASEMOVIMENTACAOPECAS          1
#define VAZIOIMPCSE    '.'
#define VAZIOIMPCSD    '.'
#define VAZIOIMPCIE    '.'
#define VAZIOIMPCID    '.'
#define VAZIOIMPSUP    '.'
#define VAZIOIMPINF    '.'
#define VAZIOIMPESQ    '.'
#define VAZIOIMPDIR    '.'
#define VAZIOIMPCRUZ   '.'
#define VAZIOIMPVER    '|'
#define VAZIOIMPHOR    '_'
#define VAZIOIMPCAR    32
#define JOGBRANCOIMP   'x'
#define JOGPRETOIMP    'o'
#define TAMANHOTAB     24
#define NUMEROPECAS     9




//template <class T>  T min(T x, T y) { return (x < y ? x : y);};

inline int randomValue(int lower = DEFAULTINTLIMITLOWER, int upper = DEFAULTINTLIMITUPPER)
                {return (std::min(lower + (int)((float)rand() / RAND_MAX * (upper - lower + 1)),upper));};

typedef struct {
  int orig, dest, ret;
  bool moinho;
  int nnodes;
  clock_t time;
} Jogada;
typedef struct {
  int njog, nnodos;
  clock_t time;
} Estatistica;

bool escolheJogadaInclusao(int jor, int * tab, Jogada & jog);
bool escolheJogadaMovimento(int jor, int * tab, Jogada & jog);
bool escolheJogadaSalto(int jor, int * tab, Jogada & jog);
void efetuaJogada(int jor, int n, int * tab, Jogada jog);


int escolheAdversario(int jor, int * tab);
int * novoTabuleiro();
void imprimeTabuleiro(int* = NULL);
int primeiroJogador(int jog);
int proximoJogador(int jor);
int proximaJogada(int jog);
int faseAtual(int jog);
bool jogadaOk(int jor, int * tab, Jogada jog);
bool indiceOk(int pos);
char * jogadorNome(int jor);
char * textoJogada(Jogada jog);
bool moinhoOk(int jor, int * tab, Jogada jog);
bool moinhoPrevisto(int jor, int * tab, Jogada jog);
bool limpaJogada(Jogada &jog);
bool jogadaVazia(Jogada & jog);
int nroPecas(int jor, int * tab);
bool fimJogo(int jor, int jog, int * tab, int);
bool saltoOk(int jor, int * tab);
bool vizinhos(int pos1, int pos2);
void inicializaEstatisticas(int jor);
void atualizaEstatisticas(int jor, Jogada jog);
void imprimeEstatisticas(int jor);
bool moinho_feito(int * tab, int peca, int peca_orig, int jor);


#endif // UTILS_H_INCLUDED
