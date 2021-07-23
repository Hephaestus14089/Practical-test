#include <stdio.h>
#include <stdlib.h>

struct Array {

    int length;
    int *arr;
};

typedef struct Array Array;

Array* new_array() {

    Array *array = (Array*)malloc(sizeof(Array));

    printf("Enter length of array: ");
    scanf("%d", &array->length);

    array->arr = (int*)malloc(sizeof(int) * array->length);

    printf("Enter elements in array: ");
    int i = 0;
    for (; i < array->length; i++) {
        scanf("%d", (array->arr + i));
    }

    return array;
} // end of new_array(int)

void display_array(Array* array) {

    int i = 0;
    for (; i < array->length; i++) {
        printf("%d ", *(array->arr + i));
    }
} // end of display_array(Array*)


void swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;
} // end of swap(int*, int*)

int partition(int *arr, int low, int high) {

    int pivot = *(arr + low);
    int left = low;
    int right = high + 1;

    while (left < right) {

        do {
            left++;
        } while (left <= high && *(arr + left) < pivot);

        do {
            right--;
        } while (*(arr + right) > pivot);


        if (left < right) {
            swap((arr + left), (arr + right));
        }

    } // end of outer while loop

    swap((arr + low), (arr + right));

    return right;
} // end of partition(int*, int, int)

void quick_sort(int *arr, int low, int high) {

    if (!(low < high)) return;

    int p = partition(arr, low, high);

    quick_sort(arr, low, p - 1);
    quick_sort(arr, p + 1, high);

} // end of quick_sort(int*, int, int)


int main() {

    Array *array = new_array();

    printf("Initial array: ");
    display_array(array);
    printf("\n");

    quick_sort(array->arr, 0, array->length - 1);

    printf("Array after sorting: ");
    display_array(array);
    printf("\n");

    return 0;
} // end of main()