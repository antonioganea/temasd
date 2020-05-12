#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstdlib>
using namespace std;

int compare (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}

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

void countsort(int * v, int length, int maxNo, int * V ){
    // int V[maxNo+1]; // used to cause stack overflows

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


void merge(int * v, int left, int mid, int right){
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
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(int * v, int left, int right){
    if (left < right){
        int mid = (left+right)/2;

        mergesort(v, left, mid);
        mergesort(v, mid+1, right);

        merge(v, left, mid, right);
    }
}

void radixSortCount(int * v, int n, int exp){
    int output[n];
    int i;
    int count[10] = {0};

    for (i = 0; i < n; i++)
        count[ ( v[i] / exp )%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--){
        output[count[ ( v[i] / exp )%10 ] - 1] = v[i];
        count[ ( v[i] / exp )%10 ]--;
    }

    memcpy( v, output, n * sizeof(int) );
}

void radixsort(int * v, int n, int max) {
    for (int exp = 1; max/exp > 0; exp *= 10)
        radixSortCount(v, n, exp);
}

void binradixSortCount(int * v, int n, int exp){
    int output[n];
    int i;
    int count[2] = {0};

    for (i = 0; i < n; i++)
        count[ (v[i] & exp) != 0 ]++;

    for (i = 1; i < 2; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--){
        output[count[ (v[i] & exp) !=  0 ] - 1] = v[i];
        count[ (v[i] & exp) !=  0 ]--;
    }

    memcpy( v, output, n * sizeof(int) );
}

// Binary Radix Sort version
void binradixsort(int * v, int n, int max){
    for (int exp = 1; max >= exp; exp = exp << 1)
        binradixSortCount(v, n, exp);
}

FILE * fin;

void printVector(int * v, int length){
    for ( int i = 0; i < length; i++ ){
        printf("%d ",v[i]);
    }
    puts("");
}

void quickSort(int * v, int left, int right){
    int i = left;
    int j = right;
    int pivot = v[(i + j) / 2];
    int temp;

    while (i <= j){
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j){
            // swap v[i], v[j]
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            j--;
        }
    }
    if (j > left)
        quickSort(v, left, j);
    if (i < right)
        quickSort(v, i, right);
}

// Checks if two arrays contain the same data
bool verify(int * v, int * sorted, int length){
    for ( int i = 0; i < length; i++ ){
        if ( v[i] != sorted[i] ){
            return false;
        }
    }

    return true;
}

int main (){

    int T;
    int N, M;

    fin = fopen("test.txt","r");

    fscanf(fin,"%d",&T); // read T

    for ( int testNo = 0; testNo < T; testNo++ ) {
        fscanf(fin,"%d%d",&N,&M);
        printf("Running test : %d -- %d numbers, maximum = %d\n",testNo,N,M);
        int * V = new int[N];
        for ( int i = 0; i < N; i++ ){
            fscanf(fin,"%d",V+i);
            //printf("%d ",V[i]);
        }
        //puts("");

        int * tempVector = new int[N];

        int * stdSorted = new int[N];

        {
        memcpy(stdSorted, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        qsort (stdSorted, N, sizeof(int), compare);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(stdSorted,N);
        cout << "STD quicksort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }

        if ( N <= 10000 )
        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        bubblesort(tempVector,N);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(tempVector,N);
        if ( verify(tempVector, stdSorted, N) ){
            cout << "Passed! ";
        } else {
            cout << "Failed! ";
        }
        cout << "Bubble sort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }
        else{
            cout << "Input too big for bubblesort! ( > 10000 )" << endl;
        }

        int * allocatedV = new int[M+1];
        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        countsort(tempVector,N,M,allocatedV);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(tempVector,N);
        if ( verify(tempVector, stdSorted, N) ){
            cout << "Passed! ";
        } else {
            cout << "Failed! ";
        }
        cout << "Count sort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }
        delete[] allocatedV;

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        mergesort(tempVector,0,N-1);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(tempVector,N);
        if ( verify(tempVector, stdSorted, N) ){
            cout << "Passed! ";
        } else {
            cout << "Failed! ";
        }
        cout << "Merge sort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        radixsort(tempVector,N,M);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(tempVector,N);
        if ( verify(tempVector, stdSorted, N) ){
            cout << "Passed! ";
        } else {
            cout << "Failed! ";
        }
        cout << "Radix sort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        binradixsort(tempVector,N,M);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(tempVector,N);
        if ( verify(tempVector, stdSorted, N) ){
            cout << "Passed! ";
        } else {
            cout << "Failed! ";
        }
        cout << "Binary Radix sort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }

        {
        memcpy(tempVector, V, N * sizeof(int));
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        quickSort (tempVector, 0, N-1);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // printVector(tempVector,N);
        if ( verify(tempVector, stdSorted, N) ){
            cout << "Passed! ";
        } else {
            cout << "Failed! ";
        }
        cout << "Custom quicksort - duration " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds" << endl;
        }

        delete[] tempVector;
        delete[] stdSorted;
        delete[] V;

        puts("");
    }

    fclose(fin);

    return 0;
}