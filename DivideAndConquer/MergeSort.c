#include<stdio.h>

void merge(int *arr, int lb, int rb, int mid) {

	int aux_arr[rb - lb + 1];
	int aux_i = 0;
	int i1 = lb, i2 = mid + 1;

	while (i1 <= mid && i2 <= rb) {
	
		if (arr[i1] < arr[i2])
		       aux_arr[aux_i] = arr[i1++];
		else
			aux_arr[aux_i] = arr[i2++];
		aux_i++;	
	}

	while (i1 <= mid) { aux_arr[aux_i++] = arr[i1++]; }

	while (i2 <= rb) { aux_arr[aux_i++] = arr[i2++]; }
	
	aux_i = 0;
	int i;

	for (i = lb; i <= rb; i++) { arr[i] = aux_arr[aux_i++]; }

} // end of merge(int*, int, int, int)

void merge_sort_recur(int *arr, int lb, int rb) {

	// lb = left bound of sub-array
	// rb = right bound of sub-array
	
	if (rb - lb < 1) return; 
	
	int mid = (lb + rb) / 2;

	merge_sort_recur(arr, lb, mid);
	merge_sort_recur(arr, mid + 1, rb);

	merge(arr, lb, rb, mid);
	
} // end of merge_sort_recur(int*, int, int)

void merge_sort(int *arr, int len) { // wrapper function for merge_sort_recur(int*, int, int)

	merge_sort_recur(arr, 0, len - 1);
} // end of merge_sort(int*, int)

void input(int *arr, int len) {
	
	int i = 0;
	for (; i < len; i++) {
		scanf("%d", (arr + i));
	}
} // end of input(int*, int)

void display(int *arr, int len) {

	int i = 0;
	for (; i < len; i++) {
		printf("%d ", *(arr + i));
	}
} // end of display(int*, int)

int main() {
	
	int len;
	int arr[len];

	printf("Enter length of array: ");
	scanf("%d", &len);
	
	printf("Enter elements in array: ");
	input(arr, len);

	printf("Initial array: ");
	display(arr, len);
	printf("\n");

	merge_sort(arr, len);

	printf("Array after sorting: ");
	display(arr, len);
	printf("\n");

	return 0;
} // end of main()
