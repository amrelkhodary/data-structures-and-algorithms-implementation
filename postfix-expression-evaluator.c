/* This program evaluates a postfix expression.
   This postfix expression evaluator is a rather basic one and intended for 
   educational purposes only, as it doesn't take external input (couldn't bother to 
   add all the code for input validation) and only deals with single digit numbers (also didn't 
   bother to write all the code to handle multidigit numbers). Also, it can't handle anything
   input string longer than 25 (yet again couldn't bother to write the dynamic memory reallocation logic)
   Also, it only recognizes four operations (+, -, *, /)


   TODO(1): Finish the implementation of the postfix expression evaluator
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Stack {
    char* chararr; 
    int top; 
} Stack; 

typedef enum Errors {
    SUCCESSFUL, 
    MEMORY_ERROR, 
    STACK_OVERFLOW, 
    STACK_UNDERFLOW,
    UNSUPPORTED_OPERATOR, 

} Errors;

int evaluatePostfixExpression(const char* POSTFIX_EXPRESSION, Stack* stackptr, const int STACK_SIZE);
int createNewStack(Stack* stackptr, char* chararr_ptr, const int SIZE);
int push(Stack* stackptr, char character, const int STACK_SIZE);
int pop(Stack* stackptr);
int calculate(int firstoperand, int secondoperand, char operator);
bool isOperand(char character);
bool isOperator(char character);

const char* MEMORY_ALLOCATION_FAILED_ERROR_MESSAGE = "Program failed to allocate memory it needed. Please try running it again..\n";
const char* STACK_OVERFLOW_ERROR_MESSAGE = "Stack Overflow. \n";
const char* STACK_UNDERFLOW_ERROR_MESSAGE = "Stack Underflow. \n";
const char* UNSUPPORTED_OPERATOR_ERROR_MESSAGE = "Unsupported Operator. \n";
int main() {
    //define program constants
    const int SIZE = 25; 
    const char* POSTFIX_EXPRESSION = "5 3 8 * 2 / + 7 4 - 6 * - 9 +";

    //create a new stack
    Stack* stackptr;  char* chararr_ptr; 
    stackptr = createNewStack(stackptr, chararr_ptr, SIZE);
     
    //evaluate the postfix expression

    return 0;
}

int createNewStack(Stack* stackptr, char* chararr_ptr, const int SIZE) {
    //allocate memory for a new stack struct
    stackptr = (Stack*) malloc(sizeof(Stack));
    if(!stackptr) {
        fprintf(stderr, MEMORY_ALLOCATION_FAILED_ERROR_MESSAGE);
        exit(MEMORY_ERROR);
    }

    //allocate memory for the new character array that will be part of the stack
    chararr_ptr = (char*) malloc(SIZE * sizeof(char));
    if(!chararr_ptr) {
        fprintf(stderr, MEMORY_ALLOCATION_FAILED_ERROR_MESSAGE);
        exit(MEMORY_ERROR);
    }

    //initialize the stack struct
    stackptr -> chararr = chararr_ptr; 
    stackptr -> top = -1; 

    return SUCCESSFUL;
}

int evaluatePostfixExpression(const char* POSTFIX_EXPRESSION, Stack* stackptr, const int STACK_SIZE) {
    //variables needed for some computations
    int temp_firstoperand, temp_secondoperand; 

    //go through the postfix expression
    for(int i = 0; POSTFIX_EXPRESSION[i] != '\0' || i == STACK_SIZE; i++) {
        //if you encounter an operand, simply push it to the stack
        if(isOperand(POSTFIX_EXPRESSION[i])) {
            push(stackptr, POSTFIX_EXPRESSION[i], STACK_SIZE);
        }
        
        //if you encounter an operator, pop the two operands it operates on and push the result
        if(isOperator(POSTFIX_EXPRESSION[i])) {
            temp_secondoperand = pop(stackptr) - '0';
            temp_firstoperand = pop(stackptr) - '0';

        }
    }
}

int push(Stack* stackptr, char character, const int STACK_SIZE) {
    //if the stack is full, return a stackoverflow error. 
    if(stackptr -> top == STACK_SIZE) {
        fprintf(stderr, STACK_OVERFLOW_ERROR_MESSAGE);
        return STACK_OVERFLOW;
    }

    //otherwise, push the new element to the stack
    stackptr -> chararr[++stackptr -> top] = character;
    return SUCCESSFUL;
}

int pop(Stack* stackptr) {
    if(stackptr -> top == -1) {
        fprintf(stderr, STACK_UNDERFLOW_ERROR_MESSAGE);
        return STACK_UNDERFLOW;
    }

    stackptr -> top--;
    return SUCCESSFUL;
}

bool isOperand(char character) {
    if(isupper(character)) {
        return true;
    }  

    return false;
}

bool isOperator(char character) {
    if(character == '+' || character == '-' || character == '*' || character == '/') {
        return true;
    }

    return false;
}

int calculate(int firstoperand, int secondoperand, char operator) {
    switch (operator)
    {
    case '+':
        return firstoperand + secondoperand;
        break;

    case '-':
        return firstoperand - secondoperand;
        break;

    case '*':
        return firstoperand * secondoperand;
        break;
    
    case '/':
        return firstoperand / secondoperand;
        break;

    default:
        fprintf(stderr, UNSUPPORTED_OPERATOR_ERROR_MESSAGE);
        exit(UNSUPPORTED_OPERATOR);
        break;
    }
}