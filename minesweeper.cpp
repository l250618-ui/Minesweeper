#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    int board[5][5];

    // initialize
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = 0;
        }
    }

    // generating random numbers
    srand(time(0));
    // Seeds the random number generator using current time
    // so that we get different random values every time the program runs
    for (int count = 0; count < 4; ){ 
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

    // generating numbers around all mines
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
                if (neighbourRow >= 0 && neighbourRow < 5 && neighbourCol >= 0 && neighbourCol < 5) {

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

    // print
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}