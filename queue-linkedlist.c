/*
 * this program implements a queue (more accurately, a circular queue) using a linked list
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node* right;
    struct node* left;
} node;

typedef struct {
   node* front;
   node* rear;
} queue;

queue* createqueue() {
    queue* nqueue = malloc(sizeof(queue));
   if(!nqueue) {
       return NULL;
   }
   nqueue -> front = NULL;
   nqueue -> rear = NULL;
   return nqueue;
}

void deletequeue(queue* queue) {
   if(!queue) {
      return;
   }
   node* current = queue -> front;
   if(!current) {
       return;
   }

   while(current -> left != NULL) {
       current = current -> left;
       free(current -> right);
   }

   free(current);
}

int enqueue(queue* queue, int element) {
    node* nnode = malloc(sizeof(node));
    if(!nnode) {
        return 1;
    }

    nnode -> val = element;
    if(queue -> front == NULL && queue -> rear == NULL) {
        //queue is empty
        nnode -> left = NULL;
        nnode -> right = NULL;
        queue -> front = nnode;
        queue -> rear = nnode;
    } else {
        nnode -> right = queue -> rear;
        nnode -> left = NULL;
        queue -> rear -> left = nnode;
        queue -> rear = queue -> rear -> left;
    }

    return 0;
}

int dequeue(queue* queue) {
    if(!queue) {
        return 1;
    }

    if(queue -> front == NULL && queue -> rear == NULL) {
        //queue is already empty
        printf("queue is already empty..\n");
    } else if(queue -> front == queue -> rear) {
        //queue has one element
        free(queue -> front);
        queue -> front = NULL;
        queue -> rear = NULL;
    } else {
        //queue has more than one element
        queue -> front = queue -> front -> left;
        free(queue -> front -> right);
        queue -> front -> right = NULL;
    }

    return 0;
}

int peek(queue* queue) {
    if(!queue) {
        return -1;
    }

    if(queue -> front == NULL && queue -> rear == NULL) {
        printf("cannot peak at an empty queue..\n");
        return -1;
    }

    return queue -> front -> val;
}

void printqueue(queue* queue) {
    if(!queue) {
        return;
    }

    if(queue -> front == NULL && queue -> rear == NULL) {
        printf("cannot print an empty queue..\n");
        return;
    }

    printf("queue: ");
    node* current = queue -> front;
    while(current -> left != NULL) {
        if(current == queue -> front) {
           printf("*%i*\t", current -> val);
        } else {
           printf("%i\t", current -> val);
        }

       current = current -> left;
    }
    printf("+%i+\n", current -> val);
}

int main(int argc, char** argv) {
    return 0;
}
