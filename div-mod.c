/*
    given two integers a and d, such that d > 0 this program calculates a div d and a mod d
*/
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool isNumber(const char* STRING);
int convertStrToNumber(const char* STRING);

int main(int argc, char** argv) {
    if(!(argc == 3 && isNumber(argv[1]) && isNumber(argv[2]))) {
        return 1;
    }

    /*
        remember the division algorithm
        a = d * q + r 
    */
    int a = convertStrToNumber(argv[1]);
    int d = convertStrToNumber(argv[2]);
    int q = 0;
    int r = abs(a);

    if(d <= 0) {return 2;}

    while (r >= d) {
        q += 1;
        r -= d; 
    }

    if(a < 0) {
        if(r == 0) {
            q = -q;
        } else {
            q = -(q + 1);
            r = d - r;
        }
    } 

    printf("%i div %i = %i, %i mod %i = %i\n", a, d, q, a, d, r);
    return 0;
}

bool isNumber(const char* STRING) {
    if(STRING[0] == '-') {STRING+=1;}
    int i = 0;
    while(STRING[i] != '\0') {
        if(!isdigit(STRING[i])) {
            return false;
        }

        i++;
    }

    return true;
}

int convertStrToNumber(const char* STRING) {
    bool isNegative = (STRING[0] == '-') ? true : false;
    if(isNegative) {STRING += 1;}
    int number = 0;
    int i = strlen(STRING) - 1; //index pointing at the LSB 

    while(i >= 0) {
        number += (STRING[i] - '0') * (int) pow(10, strlen(STRING) - 1 - i);
        i--;
    }

    return isNegative ? -1 * number : number;
}

