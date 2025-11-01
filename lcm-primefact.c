/*
 *  This program calculates the lcm of two integers by using prime factorization
 */

#include <stdlib.h>
#include <stdio.h>

 int main(int argc, char** argv) {
     //for simplicity, this program assumes valid input
     const int FIRST_NUMBER = atoi(argv[1]);
     const int SECOND_NUMBER = atoi(argv[2]);

     int temp_firstnum = FIRST_NUMBER, temp_secondnum = SECOND_NUMBER;
     int temp_foundnextprime = 0; //0 --> false, 1 --> true
     int current_prime = 2;
     int lcm = 1;
     while(!(temp_firstnum == 1 && temp_secondnum == 1)) {
         if((temp_firstnum % current_prime != 0) && (temp_secondnum % current_prime != 0)) {
             //current prime does not divide first or second num

             //update current prime
             temp_foundnextprime = 0; //0 --> false, 1 --> true
             while(!temp_foundnextprime) {
                 current_prime++;
                 for(int i = 2; i<current_prime; i++) {
                     if(current_prime % i == 0) {
                         //found a number that divides the current value of current_prime
                         //therefore it is not a prime
                         //continue until a prime is found
                         continue;
                     }
                 }

                 //terminate the loop
                 temp_foundnextprime = 1;
             }
         }
         else if((temp_firstnum % current_prime == 0) && (temp_secondnum % current_prime == 0)) {
             temp_firstnum /= current_prime;
             temp_secondnum /= current_prime;
             lcm *= current_prime;
         }

         else if(temp_firstnum % current_prime == 0) {
            //if the current prime divides the first num; indeed divide the first num
            temp_firstnum /= current_prime;
            lcm *= current_prime;
         }

         else {
             //if the current prime divides the second num; indeed divide the second num
             temp_secondnum /= current_prime;
             lcm *= current_prime;
         }
     }

     printf("lcm: %i\n", lcm);
     return 0;
 }
