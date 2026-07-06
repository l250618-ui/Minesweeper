#include <iostream>
#include <cstdlib>
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
    int row = rand() % 5;
    int col = rand() % 5;
    board[row][col] = -1;

    // print
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}