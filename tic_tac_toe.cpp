#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm> // For utility functions

/**
 * @brief Represents the state and logic of a Tic-Tac-Toe game.
 * This class handles the board, player turns, move validation,
 * and checking for win conditions or a draw.
 */
class TicTacToe {
private:
    // Board state and control
    std::vector<char> board;
    char currentPlayer;
    bool gameStatus; // true if game is ongoing, false otherwise

    // Game Statistics (New feature for resume)
    int playerXWins;
    int playerOWins;
    int draws;
    int totalGames;

    /**
     * @brief Initializes the board state for a new round.
     */
    void initializeBoard() {
        for (int i = 0; i < 9; ++i) {
            board[i] = (char)('1' + i);
        }
        currentPlayer = 'X';
        gameStatus = true;
    }

    /**
     * @brief Displays the current game statistics.
     */
    void displayStats() const {
        std::cout << "\n========================================\n";
        std::cout << "        GAME STATISTICS (" << totalGames << " Rounds)\n";
        std::cout << "----------------------------------------\n";
        std::cout << "Player X (You) Wins: " << playerXWins << "\n";
        std::cout << "Player O (AI) Wins:  " << playerOWins << "\n";
        std::cout << "Draws:               " << draws << "\n";
        std::cout << "========================================\n\n";
    }

    /**
     * @brief Draws the current state of the board to the console.
     */
    void drawBoard() const {
        std::cout << "\n\t   |   |   \n";
        std::cout << "\t " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
        std::cout << "\t___|___|___\n";
        std::cout << "\t   |   |   \n";
        std::cout << "\t " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
        std::cout << "\t___|___|___\n";
        std::cout << "\t   |   |   \n";
        std::cout << "\t " << board[6] << " | " << board[7] << " | " << board[8] << " \n";
        std::cout << "\t   |   |   \n\n";
    }

    /**
     * @brief Checks if any player has won the game.
     * @return true if there is a winner, false otherwise.
     */
    bool checkWin() const {
        // Check 3 rows
        for (int i = 0; i < 9; i += 3) {
            if (board[i] == board[i+1] && board[i+1] == board[i+2]) return true;
        }
        // Check 3 columns
        for (int i = 0; i < 3; ++i) {
            if (board[i] == board[i+3] && board[i+3] == board[i+6]) return true;
        }
        // Check 2 diagonals
        if ((board[0] == board[4] && board[4] == board[8]) ||
            (board[2] == board[4] && board[4] == board[6])) {
            return true;
        }
        return false;
    }

    /**
     * @brief Checks if the game has ended in a draw.
     * @return true if all spots are filled, false otherwise.
     */
    bool checkDraw() const {
        for (char c : board) {
            // Check if any position still holds its initial number
            if (c >= '1' && c <= '9') {
                return false; // Found an empty spot
            }
        }
        return true; // All spots are filled
    }

    /**
     * @brief Switches the current player from 'X' to 'O' or vice versa.
     */
    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // --- AI LOGIC FUNCTIONS ---

    /**
     * @brief Checks if making a move at index i results in a win for the specified player.
     * @param i The index to test (0-8).
     * @param player The player ('X' or 'O') to check for a win.
     * @return true if making the move wins the game for that player.
     */
    bool checkPotentialWin(int i, char player) {
        char originalChar = board[i];
        // Ensure the spot is not already taken by a committed move
        if (originalChar == 'X' || originalChar == 'O') return false;

        board[i] = player; // Commit test move
        bool isWin = checkWin();
        board[i] = originalChar; // Undo test move (backtracking)

        return isWin;
    }

    /**
     * @brief AI logic to determine the best move (winning, blocking, or heuristic).
     * @return The index (0-8) of the chosen move, or -1 if no move is found (i.e., draw).
     */
    int getAIMoveIndex() {
        // 1. Check if 'O' (AI) can win on this turn.
        for (int i = 0; i < 9; ++i) {
            if (checkPotentialWin(i, 'O')) {
                return i;
            }
        }

        // 2. Check if 'X' (Human) can win on their next turn and block it.
        for (int i = 0; i < 9; ++i) {
            if (checkPotentialWin(i, 'X')) {
                return i;
            }
        }

        // 3. Simple Heuristics: Center, Corners, Edges
        int corners[] = {0, 2, 6, 8};
        int edges[] = {1, 3, 5, 7};
        
        // Take Center (index 4) if available
        if (board[4] != 'X' && board[4] != 'O') {
            return 4;
        }

        // Take any available Corner
        for (int index : corners) {
            if (board[index] != 'X' && board[index] != 'O') {
                return index;
            }
        }
        
        // Take any available Edge
        for (int index : edges) {
            if (board[index] != 'X' && board[index] != 'O') {
                return index;
            }
        }

        return -1; // No valid move found (board is full)
    }

