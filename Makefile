C=gcc
CFLAGS=-Wall -Werror -Wextra
SUPER_COMPILE=$(C) $(CFLAGS)
EXE=../build/graph
BUILD_FILES=graph.o draw.o parse.o dynamic.o calculate.o

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h
	clang-format -n *.c *.h
	cppcheck --enable=all .
	rm .clang-format
	leaks -atExit -- $(EXE)

all: $(BUILD_FILES)
	$(SUPER_COMPILE) $(BUILD_FILES) -o $(EXE)

run: rebuild
	./$(EXE)

dynamic.o:
	$(SUPER_COMPILE) -c dynamic.c dynamic.h

parse.o:
	$(SUPER_COMPILE) -c parse.c parse.h

graph.o:
	$(SUPER_COMPILE) -c graph.c

draw.o:
	$(SUPER_COMPILE) -c draw.c draw.h

calculate.o:
	$(SUPER_COMPILE) -c calculate.c calculate.h

clean:
	rm -f *.o *.gch ../build/*

rebuild: clean all