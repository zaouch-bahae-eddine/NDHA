#include<ManageBlock.h>
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void displayBlaock(int*** A, int N){
    int i = 0, j = 0;
    while(*(A+i) != nullptr){
        cout << "\nnew Block" << endl;
        while(*(*(A+i)+j) != nullptr){
            for(int z = 0; z < N; z++){
                cout << A[i][j][z] << "-";
            }
            j++;
            cout << endl;
        }
        cout << endl;
        j = 0;
        i++;
    }
}

int*** addNewBlock(int***A, int* sizeI, int**sizeJ, int* sizeZ){
    cout << "--addNewBlock--" << endl;
    //declaration variables
    int i,j;

    //Incrimenter sizeI
    (*sizeI)++;
    cout << "siazI = " << *sizeI;
    //Initialiser sizeJ � 2 puisque c'est un nouveux block
    int* sizeJReplace = (int*) malloc(sizeof(int) * (*sizeI - 1));
    
    for(i = 0; i < *sizeI - 1; i++){
        if((i == *sizeI - 2) || (*(*sizeJ + i) == 1)){
            sizeJReplace[i] = 2;
            cout << "\nsizeReplace-" << i << "- = " << sizeJReplace[i] << endl;
        } else {
            sizeJReplace[i] = *(*sizeJ + i);
            cout << "\nsizeReplace-" << i << "- = " << sizeJReplace[i] << endl;
        }
    }

    //free(*sizeJ);
    *sizeJ = sizeJReplace;
    
    //Creation d'un nouveau B1[i][j] avec les nouveaux sizes
    int*** Alfa = (int***) malloc((*sizeI) * sizeof(int**));

    for(i = 0; i < *sizeI; i++){
        if(i == ((*sizeI) - 1)){
            *(Alfa + i) = nullptr;
        } else {
            *(Alfa + i) = (int**) malloc(*(*sizeJ + i) * sizeof(int*));
        }
    }

    for(i = 0; i < (*sizeI - 1) ; i++){
        for(j = 0; j < *(*sizeJ + i); j++){
            if(j == (*(*sizeJ + i) - 1)){
                *(*(Alfa+i)+j) = nullptr;
            }else {
                *(*(Alfa+i)+j) = (int*) malloc((*sizeZ) * sizeof(int));
            }
        }
    }

    //Remplisage du nouveau B1 par les valeurs anciennes Sauf le nouveau block ajout�

    i = 0;
    j = 0;
    while(*(Alfa+i) != nullptr ){
        while(*(*(Alfa+i)+j) != nullptr){
            for(int z = 0; z < *sizeZ; z++){
                if(i == (*sizeI - 2)){
                    *(*(*(Alfa+i)+j)+z) = -1;
                } else {
                    *(*(*(Alfa+i)+j)+z) = *(*(*(A+i)+j)+z);
                }
            }
            j++;
        }
        j = 0;
        i++;
    }
    if(*sizeI > 2){ // si le B1 contient des block
        //Liberation de m�moire du ancien B1
       i = 0;
       j = 0;
        while(A[i] != nullptr){
            while(A[i][j] != nullptr){
                free(*(*(A+i)+j));
                j++;
            }
            free(*(A+i));
            j = 0;
            i++;
        }
        free(A);
    }
    *(*sizeJ + *sizeI -2 ) = 1;
    cout << "kk:" << *(*sizeJ + *sizeI -2 ) << endl;
    return Alfa;
}

void addToBlock(int*** A, int* nvSolution, int* sizeI, int** sizeJ, int* sizeZ){
    cout << "--addToBlock--" << endl;
    int i, j;
        //incrementer sizeJ
    (*(*sizeJ + *sizeI - 2))++;
    cout << "mm:" << (*sizeJ)[0] ;
    if((*sizeJ)[*sizeI - 2] == 2){
        for(i = 0; i < *sizeZ; i++){
            *(**(A + *sizeI - 2)+i) = nvSolution[i];
        }
        
            cout << "\nBmm:" << (*(*sizeJ + *sizeI - 2)) ;
        //(*(*sizeJ + *sizeI - 2))++;
            cout << "\nBBmm:" << (*sizeJ)[*sizeI - 2] ;
        return;
    }
    //Creation d'une nv B1[][] plus large pour la nv solution(nvSolution)
    int** Beta = (int**) malloc((*(*sizeJ + *sizeI - 2)) * sizeof(int*));
    for(i = 0; i < (*(*sizeJ + *sizeI - 2)); i++){
        if(i == (*(*sizeJ + *sizeI - 2)) - 1){
            *(Beta + i) = nullptr;
        } else {
            *(Beta + i) = (int*) malloc((*sizeZ) * sizeof(int));
        }
    }
    //Remplir Beta par les anciennes valeurs et la nv Solution(nvSolution)
    j = 0;
    while(*(*(A + *sizeI - 2)+j) != nullptr){
        for(int z = 0; z < *sizeZ; z++){
            *(*(Beta + j)+z) = *(*(*(A + *sizeI - 2)+j)+z);
        }
        //liberer A[i][j] qui represente les Anciennes solutions
        free(*(*(A + *sizeI - 2)+j));
        j++;
    }


    //liberer A[i]
    free(*(A + *sizeI - 2));
    *(Beta + j) = nvSolution;
    *(A + *sizeI - 2) = Beta;
}
/*
    mettre la solution dans un ordre croissant
    garder une trace sur la position des indices avant l'ordonement
*/
int* orderSolution(int* s, int N){
    int* refs = (int*) malloc(sizeof(int) * N);
    int change;
    for(int i = 0; i < N; i++){
        refs[i] = i;
        cout << s[i] << endl;
    }
    for(int i = 0; i < N - 1; i++){
        for(int j = i + 1; j < N; j++){
            if(s[j] < s[i]){
                change = s[i];
                s[i] = s[j];
                s[j] = change;
                change = refs[i];
                refs[i] = refs[j];
                refs[j] = change;
            }
        }
    }
    return refs;
}

int* copyArray(int* s, int N){
    int* res = (int*) malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++){
        res[i] = s[i];
    }
    return res;
}
int* oldOrder(int* s, int* refs, int N){
    int change;
    int* ss = copyArray(s, N);
    for(int i = 0; i < N - 1; i++){
        for(int j = i + 1; j < N; j++){
            if(refs[j] < refs[i]){
                change = refs[i];
                refs[i] = refs[j];
                refs[j] = change;
                change = ss[i];
                ss[i] = ss[j];
                ss[j] = change;
            }
        }
    }
    return ss;
}
