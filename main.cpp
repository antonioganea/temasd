#include <iostream>
using namespace std;

int V[10000];

void bubblesort(int * v, int length){
    bool unsorted = true;
    while ( unsorted ){
        unsorted = false;
        for ( int i = 0; i < length-1; i++ ){
            if ( v[i] < v[i+1] ){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = v[i];
                unsorted = true;
            }
        }
    }
}




int main (){

    return 0;
}