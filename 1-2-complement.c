/*
    This program provides the one's and two's complement of a number

    inputs: the number, number of bits intended to hold the number
    outputs: 1's and 2's complement of the number given the specified bits, or an overflow error if the number doesn't fit
*/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INVALID_INPUT 1
#define OVERFLOW 2
#define MAX_NUM_OF_BITS 31

int helper_fastexp(const int BASE, const int EXPONENT);
void print_booleanexpansion(const uint32_t NUMBER);
void display_boolexpansion(const uint32_t NUMBER, char* resultptr, const size_t length);
bool fitsInOnesC(const int NUMBER, const int NUMBER_OF_BITS);
bool fitsInTwosC(const int NUMBER, const int NUMBER_OF_BITS);

int main(int argc, char** argv) {
    //catch the values passed to the program
    const int NUMBER = atoi(argv[1]);
    const int NUMBER_OF_BITS = atoi(argv[2]);

    //input validation
    if(! ( (argc == 3) &&
           (strcmp(argv[1], "0") == 0 || NUMBER != 0) &&
           (strcmp(argv[2], "0") == 0 || NUMBER_OF_BITS != 0))) {
               fprintf(stderr, "Invalid Input.\n");
               return INVALID_INPUT;
    }

    if(NUMBER_OF_BITS > MAX_NUM_OF_BITS) {
        fprintf(stderr, "Maximum number of bits allowed in this progarm in 31 bits.\n");
        return INVALID_INPUT;
    }
    //determine if the number fits in the amount of allocated bits
    if(!(fitsInOnesC(NUMBER, NUMBER_OF_BITS) && fitsInTwosC(NUMBER, NUMBER_OF_BITS))) {
         fprintf(stderr, "Integer Overflow.\n");
         return OVERFLOW;
    }

    //find one's and two's complement
    uint32_t ones_complement = (NUMBER >= 0) ? (uint32_t) NUMBER : (uint32_t) (helper_fastexp(2, NUMBER_OF_BITS) - 1 + NUMBER); //flip the bits for one's complement
    uint32_t twos_complement = (NUMBER >= 0) ? (uint32_t) NUMBER : (uint32_t) (ones_complement + 1); //flip the bits and add one

    //print the result
    char temp_binoutput[NUMBER_OF_BITS + 1]; temp_binoutput[NUMBER_OF_BITS] = '\0'; memset(temp_binoutput, '0', NUMBER_OF_BITS);
    printf("INPUT NUMBER: %s, NUMBER OF BITS: %s\n\n", argv[1], argv[2]);
    printf("1's Complement Representation: %u (in binary: ", ones_complement);
    display_boolexpansion(ones_complement, temp_binoutput, NUMBER_OF_BITS);
    printf(")\n");
    memset(temp_binoutput, '0', NUMBER_OF_BITS);
    printf("2's Complement Representation: %u (in binary: ", twos_complement);
    display_boolexpansion(twos_complement, temp_binoutput, NUMBER_OF_BITS);
    printf(")\n");

    return 0;
}

int helper_fastexp(const int BASE, const int EXPONENT) {
    int result = 1;
    int base = BASE;
    int exponent = EXPONENT;

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

void display_boolexpansion(const uint32_t NUMBER, char* resultptr, const size_t length) {
    int temp = NUMBER;
    int index = length - 1;

    while(temp != 0) {
        resultptr[index--] = temp % 2 + '0';
        temp /= 2;
    }


    printf("%s", resultptr);
}

bool fitsInOnesC(const int NUMBER, const int NUMBER_OF_BITS) {
    if(abs(NUMBER) < helper_fastexp(2, NUMBER_OF_BITS - 1)) {
        return true;
    }

    return false;
}

bool fitsInTwosC(const int NUMBER, const int NUMBER_OF_BITS) {
    if(!(NUMBER >= -1 * helper_fastexp(2, NUMBER_OF_BITS - 1))) {
        return false;
    }

    if(!(NUMBER <= helper_fastexp(2, NUMBER_OF_BITS -1 ) - 1)) {
        return false;
    }

    return true;
}
