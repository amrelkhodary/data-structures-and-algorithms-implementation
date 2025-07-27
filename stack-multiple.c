/* This program implements multiple stacks in C*/

#include <stdio.h>
#include <stdlib.h>
#define SUCCESSFUL 0
#define UNSUCCESSFUL -1
typedef struct MulStack {
    int* arr; //array that holds the elements of the stack
    int* tops; //array that holds the top indicies of each individual stack
    int size; //size of the stack array
    int stack_count; //number of stacks in the multistack
} MulStack;

/*adds an element to a specific stack in the multistack*/
void push(MulStack* mulstack, int stack, int element);

/*pops an element off a specific stack in the multistack*/
int pop(MulStack* mulstack, int stack);

/*peek at the top element of a specific stack in the multistack*/
int peek(MulStack* mulstack, int stack);

/*helper function to set up multistack top indicies*/
void setup_tops(MulStack* mulstack);

/*helper function to print the multistack*/
void printmstack(MulStack* mulstack);

int main() {
    //create a new multistack
    MulStack* nmulstack = (MulStack*) malloc(sizeof(MulStack));
    nmulstack -> size = 25;    
    nmulstack -> stack_count = 5; 
    int* arr = (int*) malloc(nmulstack -> size * sizeof(int));
    int* tops = (int*) malloc(nmulstack -> stack_count * sizeof(int));
    nmulstack -> arr = arr;
    nmulstack -> tops = tops;
    setup_tops(nmulstack);

    //test the code
    for(int i = 0; i<5; i++) {
    }

    for(int i = 0; i<5; i++) {
        pop(nmulstack, i);
    }

    printmstack(nmulstack);
}

void setup_tops(MulStack* mulstack) {
    for(int i = 0, j = 0; i<mulstack -> size / mulstack -> stack_count; i++, j+=5) {
        mulstack -> tops[i] = j - 1;
    }
}

void push(MulStack* mulstack, int stack, int element) {
    //check if the specific stack is full
    if( (mulstack -> tops[stack]) == ( (mulstack -> size / mulstack -> stack_count) * (stack+1) - 1)) {
        //specific stack is full
        fprintf(stderr, "Cannot add an element to a full stack.\n");
        exit(UNSUCCESSFUL);
    }

    mulstack -> arr[++mulstack -> tops[stack]] = element;
}

int pop(MulStack* mulstack, int stack) {
    //check if the specific stack is empty
    if( (mulstack -> tops[stack] == (mulstack -> size / mulstack -> stack_count) * stack) - 1) {
            //specific stack is empty
            fprintf(stderr, "Cannod pop an element off an empty stack.\n");
            exit(UNSUCCESSFUL);
    }
    
    int returnval = mulstack -> arr[mulstack -> tops[stack]];
    mulstack -> arr[mulstack -> tops[stack]--] = -1;
    return returnval;
}

int peek(MulStack* mulstack, int stack) {
    //check if the specific stack is empty
    if( (mulstack -> tops[stack] == (mulstack -> size / mulstack -> stack_count) * stack) - 1) {
            //specific stack is empty
            fprintf(stderr, "Cannod pop an element off an empty stack.\n");
            exit(UNSUCCESSFUL);
    }

    return mulstack -> arr[mulstack -> tops[stack]];
}

void printmstack(MulStack* mulstack) {
    for(int i = 0; i<mulstack -> size; i++) {
        if(i % 5 == 0 && i != 0) {printf("\n");}
        printf("%i ", mulstack -> arr[i]); 
    }

    printf("\n");
}