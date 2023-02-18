#include "draw.h"

void draw_graph(char* postfix, int* everything_is_fine) {
    double hash[WIDTH];
    int count = 0;
    for (double x = 0.0; x < 4.0 * M_PI || !*everything_is_fine; x += 4.0 * M_PI / WIDTH) {
        hash[count++] = calculate(postfix, x, everything_is_fine);
    }
    if (*everything_is_fine) {
        for (double y = 1; y >= -1; y -= STEP) {
            for (int x = 0; x < WIDTH; x++) {
                if (hash[x] <= y + INFELICITY && hash[x] >= y - INFELICITY) {
                    printf("*");
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
}