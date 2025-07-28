/* This is a program that uses the stack data structure to convert an infix expression to a postfix one*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

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
    converts an infix expression to a postfix one. 
    takes the infix string + an empty postfix string (of the same length as the infix one) to store the result
*/
void convertInfixToPostfix(char* infix, char* postfix, size_t length);

/*
    helper function to determine if a character is an operator
*/

bool isOperator(char character);

/*
    helper function to determine if a character is an operand
*/

bool isOperand(char character);

/*
    helper function to deterimine if first operand is of higher or the same precedence as second
*/

bool isHigherOrEqualPrecedence(char first_operand, char second_operand);

/*
    helper function used to print the current state for the stack (for debugging)
*/

void printstack(Stack* stack);

int main() {
    char infix_expression[21] = "A-(B/C+(D%E*F)/G)*H";
    char postfix_expression[21];
    postfix_expression[20] = '\0'; //null-terminate the string

    convertInfixToPostfix(infix_expression, postfix_expression, 21);

    printf("infix: \"%s\",\npostfix: \"%s\"\n", infix_expression, postfix_expression);
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

void convertInfixToPostfix(char* infix, char* postfix, size_t length) {
    //create a stack to hold the operators 
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    int* arr = (int*) malloc(length * sizeof(int));

    stack -> arr = arr;
    stack -> top = -1;
    stack -> size = length;

    //add ')' to the end of the infix expression, '(' to the stack
    push(stack, '(');
    infix[length - 2] = ')';

    //go through the infix expression and translate it to a postfix expression
    for(int i = 0, j = 0; i<length-1 && j<length-1; i++) {
        //if an open parenthesis is encountered, push it as an operator to the stack
        if(infix[i] == '(') {
            push(stack, '(');
        }

        //if a closed parenthesis is encoutered, evaluate everything between ( and ) 
        else if(infix[i] == ')') {
            //add all operators in the parentheses to postfix expression
            while(peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }

            //remove ( from the stack
            pop(stack);
        }

        //if an operator is encountered, 
        else if(isOperator(infix[i])) {
            /* The idea here is put operators in the stack based on the order in which they are should be executed, e.g.
                a + b * c --> stack (top -> bottom) [ * | + ]
                
                Since order is only relavent in the context of two chained operations, e.g. a + b * c what we need to do is 
                decide which operation will be where in the stack. To do this, first we normally add the first operation to the stack, 
                and before we add the second one, we check if the first one has higher (or same) precendence, and if so, push it to the postfix first, otherwise
                normally add the second operation to the stack
            */

            //add all higher (or same) precedence operators to postfix expression first till you encounter a (
            while(peek(stack) != '(' && isHigherOrEqualPrecedence(peek(stack), infix[i])) {
               postfix[j++] = pop(stack); 
            }

            //add the operator to the stack
            push(stack, infix[i]);
        }

        //if an operand is encountered, 
        else if(isOperand(infix[i])) {
            //add operand to postfix expression
            postfix[j++] = infix[i]; 
        }

        else {
            //invalid input
            fprintf(stderr, "Invalid infix string.\n");
            exit(UNSUCCESSFUL);
        }

        printstack(stack);
    }
}

bool isOperator(char character) {
    if(character == '+' || character == '-' || character == '*' || character == '/' || character == '%') {return true;}
    return false;
}

bool isOperand(char character) {
    if(isupper(character)) {return true;}
    return false;
}

bool isHigherOrEqualPrecedence(char first_operand, char second_operand) {
    if( (first_operand == '+' || first_operand == '-') && (second_operand == '*' || second_operand == '/' || second_operand == '%') ) {
        return false;
    }
    else if( (first_operand == '*' || first_operand == '/' || first_operand == '%') && (second_operand == '+' || second_operand == '-')) {
        return true;
    }
    
    return true;
}

void printstack(Stack* stack) {
    for(int i = 0; i<=stack -> top; i++) {
        printf("%c ", stack -> arr[i]);
    }

    printf("\n");
}