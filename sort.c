#include <stdio.h>

int input(int *arr, int n);
void output(int *arr, int n);
void sort(int *arr, int n);

int main() {
    int NMAX = 10;
    int data[NMAX];
    if (input(data, NMAX)) {
        sort(data, NMAX);
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

void sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}