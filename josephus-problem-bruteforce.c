/*
 * [PROBLEM DESCRIPTION TAKEN FROM DATA STRUCTURES USING C TEXTBOOK BY Reema Thareja]
        In Josephus problem, n people stand in a circle waiting to be executed. The counting starts at some
    point in the circle and proceeds in a specific direction around the circle. In each step, a certain
    number of people are skipped and the next person is executed (or eliminated). The elimination
    of people makes the circle smaller and smaller. At the last step, only one person remains who is
    declared the ‘winner’.
        Therefore, if there are n number of people and a number k which indicates that k–1 people are
    skipped and k–th person in the circle is eliminated, then the problem is to choose a position in
    the initial circle so that the given person becomes the winner.
    For example, if there are 5 (n) people and every second (k) person is eliminated, then first
    the person at position 2 is eliminated followed by the person at position 4 followed by person at
    position 1 and finally the person at position 5 is eliminated. Therefore, the person at position 3
    becomes the winner.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void fill_pplarr(int* arr, int n) {
    for(int i = 0; i<n; i++) {
        arr[i] = i+1;
    }
}

int nextindex(int index, int arrsize) {
    return (index + 1) % arrsize;
}
int getindex(int whereami) {return whereami - 1;}
int getwhereami(int index) {return index + 1;}
int move(int* pplarr, int whereami, int n) {
    int index = getindex(whereami);

    //skip all dead ppl
    while(pplarr[nextindex(index, n)] == -1) {
        index = nextindex(index, n);
    }

    return getwhereami(nextindex(index, n));
}

int find_winner_bf(int n, int k) {
    int ppl[n]; fill_pplarr(ppl, n);
    int whereami = 1, deadcount = 0, left_to_skip = k;

    while(deadcount != n - 1) {
        if(left_to_skip == 0) {
            ppl[getindex(whereami)] = -1; deadcount++;
            whereami = move(ppl, whereami, n);
            left_to_skip = k;
        }
        whereami = move(ppl, whereami, n);
        left_to_skip--;
    }

   return whereami;
}

int isnumber(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        if(!isdigit(str[i])) {
            return 0;
        }
        i++;
    }

    return 1;
}

int main(int argc, char** argv) {
    if(argc != 3 || !isnumber(argv[1]) || !isnumber(argv[2])) {fprintf(stderr, "invalid input.\n"); return 1;}
    int n = atoi(argv[1]), k = atoi(argv[2]);
    printf("winner: %i\n", find_winner_bf(n, k));
    return 0;
}
