#include <stdio.h>
#include <stdlib.h>

int min_of(int a, int b) { return (a < b) ? a : b; }

int max_of(int a, int b) { return (a > b) ? a : b; }

struct Array {

    int length;
    int *arr;
};

typedef struct Array Array;

Array* new_array(int length) {

    Array *array = (Array*)malloc(sizeof(Array));

    array->length = length;
    array->arr = (int*)malloc(sizeof(int) * length);

    printf("Enter elements in array: ");
    int i = 0;
    for (; i < length; i++) {
        scanf("%d", (array->arr + i));
    }

    return array;
} // end of new_array(int)

void display_array(Array* array) {

    printf("Elements in array: ");
    int i = 0;
    for (; i < array->length; i++) {
        printf("%d ", *(array->arr + i));
    }
} // end of display_array(Array*)


struct Parcel {

    int min;
    int max;
};

typedef struct Parcel Parcel;

Parcel* new_parcel() {

    Parcel *parcel = (Parcel*)malloc(sizeof(Parcel));

    parcel->min = 0;
    parcel->max = 0;

    return parcel;
} // end of new_parcel()

void display_parcel(Parcel *parcel) {

    printf("Smallest element: %d\n", parcel->min);
    printf("Largest element: %d\n", parcel->max);
} // end of display_parcel(Parcel*)


Parcel* find_min_max(int *arr, int lb, int rb) {

    // lb = left bound
    // rb = right bound

    Parcel *parcel = new_parcel();

    if (lb == rb) { 
        
        parcel->min = *(arr + lb);
        parcel->max = *(arr + lb);

        return parcel;
    }

    int mid = (lb + rb) / 2;

    Parcel *parcel1 = find_min_max(arr, lb, mid);
    Parcel *parcel2 = find_min_max(arr, mid + 1, rb);

    parcel->min = min_of(parcel1->min, parcel2->min);
    parcel->max = max_of(parcel1->max, parcel2->max);

    free(parcel1);
    free(parcel2);

    return parcel;
} // end of find_min_max(int*, int, int)

void display_min_max(Array *array) {

    display_parcel(find_min_max(array->arr, 0, array->length - 1));
} // end of display_min_max(Array*)


int main() {

    int length;

    printf("Enter length of array: ");
    scanf("%d", &length);

    Array *array = new_array(length);
    display_array(array);

    printf("\n\n");
    display_min_max(array);

    return 0;
} // end of main()