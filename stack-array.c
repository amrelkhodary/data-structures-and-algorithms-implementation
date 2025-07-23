/*This programs defines a stack implemented using an array*/

#include <stdlib.h>
#include <stdio.h>

#define SUCCESSFUL 0
#define UNSUCCESSFUL -1

typedef struct Stack {
    int* arr; //the underlying array that holds the stack elements
    int size; //the size of the array that holds the stack elements
    int top; //the position of the current top element in the stack
} Stack;

/*
    adds an element to the top of the stack
*/
void push(Stack* stack, int element);

/*
    pops the top element of the stack
    returns the value of the popped element
*/
int pop(Stack* stack);

/*
    returns the value of the element at the top of the stack
*/
int peek(Stack* stack);


int main() {
    //allocate memory for a new stack
    Stack* nstack = (Stack*) malloc(sizeof(Stack));

    //define stack properties
    nstack -> size = 10;
    nstack -> top = -1;

    //allocate memory for the array that will hold the stack elements
    int* arr = (int*) malloc((nstack -> size) * sizeof(int));

    //attach the created array to the stack
    nstack -> arr = arr;

    //test the code
    push(nstack, 1);
    push(nstack, 2);
    push(nstack, 3);

    printf("Current element at the top of the stack is: %i\n", peek(nstack)); //should say 3
    pop(nstack);

    printf("Current element at the top of the stack is: %i\n", peek(nstack)); //should say 2
    pop(nstack);

    printf("Current element at the top of the stack is: %i\n", peek(nstack)); //should say 1
    pop(nstack);

    return SUCCESSFUL;
}

void push(Stack* stack, int element) {
    if(stack -> top == stack -> size - 1) {
        //stack is full
        fprintf(stderr, "Cannot add an element to a full stack.\n");
        exit(UNSUCCESSFUL);
    }

    stack -> arr[++(stack -> top)] = element;
}

int pop(Stack* stack) {
    if(stack -> top == -1) {
        //stack is already empty
        fprintf(stderr, "Cannot delete elements from an already empty stack.\n");
        exit(UNSUCCESSFUL);
    }

    return stack -> arr[(stack -> top)--];   
}

int peek(Stack* stack) {
    if(stack -> top == -1) {
        //stack is empty
        fprintf(stderr, "Cannot peek at an empty stack.\n");
        exit(UNSUCCESSFUL);
    }

    return stack -> arr[stack -> top];
}