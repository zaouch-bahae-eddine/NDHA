#include <iostream>
#include<ManageBlock.h>
#include<stdio.h>
#include<OneMove.h>
using namespace std;

int main()
{
    int N = 7;
    int m = 3;
    int sizeI = 1, *sizeJ = NULL, sizeZ = N;
    int*** B;
    int s[N] = {0,1,2,0,1,2,0};
    int s2[N] = {0,1,2,0,1,2,0};

    int s3[N] = {5,1,2,0,1,2,0};
    int L[3] = {2, 1, 1};
    int U[3] = {4, 3, 3};
   B = OneMove(N, m, B, s, L, U);
    /*B = addNewBlock(B,&sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);

    B = addNewBlock(B,&sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);

    B = addNewBlock(B,&sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);*/

    displayBlaock(B, N);
    cout << "hgelo";
    return 0;
}
