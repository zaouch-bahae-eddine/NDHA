#include <iostream>
#include <random>
#include <limits>
#include <cstdlib>
#include <cstdlib>   // rand and srand
#include <fstream>
#include<F1.h>
#include<GWOApplication.h>
#include<ManageMatrix.h>
#include<math.h>
using namespace std;
//copy un des valeurs d'un tableau dans un autre
void copyTab(int* src, int* target, int size)
{
    for(int i = 0; i < size; i++){
        target[i] = src[i];
    }
}
int* GWOApplication(F1* objecFunc, int dim, int searchAgents, int max_iter, int m, int* L, int* U, float** D)
{
    std::ofstream myfile;
    myfile.open ("GWO-MDGP.csv");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
    /*initialization alpha, beta, and delta */
    int* alpha_pos = (int*) malloc(sizeof(int) * dim);
    double alpha_score = 0;

    int* beta_pos = (int*) malloc(sizeof(int) * dim);
    double beta_score = 0;

    int* delta_pos = (int*) malloc(sizeof(int) * dim);
    double delta_score = 0;

    /*inisialization des positions pour chaque loup*/
    int** positions = (int**) malloc(sizeof(int*) * searchAgents);
    for(int i = 0; i < searchAgents; i++){
        for(int j = 0; j < dim; j++){
            *(positions + i) = objecFunc->solutionInistial(dim, m, L, U);
            cout << "positions[" << i <<"][" << j << "] = " << positions[i][j]<<"\n";
        }
    }
    //les fitness de la recherche
    double convergence_courbe[max_iter];
    //initialisation du fitness
    double fitness, a, r1, r2, A1, A2, A3, C1, C2, C3, X1, X2, X3, D_alpha, D_beta, D_delta;
    int **X, *pos_rec;
    //main iteration loop
    for(int l = 0; l < max_iter; l++){

        for(int i = 0; i < searchAgents; i++){
            
            cout << "fitnessCalcul l = " << l << " i = " << i << endl;
            X = X_Matrix(dim, m, *(positions+ i));
            fitnessCalcul:
            // Calcule des fitness pour chaque agent
            fitness = objecFunc->f(dim, m, D, X, L, U);

            //rectifier les position
            if(fitness == -1){
                X = rectifySolution(X, L, U, dim, m);
                goto fitnessCalcul;
            }
            pos_rec = S_Matrix(X, dim, m);
            copyTab(pos_rec, *(positions + i), dim);
            // update Alpha, Beta, et Delta
            if(fitness > alpha_score){
                delta_score = beta_score;
                copyTab(beta_pos, delta_pos, dim);

                beta_score = alpha_score;
                copyTab(alpha_pos, beta_pos, dim);

                alpha_score = fitness;
                copyTab(*(positions + i), alpha_pos, dim);
            }
            if(fitness < alpha_score && fitness > beta_score){
                delta_score = beta_score;
                copyTab(beta_pos, delta_pos, dim);

                beta_score = alpha_score;
                copyTab(alpha_pos, beta_pos, dim);
            }
            if(fitness < alpha_score && fitness < beta_score && fitness > delta_score){
                delta_score = fitness;
                copyTab(*(positions + i), delta_pos, dim);
            }
        }
        a = 2 - l * (((double) 2) / max_iter);
        for(int i = 0; i < searchAgents; i++){
            for(int j = 0; j < dim; j++){
                r1 = (double)(dis(gen));
                r2 = (double)(dis(gen));
                A1 = 2 * a * r1 - a;
                C1 = 2 * r2;
                D_alpha = abs(C1 * alpha_pos[j] - positions[i][j]);
                X1 = alpha_pos[j] - A1 * D_alpha;

                r1 = (double)(dis(gen));
                r2 = (double)(dis(gen));
                A2 = 2 * a * r1 - a;
                C2 = 2 * r2;
                D_beta = abs(C2 * beta_pos[j] - positions[i][j]);
                X2 = beta_pos[j] - A2 * D_beta;

                r1 = (double)(dis(gen));
                r2 = (double)(dis(gen));
                A3 = 2 * a * r1 - a;
                C3 = 2 * r2;
                D_delta = abs(C3 * delta_pos[j] - positions[i][j]);
                X3 = delta_pos[j] - A3 * D_delta;

                positions[i][j] = (int) ((X1 + X2 + X3)/3);
                if(positions[i][j] >= m){
                    positions[i][j] = m -1;
                } else if(positions[i][j] < 0){
                    positions[i][j] = 0;
                }
            }
        }
        convergence_courbe[l] = alpha_score;
        myfile << l<<","<<convergence_courbe[l]<<"\n";
        cout << "l = "<< l<< " alpha_score = "<<alpha_score << endl;
    }//iteration
    myfile.close();
    return alpha_pos;
}

int** rectifySolution(int** X, int* L, int* U,int N,int m)
{
    int G[m], i, j, n = 0, k = 0, indexOne, indexZero, largeGroup;
    for(i = 0; i < m; i++){
        G[i] = 0;
    }
    for(i = 0; i < m ; i++){
        for(j = 0; j < N; j++){
            G[i] += X[j][i];
        }
    }
    while(!URespected(G, m, U)){
        largeGroup = largeGroupIndex(G, m, U, L);
        indexOne = indexOFBestOneToDelete(X, N, largeGroup);
        G[largeGroup]--;
        X[indexOne][largeGroup] = 0;
    }
    while(!LRespected(G, m, L)){
        for(i = 0; i < m; i++){
            while(G[i] < L[i]){
                indexZero = indexOFBestZeroToDelete(X, N, m);
                if(indexZero != -1){
                    G[i]++;
                    X[indexZero][i] = 1;
                } else {
                    largeGroup = largeGroupIndex(G, m, U, L);
                    indexOne = indexOFBestOneToDelete(X, N, largeGroup);
                    G[largeGroup]--;
                    X[indexOne][largeGroup] = 0;
                }
            }
        }
    }
    return X;
}
int indexOFBestOneToDelete(int**X, int N, int col){
    int moyenne = N / 2, index = 0;
    for(int i = 0; i < N; i++){
        if(X[i][col] == 1){
            if(abs(i - moyenne) < abs(index - moyenne)){
                index = i;
            }
        }
    }
    return index;
}
int indexOFBestZeroToDelete(int**X, int N, int m){
    int moyenne = N / 2, index = N / 2;
    bool exist= false;
    for(int i = 0; i < N; i++){
        if(zeroRow(X, i, m) == true){
            if(abs(i - moyenne) > abs(index - moyenne)){
                index = i;
                exist = true;
            }
        }
    }
    if(exist){
        return index;
    } else{
        return -1;
    }

}
int largeGroupIndex(int* G, int m, int* U, int* L){
    int i, maxIndex = 0;
    for(i = 0; i < m; i++){
        if(G[i] > L[i] && (G[i] - U[i]) > (G[maxIndex] - U[maxIndex]) && U[i] > L[i]){
            maxIndex = i;
        }
    }
    return maxIndex;
}
bool zeroRow(int** X, int row, int m){
    for(int i = 0; i < m; i++){
        if(X[row][i] == 1){
            return false;
        }
    }
    return true;
}
bool URespected(int* G, int m, int* U){

    for(int i = 0; i < m; i++){
        if(G[i] > U[i]){
            return false;
        }
    }
    return true;
}
bool LRespected(int* G, int m, int* L){

    for(int i = 0; i < m; i++){
        if(G[i] < L[i]){
            return false;
        }
    }
    return true;
}
