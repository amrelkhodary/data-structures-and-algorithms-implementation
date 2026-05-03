/*
    this program implements a deque using a doubly-linked list
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* left;
    struct node* right;
    int val;
} node;

typedef struct {
    node* rightmost;
    node* leftmost;
} deque;

deque* createdeque() {
    deque* dq = malloc(sizeof(deque));
    if(!dq) {
       return NULL;
    }

    dq -> rightmost = NULL;
    dq -> leftmost = NULL;

    return dq;
}

void deletedeque(deque* dq) {
    if(dq) {
        node* current = dq -> rightmost;
        if(current) {
            while(current -> left) {
                current = current -> left;
                free(current -> right);
            }
            free(current);
        }
        free(dq);
    }
}

int isempty(deque* dq) {
    if(dq -> leftmost == NULL && dq -> rightmost == NULL) {
        return 1;
    }

    return 0;
}

int insert_right(deque* dq, int element) {
    if(!dq) {return 1;}
    node* nnode = malloc(sizeof(node));
    if(!nnode) {
        return 1;
    }
    nnode -> val = element;

    if(isempty(dq)) {
        nnode -> left = NULL;
        nnode -> right = NULL;
        dq -> leftmost = nnode;
        dq -> rightmost = nnode;
    } else {
       nnode -> left = dq -> rightmost;
       nnode -> right = NULL;
       dq -> rightmost -> right = nnode;
       dq -> rightmost = nnode;
    }
    return 0;
}

int insert_left(deque* dq, int element) {
    if(!dq) {return 1;}
    node* nnode = malloc(sizeof(node));
    if(!nnode) {
        return 1;
    }
    nnode -> val = element;

    if(isempty(dq)) {
        nnode -> left = NULL;
        nnode -> right = NULL;
        dq -> leftmost = nnode;
        dq -> rightmost = nnode;
    } else {
       nnode -> right = dq -> leftmost;
       nnode -> left = NULL;
       dq -> leftmost -> left = nnode;
       dq -> leftmost = nnode;
    }
    return 0;
}

int remove_right(deque* dq) {
    if(!dq) {return 1;}
    if(isempty(dq)) {
        printf("cannot remove an element from an empty deque..\n");
        return 1;
    }
    if(dq -> leftmost == dq -> rightmost) {
        //deque has one element
        free(dq -> leftmost); //or dq -> rightmost for that matter it wouldn't make a difference
        //reset deque back to empty state (leftmost, rightmost = null)
        dq -> leftmost = NULL;
        dq -> rightmost = NULL;
    } else {
        dq -> rightmost = dq -> rightmost -> left;
        free(dq -> rightmost -> right);
        dq -> rightmost -> right = NULL;
    }

    return 0;
}

int remove_left(deque* dq) {
    if(!dq) {return 1;}
    if(isempty(dq)) {
        printf("cannot remove an element from an empty deque..\n");
        return 1;
    }
    if(dq -> leftmost == dq -> rightmost) {
        //deque has one element
        free(dq -> leftmost); //or dq -> rightmost for that matter it wouldn't make a difference
        //reset deque back to empty state (leftmost, rightmost = null)
        dq -> leftmost = NULL;
        dq -> rightmost = NULL;
    } else {
        dq -> leftmost = dq -> leftmost -> right;
        free(dq -> leftmost -> left);
        dq -> leftmost -> left = NULL;
    }

    return 0;
}
int peek_right(deque* dq) {
   if(!dq) {return 1;}
   if(isempty(dq)) {
       printf("cannot peek at an empty deque..\n");
       return 1;
   }
   return dq -> rightmost -> val;
}

int peek_left(deque* dq) {
    if(!dq) {return 1;}
    if(isempty(dq)) {
        printf("cannot peek at an empty deque..\n");
        return 1;
    }
    return dq -> leftmost -> val;
}

void printdeque(deque* dq) {
    //print elements leftmost to rightmost
    if(!dq) {return;}
    if(isempty(dq)) {
        printf("deque --> [empty]\n");
        return;
    }
    printf("deque --> ");
    node* current = dq -> leftmost;
    while(current -> right) {
        printf("%i\t", current -> val);
        current = current -> right;
    }
    printf("%i\n", current -> val);
}

int main(int argc, char** argv) {
    return 0;
}
