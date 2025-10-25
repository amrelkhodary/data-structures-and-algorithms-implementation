/*
    This program finds the cantor expansion of a given positive integer.

    input: the integer in question as a string passed to the program
    output: the cantor expansion of the integer
    constraints: the integer has to less than MAX_SAFE_CANTOR
*/

#include <stdatomic.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SAFE_CANTOR 2432902008176640000ULL  // 20!
#define INVALID_INPUT 1
#define MAX_FACTORIAL 20 // 20! i.e. this can only go till 20 cantor expansion digits
#define INITIAL_VALUE 1 //random initial value to provide to integer types when you can't assign them to zero at first

typedef struct CantorExpansion {
    char* literal;
    uint64_t value;
} CantorExpansion;

uint64_t convertStringToLargeInteger(const char* STRING, const size_t LENGTH);
uint64_t helper_fastexponent(const int BASE, const int EXPONENT);
bool isNumberTooLarge(const char* STRING, const size_t LENGTH);
void findCantorExpansion(CantorExpansion* resultptr);
void calculateFactorials(const int COUNT, uint64_t* resultptr);
int findCantorMSB(const uint64_t number, uint64_t* factorialvalues);
char finddigit(const int NUMBER);

int main(int argc, char** argv) {
    //validate input
    if(argc != 2) {
        fprintf(stderr, "The program accepts only one argument as an input, the number you want to find the cantor expansion of.\n");
        return INVALID_INPUT;
    }
    const size_t NUMBER_STRING_LENGTH = strlen(argv[1]);
    for(int i = 0; i<NUMBER_STRING_LENGTH; i++) {
        if(!(isdigit(argv[1][i]))) {
            fprintf(stderr, "The program only accepts positive integers as input.\n");
            return INVALID_INPUT;
        }
    }
    if(isNumberTooLarge(argv[1], NUMBER_STRING_LENGTH)) {
        fprintf(stderr, "The number you entered is too large, the largest number allowed is: 2432902008176640000\n");
        return INVALID_INPUT;
    }

    //convert the number string to a large integer
    const uint64_t NUMBER = convertStringToLargeInteger(argv[1], NUMBER_STRING_LENGTH);

    //find the cantor expansion
    CantorExpansion ncantorexp;
    char cantor_literal[MAX_FACTORIAL + 1];
    cantor_literal[MAX_FACTORIAL] = '\0';
    memset(cantor_literal, '0', MAX_FACTORIAL);
    ncantorexp.value = NUMBER;
    ncantorexp.literal = cantor_literal;
    findCantorExpansion(&ncantorexp);

    //print the cantor expansion literal
    printf("ORIGINAL NUMBER: %s\nCANTOR EXPANSION: %s\n", argv[1], ncantorexp.literal);
    return 0;
}

uint64_t convertStringToLargeInteger(const char* STRING, const size_t LENGTH) {
    uint64_t result = 0;
    for(int i = LENGTH - 1; i>=0; i--) {
        result += (STRING[i] - '0') * helper_fastexponent(10, (LENGTH - 1) - i);
    }

    return result;
}

uint64_t helper_fastexponent(const int BASE, const int EXPONENT) {
    uint64_t base = BASE;
    uint64_t exponent = EXPONENT;
    uint64_t result = 1;

    while(exponent > 0) {
        if(exponent % 2 != 0) {
            result *= base;
            exponent--;
        }
        base = base * base;
        exponent /= 2;
    }

    return result;
}

bool isNumberTooLarge(const char* STRING, const size_t LENGTH) {
    const char* COMPARISON_STRING = "2432902008176640000"; //the largest number the program allows

    if(LENGTH < 19) {
        return false;
    }

    else if(LENGTH > 19) {
        return true;
    }

    for(int i = 0; i<LENGTH; i++) {
        if(STRING[i] > COMPARISON_STRING[i]) {
            return true;
        }
        else if(STRING[i] < COMPARISON_STRING[i]) {
           return false;
        }
        else {
            continue;
        }
    }

    return false;
}

void findCantorExpansion(CantorExpansion* resultptr) {
    /*
        Explanation for the cantor expansion finder algorithm implmented in this function

        1- Given a number X, find the position of MSB digit of its cantor expression
        2- calculate X div (the factorial value of that position) and X mod the same factorial value
        3- the div would be the the factor multiplied by the factorial value, i.e. the digit in the cantor expasion
        4- repeat until the remainder is 0
    */

    uint64_t FACTORIALS[MAX_FACTORIAL]; //you should NOT modify this, it's not declared const because it will be passed to a function that fills it
    calculateFactorials(MAX_FACTORIAL, FACTORIALS);

    int index = 0;
    uint64_t remainder = resultptr->value;
    int factorial_index = findCantorMSB(remainder, FACTORIALS);
    while(!(remainder == 0 && factorial_index == -1)) {
        //find the value of the current digit
        resultptr->literal[index++] = finddigit(remainder / FACTORIALS[factorial_index]);

        //calculate the remainder
        remainder = remainder % FACTORIALS[factorial_index];

        factorial_index--;
    }

    //terminate the string early if the number of digits doesn't fill the entire array
    if(index != MAX_FACTORIAL) {
        resultptr -> literal[index] = '\0';
    }
}

void calculateFactorials(const int COUNT, uint64_t* resultptr) {
    uint64_t current_fact = 1;
    for(int i = 1; i<=COUNT; i++) {
        current_fact *= i;
        resultptr[i-1] = current_fact;
    }
}


int findCantorMSB(const uint64_t number, uint64_t* factorialvalues) {
    for(int i = 0; i<MAX_FACTORIAL; i++) {
        if(number < factorialvalues[i]) {
           return i - 1;
        }
    }


   return -1;
}

char finddigit(const int NUMBER) {
    if(NUMBER < 10) {return NUMBER + '0';}
    return 'A' + (NUMBER - 10);
}
