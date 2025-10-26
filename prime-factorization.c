/*
 * This program performs prime factorization on a given positive integer greater than one
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int findfactor_prime(const int NUMBER, const int START);

 int main(int argc, char** argv) {
     /*
      * for simplicity and brevity, this program assumes valid input
      */

      int number = atoi(argv[1]), start = 2, prime_factor = findfactor_prime(number, start);
      while(prime_factor != -1) {
         start = prime_factor;
         number /= prime_factor;
         prime_factor = findfactor_prime(number, start);
      }

      printf("prime factor: %i\n", number);

      return 0;
 }

 int findfactor_prime(const int NUMBER, const int START) {
     const int SQRT_NUMBER = (int) floor(sqrt(NUMBER));
     for(int i = START; i<=SQRT_NUMBER; i++) {
         if(NUMBER % i == 0) {
             printf("prime factor: %i\n", i);
             return i;
         }
     }
     return -1;
 }
