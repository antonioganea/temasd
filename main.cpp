#include <iostream>
#include <cstdio>
#include <chrono>
using namespace std;

int V[10000];
int tempVector[10000];

void bubblesort(int * v, int length){
    bool unsorted = true;
    while ( unsorted ){
        unsorted = false;
        for ( int i = 0; i < length-1; i++ ){
            if ( v[i] < v[i+1] ){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
                unsorted = true;
            }
        }
    }
}

FILE * fin;

void printVector(int * v, int length){
    for ( int i = 0; i < length; i++ ){
        printf("%d ",v[i]);
    }
    puts("");
}

int main (){

    int T;
    int N, M;

    fin = fopen("test.txt","r");

    fscanf(fin,"%d",&T); // read T

    for ( int testNo = 0; testNo < T; testNo++ ) {
        fscanf(fin,"%d%d",&N,&M);
        for ( int i = 0; i < N; i++ ){
            fscanf(fin,"%d",V+i);
            printf("%d ",V[i]);
        }
        puts("");

        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        bubblesort(tempVector,N);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        printVector(tempVector,N);
        cout << "Duration " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds" << endl;


    }

    return 0;
}