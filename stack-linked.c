/*this program implements a linked stack (i.e. a stack implemented using a linkedlist)*/

#include <stdio.h>
#include <stdlib.h>

#define SUCCESSFUL 0
#define UNSUCCESSFUL -1

typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
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
    //create a new stack
    Stack* nstack = (Stack*) malloc(sizeof(Stack));
    nstack -> top = NULL;

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
    //create a new node
    Node* node = (Node*) malloc(sizeof(Node));
    node -> val = element;
    
    //add the node to the stack
    if(!(stack -> top)) {
        //stack is empty 
        node -> next = NULL;
        stack -> top = node;
    }
    else {
        node -> next = stack -> top;
        stack -> top = node;
    }
}

int pop(Stack* stack) {
    if(!(stack -> top)) {
        //stack is empty
        fprintf(stderr, "Cannot pop an element off an empty stack.\n");
        exit(UNSUCCESSFUL);
    }

    //keep a reference to the node to be deleted so that its space could be freed and the value inside it could be returned 
    Node* to_be_deleted = stack -> top;

    //pop the top element off the stack
    stack -> top = stack -> top -> next;

    //free the memory for the popped node, return its value
    int returnval = to_be_deleted -> val;
    free(to_be_deleted);

    return returnval;
}

int peek(Stack* stack) {
    if(!(stack -> top)) {
        //stack is empty
        fprintf(stderr, "Cannot peek at an empty stack.\n");
        exit(UNSUCCESSFUL);
    }

    return stack -> top -> val;
}