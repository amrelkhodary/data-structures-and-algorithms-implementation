/*
    This program finds the Bezout Coefficients using the Extended Euclidean Algorithm
*/
#include <stdlib.h>
#include <stdio.h>

#define EVEN 0
#define ODD 1
int main(int argc, char** argv) {
    //for simplicity, this program assumes valid input
    const int BIGGER_NUMBER = atoi(argv[1]) >= atoi(argv[2]) ? atoi(argv[1]) : atoi(argv[2]);
    const int SMALLER_NUMBER = BIGGER_NUMBER == atoi(argv[1]) ? atoi(argv[2]) : atoi(argv[1]);
    int remainder;

    int smallernum = SMALLER_NUMBER, biggernum = BIGGER_NUMBER;
    int s_tempfirst = 1, s_tempsecond = 0, t_tempfirst = 0, t_tempsecond = 1;
    int even_or_odd = ODD;
    while(smallernum != 0) {
        even_or_odd = (even_or_odd == ODD) ? EVEN : ODD;
        if(even_or_odd == EVEN) {
           s_tempfirst = s_tempfirst - s_tempsecond * (biggernum / smallernum);
           t_tempfirst = t_tempfirst - t_tempsecond * (biggernum / smallernum);
        } else {
           s_tempsecond = s_tempsecond - s_tempfirst * (biggernum / smallernum);
           t_tempsecond = t_tempsecond - t_tempfirst * (biggernum / smallernum);
        }
        remainder = biggernum % smallernum;
        biggernum = smallernum;
        smallernum = remainder;
    }

    printf("%i = %i * %i + %i * %i\n", biggernum /*gcd*/, (even_or_odd == ODD ? s_tempfirst : s_tempsecond),
        BIGGER_NUMBER, (even_or_odd == ODD ? t_tempfirst : t_tempsecond), SMALLER_NUMBER);
    return 0;
}
