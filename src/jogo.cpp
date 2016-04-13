/* 
 * Universidade Federal da Fronteira Sul
 *Arquivo: jogo.cpp -> Contém as funções para jogada com minimax e poda alpha-beta
 *                          e o cálculo das heurísticas
 * Rafael Hengen Ribeiro, Ricardo Parizotto
 */

#include "../include/defs.h"

#include <iostream>
#include <cstdio>
using namespace std;

bool moinho_feito(int * tab, int peca, int peca_orig, int jor)  {
  for(int i = 0; i < N_MOINHOS; i++) {
    int soma = 0;
    for(int j = 0; j < 3; j++)  {
      int k = moinho[i][j];
      if(k == peca)
        soma++;
      if(tab[k] == jor)
        soma++;
    }
    if(soma == 4)
      return true;
  }
  return false;
}

int heuristicas_jogador_fase2(int * tab, int jor, int profundidade) {
  int valor_moinho[N_MOINHOS];
  int heuristica_lixo = 0;
  int i, j, k, e, soma;
  int mpecas = 0, pecas_oponente = 0;
  // Conta as pecas de cada um
  for(int i = 0; i < TAM_TABULEIRO; i++)    {
    if(tab[i] == jor)
        mpecas++;
    else if(tab[i] != VAZIO)
        pecas_oponente++;
  }
  heuristica_lixo += (mpecas - pecas_oponente);
   /*verifica moinhos*/
  for(i = 0; i < N_MOINHOS; i++) {
    soma = 0;
    valor_moinho[i] = 0;
    for(int j = 0; j < 3; j++)  {
      k = moinho[i][j];
      if(tab[k] == jor)
        valor_moinho[i]+=5;
      else if(tab[k] != VAZIO)
        valor_moinho[i]-=5;
      else{
        valor_moinho[i]+=1;
        for(e = 0; e < 3; e++){
           int w = jogadas_validas[i][e];
          if(w > -1 && tab[w] == jor) 
            valor_moinho[i] += 3;
        }
      }
  }


    if(valor_moinho[i] > 14)
      valor_moinho[i] = 100;                        //vc foi tão profundo. Merece uma recompensa se chegou aqui na minimax.
    else if(valor_moinho[i] < -14)
      valor_moinho[i] = -100;                     // Heurística para impedir jogadas do inimigo
    heuristica_lixo+=valor_moinho[i];
  }
  return heuristica_lixo;
}

int heuristicas_jogador_fase1_fase3(int * tab, int jor, int profundidade){    //muito profundo HAHAHAH
  int valor_moinho[N_MOINHOS];
  int heuristica_lixo = 0;
  int mpecas = 0, pecas_oponente = 0;
  // Conta as pecas de cada um
  for(int i = 0; i < TAM_TABULEIRO; i++)    {
    if(tab[i] == jor)
        mpecas++;
    else if(tab[i] != VAZIO)
        pecas_oponente++;
  }
  heuristica_lixo += (mpecas - pecas_oponente);
  // Verificar moinhos
  for(int i = 0; i < N_MOINHOS; i++) {
    int soma = 0;
    valor_moinho[i] = 0;
    for(int j = 0; j < 3; j++)  {
      int k = moinho[i][j];
      if(tab[k] == jor)
        valor_moinho[i]+=3;
      else if(tab[k] != VAZIO)
        valor_moinho[i]-=5;
      else
        valor_moinho[i]+=5;
    }
    if(valor_moinho[i] > 14)
      valor_moinho[i] = 50 * profundidade;
    else if(valor_moinho[i] < -14)
      valor_moinho[i] = -50; // Heurística para impedir jogadas do inimigo
    heuristica_lixo+=valor_moinho[i];
  }


  return heuristica_lixo += profundidade;
}



