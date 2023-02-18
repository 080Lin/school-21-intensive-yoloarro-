#include <curses.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#define SPEED_START 5
#define WIDTH 80
#define HEIGHT 25
#define BORDER "▒"
#define LIFE "█"
#define EMPTY "░"
#define BORDER_COLOR 0
#define LIFE_COLOR 1
#define EMPTY_COLOR 2
#define OUT 'q'
#define SLOW 'a'
#define QUICK 'z'

void DrawField(int **field);
int KeyRead(int *speed);
void RecalculateField(int **field, int **next_gen);
void RecalculateCell(int **field, int x, int y, int **next_gen);
int calculateNeighbors(int **field, int h, int w);
void FirstFill(int **field);
int **MakeField(int rows, int col);
void CopyMatr(int **field1, int **field2);
void CalculateSpeed(double *speed, int flag);
void DrawBorder();
void DrawEmpty();
void DrawLife();
int AreSimilar(int **matrix1, int **matrix2);
int IsNotGameOver(int **prev, int **current, int **next);

void InitColor();
void LetImpsIn();
void LetImpsOut(int **f1, int **f2, int **f3, int gen);

int main() {
    int **field_next = NULL;
    int **field_current = NULL;
    int **field_prev = NULL;
    int flag = 1, gen = 0, speed = SPEED_START;
    field_current = MakeField(HEIGHT, WIDTH);
    field_next = MakeField(HEIGHT, WIDTH);
    field_prev = MakeField(HEIGHT, WIDTH);
    FirstFill(field_current);
    LetImpsIn();
    InitColor();
    (void)freopen("/dev/tty", "rw", stdin);
    while (flag) {
        RecalculateField(field_current, field_next);
        flag = KeyRead(&speed) && IsNotGameOver(field_prev, field_current, field_next);
        clear();
        printw("GEN %d;\t SPEED: %d\n", gen, speed);
        DrawField(field_current);
        gen++;
        CopyMatr(field_prev, field_current);
        CopyMatr(field_current, field_next);
        napms(speed * 50);
        refresh();
    }
    LetImpsOut(field_prev, field_current, field_next, gen);
    return 0;
}
// Set colors for printing
void InitColor() {
    start_color();
    init_pair(BORDER_COLOR, COLOR_BLACK, COLOR_WHITE);
    init_pair(LIFE_COLOR, COLOR_BLUE, COLOR_WHITE);
    init_pair(EMPTY_COLOR, COLOR_CYAN, COLOR_WHITE);
}
// Setup and init curses
void LetImpsIn() {
    setlocale(LC_ALL, "");
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    keypad(stdscr, TRUE);
}
// Final screen and general clean-up
void LetImpsOut(int **f1, int **f2, int **f3, int gen) {
    clear();
    DrawField(f2);
    printw("\n\t\t\t\tGAME ENDED AT %d GEN", gen);
    refresh();
    free(f3);
    free(f1);
    free(f2);
    getchar();
    endwin();
}
// Calculates next gen matrix
// does not change current field
void RecalculateField(int **field, int **next_gen) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            RecalculateCell(field, i, j, next_gen);
        }
    }
}
// Calculate next gen state for particular cell
void RecalculateCell(int **field, int x, int y, int **next_gen) {
    int count_of_neighbors = calculateNeighbors(field, x, y);
    int current_state = field[x][y];
    if (current_state) {
        if (count_of_neighbors == 2 || count_of_neighbors == 3) {
            next_gen[x][y] = 1;
        } else {
            next_gen[x][y] = 0;
        }
    } else if (count_of_neighbors == 3) {
        next_gen[x][y] = 1;
    } else {
        next_gen[x][y] = 0;
    }
}
// Count living neighbours
int calculateNeighbors(int **field, int h, int w) {
    int count_of_neighbors = 0;
    for (int i = h - 1; i <= h + 1; i++) {
        for (int j = w - 1; j <= w + 1; j++) {
            if (!(i == h && j == w) && (field[(i + HEIGHT) % HEIGHT][(j + WIDTH) % WIDTH] == 1)) {
                count_of_neighbors++;
            }
        }
    }
    return count_of_neighbors;
}
// Generate dinamic matrix
int **MakeField(int rows, int col) {
    size_t size = rows * col * sizeof(int) + rows * sizeof(int *);
    int **dinamic_matr = (int **)malloc(size);
    int *pointer_to_row = (int *)(dinamic_matr + rows);
    for (int i = 0; i < rows; i++) {
        dinamic_matr[i] = pointer_to_row + col * i;
    }
    return dinamic_matr;
}
// Read initial state from file
void FirstFill(int **field) {
    int read_state = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (scanf("%d", &read_state) == 1) field[i][j] = read_state;
        }
    }
}
// copies 2 matr to 1 matr
void CopyMatr(int **field1, int **field2) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field1[i][j] = field2[i][j];
        }
    }
}
// Reads key and changes speed or stops game
int KeyRead(int *speed) {
    int flag = 1;
    char key = getch();
    switch (key) {
        case OUT:
            flag = 0;
            break;
        case SLOW:
            if (*speed < 10) *speed += 1;
            break;
        case QUICK:
            if (*speed > 1) *speed -= 1;
            break;
        default:
            flag = 1;
            break;
    }
    return flag;
}
// Pinterest.png
void DrawField(int **field) {
    for (int y = 0; y < WIDTH + 2; y++) DrawBorder();
    printw("\n");
    for (int y = 0; y < HEIGHT; y++) {
        DrawBorder();
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x] == 1)
                DrawLife();
            else
                DrawEmpty();
        }
        DrawBorder();
        printw("\n");
    }
    for (int y = 0; y < WIDTH + 2; y++) DrawBorder();
    curs_set(0);
}
// print life cell in set color
void DrawLife() {
    attron(COLOR_PAIR(LIFE_COLOR));
    printw(LIFE);
    attroff(COLOR_PAIR(LIFE_COLOR));
}
// print empty cell in set color
void DrawEmpty() {
    attron(COLOR_PAIR(EMPTY_COLOR));
    printw(EMPTY);
    attroff(COLOR_PAIR(EMPTY_COLOR));
}
// print border cell in set color
void DrawBorder() {
    attron(COLOR_PAIR(BORDER_COLOR));
    printw(BORDER);
    attroff(COLOR_PAIR(BORDER_COLOR));
}
// check if end game conditions are met
int IsNotGameOver(int **prev, int **current, int **next) {
    int check = 1;
    if (AreSimilar(next, current) || AreSimilar(next, prev)) check = 0;
    return check;
}
// Guess who? (checks if matrixes are same)
int AreSimilar(int **matrix1, int **matrix2) {
    int similar = 1;
    int i = 0;
    while (i < HEIGHT && similar) {
        int j = 0;
        while (j < WIDTH && similar) {
            if (matrix1[i][j] != matrix2[i][j]) similar = 0;
            j++;
        }
        i++;
    }
    return similar;
}
