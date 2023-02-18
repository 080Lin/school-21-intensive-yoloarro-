#include <stdlib.h>
#include <string.h>

#include "calculate.h"
#include "draw.h"
#include "parse.h"

int main(void) {
    // read expression as a string
    char* expr = input_arr();
    if (expr != NULL) {
        int len = strlen(expr);
        // convert our expr to polish notation like string
        int everything_is_fine = 1;
        char* postfix = convert(expr, len, &everything_is_fine);
        if (postfix != NULL && everything_is_fine) {
            // write polish notation string
            for (int i = 0; i < (int)strlen(postfix); i++) {
                printf("%c", postfix[i]);
            }
            printf("\n");
            // output our graphic
            draw_graph(postfix, &everything_is_fine);
            free(postfix);
        }
        free(expr);
    }

    return 0;
}