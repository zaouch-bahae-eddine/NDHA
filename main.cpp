#include <iostream>
#include<ManageBlock.h>
#include<stdio.h>
#include<OneMove.h>
#include<ManageMatrix.h>
using namespace std;

int main()
{
    int N = 7;
    int m = 3;
    int sizeI = 1, *sizeJ = NULL, sizeZ = N;
    int*** B, **BijIndex = nullptr;
    int s[N] = {0,1,2,0,1,2,0};
    int e[N] = {0,1,2,3,4,5,6};

    int s3[N] = {5,1,2,0,1,2,0};
    int L[3] = {2, 1, 1};
    int U[3] = {4, 3, 3};
    B = OneMove(N, m, B, s, L, U, &BijIndex);
    int** D = D_Matrix(N, e);
    displayMatrix(D, N, N);
    int** Xmatrice = X_Matrix(N, m, s);
    int** M1 = M_MatrixIntact(m);
    displayBlaock(B, N, e);
    displayMatrix(M1, m, m);
    displayMatrix(Xmatrice, N, m);

    displayMatrix(BijIndex, m * (m - 1), 2);
    
    
    cout << "hgelo";
    return 0;
}
