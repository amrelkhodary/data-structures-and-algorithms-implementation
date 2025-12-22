/*
    This program implements arithmetic with large numbers by applying the
   Chinese Remainder Theorem. It states that any number a could be represented
   uniquely as a tuple (a mod m1, a mod m2, ..., a mod mn) provided that a is
   smaller than m1 * m2 * ... * mn

    For example, numbers less than 12 could be represented uniquely by using
   tuples of the number mod 3, and the number mod 4 7 := (7 mod 3, 7 mod 4) =
   (1, 3) <-- unique representation

    To do arithmetic with such representations, you just do arithmetic as you
   normally would and retake the appropriate mod. For example 7 + 2 := (1, 3) +
   (2, 2)
          := (3 mod 3, 5 mod 4)
          := (0, 1)

    Now to convert a tuple result (a1, a2, ..., an) back to a normal number, you
   to to solve the following system of congruences x ≡ a1 (mod m1) x ≡ a2 (mod
   m2)
    .
    .
    x ≡ an (mod mn)

    For example, the last result (0, 1) could be converted back by solving this
   system x ≡ 0 (mod 3) x ≡ 1 (mod 4)

    the result would be: 9! Which is exactly what 7 + 2 is. This program does
   not do the final reconversion part as that would take too much time which the
   author doesn't currently have) to properly implement.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
  size_t size;
  unsigned long long *values;
} tuple;

void printtuple(tuple *tup) {
  printf("(");
  for (int i = 0; i < tup->size; i++) {
    if (i == tup->size - 1) {
      printf("%llu", tup->values[i]);
      break;
    }
    printf("%llu, ", tup->values[i]);
  }
  printf(")");
}

int main() {
  /*program assumes correct inputs for simplicity*/

  size_t moduli_count = 0;
  printf("Please enter the number of moduli you want to use for your large "
         "number comp. arithmetic system.\n");
  scanf(" %lu", &moduli_count);

  int moduli[moduli_count];
  printf("Please enter each of your moduli, pressing enter after each one.\n");
  for (int i = 0; i < moduli_count; i++) {
    scanf(" %i", moduli + i);
  }

  unsigned long long M = 1;
  for (int i = 0; i < moduli_count; i++) {
    M *= moduli[i];
  }

  printf("You can perform arithmetic on numbers (and obtain results) that are "
         "less than %llu\n",
         M);

  unsigned long long first_num, second_num;
  char operation;
  printf("Please enter the two numbers you want to perform an operation on, "
         "along with the operation that you want to perform\n");
  printf("+ for plus, * for multiply, - for sub, / for divide\n");
  scanf(" %llu", &first_num), scanf(" %llu", &second_num),
      scanf(" %c", &operation);

  unsigned long long first_tuple_values[moduli_count];
  unsigned long long second_tuple_values[moduli_count];
  unsigned long long result_tuple_values[moduli_count];

  for (int i = 0; i < moduli_count; i++) {
    first_tuple_values[i] = first_num % moduli[i];
    second_tuple_values[i] = second_num % moduli[i];
    switch (operation) {
    case '+':
      result_tuple_values[i] =
          (first_tuple_values[i] + second_tuple_values[i]) % moduli[i];
      break;
    case '-':
      result_tuple_values[i] =
          (first_tuple_values[i] - second_tuple_values[i]) % moduli[i];
      break;
    case '*':
      result_tuple_values[i] =
          (first_tuple_values[i] * second_tuple_values[i]) % moduli[i];
      break;
    case '/':
      result_tuple_values[i] =
          (first_tuple_values[i] / second_tuple_values[i]) % moduli[i];
      break;
    default:
        printf("invalid op\n");
    }
  }

  tuple first_tuple = {moduli_count, first_tuple_values},
        second_tuple = {moduli_count, second_tuple_values},
        result_tuple = {moduli_count, result_tuple_values};

  printf("%llu is represented as ", first_num), printtuple(&first_tuple); printf("\n");
  printf("%llu is represented as ", second_num), printtuple(&second_tuple); printf("\n");
  printf("result: "), printtuple(&result_tuple); printf("\n");
  return 0;
}
