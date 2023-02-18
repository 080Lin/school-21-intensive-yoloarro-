// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI
#include <stdio.h>

// function signature
void clear_field();
// draw current state of field
void draw_field(int ball_pos_x, int ball_pos_y, int rocket_p1_y_pos, int rocket_p2_y_pos, int score_p1,
                int score_p2);
// change angle of ball
int change_direction_collision(int direction);
int reverse_direction_for_new_round(int direction);
// function to calculate new ball position
int new_ball_x_pos(int ball_pos_x, int direction);
int new_ball_y_pos(int ball_pos_y, int direction);
// function to change Player's one rocket position
int move_rocket_p1(int rocket_p1_y_pos, char button);
// function to change Player's two rocket position
int move_rocket_p2(int rocket_p2_y_pos, char button);
// function to output endgame view board
int check_for_endgame_view(int score_p1, int score_p2);
void print_game_score(int score_p1, int score_p2);
// Ping - Pong !
void game(int ball_pos_x, int ball_pos_y, int rocket_p1_y_pos, int rocket_p2_y_pos, int score_p1,
          int score_p2, int direction, char button);

// field size
#define FIELD_HEIGHT 27
#define FIELD_WIDTH 82

// basic rockets position for start / restart game
#define BASIC_ROCKET_POSITION_Y (FIELD_HEIGHT / 2)
#define BASIC_ROCKET_1_POSITION_X (0 + 5)
#define BASIC_ROCKET_2_POSITION_X (FIELD_WIDTH - 5)

// basic ball position for start / restart game
#define BASIC_BALL_X_POS (FIELD_WIDTH / 2)
#define BASIC_BALL_Y_POS (FIELD_HEIGHT / 2)

// edit for fast finish / longer games
#define END_SCORE 2

#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define CYAN "\033[1;36m"

// used mostly for the game setup
int main() {
    // game objects info
    int ball_pos_x = BASIC_BALL_X_POS, ball_pos_y = BASIC_BALL_Y_POS,
        rocket_p1_y_pos = BASIC_ROCKET_POSITION_Y, rocket_p2_y_pos = BASIC_ROCKET_POSITION_Y;
    // match info
    int score_p1 = 0, score_p2 = 0;
    // ball moving info
    int direction = 1;
    printf(YELLOW "Press any button to start the game");
    char button = getchar();
    // game starts here
    game(ball_pos_x, ball_pos_y, rocket_p1_y_pos, rocket_p2_y_pos, score_p1, score_p2, direction, button);
    return 0;
}

void clear_field() { printf("\e[1;1H\e[2J"); }

