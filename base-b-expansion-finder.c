/*
    This program finds the base B expansion of a given decimal integer.
    inputs: number, base B
    outputs: base b expansion of number 

    example: 
    input: 241, 2
    output: 11110001

    This program only converts to bases 2,3,4,5,6,7,8,9,16
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum Errors {
    SUCCESSFUL,
    INVALID_INPUT,
    MEMORY_ERROR,

} Errors;

bool isPositiveInteger(const char* STRING);
int convertToBaseB(const int DECIMAL_INTEGER, const int BASE, char* result, size_t RESULT_ARR_SIZE);
int findNumOfDigitsRequired(const int DECIMAL_NUMBER, const int BASE);
char findHexadecimalCharacter(int number);

int main(int argc, char** argv) {
    //declaring some program constants and variables 
    const int CORRECT_NUMBER_OF_ARGUMENTS = 2; 
    const char* INVALID_ARGUMENTS_ERROR_MESSAGE = "Invalid arguments, program has to accept two arguments: the number, and the base b, whose values could only be either between 2 and 9, or 16. Please enter them and try again.\n";
    const char* MEMORY_ALLOCATION_ERROR_MESSAGE = "Failed to allocate memory for critical program operations, please try running the program again.\n";
    const size_t INITIAL_RESULT_STRING_SIZE = 25; 
    int number; //decimal number to be converted to base b
    int base; //base b 
    char* result; //string to store te result in
    
    //check if the user entered the correct number of arguments 
    //keep in mind that argc = 1 + number of arguments user entered (which should be two)
    if(!(argc == CORRECT_NUMBER_OF_ARGUMENTS + 1)) {
        fprintf(stderr, "%s", INVALID_ARGUMENTS_ERROR_MESSAGE);
        return INVALID_INPUT;
    }

    //If the inputs are positive integers, convert them into ints, and if not, return an error to the user
    if(isPositiveInteger(argv[1]) && isPositiveInteger(argv[2])) {
        number = atoi(argv[1]);
        base = atoi(argv[2]);
    } else {
        fprintf(stderr, "%s", INVALID_ARGUMENTS_ERROR_MESSAGE);
        return INVALID_INPUT;
    }

    //check if the base is only of the allowed values (2 to 9, and base 16)
    if(!((base >=2 && base <=9) || (base == 16))) {
        fprintf(stderr, "%s", INVALID_ARGUMENTS_ERROR_MESSAGE);
        return INVALID_INPUT;
    }

    //alloacte memory for the result array
    //remember we have to add one to number of digits required for the null terminator character required for strings in C
    const size_t REQUIRED_NUMBER_OF_DIGITS = findNumOfDigitsRequired(number, base);
    result = (char*) malloc((REQUIRED_NUMBER_OF_DIGITS + 1) * sizeof(char)); //array to store the result of the conversion 
    if(!result) {fprintf(stderr, "%s", MEMORY_ALLOCATION_ERROR_MESSAGE); return MEMORY_ERROR;}

    //add the null terminator character to the last position in the array
    //the last position is SIZE - 1 = (number of digits required + 1) - 1 = number of digits required
    else {result[REQUIRED_NUMBER_OF_DIGITS] = '\0';}

    //now that we are sure the input is valid, perform the conversion and return the result to the user 
    return(convertToBaseB(number, base, result, REQUIRED_NUMBER_OF_DIGITS + (size_t) 1));
}


bool isPositiveInteger(const char* STRING) {
    int i = 0;
    while(STRING[i] != '\0') {
        if(!(isdigit(STRING[i]))) {
            return false;
        }

        i++;
    }

    return true;
}

int convertToBaseB(const int DECIMAL_INTEGER, const int BASE, char* result, size_t RESULT_ARR_SIZE) {
    /*
        Remember the division algorithm:
        a = d * q + r
        a: dividend, d: divisor, q: quotient, r: remainder
        a = d * (a div d) + (a mod d) 
    */

   int dividend = DECIMAL_INTEGER;
   const int divisor = BASE;
   int quotient = -1; //initial value, doesn't mean anything 
   int remainder = -1; //initial value, doesn't mean anything 
   int resultarr_index = RESULT_ARR_SIZE - 2; //start at second last position, right before the null terminator 

   while(quotient != 0) {
        quotient = dividend / divisor;
        remainder = dividend % divisor; 
        result[resultarr_index--] = (BASE != 16) ? remainder + '0' : findHexadecimalCharacter(remainder);
        dividend = quotient;
   }

   printf("Input: %i\nSpecified Base: %i\nOutput: %s\n", DECIMAL_INTEGER, BASE, result);
   return SUCCESSFUL;
}

int findNumOfDigitsRequired(const int DECIMAL_NUMBER, const int BASE) {
    /*
        Remember the division algorithm:
        a = d * q + r
        a: dividend, d: divisor, q: quotient, r: remainder
        a = d * (a div d) + (a mod d) 
    */

    //the idea is to keep dividing until the quotient is zero
    int count = 0;
    int dividend = DECIMAL_NUMBER;
    const int divisor = BASE;
    int quotient = -1; 
    
    while(quotient != 0) {
        quotient = dividend / divisor;
        dividend = quotient;

        count++;
    }

    return count; 
}

char findHexadecimalCharacter(int number) {
    if(number < 10) {return number + '0';}
    else {return 'A' + (number - 10);} 
}