/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(const int *buffer, int length);
int find_numbers(const int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int NMAX = 10;
    int length;
    int arr[NMAX];
    if (input(arr, &length)) {
        int number = sum_numbers(arr, length);
        if (number == -1) {
            printf("n/a");
        } else {
            int new_arr[length];
            int new_lenght = find_numbers(arr, length, number, new_arr);
            if (new_lenght) {
                printf("%d\n", number);
                output(new_arr, new_lenght);
            } else {
                printf("n/a");
            }
        }
    } else {
        printf("n/a");
    }
    return 0;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length) {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            count++;
            sum += buffer[i];
        }
    }
    if (count == 0) {
        sum = -1;
    }
    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(const int *buffer, int length, int number, int *numbers) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[count] = buffer[i];
            count++;
        }
    }
    return count;
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