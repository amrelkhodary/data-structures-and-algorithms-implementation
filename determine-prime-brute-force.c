/*
 * This program implements a brute force algorithm to determine if a number is prime.
 * It is an application of the theorem that states that a number is prime if it doesn't have
 * any prime factors less than or equal to square root of that number
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

 int main(int argc, char** argv) {
     /*
      * for brevity and simplicity, this program assumes valid input
      */

     const int NUMBER = atoi(argv[1]);
     const int SQRT_NUMBER = (int) floor(sqrt(NUMBER));

     for(int i = 2; i<=SQRT_NUMBER; i++) {
         if(NUMBER % i == 0) {
             printf("Divisable by %i, therefore not prime.\n", i);
             return 0;
         }
     }

     printf("Prime.\n");
     return 0;
 }
