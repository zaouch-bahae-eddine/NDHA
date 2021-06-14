#include<OneMove.h>
#include<ManageBlock.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int*** OneMove(int N, int m, int*** B, int* solutionInitial, int* L, int* U){
    int sizeI = 1, *sizeJ = NULL, sizeZ = N;
    int* refs = orderSolution(solutionInitial, N);
    int* G = (int*) malloc(sizeof(int) * m);
    int* nvSolution;
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
    int groupeAcctu = -1;
    int* nvSolutionOldOrder;
    for(i = 0; i < N; i++){
        if(groupeAcctu != solutionInitial[i]){
            cout << "\n==> AddNewBlock \n";
            B = addNewBlock(B, &sizeI, &sizeJ, &sizeZ);
            groupeAcctu = solutionInitial[i];
            cout << "\n==> Fin-AddNewBlock \n";
        }
        for(j = 0; j < m; j++){
            if(j != solutionInitial[i] && G[solutionInitial[i]] > L[solutionInitial[i]] && G[j] < U[j]){
                nvSolution = copyArray(solutionInitial, N);
                nvSolution[i] = j;
                nvSolutionOldOrder = oldOrder(nvSolution, refs, N);
                
                cout << "\n==> addToBlock \n";
                addToBlock(B, nvSolutionOldOrder, &sizeI, &sizeJ, &sizeZ);
                cout << "\n==> Fin-addToBlock \n";
                break;
            }
        }
    }
    return B;
}

