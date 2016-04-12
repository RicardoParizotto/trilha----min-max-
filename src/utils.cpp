#include <iostream>
#include <stdio.h>
#include "../include/utils.h"


char * textoaux=NULL;

Estatistica estat[2];


static int casasvizinhas[24][4] =
             { {-1, -1, 1, 9}, {0, -1, 2, 4}, {1, -1, -1, 14},
               {-1, -1, 4, 10}, {3, 1, 5, 7}, {4, -1, -1, 13},
               {-1, -1, 7, 11}, {6, 4, 8, -1}, {7, -1, -1, 12},
               {-1, 0, 10, 21}, {9, 3, 11, 18}, {10, 6, -1, 15},
               {-1, 8, 13, 17}, {12, 5, 14, 20}, {13, 2, -1, 23},
               {-1, 11, 16, -1}, {15, -1, 17, 19}, {16, 12, -1, -1},
               {-1, 10, 19, -1}, {18, 16, 20, 22}, {19, 13, -1, -1},
              {-1, 9, 22, -1}, {21, 19, 23, -1}, {22, 14, -1, -1}};
static int moinhos [16][3] =
             { {0,1,2}, {3,4,5}, {6,7,8}, {9,10,11}, {12,13,14}, {15,16,17}, {18,19,20}, {21,22,23}, // Horizontais
               {0,9,21}, {3,10,18}, {6,11,15}, {1,4,7}, {16, 19, 22}, {8, 12, 17}, {5, 13, 20}, {2,14,23} // verticais
             };


