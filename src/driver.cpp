#include "driver.h"
#include <iostream>
#include <cstdlib> // for rand()
#include <ctime>   // for seeding rand()

void run() {
    std::srand(std::time(0)); // Seed randomness

    int playerScore = 0, computerScore = 0, ties = 0, round = 0, roundLimit = 0;

    std::cout << "\nWelcome to Rock, Paper, Scissors!\n\n";
    std::cout << "How many rounds would you like to play: ";
    
    std::cin >> roundLimit; // get input for rounds to play

    do { // game loop - top of round
        
        // Prompt user for choice
        std::cout << "\nROUND " << round << "\n";
        std::cout << "Enter 1 for Rock, 2 for Paper, 3 for Scissors, 4 to Quit: ";

        int playerChoice;
        std::cin >> playerChoice;
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

        if (playerChoice == 4) break; 
        if (playerChoice < 1 || playerChoice > 3) continue;

        int computerChoice = (std::rand() % 100) % 3 + 1;

        // Display choices
        std::cout << "You chose: " << (playerChoice == 1 ? "Rock" : playerChoice == 2 ? "Paper" : "Scissors") << "\n";
        std::cout << "Computer chose: " << (computerChoice == 1 ? "Rock" : computerChoice == 2 ? "Paper" : "Scissors") << "\n";

        // Determine the winner of the round
        if (playerChoice == computerChoice) {
            std::cout << "It's a tie!\n";
            ++ties;
        } else if ((playerChoice == 1 && computerChoice == 2) ||
                  (playerChoice == 2 && computerChoice == 3) ||
                  (playerChoice == 3 && computerChoice == 1))  {
            std::cout << "You win this round!\n";
            ++playerScore;
        } else {
            std::cout << "Computer wins this round!\n";
            ++computerScore;
        }

        ++round;

    } while (round < roundLimit);

    // Display final score
    std::cout << "\nFinal Score:\n"
              << "  You [" << playerScore << "]\n"
              << "  Computer [" << computerScore << "]\n"
              << "  Ties [" << ties << "]\n"
              << "Thanks for playing!\n\n";

    std::cout << "Press Enter to exit...";
    std::cin.get();  // Waits for user input before closing terminal
}
