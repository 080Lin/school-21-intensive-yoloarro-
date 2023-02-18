#include "s21_string.h"

#include <stdio.h>

void s21_strlen_test();
void s21_strcmp_test();
void s21_strcpy_test();
void s21_strcat_test();
void s21_strchr_test();
void s21_strstr_test();
// void s21_strtok_test();
void test_output(int success);

int main() {
#ifdef Quest_1
    s21_strlen_test();
#endif
#ifdef Quest_2
    s21_strcmp_test();
#endif
#ifdef Quest_3
    s21_strcpy_test();
#endif
#ifdef Quest_4
    s21_strcat_test();
#endif
#ifdef Quest_5
    s21_strchr_test();
#endif
#ifdef Quest_6
    s21_strstr_test();
#endif
    return 0;
}

void s21_strlen_test() {
    char str_1[] = "Hel\0lo";
    test_output(s21_strlen(str_1) == 3);

    char str_2[] = "GIGACHADO\n\t";
    test_output(s21_strlen(str_2) == 11);

    char str_3[] = "";
    test_output(s21_strlen(str_3) == 0);
}

void s21_strcmp_test() {
    char str_1[] = "Dog";
    char str_2[] = "Cat";
    test_output(!s21_strcmp(str_1, str_2) == 0);

    char str_3[] = "\0";
    char str_4[] = "\t\t\t";
    test_output(!s21_strcmp(str_3, str_4) == 0);

    char str_5[] = "dsdas\0dsadas\0";
    char str_6[] = "dsdas\0dsadas\0";
    test_output(s21_strcmp(str_5, str_6) == 0);
}

void s21_strcpy_test() {
    char str_from[] = "hell ya";
    char str_to[s21_strlen(str_from)];
    test_output(s21_strcmp(str_from, s21_strcpy(str_to, str_from)) == 0);

    s21_strcpy(str_from, "gigigig\0ziga");
    test_output(s21_strcmp(str_from, s21_strcpy(str_to, str_from)) == 0);

    s21_strcpy(str_from, "\n\t\0\0");
    test_output(s21_strcmp(str_from, s21_strcpy(str_to, str_from)) == 0);
}

void s21_strcat_test() {
    char str_1[] = "1234  ";
    char str_2[] = "5 678";
    test_output(s21_strcmp(s21_strcat(str_1, str_2), "1234  5 678") == 0);
    char str_3[] = "giga\0ya";
    char str_4[] = "dasdas";
    test_output(s21_strcmp(s21_strcat(str_3, str_4), "gigadasdas") == 0);
    char str_5[] = "1234  5 678";
    test_output(s21_strcmp(s21_strcat(str_5, "5 678"), "1234  5 6785 678") == 0);
}

void s21_strchr_test() {
    char str[] = "01234566789";
    int ch = '3';
    test_output(s21_strchr(str, ch) - str + 1 == 4);
    test_output(s21_strchr("1eqdfz\0\t", 'q') - "1eqdfz\0\t" + 1 == 3);
    test_output(s21_strchr("\0dsadasd", 'd') - "\0dsadasd" + 1);
}

void s21_strstr_test() {
    char str[] = "dogchamp";
    char substr[] = "amp";
    test_output(s21_strcmp(s21_strstr(str, substr), "amp") == 0);
    test_output(s21_strcmp(s21_strstr("bog", "og"), "og") == 0);
    test_output(s21_strcmp(s21_strstr("yaya\0dsadas", "ya"), "ya") == 0);
}

// void s21_strtok_test() {
//     char str[] = "ya ya ya ya";
//     char *left = s21_strtok(str, ' ');
//     printf("%s", left);
//     while(left != NULL) {
//         left = s21_strtok(str, ' ');
//         printf("%s", left);
//     }
// }

void test_output(int success) {
    if (success) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}