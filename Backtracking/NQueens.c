#include <stdio.h>
#include <stdlib.h>

struct Board {

    int N; // the N in N x N board
    int *positions; // keep track of positions of queens
    int soln_count; // counting the total number of solutions
};

typedef struct Board Board;

Board* new_board() {

    Board *board = (Board*)malloc(sizeof(Board));

    board->N = 0;
    board->positions = NULL;
    board->soln_count = 0;

    return board;
} // end of new_board()

void create_board(Board *board) {

    int N;

    while (1) {
        
        printf("Enter N for a N x N board: ");
        scanf("%d", &N);

        if (N > 0) break;

        printf("C'mon man. This joke ain't funny!\n");
    }

    board->N = N;
    board->positions = (int*)malloc(sizeof(int) * N);

} // end of create_board(Board*)

void display_positions(Board *board) {

    printf("Positions: (");
    int i = 0;
    for (; i < board->N - 1; i++) {
        printf("%d, ", *(board->positions + i));
    }
    printf("%d)\n", *(board->positions + (board->N - 1)));
} // end of display_positions(Board*)

void dump_board(Board *board) {

    int i, row, col;

    int N = board->N;
    int *positions = board->positions;

    for (i = 0; i < N; i++) { printf("----"); }
    printf("-\n");

    for (row = 0; row < N; row++) {

        printf("|");
        for (col = 0; col < N; col++) {

            if (col == positions[row])
                printf(" Q |");
            else
                printf("   |");
        } // end of inner for loop

        printf("\n");
        for (i = 0; i < N; i++) { printf("----"); }
        printf("-\n");
    } // end of outer for loop
} // end of dump_board(Board*)

int is_possible(Board *board, int row, int column) {

    int *positions = board->positions;
    int i = 0;

    for (; i < row; i++) { // checking columns
        if (positions[i] == column) { 
            return 0;
        }
    }

    int tmp_row = row--, tmp_column = column++;

    while (row >= 0 && column < board->N) { // checking upper right diagonals
        if (positions[row--] == column++) {
            return 0;
        }
    }

    row = tmp_row - 1;
    column = tmp_column - 1;

    while (row >= 0 && column >= 0) { // checking upper left diagonals
        if (positions[row--] == column--) {
            return 0;
        }
    }

    return 1;
} // end of is_possible(Board*, int, int)

void display_possible_positions(Board *board, int row) {

    int N = board->N;
    int *positions = board->positions;

    if (row == N) {
            
        printf("Solution %d :-\n", ++board->soln_count);
        display_positions(board);
        dump_board(board);
        printf("\n");
        return;
    }

    int column = 0;
    for (; column < N; column++) {
        if (is_possible(board, row, column)) {

            positions[row] = column;
            display_possible_positions(board, row + 1);
        }
    } // end of for loop
} // end of display_possible_positions(Board*, int)


int main() {

    Board *board = new_board();
    create_board(board);

    printf("\n");
    display_possible_positions(board, 0);

    printf("The total number of possible cases: %d\n", board->soln_count);

    return 0;
} // end of main()