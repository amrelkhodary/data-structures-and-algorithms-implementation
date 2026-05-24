/*
 * this program implements a queue (more accurately, a circular queue) using an array
 */

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
int main(int argc, char** argv) {
    return 0;
}
