#include <iostream>
#include <vector>
#include <sstream> // For stringstream
#include <limits>  // For clearing input buffer

// Function to convert an integer to a string
std::string intToString(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

// Function to display the Tic-Tac-Toe board with numbered boxes
void displayBoard(const std::vector<std::vector<char> >& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int boxNumber = i * 3 + j + 1;
            std::cout << " " << (board[i][j] == ' ' ? intToString(boxNumber) : std::string(1, board[i][j])) << " ";
            if (j < 2) {
                std::cout << " |";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            std::cout << " ---|--- |---\n";
        }
    }
}

char checkWin(const std::vector<std::vector<char> >& board) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) && (board[i][0] != ' ')) {
            return board[i][0]; // Return the winning player's symbol
        }
        if ((board[0][i] == board[1][i] && board[1][i] == board[2][i]) && (board[0][i] != ' ')) {
            return board[0][i]; // Return the winning player's symbol
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) && (board[0][0] != ' ')) {
        return board[0][0]; // Return the winning player's symbol
    }
    if ((board[0][2] == board[1][1] && board[1][1] == board[2][0]) && (board[0][2] != ' ')) {
        return board[0][2]; // Return the winning player's symbol
    }

    return ' '; // No winner yet
}


// Function to check if the game is a draw
bool checkDraw(const std::vector<std::vector<char> >& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; // There's an empty cell, so the game is not a draw yet
            }
        }
    }
    return true; // All cells are filled, and there's no winner, so it's a draw
}

int main() {
    char playAgain;
    do {
        std::vector<std::vector<char> > board(3, std::vector<char>(3, ' '));
        char currentPlayer = 'X';
        char winner = ' ';
        bool gameDraw = false;

        std::cout << "Welcome to Tic-Tac-Toe!\n";

        do {
            // Display the current state of the board with numbered boxes
            std::cout << "\nCurrent board:\n";
            displayBoard(board);

            // Prompt the current player for their move
            int move;
            std::cout << "\nPlayer " << currentPlayer << ", enter the number of the box (1-9): ";

            // Error handling for invalid input
            while (!(std::cin >> move) || move < 1 || move > 9) {
                std::cout << "Invalid move. Try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Convert the move to row and column
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            if (board[row][col] == ' ') {
                board[row][col] = currentPlayer;
                winner = checkWin(board);
                if (winner != ' ' || checkDraw(board)) {
                    break; // Exit the loop if there is a winner or it's a draw
                }

                // Switch players
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            } else {
                std::cout << "Invalid move. The box is already occupied. Try again.\n";
            }
            
        } while (true);

        // Display the final state of the board with numbered boxes
        std::cout << "\nFinal board:\n";
        displayBoard(board);

        // Display the result of the game based on the winner
        if (winner == 'X') {
            std::cout << "Player X wins!\n";
        } else if (winner == 'O') {
            std::cout << "Player O wins!\n";
        } else {
            std::cout << "It's a draw!\n";
        }

        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');

    std::cout << "Thank you for playing Tic-Tac-Toe!\n";

    return 0;
}

