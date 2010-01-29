#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SECSIZE (3)
#define SIZE    (9)
#define NCELLS  (SIZE*SIZE)

// Fake boolean values
#define TRUE    (1)
#define FALSE   (0)
// Define the "bool" type using "short int"
typedef short int bool;

typedef struct {
    int x, y;
} point;

typedef struct {
    int cells[SIZE][SIZE];
    int free_cells;
    point moves[NCELLS];
} sudoku_board;

void init_board(sudoku_board *board) {
    board->free_cells = NCELLS;
}

void set_cell(sudoku_board *board, int x, int y, int val) {
    if ( val == 0 ) {
        board->cells[x][y] = 0;
        ++board->free_cells;
    }
    if ( val > 0 && val < 10 ) {
        board->cells[x][y] = val;
        --board->free_cells;
    }
}

void try(sudoku_board *curr_sol, int curr_move, int candidate) {
    // Set the cell of the current move to 'candidate'
    set_cell(curr_sol, curr_sol->moves[curr_move ].x, curr_sol->moves[curr_move].y, candidate);
}
                
                
void revert(sudoku_board *curr_sol, int curr_move) {
    // Set the cell of the current move to '0' (reverted)
    set_cell(curr_sol, curr_sol->moves[curr_move ].x, curr_sol->moves[curr_move].y, 0);
}

void output(sudoku_board *curr_sol) {
    #define c curr_sol->cells
    printf(" ------- ------- ------- \n");
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][0], c[1][0], c[2][0], c[3][0], c[4][0], c[5][0], c[6][0], c[7][0], c[8][0]);
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][1], c[1][1], c[2][1], c[3][1], c[4][1], c[5][1], c[6][1], c[7][1], c[8][1]);
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][2], c[1][2], c[2][2], c[3][2], c[4][2], c[5][2], c[6][2], c[7][2], c[8][2]);
    printf(" ------- ------- ------- \n");
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][3], c[1][3], c[2][3], c[3][3], c[4][3], c[5][3], c[6][3], c[7][3], c[8][3]);
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][4], c[1][4], c[2][4], c[3][4], c[4][4], c[5][4], c[6][4], c[7][4], c[8][4]);
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][5], c[1][5], c[2][5], c[3][5], c[4][5], c[5][5], c[6][5], c[7][5], c[8][5]);
    printf(" ------- ------- ------- \n");
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][6], c[1][6], c[2][6], c[3][6], c[4][6], c[5][6], c[6][6], c[7][6], c[8][6]);
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][7], c[1][7], c[2][7], c[3][7], c[4][7], c[5][7], c[6][7], c[7][7], c[8][7]);
    printf("| %d %d %d | %d %d %d | %d %d %d |\n", c[0][8], c[1][8], c[2][8], c[3][8], c[4][8], c[5][8], c[6][8], c[7][8], c[8][8]);
    printf(" ------- ------- ------- \n");
    
    printf("\n-> Free Cells: %d\n\n", curr_sol->free_cells);
}

bool accept(sudoku_board *curr_sol) {
    return (curr_sol->free_cells == 0);
}

void generate_candidates(int x, int y, sudoku_board *curr_sol, bool *candidates) {
    int i, j;
    // Coordinate of the TOP-LEFT sector where (x,y) lay
    int tlx = SECSIZE * (x/SECSIZE), tly = SECSIZE * (y/SECSIZE);
    for ( i = 0; i < SIZE; ++i ) { // For all the candidate value '1->9'
        for ( j = 0; j < SIZE; ++j ) {
            if ( j != x && curr_sol->cells[j][y] == (i+1) ) {
                candidates[i] = FALSE;
                break; // i already present on this row
            }
            if ( j != y && curr_sol->cells[x][j] == (i+1) ) {
                candidates[i] = FALSE;
                break; // i already present on this column
            }
            if ( curr_sol->cells[tlx + (j % SECSIZE)][tly + (j / SECSIZE)] == (i+1) ) {
                candidates[i] = FALSE;
                break; // i already present in this section
            }
                
            candidates[i] = TRUE;
        }
    }
}

void next_square(int *x, int *y, sudoku_board *curr_sol) {
    /*
    int px = 0, py = 0;
    while ( TRUE ) {
        px = rand() % SIZE; py = rand() % SIZE;
        if ( curr_sol->cells[px][py] == 0 ) { // if it's free
            break;
        }
    }
    *x = px; *y = py;
    */
    
    int i,j;
    for ( i = 0; i < SIZE; ++i ) {
        for ( j = 0; j < SIZE; ++j ) {
            if ( curr_sol->cells[i][j] == 0 ) {
                *x = i; *y = j;
                return;
            }
        }
    }
    
}

void extend_solution(sudoku_board *curr_sol, int curr_move, bool *candidates) {
    int x, y; // Next square
    int i;
    
    x = y = -1;
    next_square(&x, &y, curr_sol); // choose the best next square to try to fill
    
    if ( x < 0 || y < 0 ) return; // There are no square for this
    
    curr_sol->moves[curr_move].x = x; // Next move is on (x,y)
    curr_sol->moves[curr_move].y = y;
    
    generate_candidates(x, y, curr_sol, candidates);
}

void backtrack(sudoku_board *curr_sol, int curr_move) {
    //output(curr_sol);
    
    bool candidates[SIZE];
    int i;
  
    if ( accept(curr_sol) ) {
        output(curr_sol); // Found! Print it
    } else {        
        // Generate solution extension
        extend_solution(curr_sol, curr_move, candidates);
        // Try every candidates just generated
        for ( i = 0; i < SIZE; ++i ) {
            if ( candidates[i] == TRUE ) {
                try(curr_sol, curr_move, i+1);
                
                backtrack(curr_sol, curr_move+1);
                
                revert(curr_sol, curr_move);
            }
        }
    }
}

int main(int argc, char **argv) {
    sudoku_board *board = malloc(sizeof(sudoku_board));
    init_board(board);
    
    set_cell(board, 7, 0, 1);
    set_cell(board, 8, 0, 2);
    set_cell(board, 4, 1, 3);
    set_cell(board, 5, 1, 5);
    set_cell(board, 3, 2, 6);
    set_cell(board, 7, 2, 7);
    set_cell(board, 0, 3, 7);
    set_cell(board, 6, 3, 3);
    set_cell(board, 3, 4, 4);
    set_cell(board, 6, 4, 8);
    set_cell(board, 0, 5, 1);
    set_cell(board, 3, 6, 1);
    set_cell(board, 4, 6, 2);
    set_cell(board, 1, 7, 8);
    set_cell(board, 7, 7, 4);
    set_cell(board, 1, 8, 5);
    set_cell(board, 6, 8, 6);
    
    output(board);
    
    backtrack(board, 0);
}