/*
    This program find the inverse mod m of a number (if it exists).
    Example: inverse of 3 mod 7 is 5 because 3 * 5 = 15, diff 1 from 14
*/
#include <stdlib.h>
#include <stdio.h>

int gcd(const int FIRST_NUM, const int SECOND_NUM) {
    if(FIRST_NUM % SECOND_NUM == 0) {
        return SECOND_NUM;
    }

    return gcd(SECOND_NUM, FIRST_NUM % SECOND_NUM);
}

int main(int argc, char** argv) {
    //for simplicity, this program assumes correct input
    const int NUMBER = atoi(argv[1]);
    const int MOD = atoi(argv[2]);

    //make sure NUMBER and MOD are coprimes, i.e. their gcd is 1
    if(gcd(NUMBER, MOD) != 1) {
        printf("There is no inverse mod %i for %i\n", MOD, NUMBER);
        return 0;
    }

    int inverse = 1;
    while(inverse < MOD && (inverse * NUMBER) % MOD != 1) {
        inverse++;
    }

    printf("inverse of %i mod %i = %i\n", NUMBER, MOD, inverse);
    return inverse;
}
