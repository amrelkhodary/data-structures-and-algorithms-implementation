/* This program implements a paretheses checker in C using the stack data structure*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

/*
    Checks if a string of parentheses is valid or not
*/
bool isValid(char* parentheses, size_t length);

/*
    Helper function that checks if one parenthesis matches the other
*/
bool isMatch(char first, char second);

int main() {
    char* string_1 = "({[]}){}[]{}";
    char* string_2 = "[]]][[()]]";

    if(isValid(string_1, 12) && !isValid(string_2, 10)) {
        printf("Tests successful.\n");
    } else {
        printf("Tests failed.\n");
    }
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

bool isValid(char* parentheses, size_t length) {
    //create a new stack
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    int* arr = (int*) malloc(length * sizeof(int));

    stack -> arr = arr;
    stack -> size = length;
    stack -> top = -1;

    //go through the string, checking as we go
    for(int i = 0; i<length; i++) {
        if(stack -> top == -1) {push(stack, parentheses[i]);}
        else if(isMatch(peek(stack), parentheses[i])) {pop(stack);}
        else {push(stack, parentheses[i]);}
    }

    if(stack -> top == -1) {return true;}
    else {return false;}
}

bool isMatch(char first, char second) {
    char open[3] = {'(', '{', '['};
    char closed[3] = {')', '}', ']'};

    if(first == open[0] && second == closed[0] ||
       first == open[1] && second == closed[1] ||
       first == open[2] && second == closed[2]) {
        return true;
    }

    return false;
}