int getCarCasa(int val, int pos) {

    int c;
    if (val == VAZIO) {
        switch (pos) {
            case 0:
            case 3:
            case 6: c = VAZIOIMPCSE; break;
            case 2:
            case 5:
            case 8: c = VAZIOIMPCSD; break;
            case 15:
            case 18:
            case 21: c = VAZIOIMPCIE; break;
            case 17:
            case 20:
            case 23: c = VAZIOIMPCID; break;
            case 1:
            case 16: c = VAZIOIMPSUP; break;
            case 7:
            case 22: c = VAZIOIMPINF; break;
            case 11:
            case 14: c = VAZIOIMPDIR; break;
            case 9:
            case 12: c = VAZIOIMPESQ; break;
            case 4:
            case 10:
            case 13:
            case 19: c = VAZIOIMPCRUZ; break;
        }
        return c;
    } else if (val == JOGBRANCO)
        return JOGBRANCOIMP;
    else if (val == JOGPRETO)
        return JOGPRETOIMP;

    return -1;
}
int * novoTabuleiro() {
    int i = 0;

    int * tab = new int[TAMANHOTAB];
    for(i=0; i < TAMANHOTAB; i++) tab[i] = VAZIO;
    return tab;
}
void imprimeTabuleiro(int * tab) {

    if (tab == NULL)  {
        printf("%2d %c %c %c %c %d %c %c %c %c %d\n",0,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,1,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,2);
        printf(" %c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER);
        printf(" %c %c%2d %c %c%2d %c %c%2d %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,3,VAZIOIMPHOR,VAZIOIMPHOR,4,VAZIOIMPHOR,VAZIOIMPHOR,5,VAZIOIMPCAR,VAZIOIMPVER);
        printf(" %c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf(" %c %c %c %c%2d%2d%2d %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,6,7,8,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%2d %c%2d %c%2d %c%2d %c%2d %c%2d\n",9,VAZIOIMPHOR,10,VAZIOIMPHOR,11,VAZIOIMPCAR,12,VAZIOIMPHOR,13,VAZIOIMPHOR,14);
        printf(" %c %c %c %c%2d%2d%2d %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,15,16,17,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf(" %c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf(" %c %c%2d %c %c%2d %c %c%2d %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,18,VAZIOIMPHOR,VAZIOIMPHOR,19,VAZIOIMPHOR,VAZIOIMPHOR,20,VAZIOIMPCAR,VAZIOIMPVER);
        printf(" %c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%2d %c %c %c %c%2d %c %c %c %c%2d\n\n",21,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,22,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,23);
    } else {
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",getCarCasa(tab[0], 0),VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[1], 1),VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[2], 2));
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,getCarCasa(tab[3], 3),VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[4], 4),VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[5], 5),VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,getCarCasa(tab[6], 6),getCarCasa(tab[7], 7),getCarCasa(tab[8], 8),VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",getCarCasa(tab[9], 9),VAZIOIMPHOR,getCarCasa(tab[10], 10),VAZIOIMPHOR,getCarCasa(tab[11], 11),VAZIOIMPCAR,getCarCasa(tab[12], 12),VAZIOIMPHOR,getCarCasa(tab[13], 13),VAZIOIMPHOR,getCarCasa(tab[14], 14));
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,getCarCasa(tab[15], 15),getCarCasa(tab[16], 16),getCarCasa(tab[17], 17),VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,getCarCasa(tab[18], 18),VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[19], 19),VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[20], 20),VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n",VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPCAR,VAZIOIMPVER);
        printf("%c %c %c %c %c %c %c %c %c %c %c\n\n",getCarCasa(tab[21], 21),VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[22], 22),VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,VAZIOIMPHOR,getCarCasa(tab[23], 23));
    }
}
int primeiroJogador(int jog) {

    if (jog % 2 == 0)
        return JOGPRETO;
    return JOGBRANCO;

}
int faseAtual(int jog) {

    if (jog <= NUMEROPECAS*2 )
        return FASEINSERCAOPECAS;
    return FASEMOVIMENTACAOPECAS;

}
int proximoJogador(int jor) {

    if (jor == JOGPRETO)
        return JOGBRANCO;
    return JOGPRETO;
}
int proximaJogada(int jog) {
    return jog+1;
}
char * jogadorNome(int jor) {
    if (jor == JOGBRANCO)
        return "Branco";

    return "Preto";
}
char * textoJogada(Jogada jog) {
    if (textoaux == NULL)
        textoaux = new char[100];

    if (jog.orig == -1)
        sprintf(textoaux,"inclui peça na posição %d (%d nodos)", jog.dest, jog.nnodes);
    else if (vizinhos(jog.orig,jog.dest))
        sprintf(textoaux,"move peça da posição %d para a posição %d (%d nodos)", jog.orig, jog.dest, jog.nnodes);
    else
        sprintf(textoaux,"salta da posição %d para a posição %d  (%d nodos)", jog.orig, jog.dest, jog.nnodes);

    return textoaux;

}
bool indiceOk(int ind) {
    if (ind >= 0 && ind < TAMANHOTAB)
        return true;
    return false;
}
bool vizinhos(int pos1, int pos2) {

    bool vizOk = false;

    if (!(indiceOk(pos1) && indiceOk(pos2)))
        return false;

    int i;

    for(i=0;i < 4; i++)
        if (casasvizinhas[pos1][i] == pos2)
            return true;

    return false;
}

