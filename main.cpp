#include <iostream>
#include<ManageBlock.h>
#include<stdio.h>
using namespace std;

int main()
{
    int N = 3;
    int sizeI = 1, sizeJ = 2, sizeZ = N;
    int*** B = addNewBlock(B, &sizeI, &sizeJ, &sizeZ);
    int s[N] = {15, 12, 3};
    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);

    addToBlock(B, s, &sizeI, &sizeJ, &sizeZ);
    displayBlaock(B, N);
    cout << "hgelo";
    return 0;
}
