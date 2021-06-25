#include "F1.h"
#include <random>
#include <cstdlib>   // rand and srand
#include <iostream>
using namespace std;



F1::F1()
{

}

double F1::f(int N, int m, float** D, int** X, int* L, int* U){
    if(!subjectToOnlyOneVariable(N, m, X) || !subjectToBounds(N, m, X, L, U)){
        return -1;
    }
    double sum = 0;
    for(int g = 0; g < m; g++){
        for(int i = 0; i < N-1; i++){
            for(int j = i + 1; j < N; j++){
                sum += D[i][j] * X[i][g] * X[j][g];
            }
        }
    }
    return sum;
}
bool F1::subjectToOnlyOneVariable(int N, int m, int** X){
    int cmp = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < m; j++){
           if(cmp < 2){
                cmp += X[i][j];
            } else{
                return false;
            }
        }
        cmp = 0;
    }
    return true;
}
bool F1::subjectToBounds(int N, int m, int** X, int* L, int* U){
    int sum;
    for(int j = 0; j < m; j++){
        sum = 0;
        for(int i = 0; i < N; i++){
            sum += X[i][j];
        }
        if(sum > U[j] || sum < L[j]){
            return false;
        }
    }
    return true;
}

int* F1::solutionInistial(int N, int m, int* L, int* U){
        std::uniform_int_distribution<int> dis(0, 10);
        std::uniform_int_distribution<int> randGroup(0, 3);
    int r,i,j,k, *s = (int*) malloc(sizeof(int) * N), G[N];
    for(i = 0; i < N; i++){
        s[i] = -1;
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < L[i]; j++){
            
            r = (int) (dis(gen));
            effectiveRandom :
                if(s[r] == -1){
                    s[r] = i;
                }else {
                    r += (int) (dis(gen));
                    r = (r + 1)% N;
                    goto effectiveRandom;
                }
        }
    }
    for(i = 0; i < m; i++){
        G[i] = 0;
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < N; j++){
            if(s[j] == i){
                G[i] ++;
            }
        }
    }
    k = (int) (randGroup(gen));
    for(i = 0; i < N; i++){

        if(s[i] == -1){
            while(s[i] == -1){
                if(G[k] < U[k]){
                    s[i] = k;
                    G[k]++;
                }
                k += (int) (randGroup(gen));
                k = k % m;
            }
        }
    }
   
    return s;
}
F1::~F1()
{
    //dtor
}
