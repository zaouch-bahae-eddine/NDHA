#include <iostream>
#include<ManageBlock.h>
#include<stdio.h>
#include<OneMove.h>
#include<ManageMatrix.h>
#include "F1.h"
#include<GWOApplication.h>
using namespace std;

int main()
{
    int N = 9;
    int m = 3;
    //int sizeI = 1, *sizeJ = NULL, sizeZ = N;
    int L[3] = {2, 2, 2};
    int U[3] = {4, 5, 3};
    int e[N] = {1,1,2,13,14,16,17,20,25};
    int sTest[9] = {0,1,1,0,0,0,0,0,0};

    /*int **fakeRectifuedX = rectifySolution(X_Matrix(N, m, sTest), L, U, N, m);
    displayMatrix(fakeRectifuedX, 9, 3);*/
    float** D = D_Matrix(N, e);
    F1 *fObj = new F1;
    int dim = N, searchAgents = 30, max_iter = 200;
    int* s = GWOApplication(fObj, dim, searchAgents, max_iter, m, L, U, D);
    system("C:/M1/stage/NDHA/GWO-MDGP.csv");
    /*inisialization des positions pour chaque loup*/
    /*int** positions = (int**) malloc(sizeof(int*) * searchAgents);
    for(int i = 0; i < searchAgents; i++){
        for(int j = 0; j < dim; j++){
            *(positions + i) = fObj->solutionInistial(dim, m, L, U);
            cout << " " << positions[i][j];
        }
        cout << endl;
    }*/

        cout << "*********** Best solution founded ************" << endl;
    for(int i = 0; i < N; i++){
        cout << " " << s[i];
    }
    return 0;
}
