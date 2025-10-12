/*
    This program implements the algorithm for the addition of two binary numbers 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

void add(const char* FIRST_NUMBER, const char* SECOND_NUMBER, char* result, const size_t SIZE);
bool isValidInput(int argc, char** argv);
bool isBitString(const char* STRING);

int main(int argc, char** argv) {
    //make sure input is valid
    if(!isValidInput(argc, argv)) {
        fprintf(stderr, "Invalid Input.\n");
        return -1;
    }

    //calcualte sizes of first and second array, and calculate what the size of the result array would be 
    size_t sizes[5]; 
    
    sizes[0] = strlen(argv[1]) + 1;//first arr size
    sizes[1] = strlen(argv[2]) + 1; //second arr size
    sizes[2] = (sizes[0] == sizes[1]) ? 0 :     //which is bigger? 0 -> equal, 1 -> first bigger, 2 -> second bigger
               (sizes[0] > sizes[1])  ? 1 : 2;
    sizes[3] = (sizes[2] < 2) ? sizes[0] + 1 : sizes[1] + 1; //result arr size
    sizes[4] = abs(sizes[1] - sizes[0]); //difference betewee both arrays sizes

    char result[sizes[3]];
    result[sizes[3] - 1] = '\0';
    char temp[sizes[3] - 1];
    temp[sizes[3] - 2] = '\0';
    //add leading zeros to the number with the lower amount of digits, then add
    switch (sizes[2])
    {
    case 0:
        //numbers are of the same length, we can add them directly
        add(argv[1], argv[2], result, sizes[3] - 1);
        break;
    case 1: 
        //second number is smaller than the first, so we need to add leading zeros to it 
        strcpy(temp + sizes[4], argv[2]);
        memset(temp, '0', sizes[4]);

        //now we can add
        add(argv[1], temp, result, sizes[3] - 1);
        break;
    case 2: 
        //first number is smaller than the second, so we need to add leading zeros to it 
        strcpy(temp + sizes[4], argv[1]);
        memset(temp, '0', sizes[4]);

        //now we can add
        add(temp, argv[2], result, sizes[3] - 1);
        break;
    default:
        break;
    }
}


void add(const char* FIRST_NUMBER, const char* SECOND_NUMBER, char* result, const size_t SIZE) {
    int index_first = SIZE - 2, index_second = SIZE - 2, index_result = SIZE - 1;
    int sum = 0, carry = 0, temp = 0;

    while(index_first != -1) {
        temp = (FIRST_NUMBER[index_first] - '0') + (SECOND_NUMBER[index_second] - '0') + (carry); 
        switch (temp)
        {
        case 0:
            sum = 0; carry = 0;
            break;
        case 1:
            sum = 1; carry = 0; 
            break;
        case 2: 
            sum = 0; carry = 1; 
            break;
        case 3:
            sum = 1; carry = 1; 
            break;
        default:
            break;
        }

        result[index_result] = sum + '0';
        index_first--; index_second--; index_result--;

    }

    result[0] = carry + '0';
    printf("  %s\n+ %s\n=%s\n", FIRST_NUMBER, SECOND_NUMBER, result);
}

bool isValidInput(int argc, char** argv) {
    if(argc == 3) {
        if(isBitString(argv[1]) && isBitString(argv[2])) {
            return true;
        }
    }

    return false;
}

bool isBitString(const char* STRING) {
    int i = 0;
    while(STRING[i] != '\0') {
        if(!(STRING[i] == '1' || STRING[i] == '0')) {
            return false;
        }

        i++;
    }

    return true;
}
 