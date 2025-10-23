/*
    This program solves the towers of hanoi program; Given three poles A, B and C and an arbitrary number of
    rings initially put on pole A, it moves them from pole A to pole C while maintaining the same order throughout
    all the steps
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MEMORY_ERROR 1
#define USER_INPUT_ERROR 2
#define IS_NUMBER 1
#define IS_NOT_NUMBER 0
#define USER_INPUT_VALID 3

//define the stack adt
typedef struct Stack {
    int* elements;
    int top;
    size_t size;
} Stack;

Stack* createStack(const size_t STACK_SIZE) {
    Stack* nstack = (Stack*) malloc(sizeof(Stack));
    if(!nstack) {
        fprintf(stderr, "Memory Error");
        return NULL;
    }

    nstack -> elements = (int*) malloc(sizeof(int) * STACK_SIZE);
    if(!nstack -> elements) {
        fprintf(stderr, "Memory Error");
        return NULL;
    }

    nstack -> top = -1;
    nstack -> size = STACK_SIZE;
    return nstack;
}

Stack* increaseStackSize(Stack* stackptr, const size_t NEW_SIZE) {
    stackptr -> size = NEW_SIZE;
    stackptr -> elements = realloc(stackptr -> elements, sizeof(int) * NEW_SIZE);
    return stackptr;
}

void push(Stack* stackptr, int element) {
    //increase stack size if needed
    if( (stackptr -> top + 1) == (stackptr -> size) ) {
        //if the index of the next element to be added would be one more than the current max index, increase the size by two
        increaseStackSize(stackptr, stackptr -> size * 2);
    }


    stackptr -> elements[++stackptr -> top] = element;
}

int pop(Stack* stackptr) {
    if(stackptr -> top == -1) {
        fprintf(stderr, "Cannot remove an element from an empty stack\n");
    }

    stackptr -> size--;
    return stackptr -> elements[stackptr -> top--];
}

int peek(Stack* stackptr) {
    if(stackptr -> top == -1) {
        fprintf(stderr, "Cannot peek at an element from an empty stack\n");
    }

    return stackptr -> elements[stackptr -> top];
}

//basic helper functions
int isNumber(const char* STRING) {
    for(int i = 0; i<strlen(STRING); i++) {
        if(!isdigit(STRING[i])) {
            return IS_NOT_NUMBER;
        }
    }

    return IS_NUMBER;
}

int inputIsValid(int argc, char** argv) {
    if(argc != 2) {
        return USER_INPUT_ERROR;
    }

    if(!isNumber(argv[1])) {
        return USER_INPUT_ERROR;
    }

    return USER_INPUT_VALID;
}

int fastpower(const int BASE, const int EXPONENT) {
    int result = 1;
    int current_base = BASE;
    int current_power = EXPONENT;


    while(current_power > 0) {
        if(current_power % 2 != 0) {
            result *= current_base;
            current_power--;
        }
        current_base = current_base * current_base;
        current_power /= 2;
    }

    return result;
}

int convertStringToNumber(const char* STRING) {
    int result = 0;

    for(int i = strlen(STRING) - 1; i >= 0; i--) {
        result += (STRING[i] - '0') * fastpower(10, (strlen(STRING) - 1) - i);
    }

    return result;
}


void pushInputIntoPoleA(Stack* pole_a, const int NUMBER_OF_DISKS) {
    for(int i = 1; i<= NUMBER_OF_DISKS; i++) {
        push(pole_a, i);
    }
}

void printstack(const Stack* STACKPTR) { for(int i = 0; i<= STACKPTR -> top; i++) {
        printf("%i ", STACKPTR -> elements[i]);
    }
}

void printCurrentState(const Stack* POLE_A, const Stack* POLE_B, const Stack* POLE_C) {
    //print pole a
    printf("A: ");
    printstack(POLE_A);
    printf("\n");

    //print pole b
    printf("B: ");
    printstack(POLE_B);
    printf("\n");

    //print pole c
    printf("C: ");
    printstack(POLE_C);
    printf("\n----------------------------------------------------------------------------------------------------\n\n");
}

void towersOfHanoi(Stack** poles, const int CURRENT, const int GOAL);

int main(int argc, char** argv) {
    const size_t INITIAL_STACK_SIZE = 10;

    //basic input validation
    if(inputIsValid(argc, argv) == USER_INPUT_ERROR) {
        fprintf(stderr, "Invalid Input\n");
        return USER_INPUT_ERROR;
    }

    //convert input to number
    const int NUMBER_OF_DISKS = convertStringToNumber(argv[1]);
    if(NUMBER_OF_DISKS == 0) {
        fprintf(stderr, "Invalid Input\n");
        return USER_INPUT_ERROR;
    }

    printf("Number of disks: %i\n", NUMBER_OF_DISKS);

    //create three stacks for the three poles A, B and C
    Stack* pole_a = createStack(INITIAL_STACK_SIZE);
    Stack* pole_b = createStack(INITIAL_STACK_SIZE);
    Stack* pole_c = createStack(INITIAL_STACK_SIZE);

    //push the initial disks into pole a
    pushInputIntoPoleA(pole_a, NUMBER_OF_DISKS);

    //solve the towers of hanoi problem
    Stack* poles[] = {pole_a, pole_b, pole_c};
    towersOfHanoi(poles, 1, 3);
    return 0;
}


/*
    WARNING: NEVER change the order of the poles you pass in the poles array, it always has to be pole_a, pole_b then pole_c,
             otherwise, the function will NOT work
*/
void towersOfHanoi(Stack** poles, const int CURRENT, const int GOAL) {
    /*
        logic behind this is that every pole is given a number (A -> 1, B -> 2, C -> 3) and
        the sum of those is 6, so to get the spare, simply just subtract whatever the current and goal are from 6
    */

    const int SPARE = 6 - (CURRENT + GOAL);
    printCurrentState(poles[0], poles[1], poles[2]);

    //base case, current contains only one element
    if(poles[CURRENT - 1] -> top == 0) {
        //simply just move this element from the CURRENT pole to the GOAL pole
        push(poles[GOAL - 1], pop(poles[CURRENT - 1]));
        return;
    }

     //recursive case, current contains more than one element

}
