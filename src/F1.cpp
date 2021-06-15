#include "F1.h"
#include <random>
#include <cstdlib>   // rand and srand

F1::F1()
{
    
}

float F1::f(int N,int m,float** D,int** X, int* L, int* U){
    if(!subjectToOnlyOneVariable(N, m, X) || !subjectToBounds(N, m, X, L, U)){
        return -1;
    }
    float sum = 0;
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, N);
    int r,i,j, *s = (int*) malloc(sizeof(int) * N);
    for(i = 0; i < N; i++){
        s[i] = -1;
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < L[i]; j++){
            r = (int) (dis(gen));
            effectiveRandom :
                if(s[r] == -1){
                    s[r] = L[i];
                }else {
                    r++;
                    r = r% N;
                    goto effectiveRandom;
                }
        }
    }
    //remplire s avec le reste des element en respectant le U
    int n = 0, cmpM = 0, cmpMaxM = 0;
    r = 0;
    int maxM[m];
    for(i = 0; i < m; i++){
            maxM[i] = U[i] - L[i];
    }
    for(int i = 0; i < N; i++){
            otherGroup :
            if(cmpMaxM < m || maxM[cmpM] > 0){
                cmpM++;
                cmpM %= m;
                cmpMaxM ++;
                if(maxM[cmpM] == 0){
                    goto otherGroup;
                }
            } else {
                break;
            }

            effectiveRandomTwo :
            if(n < N && s[r] == -1){
                s[i] = cmpM;
                maxM[cmpM] -= 1;
                n = 0;
                continue;
            } else if(n < N){
                r++;
                r %= N;
                n++;
                goto effectiveRandomTwo;
            }else {
                break;
            }
    }
    return s;
}

F1::~F1()
{
    //dtor
}