    /**
     * @brief Executes the AI's determined move.
     */
    void processAIMove() {
        int index = getAIMoveIndex();

        if (index != -1) {
            std::cout << "\nPlayer " << currentPlayer << " (AI) is calculating...\n";
            // Simple delay loop for effect
            for(volatile int i = 0; i < 90000000; ++i){} 

            std::cout << "Player " << currentPlayer << " chooses position " << (index + 1) << ".\n";
            board[index] = currentPlayer;
        }
    }

    // --- HUMAN INPUT FUNCTION ---

    /**
     * @brief Gets input from the current human player ('X') and processes the move.
     */
    void getPlayerMove() {
        int choice;
        bool validMove = false;

        while (!validMove) {
            std::cout << "Player " << currentPlayer << ", enter a number (1-9): ";

            // Check for valid integer input
            if (!(std::cin >> choice)) {
                std::cout << "Invalid input. Please enter a number.\n";
                std::cin.clear(); // Clear error flags
                // Discard bad input up to the newline character
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            // Check if the choice is within the valid range (1 to 9)
            if (choice >= 1 && choice <= 9) {
                int index = choice - 1;

                // Check if the chosen spot is already taken
                if (board[index] != 'X' && board[index] != 'O') {
                    board[index] = currentPlayer;
                    validMove = true;
                } else {
                    std::cout << "Spot already taken. Try again.\n";
                }
            } else {
                std::cout << "Invalid number. Please enter a number between 1 and 9.\n";
            }
        }
    }

public:
    /**
     * @brief Constructor: Initializes the board and sets the starting player, and stats.
     */
    TicTacToe() : playerXWins(0), playerOWins(0), draws(0), totalGames(0) {
        initializeBoard();
    }

    /**
     * @brief Runs the main game loop and manages multiple rounds.
     */
    void runGame() {
        char playAgain = 'y';
        std::cout << "--- C++ Console Tic-Tac-Toe (vs AI) ---\n";
        std::cout << "Player X (You) vs Player O (AI)\n";
        
        while (std::tolower(playAgain) == 'y') {
            totalGames++;
            std::cout << "\n================ ROUND " << totalGames << " START =============\n";
            initializeBoard(); // Reset board for new game

            while (gameStatus) {
                drawBoard();

                if (currentPlayer == 'X') {
                    // Human Player (X)
                    getPlayerMove();
                } else {
                    // AI Player (O)
                    processAIMove();
                }

                // Check game state after the move
                if (checkWin()) {
                    drawBoard();
                    std::string winnerName = (currentPlayer == 'X') ? "You" : "The AI";
                    std::cout << "\n*** Player " << currentPlayer << " WINS! (" << winnerName << ") ***\n";
                    
                    if (currentPlayer == 'X') {
                        playerXWins++;
                    } else {
                        playerOWins++;
                    }
                    gameStatus = false;
                } else if (checkDraw()) {
                    drawBoard();
                    std::cout << "\n*** It's a DRAW! ***\n";
                    draws++;
                    gameStatus = false;
                } else {
                    switchPlayer();
                }
            }
            
            displayStats();

            // Prompt to play again
            std::cout << "Do you want to play another round? (y/n): ";
            std::cin >> playAgain;
            // Clear input buffer for next game loop
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "\nThank you for playing! Final statistics recorded.\n";
    }
};

/**
 * @brief Main function to start the Tic-Tac-Toe game.
 */
int main() {
    TicTacToe game;
    game.runGame();

    // Prevent the console from closing immediately on some systems
    std::cout << "\nGame process finished. Press ENTER to exit.";
    std::cin.get();
    
    return 0;
}