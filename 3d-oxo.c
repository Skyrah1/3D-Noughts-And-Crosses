/* Play noughts and crosses (tic-tac-toe) between two human players. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
// Setting up types and constants.  Don't change this section.

// Constants for player X, player O, and neither N.
enum player { X, O, N };
typedef enum player player;

// Constants to represent validity checking.
enum validity { Unchecked, BadFormat, BadLetter, BadDigit, BadCell, OK };
typedef enum validity validity;

// A game object contains the current state of a game: the number of moves made,
// the player whose turn it is next, and the grid with each cell recording which
// player owns it.
struct game {
    int moves;
    player next;
    player grid1[3][3];
    player grid2[3][3];
    player grid3[3][3];
};
typedef struct game game;

//-----------------------------------------------------------------------------
// Functions providing the logic of the game.  Develop these.

// Initialize a game, with the given player to move first.
void newGame(game *g, player first) {
    g->moves = 0;
    g->next = first;
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            g->grid1[r][c] = N;
            g->grid2[r][c] = N;
            g->grid3[r][c] = N;
        }
    }
}

int gridNo(char *text){
    int h = -1;
    int nums[] = {1, 2, 3};
    char cols[] = {'1', '2', '3'};
    for (int i = 0; i < 3; i++){
        if (text[0] == cols[i]){
            h = nums[i];
        }
    }
    //printf("%d\n", c);
    return h;
}

// Convert the letter in a valid move string such as "b2" into a row index.
int row(char *text) {
    int r = -1;
    switch (text[1]){
        case 'a':
            r = 0;
            break;
        case 'b':
            r = 1;
            break;
        case 'c':
            r = 2;
            break;
        default:
            break;
    }
    return r;
}

// Convert the digit in a valid move string such as "b2" into a column index.
int col(char *text) {
    int c = -1;
    int nums[] = {0, 1, 2};
    char cols[] = {'1', '2', '3'};
    for (int i = 0; i < 3; i++){
        if (text[2] == cols[i]){
            c = nums[i];
        }
    }
    //printf("%d\n", c);
    return c;
}

//Returns the integer value of c if c is an integer, or -1 otherwise.
int charToInt(char c){
    int result = -1;
    char charArray[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int intArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++){
        if (c == charArray[i]){
            result = intArray[i];
        }
    }
    return result;
}

// Check whether a move string typed in by the user such as "b2" is valid, and
// the corresponding cell is available.  Return a validity code.
validity valid(game *g, char *text) {
    int validity;
    int length = strlen(text);
    //printf("%s\n", text);
    //printf("%d\n", length);
    if (length != 3){
        //printf("...\n");
        validity = BadFormat;
    } else if (row(text) == -1 || ((charToInt(text[0]) == -1) && charToInt(text[2] == -1))){
        validity = BadLetter;
    } else if (col(text) == -1){
        validity = BadDigit;
    } else if (gridNo(text) == 1 && g->grid1[row(text)][col(text)] != N){
        validity = BadCell;
    } else if (gridNo(text) == 2 && g->grid2[row(text)][col(text)] != N){
        validity = BadCell;
    } else if (gridNo(text) == 3 && g->grid3[row(text)][col(text)] != N){
        validity = BadCell;
    } else {
        validity = OK;
    }
    //printf("%d\n", validity);
    //printf("%d\n", validity);
    return validity;
}

void update(game *g, int h, int r, int c, int p){
    if (h == 1){
        g->grid1[r][c] = p;
    } else if (h == 2){
        g->grid2[r][c] = p;
    } else if (h == 3){
        g->grid3[r][c] = p;
    } else {
        printf("MOVE ERROR\n");
    }
}

// Make a move at the given valid position.
void move(game *g, int h, int r, int c) {
    int p = g->next;
    update(g, h, r, c, p);
    if (g->next == X){
        g->next = O;
    } else if (g->next == O){
        g->next = X;
    }
    g->moves++;
}

// Check if the given line is a winning one, and return the winning player.
player line(player p0, player p1, player p2) {
    player p = N;
    if (p0 == p1 && p0 == p2){
        if (p0 == X){
            p = X;
        } else if (p0 == O){
            p = O;
        }
    }
    return p;
}

bool checkForWinner(player winner){
    bool winnerFound = false;
    if (winner != N){
        winnerFound = true;
    }
    return winnerFound;
}

// Check whether a player has won, and return the winning player.
player win(game *g) {
    bool winnerFound = false;
    player winner = N;
    //rows:
    for (int r = 0; r < 3 && !winnerFound; r++){
        winner = line(g->grid1[r][0], g->grid1[r][1], g->grid1[r][2]);
        winnerFound = checkForWinner(winner);
    }
    for (int r = 0; r < 3 && !winnerFound; r++){
        winner = line(g->grid2[r][0], g->grid2[r][1], g->grid2[r][2]);
        winnerFound = checkForWinner(winner);
    }
    for (int r = 0; r < 3 && !winnerFound; r++){
        winner = line(g->grid3[r][0], g->grid3[r][1], g->grid3[r][2]);
        winnerFound = checkForWinner(winner);
    }
    for (int r = 0; r < 3 && !winnerFound; r++){
        winner = line(g->grid1[r][0], g->grid2[r][1], g->grid3[r][2]);
        winnerFound = checkForWinner(winner);
    }
    for (int r = 0; r < 3 && !winnerFound; r++){
        winner = line(g->grid3[r][0], g->grid2[r][1], g->grid1[r][2]);
        winnerFound = checkForWinner(winner);
    }
    //columns:
    for (int c = 0; c < 3 && !winnerFound; c++){
        winner = line(g->grid1[0][c], g->grid1[1][c], g->grid1[2][c]);
        winnerFound = checkForWinner(winner);
    }
    for (int c = 0; c < 3 && !winnerFound; c++){
        winner = line(g->grid2[0][c], g->grid2[1][c], g->grid2[2][c]);
        winnerFound = checkForWinner(winner);
    }
    for (int c = 0; c < 3 && !winnerFound; c++){
        winner = line(g->grid3[0][c], g->grid3[1][c], g->grid3[2][c]);
        winnerFound = checkForWinner(winner);
    }
    for (int c = 0; c < 3 && !winnerFound; c++){
        winner = line(g->grid1[0][c], g->grid2[1][c], g->grid3[2][c]);
        winnerFound = checkForWinner(winner);
    }
    for (int c = 0; c < 3 && !winnerFound; c++){
        winner = line(g->grid3[0][c], g->grid2[1][c], g->grid1[2][c]);
        winnerFound = checkForWinner(winner);
    }
    //diagonals:
    if (!winnerFound){
        winner = line(g->grid1[0][0], g->grid1[1][1], g->grid1[2][2]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid1[0][2], g->grid1[1][1], g->grid1[2][0]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid2[0][0], g->grid2[1][1], g->grid2[2][2]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid2[0][2], g->grid2[1][1], g->grid2[2][0]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid3[0][0], g->grid3[1][1], g->grid3[2][2]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid3[0][2], g->grid3[1][1], g->grid3[2][0]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid1[0][0], g->grid2[1][1], g->grid3[2][2]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid1[0][2], g->grid2[1][1], g->grid3[2][0]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid3[0][0], g->grid2[1][1], g->grid1[2][2]);
        winnerFound = checkForWinner(winner);
    }
    if (!winnerFound){
        winner = line(g->grid3[0][2], g->grid2[1][1], g->grid1[2][0]);
        winnerFound = checkForWinner(winner);
    }
    //pillars:
    for (int r = 0; r < 3 && !winnerFound; r++){
        for (int c = 0; c < 3 && !winnerFound; c++){
            winner = line(g->grid1[r][c], g->grid2[r][c], g->grid3[r][c]);
            winnerFound = checkForWinner(winner);
        }
    }
    return winner;
}

// Check whether the game has ended in a draw.
bool draw(game *g) {
    bool isEnd = true;
    bool isDraw = false;
    int r = 0;
    int c = 0;
    while (r < 3 && isEnd){
        while (c < 3 && isEnd){
            if (g->grid1[r][c] == N){
                isEnd = false;
            }
            c++;
        }
        r++;
    }
    if (isEnd && win(g) == N){
        isDraw = true;
    } else {
        isDraw = false;
    }
    return isDraw;
}

//-----------------------------------------------------------------------------
// Playing the game: Don't change this section until after submitting.

// Convert a player constant into a character for printing.
char show(player c) {
    return (c == X) ? 'X' : (c == O) ? 'O' : ' ';
}

// Print a validity error message.
void printInvalid(validity v) {
    if (v == BadFormat) printf("Type a letter and a digit");
    else if (v == BadLetter) printf("Type a letter a, b or c");
    else if (v == BadDigit) printf("Type a digit 1, 2 or 3");
    else if (v == BadCell) printf("Choose an empty cell");
    printf("\n");
}

void displayGrid(game *g, int gridNo){
    printf("     1   2   3\n");
    printf("   -------------\n");
    char rows[3] = "abc";
    for (int r = 0; r < 3; r++){
        printf("%c ", rows[r]);
        for (int c = 0; c < 3; c++){
            if (gridNo == 1){
                printf(" | %c", show(g->grid1[r][c]));
            } else if (gridNo == 2){
                printf(" | %c", show(g->grid2[r][c]));
            } else if (gridNo == 3){
                printf(" | %c", show(g->grid3[r][c]));
            } else {
                printf("ERROR!!!");
            }
        }
        printf(" |\n   -------------\n");
    }
}

// Display the grid.
void display(game *g) {
    printf("Grid 1:\n");
    displayGrid(g, 1);
    printf("Grid 2:\n");
    displayGrid(g, 2);
    printf("Grid 3:\n");
    displayGrid(g, 3);
}

// Ask the current player for their move, putting it into the given array.
// Ask repeatedly until the user types in a valid move.
void ask(game *g, char text[100]) {
    bool asking = true;
    int h, r, c;
    printf("It's %c's turn\n", show(g->next));
    while (asking){
        printf("Enter your position (e.g. 1b3)\n");
        scanf("%s", text);
        h = gridNo(text);
        r = row(text);
        c = col(text);
        if (valid(g, text) == OK){
            move(g, h, r, c);
            asking = false;
        } else {
            printf("That move is invalid. Please try again.\n");
        }
    }
}

void gameLoop(game *g){
    bool playing = true;
    char text[100];
    //printf("...\n");
    while(playing){
        display(g);
        ask(g, text);
        //display(g);
        if (win(g) != N){
            display(g);
            printf("%c WINS!!!", show(win(g)));
            playing = false;
        } else if (draw(g)){
            display(g);
            printf("DRAW!!!\n");
            playing = false;
        }
    }
}

// Play the game interactively between two human players who take turns.
void play(char player) {
    setbuf(stdout, NULL);
    game gData;
    game *g = &gData;
    newGame(g, player);
    gameLoop(g);
}

//-----------------------------------------------------------------------------
// Testing and running: Don't change this section.
/*
// Check constants haven't been changed, so that automarking works.
void checkConstants() {
    assert(X == 0 && O == 1 && N == 2);
    assert(Unchecked == 0 && BadFormat == 1 && BadLetter == 2);
    assert(BadDigit == 3 && BadCell == 4 && OK == 5);
}

// Set up a game structure with given contents.  The grid is given as a string
// of the form "XO- -XO X-X", then the next player, then the number of moves.
// Work out the number of moves made and the player to move next.
void setup(game *g, char *grid) {
    int xs = 0, os = 0, moves = 0;
    for (int r=0; r<3; r++) {
        for (int c=0; c<3; c++) {
            char ch = grid[r*4 + c];
            if (ch == 'X') { g->grid[r][c] = X; xs++; moves++; }
            else if (ch == 'O') { g->grid[r][c] = O; os++; moves++; }
            else g->grid[r][c] = N;
        }
    }
    g->moves = moves;
    if (xs == os || xs == os - 1) g->next = X;
    else if (xs == os + 1) g->next = O;
    else printf("Setup problem\n");
}

// Test initialization of the game (tests 1 to 8)
void testNew(game *g) {
    setup(g, "XXO XOO XOX");
    g->next = N;
    newGame(g, X);
    // Test a few of the cells (all should be filled with N).
    assert(g->grid[0][0] == N);
    assert(g->grid[1][1] == N);
    assert(g->grid[2][2] == N);
    assert(g->grid[0][2] == N);
    assert(g->grid[2][1] == N);
    assert(g->next == X);
    assert(g->moves == 0);
    // Test g->next isn't always set to X
    newGame(g, O);
    assert(g->next == O);
}

// Test that the row/col functions give the right answers (tests 9 to 14)
void testRowCol() {
    assert(row("a3") == 0);
    assert(row("b2") == 1);
    assert(row("c2") == 2);
    assert(col("b1") == 0);
    assert(col("b2") == 1);
    // Test pointer comparisons aren't being used
    char text[] = "a3";
    assert(row(text) == 0 && col(text) == 2);

}

// Test invalid input, or trying to play in an occupied cell (tests 15 to 23)
void testInvalid(game *g) {
    newGame(g, X);
    assert(valid(g, "d2") == BadLetter);
    assert(valid(g, "2b") == BadLetter);
    assert(valid(g, "b0") == BadDigit);
    assert(valid(g, "b4") == BadDigit);
    assert(valid(g, "b2x") == BadFormat);
    // Test input "b", but with different values for text[2], in case it is
    // incorrectly being used to test for 'length == 2'.
    assert(valid(g, "b\0x") == BadFormat);
    assert(valid(g, "b\0\0") == BadFormat);
    assert(valid(g, "") == BadFormat);
    setup(g, "---/---/-X-");
    assert(valid(g, "c2") == BadCell);
}

// Test making a move (tests 24 to 29)
void testMove(game *g) {
    newGame(g, X);
    move(g, row("b2"), col("b2"));
    assert(g->grid[1][1] == X);
    assert(g->next == O);
    assert(g->moves == 1);
    move(g, row("a3"), col("a3"));
    assert(g->grid[0][2] == O);
    assert(g->next == X);
    assert(g->moves == 2);
}

// Test the line function (tests 30 to 36)
void testLine() {
    assert(line(X, X, X) == X);
    assert(line(O, O, O) == O);
    assert(line(X, O, O) == N);
    assert(line(O, X, O) == N);
    assert(line(O, O, X) == N);
    assert(line(N, N, N) == N);
    assert(line(X, N, N) == N);
}

// Test winning lines (tests 37 to 44)
void testWin(game *g) {
    setup(g, "XXX -O- -O-");
    assert(win(g) == X);
    setup(g, "-O- XXX -O-");
    assert(win(g) == X);
    setup(g, "-O- -O- XXX");
    assert(win(g) == X);
    setup(g, "O-- OX- O-X");
    assert(win(g) == O);
    setup(g, "-O- XO- -OX");
    assert(win(g) == O);
    setup(g, "--O X-O -XO");
    assert(win(g) == O);
    setup(g, "X-O -XO --X");
    assert(win(g) == X);
    setup(g, "X-O -OX O--");
    assert(win(g) == O);
}

// Test no winning line (tests 45 to 48)
void testNoWin(game *g) {
    setup(g, "--- --- ---");
    assert(win(g) == N);
    setup(g, "O-X XXO OX-");
    assert(win(g) == N);
    setup(g, "XOX XOO OXO");
    assert(win(g) == N);
    setup(g, "OOX XXO OXX");
    assert(win(g) == N);
}

// Test drawn games (tests 49 to 50)
void testDraw(game *g) {
    setup(g, "O-X XXO OX-");
    assert(draw(g) == false);
    setup(g, "OOX XXO OXX");
    assert(draw(g) == true);
}

// Unit testing.
void test() {
    game *g = malloc(sizeof(game));
    checkConstants();
    testNew(g);
    testRowCol();
    testInvalid(g);
    testMove(g);
    testLine();
    testWin(g);
    testNoWin(g);
    testDraw(g);
    free(g);
    printf("All tests passed.\n");
}
*/

// Run the program with no args to carry out the tests, or with one arg (the
// player to go first) to play the game.
int main(int n, char *args[n]) {
    if (n == 1); //test();
    else if (n == 2 && strcmp(args[1],"X") == 0) play(X);
    else if (n == 2 && strcmp(args[1],"O") == 0) play(O);
    else {
        fprintf(stderr, "Use: ./oxo  OR  ./oxo X  OR  ./oxo O\n");
        exit(1);
    }
    return 0;
}
