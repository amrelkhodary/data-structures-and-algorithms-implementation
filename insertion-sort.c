/*This program implements the insertion sort algorithm*/

#include <stdio.h>
void sort(int* arr, size_t size); 
void printarr(int* arr, size_t size);
void swap(int* arr, int first_index, int second_index);

int main() {
    //define an array to be sorted
    int a[] = {31,41,59,26,41,58};
    const int ARR_SIZE = 6;
    //apply the insertion sort algorithm to the array
    sort(a, ARR_SIZE);
    printarr(a, ARR_SIZE);
}

void sort(int* arr, size_t size) {
    for(int i = 1; i<size; i++) {
        for(int j = i-1, k = i; j>=0 && arr[k] < arr[j]; j--, k--) {
            swap(arr, j, k);
        }
    }
}

void printarr(int* arr, size_t size) {
    for(int i = 0; i<size; i++) {
        printf("%i ", arr[i]);
    }

    printf("\n");
}

void swap(int* arr, int first_index, int second_index) {
    int temp = arr[first_index];
    arr[first_index] = arr[second_index];
    arr[second_index] = temp;
}