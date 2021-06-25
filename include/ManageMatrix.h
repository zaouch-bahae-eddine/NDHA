#ifndef MANAGEMATRIX_H_INCLUDED
#define MANAGEMATRIX_H_INCLUDED

void displayMatrix(int** D, int row, int col);
float** D_Matrix(int N, int* elements);
int** X_Matrix(int N, int m, int* solution);
int** M_MatrixIntact(int m);
int* S_Matrix(int** X, int N, int m);
#endif // MANAGEMATRIX_H_INCLUDED
