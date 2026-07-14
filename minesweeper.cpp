#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


// Initializes the hidden board
// At the start, every cell is empty and has no mines or numbers
void initializeBoard(int board[5][5]) {

    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            board[i][j] = 0;
        }
    }
}


// Places random mines on the board
// Mines are represented using -1
void placeMines(int board[5][5]) {

    // Seed the random number generator using current time
    // This makes the mine positions different every time the program runs
    srand(time(0));


    // Keep placing mines until 4 mines have been successfully placed
    // The loop does not increase count if a duplicate position is generated
    for (int count = 0; count < 4;) {

        int row = rand() % 5;
        // Generates a random row between 0 and 4

        int col = rand() % 5;
        // Generates a random column between 0 and 4


        // Check if this position already contains a mine
        // If it does, generate another position
        if (board[row][col] == -1) {

            continue;
        }

        else {

            board[row][col] = -1;
            count++;
        }
    }
}


// Checks whether a cell exists inside the board
// Prevents accessing invalid positions like board[-1][0] or board[5][2]
bool validcell(int row, int col) {

    if (row >= 0 && row < 5 && col >= 0 && col < 5) {

        return true;
    }

    return false;
}


// Calculates the numbers around every mine
// Each non-mine cell stores how many mines exist in its neighboring cells
void calculateNumbers(int board[5][5]) {


    int neighbourRow, neighbourCol;


    // Go through every cell because every cell needs to know its surrounding mines
    for (int r = 0; r < 5; r++) {


        for (int c = 0; c < 5; c++) {


            // Stores the number of mines around the current cell
            // Reset for every new cell because every cell has its own count
            int count = 0;


            // If this cell is a mine, it already contains -1
            // No number needs to be calculated
            if (board[r][c] == -1) {

                continue;
            }


            // Check all 8 possible neighboring positions
            // i changes the row (-1 = above, 0 = same row, 1 = below)
            // j changes the column (-1 = left, 0 = same column, 1 = right)
            for (int i = -1; i <= 1; i++) {


                for (int j = -1; j <= 1; j++) {


                    // Skip the current cell itself
                    // A cell is not its own neighbor
                    if (i == 0 && j == 0) {

                        continue;
                    }


                    // Calculate the actual neighbor position
                    neighbourRow = r + i;
                    neighbourCol = c + j;



                    // Before accessing the neighbor,
                    // check that it exists inside the board
                    if (validcell(neighbourRow, neighbourCol) == true) {


                        // If the neighboring cell contains a mine,
                        // increase the count
                        if (board[neighbourRow][neighbourCol] == -1) {

                            count++;
                        }
                    }
                }
            }


            // Store the final number of surrounding mines
            // Example: if 3 mines surround this cell, store 3
            board[r][c] = count;
        }
    }
}


// Prints the player's visible board
// This board only shows cells the player has revealed
void printpboard(char playboard[5][5]) {

    cout << "  ";

    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }

    cout << endl;

    for (int i = 0; i < 5; i++) {

        cout << i << " ";

        for (int j = 0; j < 5; j++) {

            cout << playboard[i][j] << " ";
        }

        cout << endl;
    }
}


// Creates the hidden player board
// '#' represents cells that the player has not discovered yet
void initializePlayerBoard(char playerboard[5][5]) {


    for (int i = 0; i < 5; i++) {


        for (int j = 0; j < 5; j++) {

            playerboard[i][j] = '#';
        }
    }
}


// Counts how many safe cells exist on the board
// Used to check when the player has revealed all non-mine cells
int countSafeCells(int board[5][5]) {

    int safecells = 0;


    for (int i = 0; i < 5; i++) {


        for (int j = 0; j < 5; j++) {


            // Every cell except mines is a safe cell
            if (board[i][j] != -1) {

                safecells++;
            }
        }
    }


    return safecells;
}


// Prints the hidden board for testing purposes
// This allows us to see mines and calculated numbers while developing
void printHiddenBoard(int board[5][5]) {


    for (int i = 0; i < 5; i++) {


        for (int j = 0; j < 5; j++) {

            cout << board[i][j] << " ";
        }

        cout << endl;
    }
}

