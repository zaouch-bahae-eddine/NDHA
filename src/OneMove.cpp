#include<OneMove.h>
#include<ManageBlock.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int*** OneMove(int N, int m, int*** B, int* solutionInitial, int* L, int* U){
    int sizeI = 1, *sizeJ = NULL, sizeZ = N;
    int* refs = orderSolution(solutionInitial, N);
    int* G = (int*) malloc(sizeof(int) * m);
    int i, j, pos = 0, nbEinG = 0, acctu;
    acctu = solutionInitial[0];

    for(i = 0; i < m; i++){
        for(j = pos; j < N; j++){
            if(acctu == solutionInitial[j]){
                pos++;
                nbEinG++;
            }
        }
        acctu = solutionInitial[pos];
        G[i] = nbEinG;
        cout << nbEinG <<" ";
        nbEinG = 0;
    }
    int gsAcctu = -1, gdAcctu = -1;
    pos = 0;
    int* nvSolutionOldOrder, *nvSolution;
    for(int gs = 0; gs < m; gs ++){
        for(int gd = 0; gd < m; gd++){
            for(int e = 0; e < G[gs]; e++){
                cout << "\nPosAcctu " <<  pos + e << endl;
                if(solutionInitial[pos + e] != gd && G[gs] > L[gs] && G[gd] < U[gd]){
                    if(gsAcctu != gs || gdAcctu != gd){
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

