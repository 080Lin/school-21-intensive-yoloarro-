C=gcc
CFLAGS=-Wall -Werror -Wextra
BUILD_PATH=-o ../build/
BUILD_SOURCE=s21_string.o s21_string_test.c

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests

strlen_tests: s21_string.o
	$(C) $(CFLAGS) -D Quest_1 $(BUILD_SOURCE) $(BUILD_PATH)Quest_1

strcmp_tests: s21_string.o
	$(C) $(CFLAGS) -D Quest_2 $(BUILD_SOURCE) $(BUILD_PATH)Quest_2

strcpy_tests: s21_string.o
	$(C) $(CFLAGS) -D Quest_3 $(BUILD_SOURCE) $(BUILD_PATH)Quest_3

strcat_tests: s21_string.o
	$(C) $(CFLAGS) -D Quest_4 $(BUILD_SOURCE) $(BUILD_PATH)Quest_4

strchr_tests: s21_string.o
	$(C) $(CFLAGS) -D Quest_5 $(BUILD_SOURCE) $(BUILD_PATH)Quest_5

strstr_tests: s21_string.o
	$(C) $(CFLAGS) -D Quest_6 $(BUILD_SOURCE) $(BUILD_PATH)Quest_6

s21_string.o: s21_string.c s21_string.h
	$(C) $(CFLAGS) -c s21_string.c

rebuild: clean all

clean:
	rm -rf *.o ../build/* *.out