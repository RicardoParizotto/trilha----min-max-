/*
    Universidade Federal da Fronteira Sul
    Rafael Hengen Ribeiro, Ricardo Parizotto
    Chamadas das funções principais
*/

#include <iostream>
#include <stdio.h>
#include "../include/trilha.h"
#include "../include/defs.h"

int jog=0;

bool jogaTrilhaGrupo01(int * tab, int fase, int jor, int alt, Jogada &prox) {
    if (fase == FASEINSERCAOPECAS)
        escolheJogadaInclusao(jor,tab, prox);
    else if (saltoOk(jor, tab))
        escolheJogadaSalto(jor,tab, prox);
    else{
        //minimax(tab, &prox, 0, alt, jor, fase);
        poda_alpha_beta(tab, &prox, 0, alt, jor, fase, -infinite, infinite);
    
        //escolheJogadaMovimento(jor,tab, prox);
    }
    return true;
}
bool jogaTrilhaGrupo02(int * tab, int fase, int jor, int alt, Jogada &prox) {

    if (fase == FASEINSERCAOPECAS)
        escolheJogadaInclusao(jor,tab, prox);
    else if (saltoOk(jor, tab))
        escolheJogadaSalto(jor,tab, prox);
    else
        escolheJogadaMovimento(jor,tab, prox);
    
    return true;
}

int main(int argc, char ** argv) {

    int nrandsel=0;
    int prof=4;
    bool Okrandsel = false, Okprof = false;

    if (argc > 1) {
//      nrandsel = getCommandLineParameter<int>(
//                  argc,
//                  argv,
//                  NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
//                  "-inicsel",
//                  Okrandsel
//              );
//        nrandsel = limitValue(nrandsel,0,TAMANHOTAB);
//      prof = getCommandLineParameter<int>(
//                  argc,
//                  argv,
//                  NAME_OPTIONALSPACE_EQUAL_OPTIONALSPACE_VALUE_CLPARAM,
//                  "-profbusca",
//                  Okprof
//              );
//        prof = limitValue(prof,2,999);
        nrandsel = atoi(argv[1]);
        prof = atoi(argv[2]);
    }

    int * tabuleiro = NULL;

    imprimeTabuleiro(NULL);


    tabuleiro = novoTabuleiro();

    clock_t tpre, tpos;
    Jogada prox;
    srand(time(NULL));
    jog = 1;
    inicializaEstatisticas(JOGBRANCO);
    inicializaEstatisticas(JOGPRETO);
    if (nrandsel > 0) {
        int n = nrandsel;
        while (n > 0) {
            tpre = clock();
	    printf("cu\n");
            escolheJogadaInclusao(JOGBRANCO, tabuleiro, prox);
            tpos = clock();
            efetuaJogada(JOGBRANCO, jog, tabuleiro, prox);
            prox.time = tpos - tpre;
            atualizaEstatisticas(JOGBRANCO,prox);
            n--;jog++;
            if (n > 0) {
                tpre = clock();
                escolheJogadaInclusao(JOGPRETO, tabuleiro, prox);
                tpos = clock();
                prox.time = tpos - tpre;
                efetuaJogada(JOGPRETO, jog, tabuleiro, prox);
                atualizaEstatisticas(JOGPRETO,prox);
                n--;jog++;
            }
       }
    }

    int jor, fase;
    bool fim = false;

    jor = primeiroJogador(jog);


    while (!fim) {
        fase = faseAtual(jog);
        tpre = clock();
        if(jor == JOGBRANCO)
            jogaTrilhaGrupo01(tabuleiro, fase, jor, prof, prox);
        else
            jogaTrilhaGrupo02(tabuleiro, fase, jor, prof, prox);

        tpos = clock();
        prox.time = tpos - tpre;
        if (jogadaOk(jor,tabuleiro, prox)) {
            efetuaJogada(jor, jog, tabuleiro, prox);
            atualizaEstatisticas(jor,prox);
        } else {
            printf("ERRO: Jogada Invalida do Jogador %s (%s)\n", jogadorNome(jor), textoJogada(prox));
            exit(EXIT_FAILURE);
        }

        fim = fimJogo(jor,jog,tabuleiro, fase);
        jog = proximaJogada(jog);
        jor = proximoJogador(jor);
    }

    imprimeEstatisticas(JOGBRANCO);
    imprimeEstatisticas(JOGPRETO);
    getchar();
    return 1;
}
