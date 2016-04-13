/*
 * Universidade Federal da Fronteira Sul
 * Definição das estruturas principais e protótipos das funções utilizadas 
 * Rafael Hengen Ribeiro, Ricardo Parizotto
 */

#ifndef DEFS_INCLUDED
#define DEFS_INCLUDED
#include <algorithm>
#include "../include/utils.h"
// Peça tabuleiro
#define VAZIO 0
#define JOGBRANCO 1
#define JOGPRETO 2

// Fase jogo
#define FASEINSERCAOPECAS 0
#define FASEMOVIMENTACAOPECAS 1

// Jogador
#define JOGBRANCO 1
#define JOGPRETO 2

#define MAXIMIZADOR true
#define MINIMIZADOR false

#define N_MOINHOS         16
#define MOVIMENTO_VALIDO  24
#define TAM_TABULEIRO     24
#define PROXIMO_JOGADORPFV (x) (x%2)?(1):(2)

#define infinite 100000

//Colunas: Esquerda, Direita, Cima, Baixo
//Linhas: posições do tabuleiro
const int jogadas_validas[MOVIMENTO_VALIDO][4] =
             { {-1, -1, 1, 9}, {0, -1, 2, 4}, {1, -1, -1, 14},
               {-1, -1, 4, 10}, {3, 1, 5, 7}, {4, -1, -1, 13},
               {-1, -1, 7, 11}, {6, 4, 8, -1}, {7, -1, -1, 12},
               {-1, 0, 10, 21}, {9, 3, 11, 18}, {10, 6, -1, 15},
               {-1, 8, 13, 17}, {12, 5, 14, 20}, {13, 2, -1, 23},
               {-1, 11, 16, -1}, {15, -1, 17, 19}, {16, 12, -1, -1},
               {-1, 10, 19, -1}, {18, 16, 20, 22}, {19, 13, -1, -1},
              {-1, 9, 22, -1}, {21, 19, 23, -1}, {22, 14, -1, -1}};

const int moinho[N_MOINHOS][3] =
  {{0,1,2},{0,9,21},{1,4,7},
  {2,14,23},{3,4,5},{3,10,18},
  {5,13,20},{6,7,8},{6,11,15},
  {8,12,17},{9,10,11},{12,13,14},
  {15,16,17},{16,19,22},{18,19,20},
  {21,22,23}};
  
/*
  tab é o tabuleiro: um vetor de inteiros de 24 posições
  fase é a fase do jogo: inserção de peças ou movimentação
  jor é o número do jogador
  alt é a altura máxima a percorrer na busca: Deve ser ≥ 2
*/
Jogada * jogaTrilhaMinMaxGrupo666(int *tab, int fase, int jor, int alt);
Jogada * jogaTrilhaAlfaBetaGrupo666(int *tab, int fase, int jor, int alt);

int heuristicas_jogador_fase1_fase3(int * tab, int jor, int profundidade);

int heuristicas_jogador_fase2(int * tab, int jor, int profundidade);

int minimax(int *tab,Jogada *jogada, int profundidade, int max_prof, int jor, int fase);

int poda_alpha_beta(int * tab, Jogada *jogada, int profundidade, int max_prof, int jor, int fase, int alpha, int beta);

int minimax_insercao(int * tab, Jogada *jogada, int profundidade, int max_prof, int jor, int jog);


#endif
