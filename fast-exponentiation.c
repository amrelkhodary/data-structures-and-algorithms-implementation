/*
    This program implements the fast integer exponentiation algorithm
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int base = atoi(argv[1]);
    int exponent = atoi(argv[2]);
    int result = 1;

    while(exponent > 0) {
        if(exponent % 2 != 0) {
            result *= base;
            exponent--;
        }
        base = base * base;
        exponent /= 2;
    }

    printf("exp(%s, %s) = %i\n", argv[1], argv[2], result);
    return 0;
}