bool limpaJogada(Jogada &jog) {

    jog.dest = jog.orig = jog.ret = -1;
    jog.nnodes = jog.time = 0;;
    jog.moinho = false;
    return true;
}
bool jogadaVazia(Jogada &jog) {

    jog.dest = jog.orig = jog.ret = -1;
    jog.nnodes = jog.time = 0;
    jog.moinho = false;
    return true;
}
bool jogadaOk(int jor, int * tab, Jogada jog) {
    if (jog.orig == -1) {
        if(!indiceOk(jog.dest) || tab[jog.dest]!=VAZIO){ printf("1\n");        //ifdebug pra q KK
            return false;
        }
    } else { if (!indiceOk(jog.orig) || tab[jog.orig]!=jor ||
            !indiceOk(jog.dest) || tab[jog.dest]!=VAZIO){ printf("2\n");
                return false;
    }
            else if (!saltoOk(jor,tab) && !vizinhos(jog.orig, jog.dest)){ printf("3\n");
                return false;
            }
    }
    if (jog.moinho)
        if (!indiceOk(jog.ret) || tab[jog.ret] != proximoJogador(jor)){ printf("4\n");
            return false;
        }

    return true;
}
bool moinhoPrevisto(int jor, int * tab, Jogada jog) {

    int i, indh, indv;

    indh = indv = -1;

    for (i=0; i < 8 && indh == -1; i++)
        if (moinhos[i][0] == jog.dest || moinhos[i][1] == jog.dest || moinhos[i][2] == jog.dest)
                indh = i;
    for (i=8; i < 16 && indv == -1; i++)
        if (moinhos[i][0] == jog.dest || moinhos[i][1] == jog.dest || moinhos[i][2] == jog.dest)
                indv = i;
    if (indv == -1 || indh == -1)
        printf("Erro Inexperado!");

    if ((moinhos[indh][0] == jog.dest || tab[moinhos[indh][0]] == jor) &&
        (moinhos[indh][1] == jog.dest || tab[moinhos[indh][1]] == jor) &&
        (moinhos[indh][2] == jog.dest || tab[moinhos[indh][2]] == jor))
        return true;
    if ((moinhos[indv][0] == jog.dest || tab[moinhos[indv][0]] == jor) &&
        (moinhos[indv][1] == jog.dest || tab[moinhos[indv][1]] == jor) &&
        (moinhos[indv][2] == jog.dest || tab[moinhos[indv][2]] == jor))
        return true;
    return false;

}bool moinhoOk(int jor, int * tab, Jogada jog) {

    int i, indh, indv;

    indh = indv = -1;

    for (i=0; i < 8 && indh == -1; i++)
        if (moinhos[i][0] == jog.dest || moinhos[i][1] == jog.dest || moinhos[i][2] == jog.dest)
                indh = i;
    for (i=8; i < 16 && indv == -1; i++)
        if (moinhos[i][0] == jog.dest || moinhos[i][1] == jog.dest || moinhos[i][2] == jog.dest)
                indv = i;
    if (indv == -1 || indh == -1)
        printf("Erro Inexperado!");

    if (tab[moinhos[indh][0]] == jor && tab[moinhos[indh][1]] == jor &&tab[moinhos[indh][2]] == jor)
        return true;
    if (tab[moinhos[indv][0]] == jor && tab[moinhos[indv][1]] == jor &&tab[moinhos[indv][2]] == jor)
        return true;


    return false;

}
int escolheAdversario(int jor, int * tab){

    int ocupadas = 0;
    int i;
    int adv = proximoJogador(jor);

    for(i=0; i < TAMANHOTAB; i++)
        if (tab[i] == adv) ocupadas++;

    if (ocupadas) {
        int pos = randomValue(0,ocupadas-1);
        for(i=0; i < TAMANHOTAB; i++) {
            if (tab[i] == adv) {
                if (pos == 0) {
                    return i;
                }
                pos--;
            }
        }
    }
    return -1;

}
bool escolheJogadaInclusao(int jor, int * tab, Jogada & jog){

    limpaJogada(jog);

    int vagas = 0;
    int i;

    for(i=0; i < TAMANHOTAB; i++)
        if (tab[i] == VAZIO) vagas++;

    if (vagas) {
        int pos = randomValue(0,vagas-1);
        for(i=0; i < TAMANHOTAB; i++) {
            if (tab[i] == VAZIO) {
                if (pos == 0) {
                    jog.dest = i;
                    if (moinhoPrevisto(jor,tab,jog))
                        jog.ret = escolheAdversario(jor,tab);
                    return true;
                }
                pos--;
            }
        }
    }
    return false;

}
bool escolheJogadaMovimento(int jor, int * tab, Jogada & jog){

    int nro = 0;
    int i,j;

    limpaJogada(jog);

    Jogada novajog[TAMANHOTAB*4];

    for(i=0; i < TAMANHOTAB*4; i++)
        limpaJogada(novajog[i]);

    for(i=0; i < TAMANHOTAB; i++)
        if (tab[i] == jor)
            for (j=0; j < 4; j++)
                if (casasvizinhas[i][j] >= 0 && tab[casasvizinhas[i][j]] == VAZIO) {
                    novajog[nro].orig = i;
                    novajog[nro].dest = casasvizinhas[i][j];
                    nro++;
                }

    if (nro) {
        int pos = randomValue(0,nro-1);
        jog.orig = novajog[pos].orig;
        jog.dest = novajog[pos].dest;
        if (moinhoPrevisto(jor,tab,jog))
            jog.ret = escolheAdversario(jor,tab);
        return true;
    }
    return false;

}
bool escolheJogadaSalto(int jor, int * tab, Jogada & jog){

    int ocup = 0;
    int vagas = 0;
    int i;

    for(i=0; i < TAMANHOTAB; i++)
        if (tab[i] == jor)
            ocup++;
        else if (tab[i] == VAZIO)
            vagas++;

    if (ocup) {
        int pos = randomValue(0,ocup-1);
        for(i=0; i < TAMANHOTAB; i++) {
            if (tab[i] == jor) {
                if (pos == 0) {
                    jog.orig = i;
                    break;
               }
                pos--;
            }
        }
    }
    if (vagas) {
        int pos = randomValue(0,vagas-1);
        for(i=0; i < TAMANHOTAB; i++) {
            if (tab[i] == VAZIO) {
                if (pos == 0) {
                    jog.dest = i;
                    if (moinhoPrevisto(jor,tab,jog))
                        jog.ret = escolheAdversario(jor,tab);
                    return true;
                }
                pos--;
            }
        }
    }
    return false;
}

