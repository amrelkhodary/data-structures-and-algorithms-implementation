#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* elements; //array of elements in the queue
    size_t size;
    int queue_start; //index of the first element in the queue
    int queue_end; //index of the last element in the queue
} queue;

queue* createqueue(size_t size) {
    int* elements = malloc(size * sizeof(int));
    if(!elements) {return NULL;}
    queue* nqueue = malloc(sizeof(queue));
    if(!nqueue) {free(elements); return NULL;}
    nqueue -> elements = elements;
    nqueue -> queue_start = -1;
    nqueue -> queue_end = -1;
    nqueue -> size = size;
    return nqueue;
}

void deletequeue(queue* queue) {
    free(queue -> elements);
    free(queue);
}

int enqueue(queue* queue, int element) {
    if(queue -> queue_start == -1 && queue -> queue_end == -1) {
        //special case: queue is empty
        //initialize queue_start alongside queue_end
        ++queue -> queue_start;
        queue -> elements[++queue -> queue_end] = element;
        return 0;
    }

   if((queue -> queue_end + 1) % queue -> size != queue -> queue_start) {
       queue -> queue_end = (queue -> queue_end + 1) % queue -> size;
       queue -> elements[queue -> queue_end] = element;
   } else {
       //queue is full
       printf("queue is full.., element %i discarded\n", element);
       return 1;
   }

   return 0;
}
int dequeue(queue* queue) {
    if(queue -> queue_start == -1 && queue -> queue_end == -1) {
        //queue is empty
        printf("queue is empty..\n");
        return 1;
    }

    //store the element to be dequeued, replace it with 0
    int returnval = queue -> elements[queue -> queue_start];
    queue -> elements[queue -> queue_start] = 0;

    if(queue -> queue_start == queue -> queue_end) {
        //there is only one element in the queue
        //reset the queue back to the empty state
        queue -> queue_start = -1;
        queue -> queue_end = -1;
        return returnval;
    }

    queue -> queue_start = (queue -> queue_start + 1) % queue -> size;
    return returnval;
}

void printqueue(queue* queue) {
    if(queue -> queue_start == -1 && queue -> queue_end == -1) {
       //queue is empty
       printf("queue: [empty]");
    }

    printf("queue: ");
    for(int i = 0; i<queue -> size; i++) {
        if(i == queue -> queue_start) {
           printf("*%i*\t", queue -> elements[i]);
        } else if(i == queue -> queue_end) {
           printf("+%i+\t", queue -> elements[i]);
        } else {
            printf("%i\t", queue -> elements[i]);
        }
    }
    printf("\n");
}

int hasMoreThanOneElement(queue* q) {
    if((q->queue_end != q->queue_start) && (q->queue_start != -1)) {
        return 1;
    }

    return 0;
}

int find_winner(int n, int k) {
    //fill up the queue
    queue* q = createqueue(n);
    for(int i = 1; i<=n; i++) {
        enqueue(q, i);
    }
    printqueue(q);

    while(hasMoreThanOneElement(q)) {
        //move k elements to the rear of the queue
        for(int i = 0; i<k; i++) {
            enqueue(q, dequeue(q));
        }
        dequeue(q); //delete k+1 element
        printqueue(q);
    }

    int winner = dequeue(q);
    deletequeue(q);
    return winner; //return remaining element
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
