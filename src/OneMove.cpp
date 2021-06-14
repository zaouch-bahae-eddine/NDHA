#include<OneMove.h>
#include<ManageBlock.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int*** OneMove(int N, int m, int*** B, int* solution, int* L, int* U, int*** BijIndex){
    int sizeI = 1, *sizeJ = NULL, sizeZ = N;
    //une copie pour la solution acctuelle
    int* solutionInitial = copyArray(solution, N);

    //ordoner les élements par groupe dans un ordre croisant
    int* refs = orderSolution(solutionInitial, N);

    int* G = (int*) malloc(sizeof(int) * m);
    int i, j, pos = 0, nbEinG = 0, acctu;
    acctu = solutionInitial[0];
    //Regrouper le nb d'elements dans chaque groupe dans le tableau G
    for(i = 0; i < m; i++){
        for(j = pos; j < N; j++){
            if(acctu == solutionInitial[j]){
                pos++;
                nbEinG++;
            }
        }
        acctu = solutionInitial[pos];
        G[i] = nbEinG;
        nbEinG = 0;
    }

    //Initialisation du tableau des indices (les i, les j) pour les Block B1
    *BijIndex = (int**) malloc(sizeof(int*) * (m * (m - 1)));
    for(i = 0; i < m * (m - 1); i++){
        *(*BijIndex + i) = (int*) malloc(sizeof(int) * 2);
    }

    int gsAcctu = -1, gdAcctu = -1, k = 0;
    pos = 0;
    int* nvSolutionOldOrder, *nvSolution;
    for(int gs = 0; gs < m; gs ++){
        for(int gd = 0; gd < m; gd++){
            for(int e = 0; e < G[gs]; e++){
                if(solutionInitial[pos + e] != gd && G[gs] > L[gs] && G[gd] < U[gd]){
                    if(gsAcctu != gs || gdAcctu != gd){
                        //les i
                        (*BijIndex)[k][0] = gs;
                        //les j
                        (*BijIndex)[k][1] = gd;
                        k++;
                        B = addNewBlock(B, &sizeI, &sizeJ, &sizeZ);
                        gsAcctu = gs;
                        gdAcctu = gd;
                    }
                    nvSolution = copyArray(solutionInitial, N);

                    nvSolution[pos + e] = gd;
                    nvSolutionOldOrder = oldOrder(nvSolution, refs, N);
                    addToBlock(B, nvSolutionOldOrder, &sizeI, &sizeJ, &sizeZ);
                }
            }
        }
        pos += G[gs];
    }

    return B;
}

