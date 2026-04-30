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
    queue* q = createqueue();

    // TEST 1: Basic Enqueue
    printf("TEST 1: Basic Enqueue\n");
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);
    printqueue(q);

    // TEST 2: Peek
    printf("\nTEST 2: Peek\n");
    printf("peek() = %d\n", peek(q));
    printqueue(q);

    // TEST 3: Dequeue One-by-One
    printf("\nTEST 3: Dequeue One-by-One\n");
    peek(q); dequeue(q); printqueue(q);
    peek(q); dequeue(q); printqueue(q);
    peek(q); dequeue(q); printqueue(q);
    peek(q); dequeue(q); printqueue(q);
    peek(q); dequeue(q); printqueue(q);

    // TEST 4: Dequeue from Empty
    printf("\nTEST 4: Dequeue from Empty\n");
    dequeue(q);

    // TEST 5: Peek on Empty
    printf("\nTEST 5: Peek on Empty\n");
    printf("peek() = %d\n", peek(q));

    // TEST 6: Single Element
    printf("\nTEST 6: Single Element\n");
    enqueue(q, 99);
    printqueue(q);
    printf("peek() = %d\n", peek(q));
    dequeue(q);
    printqueue(q);

    // TEST 7: Interleaved
    printf("\nTEST 7: Interleaved Enqueue/Dequeue\n");
    enqueue(q, 100); enqueue(q, 200); printqueue(q);
    dequeue(q);                       printqueue(q);
    enqueue(q, 300);                  printqueue(q);
    dequeue(q);                       printqueue(q);
    dequeue(q);                       printqueue(q);

    // TEST 8: Large Batch
    printf("\nTEST 8: Large Batch (50 elements)\n");
    for (int i = 1; i <= 50; i++) enqueue(q, i);
    printqueue(q);
    printf("peek() = %d\n", peek(q));
    for (int i = 0; i < 25; i++) dequeue(q);
    printqueue(q);
    printf("peek() = %d\n", peek(q));
    for (int i = 0; i < 25; i++) dequeue(q);
    printqueue(q);

    // TEST 9: Re-use After Full Drain
    printf("\nTEST 9: Re-use After Full Drain\n");
    enqueue(q, 7);
    enqueue(q, 8);
    enqueue(q, 9);
    printqueue(q);

    // TEST 10: Alternating Single Enqueue/Dequeue
    printf("\nTEST 10: Alternating Single Enqueue/Dequeue\n");
    while (q->front) dequeue(q);
    for (int i = 0; i < 10; i++) {
        enqueue(q, i * 5);
        printqueue(q);
        dequeue(q);
        printqueue(q);
    }

    deletequeue(q);
    free(q);
    return 0;
    return 0;
}
