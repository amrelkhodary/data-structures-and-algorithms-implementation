/*
    This program multiplies two binary numbers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void shiftleft(char* string);
void add(char* first_addend, char* second_addend);

int main(int argc, char** argv) {
    //input validation
    if(argc == 3) {
        int i = 0;
        while(argv[1][i] != '\0')  {
            if(!(argv[1][i] == '0' || argv[1][i] == '1')) {
                return 1;
            }
            
            i++;
        }

        int j = 0;
        while(argv[2][j] != '\0')  {
            if(!(argv[2][j] == '0' || argv[2][j] == '1')) {
                return 1;
            }

            j++;
        }
    } else {
        return 1;
    }


    //initiailize necessary variables and arrays 
    const int MULTIPLICAND_SIZE = strlen(argv[1]) + 1,
              MULTIPLIER_SIZE = strlen(argv[2]) + 1, 
              PRODUCT_SIZE = strlen(argv[1]) + strlen(argv[2]), 
              MAX_SIZE = PRODUCT_SIZE;

    char *multiplicand, *multiplier, *product; 

    multiplicand = (char*) malloc(MAX_SIZE * sizeof(char));
    multiplicand[MAX_SIZE - 1] = '\0';
    memset(multiplicand, '0', MAX_SIZE - 1);
    strcpy(multiplicand + (MAX_SIZE - MULTIPLICAND_SIZE), argv[1]);

    multiplier = (char*) malloc(MULTIPLIER_SIZE * sizeof(char));
    multiplier[MULTIPLIER_SIZE - 1] = '\0';
    memset(multiplier, '0', MULTIPLIER_SIZE - 1);
    strcpy(multiplier, argv[2]);

    product = (char*) malloc(MAX_SIZE * sizeof(char));
    product[MAX_SIZE - 1] = '\0';
    memset(product, '0', MAX_SIZE - 1);

    //implement standard multiplication algorithm 
    int i = MULTIPLIER_SIZE - 2; //index to point at LSB of the multiplier 
    while(i >= 0) {
        if(multiplier[i] == '1') {
            //add shifted multiplicand to product
            add(product, multiplicand);
        }

        shiftleft(multiplicand);
        i--;
    }

    printf("product: %s\n", product);
    return 0;
}

void shiftleft(char* string) {
    if(strlen(string) == 1){
        return;
    }

    int i = 0, j = 1;
    while(string[j] != '\0') {
        string[i] = string[j];
        i++; j++;
    }

    string[i] = '0';
}

void add(char* first_addend, char* second_addend) {
    int i = strlen(first_addend);
    int sum = 0, carry = 0; 

    while(i >= 0) {
        switch ((first_addend[i] - '0') + (second_addend[i] - '0') + carry)
        {
        case 0:
            carry = 0; 
            first_addend[i] = '0';
            break;
        case 1:
            carry = 0;
            first_addend[i] = '1';
            break;
        case 2:
            carry = 1;
            first_addend[i] = '0';
            break;
        case 3:
            carry = 1;
            first_addend[i] = '1';
            break;
        default:
            break;
        }

        i--;
    }

}