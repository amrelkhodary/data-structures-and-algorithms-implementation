/*
 * this program implements a deque using a circular array
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* elements;
    size_t arrsize;
    int left;
    int right;
} deque;

int isempty(deque* dq) {
    if(dq -> left == -1 && dq -> right == -1) {
        return 1;
    }

    return 0;
}

//euclidean mod
int mod(int a, int d) {
    return ((a % d) + d) % d;
}

deque* createdeque(size_t size) {
    deque* dq = malloc(sizeof(deque));
    if(!dq) {return NULL;}
    int* elements = calloc(size, sizeof(int));
    if(!elements) {free(dq); return NULL;}

    dq -> elements = elements;
    dq -> left = -1;
    dq -> right = -1;
    dq -> arrsize = size;
    return dq;
}

void deletedeque(deque* dq) {
    if(dq) {
        if(dq -> elements) {
            free(dq -> elements);
        }
        free(dq);
    }
}


int insert_left(deque* dq, int element) {
    if(!dq || !dq -> elements) {return 1;}
    if(isempty(dq)) {
        dq -> left = dq -> arrsize / 2;
        dq -> right = dq -> arrsize / 2;
        dq -> elements[dq -> left] = element;
        return 0;
    }

    if(mod(dq -> left - 1, dq -> arrsize)== dq -> right) {
       //full deque
       printf("deque is full..\nelement %i discarded\n", element);
       return 1;
    } else {
        dq -> left = mod(dq -> left - 1, dq -> arrsize);
        dq -> elements[dq -> left] = element;
    }

    return 0;
}

int insert_right(deque* dq, int element) {
    if(!dq || !(dq -> elements)) {return 1;}
    if(isempty(dq)) {
        dq -> left = dq -> arrsize / 2;
        dq -> right = dq -> arrsize / 2;
        dq -> elements[dq -> left] = element;
        return 0;
    }

    if((dq -> right + 1) % dq -> arrsize == dq -> left) {
       //full deque
       printf("deque is full..\nelement %i discarded\n", element);
       return 1;
    } else {
        dq -> right = (dq -> right + 1) % dq -> arrsize;
        dq -> elements[dq -> right] = element;
    }

    return 0;
}

int remove_left(deque* dq) {
    if(!dq || !dq->elements) {return 1;}
    if(isempty(dq)) {
       printf("cannot delete an element from an empty deque..\n");
       return 1;
    }
    dq -> elements[dq -> left] = 0;
    if(dq -> left == dq -> right) {
        //deque has only one element
        //reset deque back to empty state
        dq -> left = -1;
        dq -> right = -1;
    } else {
        //deque has more than one element
        dq -> left = (dq -> left + 1) % dq -> arrsize;
    }
    return 0;
}

int remove_right(deque* dq) {
    if(!dq || !dq->elements) {return 1;}
    if(isempty(dq)) {
       printf("cannot delete an element from an empty deque..\n");
       return 1;
    }
    dq -> elements[dq -> right] = 0;
    if(dq -> left == dq -> right) {
        //deque has only one element
        //reset deque back to empty state
        dq -> left = -1;
        dq -> right = -1;
    } else {
        //deque has more than one element
        dq -> right = mod(dq -> right - 1, dq -> arrsize);
    }
    return 0;
}

int peek_left(deque* dq) {
    if(!dq || !dq -> elements) {return 1;}
    if(isempty(dq)) {printf("Cannot peek at an empty deque..\n"); return 1;}
    return dq -> elements[dq -> left];
}

int peek_right(deque* dq) {
    if(!dq || !dq->elements) {return 1;}
    if(isempty(dq)) {printf("Cannot peak at an empty deque..\n"); return 1;}
    return dq -> elements[dq -> right];
}

void printdeque(deque* dq) {
    if(!dq || !dq -> elements) {return;}
    if(isempty(dq)) {printf("deque: [empty]\n"); return;}
    printf("deque: ");
    for(int i = 0; i<dq -> arrsize; i++) {
        if(i == dq -> left) {
            printf("L%iL ", dq -> elements[i]);
        } else if(i == dq -> right) {
            printf("R%iR ", dq -> elements[i]);
        } else {
           printf("%i ", dq -> elements[i]);
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    // TC1: Basic insert_right (queue-style)
    deque* dq = createdeque(8);
    insert_right(dq, 10); printdeque(dq);
    insert_right(dq, 20); printdeque(dq);
    insert_right(dq, 30); printdeque(dq);
    printf("peek_left=%d  peek_right=%d\n", peek_left(dq), peek_right(dq));
    deletedeque(dq);

    // TC2: Basic insert_left (stack-style)
    dq = createdeque(8);
    insert_left(dq, 10); printdeque(dq);
    insert_left(dq, 20); printdeque(dq);
    insert_left(dq, 30); printdeque(dq);
    printf("peek_left=%d  peek_right=%d\n", peek_left(dq), peek_right(dq));
    deletedeque(dq);

    // TC3: Mixed insert_left + insert_right
    dq = createdeque(8);
    insert_right(dq, 5);  printdeque(dq);
    insert_left(dq, 3);   printdeque(dq);
    insert_right(dq, 7);  printdeque(dq);
    insert_left(dq, 1);   printdeque(dq);
    insert_right(dq, 9);  printdeque(dq);
    deletedeque(dq);

    // TC4: remove_left drain (FIFO)
    dq = createdeque(8);
    insert_right(dq, 100);
    insert_right(dq, 200);
    insert_right(dq, 300);
    printdeque(dq);
    remove_left(dq); printdeque(dq);
    remove_left(dq); printdeque(dq);
    remove_left(dq); printdeque(dq);
    remove_left(dq);                   // warns: empty
    deletedeque(dq);

    // TC5: remove_right drain (LIFO)
    dq = createdeque(8);
    insert_right(dq, 11);
    insert_right(dq, 22);
    insert_right(dq, 33);
    printdeque(dq);
    remove_right(dq); printdeque(dq);
    remove_right(dq); printdeque(dq);
    remove_right(dq); printdeque(dq);
    remove_right(dq);                  // warns: empty
    deletedeque(dq);

    // TC6: Fill to capacity then overflow
    dq = createdeque(6);
    for(int i = 1; i <= 5; i++) { insert_right(dq, i*10); printdeque(dq); }
    insert_right(dq, 999);             // warns: full
    insert_left(dq, 888);              // warns: full
    deletedeque(dq);

    // TC7: Wrap-around via right inserts + left removes
    dq = createdeque(6);
    insert_right(dq, 1);
    insert_right(dq, 2);
    insert_right(dq, 3);
    printdeque(dq);
    remove_left(dq); printdeque(dq);
    remove_left(dq); printdeque(dq);
    insert_right(dq, 4); printdeque(dq);
    insert_right(dq, 5); printdeque(dq);
    insert_right(dq, 6); printdeque(dq);
    deletedeque(dq);

    // TC8: Wrap-around via left inserts + right removes
    dq = createdeque(6);
    insert_left(dq, 1);
    insert_left(dq, 2);
    insert_left(dq, 3);
    printdeque(dq);
    remove_right(dq); printdeque(dq);
    remove_right(dq); printdeque(dq);
    insert_left(dq, 4); printdeque(dq);
    insert_left(dq, 5); printdeque(dq);
    insert_left(dq, 6); printdeque(dq);
    deletedeque(dq);

    // TC9: Single-element edge cases
    dq = createdeque(6);
    insert_right(dq, 42); printdeque(dq);
    printf("peek_left=%d  peek_right=%d\n", peek_left(dq), peek_right(dq));
    remove_left(dq);  printdeque(dq);
    insert_left(dq, 99); printdeque(dq);
    printf("peek_left=%d  peek_right=%d\n", peek_left(dq), peek_right(dq));
    remove_right(dq); printdeque(dq);
    deletedeque(dq);

    // TC10: Peek on empty
    dq = createdeque(6);
    peek_left(dq);                     // warns: empty
    peek_right(dq);                    // warns: empty
    printdeque(dq);
    deletedeque(dq);

    // TC11: Interleaved insert/remove stress (cycling data through)
    dq = createdeque(8);
    for(int i = 1; i <= 4; i++) insert_right(dq, i);
    printdeque(dq);
    for(int round = 0; round < 6; round++) {
        remove_left(dq);
        insert_right(dq, (round+5)*11);
        printdeque(dq);
    }
    deletedeque(dq);

    // TC12: Alternating insert_left / remove_right
    dq = createdeque(8);
    for(int i = 1; i <= 4; i++) insert_left(dq, i*5);
    printdeque(dq);
    for(int i = 0; i < 4; i++) {
        printf("peek_right=%d -> ", peek_right(dq));
        remove_right(dq);
        printdeque(dq);
    }
    deletedeque(dq);
   return 0;
}
