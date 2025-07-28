/* This program implements the selection sort algorithm in C*/
#include <stdio.h>

/*
    sort a given array using the selection sort algorithm
*/
void sort(int* arr, size_t length);

/*
    helper function that swaps two elements in an array
*/
void swap(int* arr, int first, int second);

/*
    helper function that finds the smallest element in an array beginning from start
*/
int findSmallestElementIndex(int* arr, int start, size_t length);

/*
    helper function to print an array for debugging purposes
*/
void printarr(int* arr, size_t length) {
    for(int i = 0; i<length; i++) {
        printf("%i ", arr[i]);
    }

    printf("\n");
}
int main() {
    int arr[5] = {5,4,2,1,3};

    sort(arr, 5);
    printarr(arr, 5);
}

void sort(int* arr, size_t length) {
    //go through all elements except the last one (we don't need to go into it because the array would be already sorted at that point)
    for(int i = 0; i<length - 1; i++) {
        //find the smallest element from i to length - 1
        swap(arr, i, findSmallestElementIndex(arr, i, length));
    }
}

void swap(int* arr, int first, int second) {
    int temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

int findSmallestElementIndex(int* arr, int start, size_t length) {
    int smallestElementIndex = start;

    for(int i = start; i<length; i++) {
        if(arr[i] < arr[smallestElementIndex]) {
            smallestElementIndex = i;
        } 
    }

    return smallestElementIndex;
}
