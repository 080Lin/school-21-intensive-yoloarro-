#ifndef S21_STRING_H
#define S21_STRING_H

#include <stddef.h>

size_t s21_strlen(const char* str);
int s21_strcmp(const char* str_1, const char* str_2);
char* s21_strcpy(char* to, const char* from);
char* s21_strcat(char* to, const char* add);
char* s21_strchr(const char* str, int ch);
char* s21_strstr(char* str, char* part);
// char* s21_strtok(char* str, char by);

#endif