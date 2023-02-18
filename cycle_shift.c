#include <stdio.h>

void cycle_shift_forward(int *buffer, int lenght);
void cycle_shift_backward(int *buffer, int length);
void cycle_shift(int *buffer, int length, int shift);
int input_shift(int *shift);
int input(int *buffer, int *length);
void output(int *buffer, int length);

int main() {
    int length, NMAX = 10, shift, arr[NMAX];
    if (input(arr, &length)) {
        if (input_shift(&shift)) {
            cycle_shift(arr, length, shift % length);
            output(arr, length);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *buffer, int *length) {
    int res = 1;
    if (scanf("%d", length) != 1 || *length > 10 || *length < 1) {
        res = 0;
    } else {
        for (int i = 0; i < *length; i++) {
            if (scanf("%d", &buffer[i]) != 1) {
                res = 0;
                break;
            }
        }
    }
    return res;
}

void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i + 1 < length) {
            printf(" ");
        }
    }
}

int input_shift(int *shift) {
    int res = 1;
    if (scanf("%d", shift) != 1) {
        res = 0;
    }
    return res;
}

void cycle_shift_forward(int *buffer, int lenght) {
    int saved = buffer[0];
    for (int i = 0; i < lenght - 1; i++) {
        buffer[i] = buffer[i + 1];
    }
    buffer[lenght - 1] = saved;
}

void cycle_shift_backward(int *buffer, int length) {
    int saved = buffer[length - 1];
    for (int i = length - 1; i > 0; i--) {
        buffer[i] = buffer[i - 1];
    }
    buffer[0] = saved;
}

void cycle_shift(int *buffer, int length, int shift) {
    if (shift > 0) {
        for (int i = 0; i < shift; i++) {
            cycle_shift_forward(buffer, length);
        }
    } else {
        for (int i = 0; i < shift * -1; i++) {
            cycle_shift_backward(buffer, length);
        }
    }
}