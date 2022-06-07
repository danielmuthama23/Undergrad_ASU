// CSE310 Summer 2022 (C) - Recitation #3
// Tyler Fichiera - 1218959911
// 06/04/2022

#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

#define MAX_HEAP_CAPACITY 100

using namespace std;

// menu driver function declaration
void executeAction(int choice);

// priority queue function declaractions
int parent(int i);
int left(int i);
int right(int i);
int heapMinimum(int *arr);
int heapExtractMin(int *arr);
void heapDecreaseKey(int *arr, int i, int key);
void minHeapInsert(int *arr, int key);
void minHeapify(int *arr, int i);

int *heap_arr = new int[MAX_HEAP_CAPACITY];
int heap_size = 0;

int main() {
    int choice;

    do {
		cout << "\nWelcome to the Plane Landing System\n";
		cout << "1. Make a landing request\n";
		cout << "2. Land a Plane\n";
		cout << "3. List all the landing requests\n";
		cout << "4. Exit\n";
		cin >> choice;
		cin.ignore();
		executeAction(choice);
	} while (choice != 4);

    return 0;
}

void executeAction(int choice) {
	switch (choice) {
		// add plane to landing queue
		case 1: {
			int duration;

			cout << "\nEnter the duration the plane can wait (in minutes): ";
			cin >> duration;
			cin.ignore();

			// insert plane duration to min heap
			minHeapInsert(heap_arr, duration);

			break;
		}

		// land plane by removing it from min heap
		case 2: {
			int min = heapExtractMin(heap_arr);
			cout << "\nPlane with " << min << " minute duration removed from landing system!\n";
			break;
		}

		// list current planes and their durations
		case 3: {
			cout << endl << heap_size << " plane(s) currently waiting to land:\n";
			for (int i = 0; i < heap_size; i++)
				cout << heap_arr[i] << " ";
			cout << endl;
			break;
		}

		// exit
		case 4:
			break;

		default:
			cout << choice << " is an invalid input!\n";
			break;
	}
}

/* Priority Queue Functions */
int parent(int i) { return floor((i - 1) / 2); }

int left(int i) { return 2 * i + 1; }

int right(int i) { return 2 * i + 2; }

int heapMinimum(int *arr) { return arr[0]; }

int heapExtractMin(int *arr) {
	if (heap_size == 0) {
		cout << "heap underflow" << endl;
		return 100000;
	}
	if (heap_size == 1) {
		heap_size--;
		return arr[0];
	}
	int min = arr[0];
	arr[0] = arr[heap_size - 1];
	heap_size--;
	minHeapify(arr, 0);
	return min;
}

void heapDecreaseKey(int *arr, int i, int key) {
	if (key < arr[i]) {
		cout << "new key is smaller than current key" << endl;
		return;
	}
	arr[i] = key;
	while (i > 0 && arr[parent(i)] > arr[i]) {
		swap(arr[i], arr[parent(i)]);
		i = parent(i);
	}
}

void minHeapInsert(int *arr, int key) {
	heap_size++;
	arr[heap_size - 1] = -1000000;
	heapDecreaseKey(arr, heap_size - 1, key);
}

void minHeapify(int *arr, int i) {
	int l = left(i);
	int r = right(i);
	int smallest;
	if (l < heap_size && arr[l] < arr[i])
		smallest = l;
	else
		smallest = i;
	if (r < heap_size && arr[r] < arr[smallest])
        smallest = r;
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, smallest);
    }
}
