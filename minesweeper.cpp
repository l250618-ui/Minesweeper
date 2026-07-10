#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void initializeBoard(int board[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = 0;
        }
    }
}

void placeMines(int board[5][5]) {
    // generating random numbers
    srand(time(0));
    // Seeds the random number generator using current time
    // so that we get different random values every time the program runs
    for (int count = 0; count < 4; ) { 
        int row = rand() % 5;
        // Generates a random number between 0 and 4 
        int col = rand() % 5;
        if (board[row][col] == -1) {
            continue;
        }
        else {
            board[row][col] = -1;
            count++;
        }
    }
}

bool validcell(int row, int col) {
    if (row >= 0 && row < 5 && col >= 0 && col < 5) {
        return true;
    }
    return false;
}

void calculateNumbers(int board[5][5]) {
    // We go through every cell because every non-mine cell needs to know how many mines are around it

int neighbourRow, neighbourCol;

for (int r = 0; r < 5; r++) { 
    // r represents the current row we are checking

    for (int c = 0; c < 5; c++) { 
        // c represents the current column we are checking
        // Together, r and c give us the position of the current cell

        int count = 0;
        // count stores how many mines are around the current cell
        // It resets for every new cell because every cell needs its own count

        // first check if current cell is a mine
        if (board[r][c] == -1) {
            // If this cell is already a mine, we don't need to calculate a number for it
            // so we skip it and move to the next cell
            continue;
        }

        // These loops check all possible neighboring positions around the current cell
        // i changes the row (-1 = above, 0 = same row, 1 = below)
        // j changes the column (-1 = left, 0 = same column, 1 = right)
        for (int i = -1; i <= 1; i++) {

            for (int j = -1; j <= 1; j++) {

                // When both i and j are 0, it means we are checking the current cell itself
                // We don't want to count the current cell as a neighbor
                if (i == 0 && j == 0) {
                    continue;
                }

                // Calculate the actual position of the neighbor using the row and column changes
                neighbourRow = r + i;
                neighbourCol = c + j;

                // Before accessing the neighbor, make sure it exists inside the board
                // This prevents accessing invalid positions like board[-1][0] or board[5][2]
                if (validcell(neighbourRow, neighbourCol) == true) {

                    // If the neighboring cell contains a mine, increase the count
                    if (board[neighbourRow][neighbourCol] == -1) {
                        count++;
                    }
                }
            }
        }

        // After checking all 8 possible neighbors,
        // store the total number of nearby mines in the current cell
        board[r][c] = count;
    }
}
}

void printpboard(char playboard[5][5]) {
     for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << playboard[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int board[5][5];

    // initialize
    initializeBoard(board);

    // generating random mines
    placeMines(board);

    // generating numbers around all mines
    calculateNumbers(board);

int safecells = 0;
for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
            if (board[i][j] != -1) {
                safecells++;
            }
        }
        cout << endl;
    }

// Creating playable board
// We create a separate board because the player should not see the hidden board
// with all mines and numbers. This board stores only what the player has revealed.
char playboard[5][5];


// Initialize playable board
// At the start, every cell is hidden, so we represent unknown cells with '#'
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
        playboard[i][j] = '#';
    }
}


// This variable controls whether the game is still running
// It starts as true because the player has not lost yet
bool game = true;
int count = 0;


// The game continues as long as the player has not hit a mine
while (game == true) {


    // Print current playable board
    // The player only sees the cells they have revealed so far
    printpboard(playboard);


    // Taking player's chosen cell coordinates
    // The player selects a row and column to reveal
    int prow, pcol;

    cout << "Row: ";
    cin >> prow;


    // Validate row input
    // The board only has indexes 0-4, so anything outside this range is invalid
    // This prevents accessing memory outside the board
    if (prow < 0 || prow > 4) {
        cout << "Invalid Input!" << endl;
        return 0;
    }


    cout << "Column: ";
    cin >> pcol;


    // Validate column input
    // Prevents accessing invalid memory locations like board[5][2] or board[-1][3]
    if (pcol < 0 || pcol > 4) {
        cout << "Invalid Input!" << endl;
        return 0;
    }


    // Check if the selected cell has already been revealed
    // If the cell is not '#', it means the player has already seen its value
    // so we reject the move and ask for another one
    if (playboard[prow][pcol] != '#') {
        cout << "Already Revealed! Invalid Input!" << endl;
        continue;
    }


    // Check what exists in the hidden board at the chosen location
    // If the cell contains a number (0-8), reveal that number on the playable board
    if (board[prow][pcol] >= 0 && board[prow][pcol] <= 8) {


        // Convert integer value into a character
        // Example: 2 becomes '2'
        // Characters for digits are stored consecutively,
        // so adding to '0' gives the correct character
        playboard[prow][pcol] = '0' + board[prow][pcol];


        // Print updated playable board after the player's move
        // Only the selected cell should be revealed
        printpboard(playboard);

        count++;
    }


    // If the selected cell contains a mine, reveal the mine symbol
    // The game will later handle losing here
    if (board[prow][pcol] == -1) {

        // Show the mine on the player's board
        playboard[prow][pcol] = '*';


        // Print final board showing where the mine was found
        printpboard(playboard);


        // Changing game state to false stops the while loop
        // and ends the game after the player hits a mine
        game = false;
    }

    if (count == safecells) {
        cout << "Congratulations! You Win!" << endl;
        return 0;
    }

}

}