void efetuaJogada(int jor, int n, int * tab, Jogada jog){


    if (!jogadaOk(jor, tab, jog))
        return;

    bool remocao = false;

    if (jog.orig == -1) {
        tab[jog.dest]=jor;
    } else {
        tab[jog.orig] = VAZIO;
        tab[jog.dest] = jor;
    }
    if (moinhoOk(jor,tab, jog)) {
        if (tab[jog.ret]== proximoJogador(jor)) {
            tab[jog.ret] = VAZIO;
            remocao = true;
        }
    }

    imprimeTabuleiro(tab);
    printf("Jogada: %3d > Jogador %s %s\n", n, jogadorNome(jor), textoJogada(jog));
    if (remocao)
        printf("              Removida peca de jogador %s da posicao %d\n", jogadorNome(proximoJogador(jor)), jog.ret);

}
int nroPecas(int jor, int * tab) {

    int i;
    int pecas = 0;

    for(i=0; i < TAMANHOTAB; i++)
        if (tab[i] == jor) pecas++;
    return pecas;

}
bool fimJogo(int jor, int jog, int * tab, int fase) {

    if (fase == FASEINSERCAOPECAS || nroPecas(proximoJogador(jor),tab) > 2)
         return false;

    printf("\n\n Fim de Jogo: Jogador %s venceu jogador %s apos %d jogadas\n", jogadorNome(jor), jogadorNome(proximoJogador(jor)), jog);
    return true;

}
bool saltoOk(int jor, int * tab) {

    if (nroPecas(jor,tab) == 3)
         return true;
    return false;

}
void inicializaEstatisticas(int jor) {
    int i = jor - 1;
    estat[i].njog = estat[i].time = estat[i].nnodos = 0;
}
void atualizaEstatisticas(int jor, Jogada jog) {
    int i = jor - 1;
    estat[i].njog ++;
    estat[i].time += jog.time;
    estat[i].nnodos += jog.nnodes;
}
void imprimeEstatisticas(int jor) {
    int i = jor - 1;
    clock_t cps = CLOCKS_PER_SEC/1000;
    printf("\n\n Jogador: %s\n Jogadas: %d\n Tempo medio:   %10.6lf ms\n Media de Nodos:%10.6lf\n",jogadorNome(jor), estat[i].njog, (double)estat[i].time/estat[i].njog/cps, (double)estat[i].nnodos/estat[i].njog/cps);
}

