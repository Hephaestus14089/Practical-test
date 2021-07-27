#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {

    int capacity;
    int *arr;
    int length;
};

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* new_priorityqueue() {

    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));

    pq->capacity = 0;
    pq->arr = NULL;
    pq->length = 0;

    return pq;
} // end of new_priorityqueue()

void swap(int *x, int *y) {

    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
} // end of swap(int*, int*)

void handle_insertion(PriorityQueue *pq, int index) {

    if (index == 0) { return; }

    int *arr = pq->arr;
    int parent_index = (index - 1) / 2;

    if (arr[index] < arr[parent_index]) {

        swap((arr + index), (arr + parent_index));
        handle_insertion(pq, parent_index);
    }
} // end of handle_insertion(PriorityQueue, int)

void handle_deletion(PriorityQueue *pq, int index) {

    int *arr = pq->arr;
    int lchild_index = 2 * index + 1;
    int rchild_index = 2 * index + 2;

    if (lchild_index >= pq->length) { return; }

    if (arr[lchild_index] < arr[index]) {
        
        swap((arr + index), (arr + lchild_index));
        handle_deletion(pq, lchild_index);
    }

    if (rchild_index >= pq->length) { return; }

    if (arr[rchild_index] < arr[index]) {
        
        swap((arr + index), (arr + rchild_index));
        handle_deletion(pq, rchild_index);
    }

} // end of handle_deletion(PriorityQueue, int)

void insert(PriorityQueue *pq, int item) {

    if (pq->length == pq->capacity) { return; }

    int *arr = pq->arr;

    arr[pq->length] = item;

    pq->length = pq->length + 1;

    handle_insertion(pq, pq->length - 1);
} // end of insert(PriorityQueue*, int)

void delete(PriorityQueue *pq) {

    if (!pq->length) { return; }

    int *arr = pq->arr;

    pq->length = pq->length - 1;

    swap(arr, (arr + pq->length));

    handle_deletion(pq, 0);
} // end of delete(PriorityQueue*)


void display_arr(int *arr, int len) {

    if (!len) {
        
        printf("Priority Queue is empty\n");
        return;
    }

    int i = 0;
    for (; i < len; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
} // end of display_arr(int*, int)


// int main() {

//     PriorityQueue *pq = new_priorityqueue();

//     pq->capacity = 15;
//     pq->arr = (int*)malloc(sizeof(int) * pq->capacity);

//     insert(pq, 8);
//     insert(pq, 6);
//     insert(pq, 2);
//     insert(pq, 9);
//     insert(pq, 4);

//     delete(pq);

//     insert(pq, 2);
//     insert(pq, 2);

//     delete(pq);
//     delete(pq);
//     delete(pq);
//     delete(pq);
//     delete(pq);
//     delete(pq);

//     display_arr(pq->arr, pq->length);

//     return 0;
// } // end of main()