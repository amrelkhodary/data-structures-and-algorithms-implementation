/*
 * this program was written to solidify my understanding of the concept of significant figures in science.
 */

#include <stdio.h>
#include <math.h>

typedef enum {
    exact,
    inexact
} numtype;

typedef struct {
    char* numstr;
    size_t numstr_size;
    numtype type;
} number ;

// 0 --> false, 1 --> true
int has_decimalplaces(number* num) {
    for(int i = 0; i<num->numstr_size; i++) {
        if(num->numstr[i] == '.') {
           return 1;
        }
    }

    return 0;
}

int countsigfigs(number* num) {
    if(num->type == exact) {
        return -1;  //exact numbers are said to have infinite significant figures
                    //use -1 to mean infinity
    }

   //check if the number has a decimcal point
   int has_decimalpt = 0;
   for(int i = 0; i<num->numstr_size; i++) {
       if(num->numstr[i] == '.') {
           has_decimalpt = 1;
           break;
       }
   }

   int sigfig_count = (has_decimalpt) ? num->numstr_size - 1 : num->numstr_size; //assume sigfig count is all characters in the numstr in the beginning
                                                                                 //remove decimalpt from count if it exists
   int index = 0;
   //skip leading zeros
   while(num->numstr[index] == '0' || num->numstr[index] == '.') {
      if(num->numstr[index] == '.') {
          index++;
          continue;
      }

      sigfig_count--;
      index++;
   }

   if(!has_decimalpt) {
       //skip trailing zeros
          index = num->numstr_size-1;
          while(num->numstr[index] == '0') {
              sigfig_count--;
              index--;
          }
   }

   return sigfig_count;
}

int main(int argc, char** argv) {

    return 0;
}
