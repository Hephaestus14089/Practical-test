#include <stdio.h>
#include <stdlib.h>

void input(int *arr, int len) {

    int i = 0;
    for (; i < len; i++) 
        scanf("%d", (arr + i));
} // end of input(int*, int)

void display(int *arr, int len) {

    int i = 0;
    for (; i < len; i++) 
        printf("%d ", *(arr + i));
} // end of display(int*, int)

void swap(int *x, int *y) {

    int temp = *x;
    *x = *y;
    *y = temp;
} // end of swap(int*, int*)

void maxHeap(int *arr, int len, int root) {

    int largest = root;
    int left = root * 2 + 1;
    int right = root * 2 + 2;

    if (left < len && *(arr + left) > *(arr + largest)) {
        largest = left;
    }
    if (right < len && *(arr + right) > *(arr + largest)) {
        largest = right;
    }

    if (largest != root) {

        swap((arr + root), (arr + largest));
        maxHeap(arr, len, largest);
    }
} // end of minHeap(int*, int, int)

void minHeap(int *arr, int len, int root) {

    int smallest = root;
    int left = root * 2 + 1;
    int right = root * 2 + 2;

    if (left < len && *(arr + left) < *(arr + smallest)) { 
        smallest = left; 
    }
    if (right < len && *(arr + right) < *(arr + smallest)) { 
        smallest = right; 
    }

    if (smallest != root) {

        swap((arr + root), (arr + smallest));
        minHeap(arr, len, smallest);
    }
} // end of maxHeap(int*, int, int)

void heapSort(int *arr, int len) {

    int i = len / 2 - 1; // last node with atleast 1 child != null
    /*
        We need to build a 'max heap'
        We achieve this by calling the recursive maxHeap function
        from the last 'parent' node to the 'root' node (0th index)
    */
    for (; i >= 0; i--) {
        maxHeap(arr, len, i);
    }

    /*
        Now, swap the last and the first index and call maxHeap on the reduced array
        [This way, we move the largest element to the end]
        Continue until reaching the 0th index
    */
    for (i = len - 1; i > 0; i--) {

        swap(arr, (arr + i)); // swapping the first and the current last node
        maxHeap(arr, i, 0); // moving the new largest element to root node (0th index)

        printf("Pass %d: ", len - i);
        display(arr, len);
        printf("\n");
    }
} // end of heapSort(int*, int)

void heapSort_desc(int *arr, int len) {

    int i = len / 2 - 1; // last node with atleast 1 child != null
    /*
        We need to build a 'min heap'
        We achieve this by calling the recursive minHeap function
        from the last 'parent' node to the 'root' node (0th index)
    */
    for (; i >= 0; i--) 
        minHeap(arr, len, i);

    /*
        Now, swap the last and the first index and call minHeap on the reduced array
        [This way, we move the smallest element to the end]
        Continue until reaching the 0th index
    */
    for (i = len - 1; i > 0; i--) {

        swap(arr, (arr + i)); // swapping the first and the current last node
        minHeap(arr, i, 0); // moving the new smallest element to root node (0th index)
    }
} // end of heapSort(int*, int)

int main() {

    int len, *arr;

    printf("Enter length of array: ");
    scanf("%d", &len);

    arr = (int*)malloc(sizeof(int) * len);

    printf("Enter elements in array: ");
    input(arr, len);

    printf("Elements in array are: ");
    display(arr, len);
    printf("\n");

    printf("\n");
    heapSort(arr, len);
    printf("\n");

    printf("Array in ascending order: ");
    
    display(arr, len);
    printf("\n");

    printf("Array in descending order: ");
    heapSort_desc(arr, len);
    display(arr, len);
    printf("\n");

    return 0;
} // end of main()