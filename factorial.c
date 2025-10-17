/*
    this program calculates the factorial of a given positive integer
*/

#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#define INVALID_INPUT -1

int convertStringToPositiveInt(int argc, char** argv);
uint64_t factorial(const int NUMBER);

int main(int argc, char** argv) {
    //validate input, if input is valid, return the value of the positive integer to find the factorial of 
    int number = convertStringToPositiveInt(argc, argv);
    
    //find the result and print it
    uint64_t result = factorial(number);
    printf("%s! = %lu\n", argv[1], result);

    return 0;
}

int convertStringToPositiveInt(int argc, char** argv) {
    if(argc != 2) {return INVALID_INPUT;}

    int value = 0;
    size_t legnth = strlen(argv[1]);
    int i = legnth - 1;
    while(argv[1][i] != '\0') {
        if(!isdigit(argv[1][i])) {
            return INVALID_INPUT;
        }

        else  {
            value += (argv[1][i] - '0') * pow(10, (legnth - 1) - i);
        }

        i--;
    }

    return value;
}

uint64_t factorial(const int NUMBER) {
    if(NUMBER == 1) {
        return (uint64_t) 1;
    }

    return NUMBER * factorial(NUMBER - 1);
}