void revealMines(char playerboard[5][5], int board[5][5]) {
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            if (board[i][j] == -1) {
                playerboard[i][j] = '*';
            }
        }
    }
}

void revealCell(char playerboard[5][5], int board[5][5], int row, int col, int &revealedcells) {


    // Base case 1:
    // If the cell is outside the board, stop recursion
    // This prevents accessing invalid memory locations
    if (validcell(row, col) == false) {

        return;
    }


    // Base case 2:
    // If the cell has already been revealed, stop recursion
    // This prevents checking the same cells again and again
    // which would cause infinite recursion
    else if (playerboard[row][col] != '#') {

        return;
    }


    else {


        // Reveal the current cell
        // Since board stores integers and playerboard stores characters,
        // we convert the number into its character equivalent
        // Example: 2 becomes '2'
        playerboard[row][col] = '0' + board[row][col];


        // Increase the number of revealed safe cells
        revealedcells++;



        // Base case 3:
        // If this cell has a number from 1-8,
        // reveal only this cell and stop
        // We only expand when the cell is 0
        if (board[row][col] != 0) {

            return;
        }



        // If this cell contains 0,
        // check all 8 neighboring cells
        // This is the recursive case
        for (int i = -1; i <= 1; i++) {


            for (int j = -1; j <= 1; j++) {



                // Skip the current cell itself
                // A cell is not considered its own neighbor
                if (i == 0 && j == 0) {

                    continue;
                }



                // Calculate the actual position of the neighboring cell
                // using the current cell's position and the offset
                int neighbourRow = row + i;
                int neighbourCol = col + j;



                // Check that the neighbor exists inside the board
                if (validcell(neighbourRow, neighbourCol) == true) {


                    // Recursively reveal the neighboring cell
                    // If it is 0, it will continue expanding
                    // If it is a number, recursion stops there
                    revealCell(playerboard, board, neighbourRow, neighbourCol, revealedcells);
                }
            }
        }
    }
}


bool playerMove(char playboard[5][5], int board[5][5], int &revealedcells) {


    // Taking player's chosen cell coordinates
    int prow, pcol;


    cout << "Row: ";
    cin >> prow;



    // Validate row input
    // The board only has indexes 0-4
    // Anything outside this range would access invalid memory
    if (prow < 0 || prow > 4) {

        cout << "Invalid Input!" << endl;

        return true;
    }



    cout << "Column: ";
    cin >> pcol;



    // Validate column input
    // Prevents accessing invalid positions
    // like board[5][2] or board[-1][3]
    if (pcol < 0 || pcol > 4) {

        cout << "Invalid Input!" << endl;

        return true;
    }




    // If the selected cell contains a mine,
    // reveal the mine and end the game
    if (board[prow][pcol] == -1) {

        
        cout << "BOOM!" << endl;
        cout << "You Lost! Game Over!" << endl;

        // Show the mine location
        revealMines(playboard, board);

        // Print final board
        printpboard(playboard);

        // Returning false stops the game loop
        return false;
    }
    
    else {
        revealCell(playboard, board, prow, pcol, revealedcells);
    }
    return true;
}


int main() {


    int board[5][5];



    // Initialize hidden board
    // Every cell starts empty
    initializeBoard(board);



    // Randomly place mines
    placeMines(board);



    // Calculate numbers around each mine
    calculateNumbers(board);



    // Display hidden board for testing
    // Shows mines and numbers while developing
    printHiddenBoard(board);




    // Create the player's visible board
    // This board hides mines and numbers until revealed
    char playboard[5][5];



    // Fill player board with '#'
    initializePlayerBoard(playboard);




    // Controls whether the game is running
    // Game starts true because the player has not lost yet
    bool game = true;



    // Keeps track of how many safe cells have been revealed
    int revealedcells = 0;

    cout << "Welcome To Minesweeper!" << endl;


    // Continue playing until the player hits a mine
    while (game == true) {



        // Show current player board
        printpboard(playboard);



        // Take player's move
        game = playerMove(playboard, board, revealedcells);





        // If all safe cells are revealed, player wins
        if (revealedcells == countSafeCells(board)) {


            cout << "Congratulations! You Win!" << endl;

            return 0;
        }
    }

}