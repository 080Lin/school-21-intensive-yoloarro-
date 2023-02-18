#include <stdio.h>

#define LEN 100
#define POTENTIAL_LEN (LEN + 1)

int input(int *buffer);
int sum(const int *buff1, int len1, const int *buff2, int len2, int *result, const int *result_length);
int sub(const int *buff1, int len1, const int *buff2, int len2, int *result);
void output(int *result, int length);

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main() {
    int num_1[100];
    int len_1 = input(num_1);
    if (len_1 >= 0) {
        if (len_1 == 0) {
            num_1[0] = 0;
            len_1 = 1;
        }
        int num_2[100];
        int len_2 = input(num_2);
        if (len_2 >= 0) {
            int new_len = len_1;
            int res_num[new_len];
            if (len_1 < len_2) new_len = len_2;
            int is_overflow = sum(num_1, len_1, num_2, len_2, res_num, &new_len);
            output(res_num, new_len + is_overflow);
            printf("\n");
            int is_underflow = sub(num_1, len_1, num_2, len_2, res_num);
            if (is_underflow == 228) {
                printf("0");
            } else if (is_underflow == 1 || is_underflow == -1)
                printf("n/a");
            else {
                output(res_num, new_len);
            }
        } else {
            printf("n/a");
        }
    } else if (len_1 == -1) {
        printf("n/a");
    }
    return 0;
}

int input(int *buffer) {
    int res = 1;
    int count = 0;
    int non_zero_count = 0;
    while (count < 100) {
        char helper;
        int curr_num;
        int iter = scanf("%d%c", &curr_num, &helper);
        count++;
        if (curr_num > 9 || curr_num < 0) {
            res = 0;
            break;
        }
        if (iter) {
            if (curr_num > 0 || non_zero_count > 0) {
                buffer[non_zero_count] = curr_num;
                non_zero_count++;
            }
            if (helper == '\n') {
                break;
            } else if (helper != ' ') {
                res = 0;
                break;
            }
        } else {
            res = 0;
            break;
        }
    }
    if (!res) {
        non_zero_count = -1;
    }
    return non_zero_count;
}

void output(int *result, int length) {
    int count = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (count == 0 && result[i] == 0) {
            continue;
        } else {
            count++;
            printf("%d", result[i]);
            if (i > 0) {
                printf(" ");
            }
        }
    }
}

int sum(const int *buff1, int len1, const int *buff2, int len2, int *result, const int *result_length) {
    int overflow = 0;
    for (int i = 0; i < *result_length; i++) {
        int num_1 = 0, num_2 = 0;
        int pos_1 = len1 - 1 - i;
        int pos_2 = len2 - 1 - i;
        if (pos_1 >= 0) {
            num_1 = buff1[pos_1];
        }
        if (pos_2 >= 0) {
            num_2 = buff2[pos_2];
        }
        if (overflow) {
            num_1++;
            overflow--;
        }
        int sum_num = num_1 + num_2;
        if (sum_num >= 10) {
            sum_num %= 10;
            overflow++;
        }
        result[i] = sum_num;
    }
    if (overflow) {
        result[*result_length] = 1;
    }
    return overflow;
}

int sub(const int *buff1, int len1, const int *buff2, int len2, int *result) {
    int underflow = 0;
    if (len2 > len1) {
        underflow = -1;
    } else {
        int return_zero = 0;
        int count = 0;
        for (int i = 0; i < len1; i++) {
            int pos_1 = len1 - 1 - i;
            int pos_2 = len2 - 1 - i;
            int num_2 = 0, num_1 = buff1[pos_1];
            if (pos_2 >= 0) {
                num_2 = buff2[pos_2];
            }
            if (underflow) {
                num_1--;
                underflow--;
            }
            int sub_num = num_1 - num_2;
            if (sub_num < 0) {
                sub_num += 10;
                underflow++;
            }

            result[i] = sub_num;

            if (num_1 == num_2 && count == return_zero) {
                return_zero++;
            }
            count++;
        }
        if (count == return_zero) {
            underflow = 228;
        }
    }
    // printf("\n\n%d\n\n", underflow);
    return underflow;
}