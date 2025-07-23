/*This program implements the linear search algorithm*/
#include <stdio.h>

/*returns the index of the first occurence of the value, -1 if it doesn't exist*/
int search(int* arr, int value, size_t size);

int main() {
    int arr[] = {23,41,56,74,100,13};
    const int ARR_SIZE = 6;

    printf("The position of the element 41 is: %i\n", search(arr, 41, ARR_SIZE));
    printf("The position of the element 23 is: %i\n", search(arr, 23, ARR_SIZE));
    printf("The position of the element 13 is: %i\n", search(arr, 13, ARR_SIZE));
}

int search(int* arr, int value, size_t size) {
    for(int i = 0; i<size; i++) {
        if(arr[i] == value) {
            return i;
        }
    }

    return -1;
}