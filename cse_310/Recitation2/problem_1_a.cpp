// CSE310 Summer 2022 (C) - Recitation #2
// Tyler Fichiera - 1218959911
// 05/25/2022

#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// algorithm function declarations
void insertionSort(double arr[], int len);
void selectionSort(double arr[], int len);
void quickSort(double arr[], int start, int end);
void mergeSort(double arr[], int start, int end);

// helper function declarations
int partition(double arr[], int start, int end);
void merge(double arr[], int start, int mid, int end);
void arrToString(double arr[], int len);
double randDouble(double min = 100, double max = 1000);

/* Main/testing function */
int main() {
    /* TEST OUTPUT: */
    cout << "TESTING OUTPUTS:" << endl;

    const int len = 6;

    // test insertion sort
    double arr1[len] = {16, 2, 13, 40, 128, 6};
    insertionSort(arr1, len);
    cout << "Insertion Sort Answer: \t";
    arrToString(arr1, len);


    // test selection sort
    double arr2[len] = {16, 2, 13, 40, 128, 6};
    insertionSort(arr2, len);
    cout << "Selection Sort Answer: \t";
    arrToString(arr2, len);

    // test quick sort
    double arr3[len] = {16, 2, 13, 40, 128, 6};
    quickSort(arr3, 0, len - 1);
    cout << "Quick Sort Answer: \t";
    arrToString(arr3, len);

    // test merge sort
    double arr4[len] = {16, 2, 13, 40, 128, 6};
    mergeSort(arr4, 0, len - 1);
    cout << "Merge Sort Answer: \t";
    arrToString(arr4, len);

    cout << endl;

    /* TEST RUNNING TIME: */
    cout << "TESTING RUN TIMES:" << endl;

    const int arraySizes[] = {1000, 10000, 25000, 50000, 100000, 150000, 200000};
    double start, duration;
    srand(time(0));

    cout << "Size\t\tInsert\t\tMerge\t\tQuick\t\tSelection" << endl;

    for (int i = 0; i < 7; i++) {
        int size = arraySizes[i];
        cout << size << "\t\t";

        double *randArr = new double[size];

        // generate random array with values [100, 1000]
        for (int j = 0; j < size; j++)
            randArr[j] = randDouble();

        // test insertion sort
        start = clock();
        insertionSort(randArr, size);
        duration = (clock() - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(3) << duration << "\t\t";

        for (int j = 0; j < size; j++)
            randArr[j] = randDouble();

        // test merge sort
        start = clock();
        mergeSort(randArr, 0, size - 1);
        duration = (clock() - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(3) << duration << "\t\t";

        for (int j = 0; j < size; j++)
            randArr[j] = randDouble();

        // test quick sort
        start = clock();
        quickSort(randArr, 0, size);
        duration = (clock() - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(3) << duration << "\t\t";

        for (int j = 0; j < size; j++)
            randArr[j] = randDouble();

        // test selection sort
        start = clock();
        selectionSort(randArr, size);
        duration = (clock() - start) / CLOCKS_PER_SEC;
        cout << fixed << setprecision(3) << duration << "\t\t";

        cout << endl;

        delete[] randArr;
    }

    return 0;
}

/* INSERTION SORT */
void insertionSort(double arr[], int len) {
    for (int i = 1; i < len; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

/* SELECTION SORT */
void selectionSort(double arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++)  {
            if (arr[j] < arr[i])
                swap(arr[j], arr[i]);
        }
    }
}

/* QUICK SORT */
void quickSort(double arr[], int start, int end) {
    if (start < end) {
        int part = partition(arr, start, end);
        quickSort(arr, start, part - 1);
        quickSort(arr, part + 1, end);
    }
}

int partition(double arr[], int start, int end) {
    int x = arr[end]; // pivot
    int i = start - 1;
    for (int j = start; j <= end - 1; j++) {
        if (arr[j] < x) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[end]);
    return i + 1;
}

/* MERGE SORT */
void mergeSort(double arr[], int start, int end) {
    if (start < end) {
        int mid = floor((start + end) / 2);
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void merge(double arr[], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;
  
    double *arrL = new double[n1];
    double *arrR = new double[n2];
  
    for (int i = 0; i < n1; i++)
        arrL[i] = arr[start + i];
    for (int j = 0; j < n2; j++)
        arrR[j] = arr[mid + j + 1];
  
    int i = 0, j = 0, k = start;
    for (; i < n1 && j < n2; k++) {
        if (arrL[i] <= arrR[j]) {
            arr[k] = arrL[i];
            i++;
        } else {
            arr[k] = arrR[j];
            j++;
        }
    }

    while (i < n1) {
        arr[k] = arrL[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = arrR[j];
        j++;
        k++;
    }
}

/* Helper methods */
void arrToString(double arr[], int len) {
    cout << "[ ";
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << "]" << endl;
}

double randDouble(double min, double max) {
    double div = RAND_MAX / (max - min);
    return min + (rand() / div);
}
