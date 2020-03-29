#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

FILE * fout;

int N = 100000;
int M = 10000000;

int main(){

    srand (time(NULL));

    fout = fopen("generated.txt", "w");
    fprintf(fout,"%d %d\n", N, M);

    for ( int i = 0; i < N; i++ ){
        int temp = rand() % (M+1);
        fprintf(fout,"%d ", temp);
    }

    fclose(fout);

    return 0;
}