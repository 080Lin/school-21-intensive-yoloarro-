#include <stdio.h>

int input(int *arr, int n);
void output(int *arr, int n);
void swap(int *arr, int i, int j);
void quick_sort(int *arr, int first, int last);
void heapify(int *arr, int low, int high);
void heapsort(int *arr, int n);

int main() {
    int NMAX = 10;
    int data[NMAX];
    if (input(data, NMAX)) {
        quick_sort(data, 0, NMAX - 1);
        output(data, NMAX);
        heapsort(data, NMAX);
        printf("\n");
        output(data, NMAX);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *arr, int n) {
    int res = 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            res = 0;
            break;
        }
    }
    return res;
}

void output(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i + 1 < n) {
            printf(" ");
        }
    }
}

void swap(int *arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void quick_sort(int *arr, int first, int last) {
    if (first < last) {
        int i, j, pivot;
        pivot = first;

        i = first;

        j = last;

        while (i < j) {
            while (i < last && arr[i] <= arr[pivot]) i++;

            while (arr[j] > arr[pivot]) j--;

            if (i < j) {
                swap(arr, i, j);
            }
        }
        swap(arr, pivot, j);

        quick_sort(arr, first, j - 1);

        quick_sort(arr, j + 1, last);
    }
}

void heapify(int *arr, int low, int high) {
    int biggest = high;
    int left = 2 * high + 1;
    int right = 2 * high + 2;
    if (left < low && arr[left] > arr[biggest]) {
        biggest = left;
    }
    if (right < low && arr[right] > arr[biggest]) {
        biggest = right;
    }
    if (biggest != high) {
        swap(arr, high, biggest);
        heapify(arr, low, biggest);
    }
}

void heapsort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(arr, 0, i);
        heapify(arr, i, 0);
    }
}