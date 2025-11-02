/*
 * This program implements the iterative version of the Euclidean Algorithm
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    /*
     *  Explanation of the Euclidean algorithm
     *  suppose we want to find the gcd of two numbers A and B
     *  further suppose that A >= B
     *  by the division algorithm
     *  A = d * B + r
     *  the idea here is that gcd(A, B) is the same as gcd(B, r), i.e. we can reduce the problem
     *  of finding the gcd(A,B) to finding gcd(B, r)
     *  so we keep repeating this until r is finally zero
     */

    //for simplicity, this program assumes valid input
    const int FIRST_NUMBER = atoi(argv[1]);
    const int SECOND_NUMBER = atoi(argv[2]);

    int biggernum = (FIRST_NUMBER >= SECOND_NUMBER) ? FIRST_NUMBER : SECOND_NUMBER;
    int smallernum = (biggernum == FIRST_NUMBER) ? SECOND_NUMBER : FIRST_NUMBER;
    int remainder;
    while(smallernum != 0) {
        remainder = biggernum % smallernum;
        biggernum = smallernum;
        smallernum = remainder;
    }

    printf("gcd: %i\n", biggernum);
    return 0;
}