/* 
    Função de jogada utilizando o algoritmo minimax
*/
int minimax(int * tab, Jogada *jogada, int profundidade, int max_prof, int jor, int fase){
    int maxmin = -infinite, temp, i, k, q, tab2[TAM_TABULEIRO], adv = proximoJogador(jor);
    Jogada jogada2;
    bool nodomax = !(profundidade % 2), remocao;

    if(profundidade == max_prof){ jogada->nnodes++; return ((fase != FASEINSERCAOPECAS)?(heuristicas_jogador_fase2(tab, (nodomax)? (jor):(adv), profundidade)):(heuristicas_jogador_fase1_fase3(tab, (nodomax)?(jor):(adv), profundidade)));}

    /*se estiver em uma folha e a fase não for inicial calcula a heuristica para a
     * segunda etapa do jogo. Caso contrário, a outra heurística (fase de inserir e de pular)
     * */

    if(!nodomax)
        maxmin = infinite;

    for (i = 0; i < TAM_TABULEIRO; i++){
        for (k = 0; k < 4; k++) {
            int j = jogadas_validas[i][k];
            if(j >= 0 && tab[j]==VAZIO && (tab[i] == jor)){
                for(q = 0; q < TAM_TABULEIRO; q++)tab2[q] = tab[q];//atualiza o tabuleiro para a futura jogada
                tab2[i] = VAZIO;
                tab2[j] = jor;
                if(moinho_feito(tab2, j, i, jor))   { //remove aleatoriamente
                    int tmp, adv_min = infinite;
                    int pmin = -1;
                    for(q = 0; q < TAM_TABULEIRO; q++){
                        if(tab2[q] == adv){
                           tab2[q] = VAZIO;
                           tmp = heuristicas_jogador_fase1_fase3(tab2, adv, profundidade);
                              if(tmp < adv_min)  {
                                  adv_min = tmp;
                                  pmin = q;
                              }
                            tab2[q] = adv;
                        }
                    }
                    jogada2.ret = pmin;
                }
                temp = minimax(tab2, jogada , profundidade + 1, max_prof, adv, fase);
                if(maxmin < temp && nodomax || temp < maxmin && !nodomax){
                    maxmin = temp;
                    jogada2.orig = i;
                    jogada2.dest = j;
                }
            }
        }
    }
    jogada->dest = jogada2.dest;
    jogada->orig = jogada2.orig;
    jogada->ret = jogada2.ret;

    return maxmin;
}

/* 
    Função de jogada utilizando a poda alfa-beta
*/
int poda_alpha_beta(int * tab, Jogada *jogada, int profundidade, int max_prof, int jor, int fase, int alpha, int beta){
    int maxmin = -infinite, temp, i, k, q, tab2[TAM_TABULEIRO], adv = proximoJogador(jor);
    Jogada jogada2;
    bool nodomax = !(profundidade % 2), remocao;

    if(profundidade == max_prof) { jogada->nnodes++;return ((fase != FASEINSERCAOPECAS)?(heuristicas_jogador_fase2(tab, (nodomax)? (jor):(adv), profundidade)):(heuristicas_jogador_fase1_fase3(tab, (nodomax)?(jor):(adv), profundidade)));}

    /*se estiver em uma folha e a fase não for inicial calcula a heuristica para a
     * segunda etapa do jogo. Caso contrário, a outra heurística (fase de inserir e de pular)
     * */

    if(!nodomax)
        maxmin = infinite;

    for (i = 0; i < TAM_TABULEIRO; i++){
        for (k = 0; k < 4; k++) {
            int j = jogadas_validas[i][k];
            if(j >= 0 && tab[j]==VAZIO && (tab[i] == jor)){
                for(q = 0; q < TAM_TABULEIRO; q++)tab2[q] = tab[q];//atualiza o tabuleiro para a futura jogada
                tab2[i] = VAZIO;
                tab2[j] = jor;
                if(moinho_feito(tab2, j, i, jor))   { //remove aleatoriamente
                    int tmp, adv_min = infinite;
                    int pmin = -1;
                    for(q = 0; q < TAM_TABULEIRO; q++){
                        if(tab2[q] == adv){
                           tab2[q] = VAZIO;
                           tmp = heuristicas_jogador_fase1_fase3(tab2, adv, profundidade);
                              if(tmp < adv_min)  {
                                  adv_min = tmp;
                                  pmin = q;
                              }
                            tab2[q] = adv;
                        }
                    }
                    jogada2.ret = pmin;
                }
                
                if(alpha >= beta){maxmin = (nodomax)?alpha:beta; goto retorno;}  
                 
                temp = poda_alpha_beta(tab2, jogada , profundidade + 1, max_prof, adv, fase, alpha, beta);
                    
                if(maxmin < temp && nodomax || temp < maxmin && !nodomax){
                    maxmin = temp;
                    jogada2.orig = i;
                    jogada2.dest = j;
                }
                if(!nodomax && beta < maxmin)
                    beta = maxmin;
                if(nodomax && alpha > maxmin)
                    alpha = maxmin;
            }
        }
    }
    retorno:
    jogada->dest = jogada2.dest;
    jogada->orig = jogada2.orig;
    jogada->ret = jogada2.ret;

    return maxmin;
}
