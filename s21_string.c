#include <stdlib.h>

size_t s21_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int s21_strcmp(const char* str_1, const char* str_2) {
    int same = 0;
    size_t index = 0;
    while ((str_1[index] != '\0' || str_2[index] != '\0') && same == 0) {
        if (str_1[index] > str_2[index]) {
            same++;
        } else if (str_1[index] < str_2[index]) {
            same--;
        }
        index++;
    }
    return same;
}

char* s21_strcpy(char* to, const char* from) {
    size_t index = 0;
    while (from[index] != '\0') {
        to[index] = from[index];
        index++;
    }
    to[index] = '\0';
    return to;
}

char* s21_strcat(char* to, const char* add) {
    size_t index = s21_strlen(to);
    size_t len_1 = s21_strlen(to);
    size_t len_2 = s21_strlen(add);
    while (index < len_1 + len_2) {
        if (add[index - len_1] == ' ') {
            to[index] = ' ';
        } else {
            to[index] = add[index - len_1];
        }
        index++;
    }
    to[index] = '\0';
    return to;
}

char* s21_strchr(const char* str, int ch) {
    char* from = NULL;
    size_t index = 0;
    while (str[index] != '\0' && str[index] != ch) {
        index++;
    }
    if (str[index] == ch) {
        from = (char*)(index + str);
    }
    return from;
}

char* s21_strstr(char* str, char* part) {
    int res = 0;
    char* out = NULL;
    while (*str != '\0' && res == 0) {
        if ((*str == *part) && s21_strcmp(str, part) == 0) {
            res = 1;
            out = str;
        }
        str++;
    }
    return out;
}

// char* s21_strtok(char* str, char by) {
//     char* input = NULL;
//     if(str != NULL) {
//         input = str;
//     }

//     if(input == NULL) {
//         return NULL;
//     }

//     char *res = malloc(sizeof(char) * s21_strlen(input) + 1);
//     int i = 0;
//     for(; input[i] != '\0'; i++) {
//         if(input[i] != by) {
//             res[i] = input[i];
//         } else {
//             res[i] = '\0';
//             return res;
//         }
//     }
//     res[i] = '\0';
//     input = NULL;

//     return res;
// }