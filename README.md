C++ Console Tic-Tac-Toe (vs AI)



A robust, console-based implementation of the classic Tic-Tac-Toe game, featuring a single-player mode against a rule-based Artificial Intelligence (AI) opponent. This project demonstrates core C++ principles, object-oriented design, and algorithmic thinking.



✨ Key Features Demonstrated



Object-Oriented Design (OOD): Encapsulation of all game state and logic within a single TicTacToe class.



AI Implementation: The AI opponent ('O') uses a simple heuristic-based decision tree:



Check for winning moves.



Check for blocking the human player ('X').



Prioritize strategic positions (Center, Corners, Edges) for optimal play.



Data Structures: Utilization of std::vector for board representation and dynamic state management.



Robust Input Handling: Includes validation and error clearing using std::cin.clear() and std::cin.ignore() to ensure the program doesn't crash on invalid (non-numeric or out-of-range) user input.



Game Loop Management: Clear separation between game drawing, input processing, state checking, and turn switching.



Game Statistics: Tracks and displays wins, losses, and draws across multiple rounds.



🛠️ How to Compile and Run



This project is a standard C++ application and requires a C++ compiler (like g++ or Visual Studio) to run.



Prerequisites



A C++ compiler (e.g., GCC/g++ on Linux/macOS, or MinGW/Visual Studio on Windows).



Compilation Steps



Save the file: Ensure tic\_tac\_toe.cpp is saved locally.



Compile using g++: Open your terminal and run the following command to compile the source file:



g++ -std=c++11 tic\_tac\_toe.cpp -o tictactoe





Execution Steps



Run the executable:



./tictactoe





(On Windows, you may need to type tictactoe.exe)



Follow the on-screen prompts to play as Player 'X' against the AI.



📄 Project Structure



File



Description



tic\_tac\_toe.cpp



The complete source code for the game, including the main TicTacToe class and game logic.



README.md



This document, explaining the project's features and build instructions.



.gitignore



Ensures compiled files (\*.out, \*.exe) are not tracked by Git.

