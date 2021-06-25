#ifndef GWOAPPLICATION_H_INCLUDED
#define GWOAPPLICATION_H_INCLUDED


int* GWOApplication(F1* objecFunc, int dim, int searchAgents, int max_iter, int m, int* L, int* U, float** D);
int** rectifySolution(int** X, int* L, int* U,int N,int m);
int indexOFBestZeroToDelete(int**X, int N, int m);
int indexOFBestOneToDelete(int**X, int N, int col);
int largeGroupIndex(int* G, int m, int* U, int* L);
bool zeroRow(int** X, int row, int m);
bool URespected(int* G, int m, int* U);
bool LRespected(int* G, int m, int* L);
#endif // GWOAPPLICATION_H_INCLUDED