// accept ball, rockets position and draw field depending on the current state
void draw_field(int ball_pos_x, int ball_pos_y, int rocket_p1_y_pos, int rocket_p2_y_pos, int score_p1,
                int score_p2) {
    for (int border_height = 0; border_height < 5; border_height++) {
        printf(CYAN);
        for (int border_width = 0; border_width < FIELD_WIDTH; border_width++) {
            if (border_height == 0 || border_height == 4) {
                printf("-");
            }
            if (border_height == 2 && border_width == 1) {
                print_game_score(score_p1, score_p2);
            }
        }
        printf("\n");
    }
    for (int height = 0; height < FIELD_HEIGHT; height++) {
        if (height < FIELD_HEIGHT / 2) {
            printf(GREEN);
        } else {
            printf(YELLOW);
        }
        for (int width = 0; width < FIELD_WIDTH; width++) {
            if (height == FIELD_HEIGHT - 1 || height == 0) {
                // height border
                printf("⌗");
            } else if (width == 0 || width == FIELD_WIDTH - 1) {
                // side border
                printf("⌗");
            } else if (width == ball_pos_x && height == ball_pos_y) {
                // ball itself
                printf("ߋ");
            } else if (width == BASIC_ROCKET_1_POSITION_X && height >= rocket_p1_y_pos - 1 &&
                       height <= rocket_p1_y_pos + 1) {
                // rocket 1 itself
                printf("█");
            } else if (width == BASIC_ROCKET_2_POSITION_X && height >= rocket_p2_y_pos - 1 &&
                       height <= rocket_p2_y_pos + 1) {
                // rocket 2 itself
                printf("█");
            } else {
                // other field
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Upper = U, Lower = O, Right = R, Left = L
// 1 direction - RU, 2 - R, 3 - RO, 4 - LO, 5 - L, 6 - LU
// switch direction RU -> LO, R -> L -> RL -> LU
int change_direction_collision(int direction) {
    int res;
    if (direction == 2) {
        res = 5;
    } else if (direction == 5) {
        res = 2;
    } else if (direction == 1) {
        res = 3;
    } else if (direction == 3) {
        res = 1;
    } else if (direction == 4) {
        res = 6;
    } else {
        res = 4;
    }
    return res;
}

int new_ball_x_pos(int ball_pos_x, int direction) {
    int new_pos = ball_pos_x;
    if (direction == 1 || direction == 2 || direction == 3) {
        new_pos++;
    } else {
        new_pos--;
    }
    return new_pos;
}

int new_ball_y_pos(int ball_pos_y, int direction) {
    int new_pos = ball_pos_y;
    if (direction == 1 || direction == 6) {
        new_pos--;
    } else if (direction == 3 || direction == 4) {
        new_pos++;
    }
    return new_pos;
}

// function to change Player's one rocket position
int move_rocket_p1(int rocket_p1_y_pos, char button) {
    int new_pos = rocket_p1_y_pos;
    if (button == 'a' || button == 'A') {
        if (rocket_p1_y_pos >= 3) {
            new_pos--;
        }
    } else if (button == 'z' || button == 'Z') {
        if (rocket_p1_y_pos < FIELD_HEIGHT - 3) {
            new_pos++;
        }
    }
    return new_pos;
}

// function to change Player's two rocket position
int move_rocket_p2(int rocket_p2_y_pos, char button) {
    int new_pos = rocket_p2_y_pos;
    if (button == 'k' || button == 'K') {
        if (rocket_p2_y_pos >= 3) {
            new_pos--;
        }
    } else if (button == 'M' || button == 'm') {
        if (rocket_p2_y_pos < FIELD_HEIGHT - 3) {
            new_pos++;
        }
    }
    return new_pos;
}

int check_for_endgame_view(int score_p1, int score_p2) {
    int res = 0;
    if (score_p1 == END_SCORE || score_p2 == END_SCORE) {
        res = 1;
        if (score_p1 > score_p2) {
            printf("Player one won with score %d and handicap is %d", score_p1, score_p1 - score_p2);
        } else {
            printf("Player two won with score %d and handicap is %d", score_p2, score_p2 - score_p1);
        }
    }
    return res;
}

void print_game_score(int score_p1, int score_p2) {
    printf("Player one: %d", score_p1);
    for (int i = 0; i < FIELD_WIDTH / (FIELD_WIDTH / 8); i++) {
        printf("\t");
    }
    printf("Player two: %d", score_p2);
}

int reverse_direction_for_new_round(int direction) {
    int res;
    if (direction == 1) {
        res = 4;
    } else if (direction == 2) {
        res = 5;
    } else if (direction == 3) {
        res = 6;
    } else if (direction == 4) {
        res = 1;
    } else if (direction == 5) {
        res = 2;
    } else {
        res = 3;
    }
    return res;
}

void game(int ball_pos_x, int ball_pos_y, int rocket_p1_y_pos, int rocket_p2_y_pos, int score_p1,
          int score_p2, int direction, char button) {
    while (button != 'r' || button == -1) {
        if (button == 'a' || button == 'A' || button == 'z' || button == 'Z' || button == 'k' ||
            button == 'K' || button == 'M' || button == 'm' || button == ' ') {
            if (ball_pos_y > FIELD_HEIGHT - 3 || ball_pos_y < 2) {
                direction = change_direction_collision(direction);
            }
            if (ball_pos_x == FIELD_WIDTH - 6 && ball_pos_y <= rocket_p2_y_pos + 1 &&
                ball_pos_y >= rocket_p2_y_pos - 1) {
                if (ball_pos_y == rocket_p2_y_pos) {
                    direction = 2;
                } else if (ball_pos_y == rocket_p2_y_pos - 1) {
                    direction = 4;
                } else {
                    direction = 6;
                }
                direction = change_direction_collision(direction);
            } else if (ball_pos_x == 6 && ball_pos_y >= rocket_p1_y_pos - 1 &&
                       ball_pos_y <= rocket_p1_y_pos + 1) {
                if (ball_pos_y == rocket_p1_y_pos) {
                    direction = 5;
                } else if (ball_pos_y == rocket_p1_y_pos - 1) {
                    direction = 3;
                } else {
                    direction = 1;
                }
                // change direction because of touching rocket
                direction = change_direction_collision(direction);
            }
            ball_pos_x = new_ball_x_pos(ball_pos_x, direction);
            ball_pos_y = new_ball_y_pos(ball_pos_y, direction);
            rocket_p1_y_pos = move_rocket_p1(rocket_p1_y_pos, button);
            rocket_p2_y_pos = move_rocket_p2(rocket_p2_y_pos, button);
            if (ball_pos_x <= 2 || ball_pos_x > FIELD_WIDTH - 2) {
                ball_pos_x = BASIC_BALL_X_POS;
                ball_pos_y = BASIC_BALL_Y_POS;
                rocket_p1_y_pos = BASIC_ROCKET_POSITION_Y;
                rocket_p2_y_pos = BASIC_ROCKET_POSITION_Y;
                // change direction to reverse because of scored
                direction = reverse_direction_for_new_round(direction);
                if (ball_pos_x <= 2) {
                    score_p2++;
                } else {
                    score_p1++;
                }
            }
        }
        draw_field(ball_pos_x, ball_pos_y, rocket_p1_y_pos, rocket_p2_y_pos, score_p1, score_p2);
        button = getchar();
        clear_field();
        if (check_for_endgame_view(score_p1, score_p2)) {
            break;
        }
    }
}