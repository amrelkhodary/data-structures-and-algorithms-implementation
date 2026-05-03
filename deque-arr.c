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
   return 0;
}
