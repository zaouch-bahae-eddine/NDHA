#include<iostream>
#include<ManageMatrix.h>
#include<stdlib.h>
using namespace std;


void displayMatrix(int** D, int row, int col){
    cout << "\nMatrix : \n" << endl;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            cout << " m[" << i << "]["<< j <<"]= " << D[i][j] << " ; ";
        }
        cout << endl;
    }
}

float** D_Matrix(int N, int* elements){
    int i, j;
    float** D = (float**) malloc(sizeof(float*) * N);
    for(i = 0; i < N; i++){
        D[i] = (float*) malloc(sizeof(int) * N);
    }
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            D[i][j] = abs(elements[j] - elements[i]);
        }
    }
    return D;
}

int** X_Matrix(int N, int m, int* solution){
    int i, j;
    int** X = (int**) malloc(sizeof(int*) * N);
    for(i = 0; i < N; i++){
        X[i] = (int*) malloc(sizeof(int) * m);
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < N; j++){
            if(i == solution[j]){
                X[j][i] = 1;
            }else {
                X[j][i] = 0;
            }
        }
    }
    return X;
}
int* S_Matrix(int** X, int N, int m){
    int i, j, *s = (int*) malloc(sizeof(int) * N);
    for(i = 0; i < m; i++){
        for(j = 0; j < N; j++){
            if(X[j][i] == 1){
                s[j] = i;
            }
        }
    }
    return s;
}
int** M_MatrixIntact(int m){
    int i, j;
    int **M = (int**) malloc(sizeof(int*) * m);
    for(i= 0; i < m; i++){
        M[i] = (int*) malloc(sizeof(int) * m);
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < m; j++){
            if(i == j){
                M[i][j] = -1;
            } else {
                M[i][j] = 1;
            }
        }
    }
    return M;
}