#include "calculate.h"

#include <stdio.h>
double calculate(char* postfix, double x, int* everything_is_fine) {
    double nums[80];
    int top = -1, is_double = 0;
    double num1, num2, result;
    while (*postfix != '\0' && *everything_is_fine) {
        if (*postfix == 'x') {
            push_num(nums, &top, x);
        } else if (((int)*postfix >= 48 && (int)*postfix <= 57)) {
            double cur_num = 0;

            while (*postfix != 'x' && *postfix != ' ') {
                if (*postfix != '.' && !is_double) {
                    cur_num = cur_num * 10 + (double)(*postfix - 48);
                    postfix++;
                } else if (*postfix == '.' && !is_double) {
                    postfix++;
                    is_double = 1;
                } else {
                    cur_num = cur_num + (double)(*postfix - 48) / pow(10, is_double);
                    postfix++;
                    is_double++;
                }
            }
            postfix--;
            is_double = 0;
            push_num(nums, &top, cur_num);
        } else if (*postfix != ' ') {
            num1 = pop_num(nums, &top);
            num2 = pop_num(nums, &top);
            *everything_is_fine = make_decision(postfix, num1, num2, &result, nums, &top);
            push_num(nums, &top, result);
        }
        postfix++;
    }
    return pop_num(nums, &top);
}

int make_decision(char* postfix, double num1, double num2, double* result, double* nums, int* top) {
    int res = 1;
    switch (*postfix) {
        case '+':
            *result = num2 + num1;
            break;
        case '-':
            *result = num2 - num1;
            break;
        case '*':
            *result = num2 * num1;
            break;
        case '/':
            *result = num2 / num1;
            break;
        case 's':
            *result = sin(num1);
            push_num(nums, top, num2);
            break;
        case 'c':
            *result = cos(num1);
            push_num(nums, top, num2);
            break;
        case 't':
            *result = tan(num1);
            push_num(nums, top, num2);
            break;
        case 'g':
            *result = 1 / tan(num1);
            push_num(nums, top, num2);
            break;
        case 'q':
            *result = sqrt(num1);
            push_num(nums, top, num2);
            break;
        case 'l':
            *result = log(num1);
            push_num(nums, top, num2);
            break;
        default:
            res = 0;
    }
    return res;
}