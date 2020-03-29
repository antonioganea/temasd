#include <iostream>
#include <cstdio>
#include <chrono>
using namespace std;

void bubblesort(int * v, int length){
    bool unsorted = true;
    while ( unsorted ){
        unsorted = false;
        for ( int i = 0; i < length-1; i++ ){
            if ( v[i] > v[i+1] ){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
                unsorted = true;
            }
        }
    }
}

void countsort(int * v, int length, int maxNo ){
    int V[maxNo+1];
    for ( int i = 0; i <= maxNo; i++ ){
        V[i] = 0;
    }
    for ( int i = 0; i < length; i++ ){
        V[v[i]]++;
    }
    int k = 0;
    for ( int i = 0; i <= maxNo; i++ ){
        while ( V[i] > 0 ){
            v[k] = i;
            k++;
            V[i]--;
        }
    }
}


void merge(int * v, int left, int mid, int right) 
{ 
    int i, j, k; 
    int n1 = mid - left + 1; 
    int n2 =  right - mid; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = v[left + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = v[mid + 1 + j]; 
  
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            v[k] = L[i]; 
            i++; 
        } 
        else
        { 
            v[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 

    while (i < n1) 
    { 
        v[k] = L[i]; 
        i++; 
        k++; 
    } 

    while (j < n2) 
    { 
        v[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void mergesort(int * v, int left, int right) 
{ 
    if (left < right) 
    { 
        int mid = (left+right)/2; 

        mergesort(v, left, mid); 
        mergesort(v, mid+1, right); 
  
        merge(v, left, mid, right); 
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
        int * V = new int[N];
        for ( int i = 0; i < N; i++ ){
            fscanf(fin,"%d",V+i);
            printf("%d ",V[i]);
        }
        puts("");

        int * tempVector = new int[N];

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        bubblesort(tempVector,N);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        printVector(tempVector,N);
        cout << "Bubble sort - duration " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds" << endl;
        }

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        countsort(tempVector,N,M);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        printVector(tempVector,N);
        cout << "Count sort - duration " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds" << endl;
        }

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        mergesort(tempVector,0,N-1);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        printVector(tempVector,N);
        cout << "Merge sort - duration " << chrono::duration_cast<chrono::nanoseconds>(end-start).count() << " nanoseconds" << endl;
        }

        delete[] tempVector;
        delete[] V;
    }

    return 0;
}