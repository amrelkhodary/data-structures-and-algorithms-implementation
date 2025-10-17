/*
    This program find the greatest common divisor of two positive integers
*/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define INVALID_INPUT 1
#define VALID_INPUT 0

int inputIsValid(const int argc, char* const * argv);
int isPositiveInt(const char* STRING);
int convertStringToNumber(const char* STRING, const size_t length);
int gcd(const int FIRST_NUM, const int SECOND_NUM);

int main(int argc, char** argv) {
    //validate input
    if(inputIsValid(argc, argv) == INVALID_INPUT) {return INVALID_INPUT;}

    //convert the input strings into integers
    size_t firstnum_length = strlen(argv[1]);
    size_t secondnum_length = strlen(argv[2]);
    int firstnum = convertStringToNumber(argv[1], firstnum_length);
    int secondnum = convertStringToNumber(argv[2], secondnum_length);

    //calcuatle the greatest common divisor
    printf("gcd(%i, %i) = %i\n", firstnum, secondnum, gcd(firstnum, secondnum));
    return 0;
}

int inputIsValid(const int argc, char* const *argv) {
    if(argc != 3) {return INVALID_INPUT;}
    return isPositiveInt(argv[1]) | isPositiveInt(argv[2]); 
}

int isPositiveInt(const char* STRING) {
    for(int i = 0; STRING[i] != '\0'; i++) {
        if(!isdigit(STRING[i])) {return INVALID_INPUT;}
    }

    return VALID_INPUT;
}

int convertStringToNumber(const char* STRING, const size_t length) {
    int result = 0;
    for(int i = length - 1; i>=0; i--) {
        result += (STRING[i] - '0') * pow(10, (length - 1) - i);
    }

    return result;
}

int gcd(const int FIRST_NUM, const int SECOND_NUM) {
    /*
        Remember Euclid's Algorithm
        GCD(a,b) = |b                if b divides a,
                   |GCD(b, a mod b)  otherwise 
    */
    
    if(FIRST_NUM % SECOND_NUM == 0) {
        return SECOND_NUM;
    }

    return gcd(SECOND_NUM, FIRST_NUM % SECOND_NUM);
}