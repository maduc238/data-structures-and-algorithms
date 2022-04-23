#include <iostream>
using namespace std;

/*****************************************************************************
 * To run these functions:
 * initial an array:
 * 		arr[] = {10, 7, 8, 9, 1, 5};
 * 		n = sizeof(arr) / sizeof(arr[0]);
 * you can use quicksort, mergesort, heapsort, etc...
 * 		quick_sort(arr, 0, n - 1);
 * 		or... heap_sort(arr, n);
*****************************************************************************/

/*****************************************************************************
 * Quick Sort
*****************************************************************************/

void swap(int* a, int* b);
int partition(int arr[], int low, int high);
/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quick_sort(int arr[], int low, int high){
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now at right place */
		int pi = partition(arr, low, high);
		// Separately sort elements before partition and after partition
		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

// A utility function to swap two elements
void swap(int* a, int* b){
	int t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high){
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

	for (int j = low; j <= high - 1; j++){
		// If current element is smaller than the pivot
		if (arr[j] < pivot){
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/*****************************************************************************
 * Heap Sort
*****************************************************************************/

void heapify(int arr[], int n, int i);
// main function to do heap sort
void heap_sort(int arr[], int n){
	// Build heap (rearrange array)
	for(int i = n/2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	// One by one extract an element from heap
	for(int i = n - 1; i > 0; i--){
		// Move current root to end
		swap(arr[0], arr[i]);
		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

/* To heapify a subtree rooted with node i which is an index in arr[]. n is size of heap */
void heapify(int arr[], int n, int i){
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	// If left child is larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;
	// If right child is larger than largest so far
	if (r < n && arr[r] > arr[largest])
		largest = r;
	// If largest is not root
	if (largest != i){
		swap(arr[i], arr[largest]);
		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}

/* A utility function to print array of size n. You can use it to check your array or sorted array */
void print_array(int arr[], int n){
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}