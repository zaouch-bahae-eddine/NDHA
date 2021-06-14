#ifndef MANAGEBLOCK_H_INCLUDED
#define MANAGEBLOCK_H_INCLUDED

void displayBlaock(int*** A, int N);
int*** addNewBlock(int***A, int* sizeI, int** sizeJ, int* sizeZ);
void addToBlock(int*** A, int* nvSolution, int* sizeI, int** sizeJ, int* sizeZ);
int* orderSolution(int* s, int N);
int* oldOrder(int* s, int* refs, int N);
int* copyArray(int* s, int N);
#endif // MANAGEBLOCK_H_INCLUDED
