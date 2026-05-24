#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>


int find_winner(int n, int k) {

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
    printf("winner: %i\n", find_winner(n, k));
    return 0;
}
