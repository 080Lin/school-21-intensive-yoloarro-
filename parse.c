#include "parse.h"

// reads our input via scanf string
char* input_arr(void) {
    char* input = malloc(sizeof(char) * 200);
    scanf("%200s", input);
    return input;
}

// calculate operator weight depending on its state
int op_weigth(char op) {
    int result = -1;
    switch (op) {
        case '+':
        case '-':
            result = 1;
            break;
        case '*':
        case '/':
            result = 2;
            break;
        case 's':  // sin
        case 'c':  // cos
        case 't':  // tan
        case 'g':  // ctg
        case 'q':  // sqrt
        case 'l':  // ln
            result = 3;
            break;
    }
    return result;
}

// check if our char is a operator
int is_op(char ch) { return (ch == '+' || ch == '-' || ch == '*' || ch == '/'); }

// same but is a func
int is_func(const char* input, int i, int len) {
    int result = 0;
    // reading further than just a symbol if it matches our pattern below
    if (i + 2 < len && input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n') result = 1;
    if (i + 2 < len && input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's') result = 2;
    if (i + 2 < len && input[i] == 't' && input[i + 1] == 'a' && input[i + 2] == 'n') result = 3;
    if (i + 2 < len && input[i] == 'c' && input[i + 1] == 't' && input[i + 2] == 'g') result = 4;
    if (i + 3 < len && input[i] == 's' && input[i + 1] == 'q' && input[i + 2] == 'r' && input[i + 3] == 't')
        result = 5;
    if (i + 1 < len && input[i] == 'l' && input[i + 1] == 'n') result = 6;
    return result;
}

// make polish notation string
char* convert(char* input, int len, int* everything_is_fine) {
    char* result = malloc((len * 2) * sizeof(char));
    char stack[50];
    // top is counting nodes after head. -1 is empty stack
    int top = -1, j, i, check = 0;
    for (i = 0, j = 0; i < len && *(everything_is_fine); i++) {
        // range 48-57 our nums, 120 is x
        if (((int)input[i] >= 48 && (int)input[i] <= 57) || ((int)input[i] == 120)) {
            // '.' is for double check
            while (((int)input[i] >= 48 && (int)input[i] <= 57) || input[i] == '.' || (input[i] == 'x')) {
                result[j++] = input[i];
                check = 1;
                i++;
            }
            i--;
        } else if (input[i] == '(')
            push_op(stack, &top, input[i]);
        else if (input[i] == ')') {
            while (top > -1 && stack[top] != '(') {
                result[j++] = pop_op(stack, &top);
                result[j++] = ' ';
            }
            if (top > -1 && stack[top] != '(')
                *(everything_is_fine) = 0;
            else
                top--;
            // check if our symbol is a operator or a func
        } else if (is_op(input[i]) || is_func(input, i, len)) {
            int func = is_func(input, i, len);
            while (!func && top > -1 && op_weigth(stack[top]) >= op_weigth(input[i])) {
                result[j++] = pop_op(stack, &top);
                result[j++] = ' ';
            }
            push_all_possible_op(func, stack, &top, input, &i);
        } else
            *(everything_is_fine) = 0;
        if (check) {
            result[j++] = ' ';
            check = 0;
        }
    }

    while (top > -1) {
        result[j++] = pop_op(stack, &top);
        result[j++] = ' ';
    }
    result[j] = '\0';

    return result;
}

// refactor and gather all push ops in one function
void push_all_possible_op(int func, char stack[50], int* top, char* input, int* i) {
    if (!func)
        push_op(stack, top, input[*i]);

    else if (func == 1) {
        push_op(stack, top, 's');
        *i += 2;
    } else if (func == 2) {
        push_op(stack, top, 'c');
        *i += 2;
    } else if (func == 3) {
        push_op(stack, top, 't');
        *i += 2;
    } else if (func == 4) {
        push_op(stack, top, 'g');
        *i += 2;
    } else if (func == 5) {
        push_op(stack, top, 'q');
        *i += 3;
    } else if (func == 6) {
        push_op(stack, top, 'l');
        *i += 1;
    }
}