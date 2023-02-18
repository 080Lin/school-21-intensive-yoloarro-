#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic.h"

// reads our input via scanf string
char* input_arr(void);
// calculate operator weight depending on its state
int op_weigth(char op);
// check if our char is operator
int is_op(char ch);
// make polish notation string
char* convert(char* input, int len, int* everything_is_fine);
// same but is func
int is_func(const char* input, int i, int len);
// decomposize operators
void push_all_possible_op(int func, char stack[50], int* top, char* input, int* i);

#endif