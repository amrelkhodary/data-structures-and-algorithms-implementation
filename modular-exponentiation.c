/*
    This program implements the fast modular exponentiation algorithm defined in Section 2 of Chapter 4 in 
    Rosen's discrete mathematics textbook
*/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

bool inputIsValid(int argc, char** argv);
bool isNumber(const char* STRING);
void convertToBinary(const int NUMBER, char* returnval, const size_t length);
size_t calculateBinaryResultArrSize(const int DECIMAL_NUMBER);
int convertStringToDecimalNumber(const char* STRING, const size_t length);
int calculateModExpo(const int BASE_B, const char* BINARY_EXPANSION_OF_EXPONENT, const int MOD_M, const size_t BINARY_EXPANSION_CHAR_ARR_SIZE);

#define INVALID_INPUT 1

int main(int argc, char** argv) {
    //validate input
    if(!inputIsValid(argc, argv)) {
        return INVALID_INPUT; 
    }


    /*
        remember b^n mod m is what we are trying to calculate
    */

    //storing string lengths so we calcualte them once and use them as many times as we need
    const size_t B_LENGTH = strlen(argv[1]) + 1; //this is the complete length including null terminator
    const size_t N_LENGTH = strlen(argv[2]) + 1;
    const size_t M_LENGTH = strlen(argv[3]) + 1;

    //also lets convert all the strings into decimals 
    const int DECIMAL_B = convertStringToDecimalNumber(argv[1], B_LENGTH);
    const int DECIMAL_N = convertStringToDecimalNumber(argv[2], N_LENGTH);
    const int DECIMAL_M = convertStringToDecimalNumber(argv[3], M_LENGTH);

    //first convert n to binary because it is required for the algorithm
    //let's first allocate memory for a result array, to do that we need to calculate how long it will be 
    const size_t BINARY_EXPANSION_CHAR_ARR_SIZE = calculateBinaryResultArrSize(DECIMAL_N);
    char binary_expansion[BINARY_EXPANSION_CHAR_ARR_SIZE];
    binary_expansion[BINARY_EXPANSION_CHAR_ARR_SIZE - 1] = '\0';
    convertToBinary(DECIMAL_N, binary_expansion, BINARY_EXPANSION_CHAR_ARR_SIZE);

    //now we can finally calculate b^n mod m
    printf("(%i)^%i mod %i = %i\n", DECIMAL_B, DECIMAL_N, DECIMAL_M, calculateModExpo(DECIMAL_B, binary_expansion, DECIMAL_M, BINARY_EXPANSION_CHAR_ARR_SIZE));

    return 0;
}

bool inputIsValid(int argc, char** argv) {
    if(argc == 4) {
        for(int i = 1; i<4; i++) {
            if(!isNumber(argv[i])) {
                return false;
            }
        }

        return true;
    }

    return false;
}


bool isNumber(const char* STRING) {
    for(int i = 0; STRING[i] != '\0'; i++) {
        if(!isdigit(STRING[i])) {
            return false;
        }
    }

    return true;
}

size_t calculateBinaryResultArrSize(const int DECIMAL_NUMBER) {
    return (size_t) (floor(log2(DECIMAL_NUMBER)) + 1) + 1; //the last +1 accounts for the null terminator
}

int convertStringToDecimalNumber(const char* STRING, const size_t length) {
    int sum = 0;
    for(int i = length - 2; i >= 0; i--) {
        sum += (STRING[i] - '0') * pow(10, (length - 2) - i);
    }

    return sum;
}

void convertToBinary(const int NUMBER, char* returnval, const size_t length) {
    /*
        standard binary expansion algorithm
    */

    int binary_index = length - 2; // -2 and not -1 because we have to take into account null terminator in C strings 
    int quotient = -1; //-1 is a meaningless initial value
    int number_temp = NUMBER; //copying the constant value of NUMBER into an internal variable so we can manipulate it inside the function

    for(; quotient != 0; binary_index--) {
        quotient =  number_temp / 2;
        returnval[binary_index] = (number_temp % 2) + '0';

        number_temp = quotient;
    }

}

int calculateModExpo(const int BASE_B, const char* BINARY_EXPANSION_OF_EXPONENT, const int MOD_M, const size_t BINARY_EXPANSION_CHAR_ARR_SIZE) {
    /*
        implementation of the fast modular exponentiation algorithm
    */

    /*
        let's say we need to compute 3^9 mod 7
        9 = (1001) in binary
        
        so 3^9 mod 7 = 3^(1001) mod 7
               = 3^(1 * 2^0 + 0 * 2^1 + 0 * 2^2 + 1 * 2^3) mod 7
               = 3^(2^0) + ... mod 7
               ...
               = 3 mod 7 = 3
               + 3^0 (=9) * 1 mod 7 = 1
               + 9^0 (=81) * 1 mod 7 = 1
               + 81^2 (=6561) mod 7 = 2
               all mod 7: (3 * 1 * 1 * 2) mod 7 = 6 mod 7 = 6
    */

    int result = 1;
    int binary_index = BINARY_EXPANSION_CHAR_ARR_SIZE - 2; //not -1 because we have to account for null terminator
    int power = BASE_B % MOD_M;

    while(binary_index >= 0) {
        if(BINARY_EXPANSION_OF_EXPONENT[binary_index] == '1') {
            result = (result * power) % MOD_M;
        }

        power = (power * power) % MOD_M;
        binary_index--;
    }

    result %= MOD_M;
    
    return result;
}