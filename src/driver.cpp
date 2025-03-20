module driver;
import <iostream>;
import <regex>;
import <random>;
import <format>;

namespace game
{
#ifdef _WIN32
#include <conio.h>      //for _getch();
#include <windows.h>    //for  SetConsoleTextAttribute(hConsole, int);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    static inline void ClearScreen()
    {
        system("cls");
    }
    

#else // UNIX:

    static inline void ClearScreen()
    {
        std::system("clear");
    }
    std::cout << "\nInstall Windows!\n";
    exit(EXIT_FAILURE);

#endif

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13


    const int MIN_ROUNDS{ 1 };
    const int MAX_ROUNDS{ 100 };

    // Check for integer
    static bool isInteger(const std::string& str) 
    {
        static const std::regex pattern("^-?[0-9]+$");
        return std::regex_match(str, pattern);
    }

    void MenuRockSelected();
    void MenuPaperSelected();
    void MenuScissorsSelected();

    enum Choice{ Rock=1, Paper, Scissors };
    enum Color {Black=0, LightGrey=7, DarkGrey=8, Blue=9, Green=10, Cyan=11, Red=12, Pink=13, Yellow=14, White=15};

    bool bRockSelected{ false };
    bool bPaperSelected{ false };
    bool bScissorsSelected{ false };

    void run() {
        //SETUP
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, 3);

        int playerScore{ 0 }, computerScore{ 0 }, ties{ 0 }, round{ 1 }, roundLimit{ 0 };
        std::string getUserInput{};
       
        //SELECT ROUNDS
        do{
            std::cout << std::format("Welcome to Rock, Paper, Scissors!\n");
            std::cout << std::format("How many rounds would you like to play ({}-{}): ", MIN_ROUNDS, MAX_ROUNDS);
            std::getline(std::cin, getUserInput);

            if (isInteger(getUserInput)) //Check if integer
            {
                int userInput = stoi(getUserInput); //Convert string to int
                if (MIN_ROUNDS <= userInput && MAX_ROUNDS >= userInput) //Check if in range
                {
                    roundLimit = userInput;
                    break; //If OK break from the loop
                }
            }
            ClearScreen(); //Clear the console screen before repeating the loop
        } while (true);
       

        //MAIN GAME

        do { // game loop - top of round
            ClearScreen();
            SetConsoleTextAttribute(hConsole, Color::White);
            std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
           
            MenuRockSelected(); //Default starting menu

            int userChoice{ 0 };
            int playerChoice{ 0 };

            while (true)
            {
                userChoice = 0;
                userChoice = _getch();

                if (userChoice == KEY_UP)
                {
                    if (bRockSelected)
                    {
                        ClearScreen();
                        SetConsoleTextAttribute(hConsole, Color::White);
                        std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
                        MenuScissorsSelected();
                    }
                    else if (bPaperSelected)
                    {
                        ClearScreen();
                        SetConsoleTextAttribute(hConsole, Color::White);
                        std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
                        MenuRockSelected();
                    }
                    else if (bScissorsSelected)
                    {
                        ClearScreen();
                        SetConsoleTextAttribute(hConsole, Color::White);
                        std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
                        MenuPaperSelected();
                    }
                }
                if (userChoice == KEY_DOWN)
                {
                    if (bRockSelected)
                    {
                        ClearScreen();
                        SetConsoleTextAttribute(hConsole, Color::White);
                        std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
                        MenuPaperSelected();
                    }
                    else if (bPaperSelected)
                    {
                        ClearScreen();
                        SetConsoleTextAttribute(hConsole, Color::White);
                        std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
                        MenuScissorsSelected();
                    }
                    else if (bScissorsSelected)
                    {
                        ClearScreen();
                        SetConsoleTextAttribute(hConsole, Color::White);
                        std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);
                        MenuRockSelected();
                    }
                }
                if (userChoice == KEY_ENTER)
                {
                    if (bRockSelected)
                    {
                        playerChoice = Choice::Rock;
                        break;
                    }

                    if (bPaperSelected)
                    {
                        playerChoice = Choice::Paper;
                        break;
                    }

                    if (bScissorsSelected)
                    {
                        playerChoice = Choice::Scissors;
                        break;
                    }
                }
            }


            int computerChoice = distribution(generator); 

            // Display choices
            SetConsoleTextAttribute(hConsole, Color::LightGrey);
            std::cout << "\nYou chose: " << (playerChoice == Choice::Rock ? "Rock" : playerChoice == Choice::Paper ? "Paper" : "Scissors") << "\n";
            std::cout << "Computer chose: " << (computerChoice == Choice::Rock ? "Rock" : computerChoice == Choice::Paper ? "Paper" : "Scissors") << "\n";

            // Determine the winner of the round
            if (playerChoice == computerChoice) {
                std::cout << "It's a tie!\n";
                ++ties;
            }
            else if ((playerChoice == Choice::Rock && computerChoice == Choice::Scissors) ||
                (playerChoice == Choice::Paper && computerChoice == Choice::Rock) ||
                (playerChoice == Choice::Scissors && computerChoice == Choice::Paper)) {
                std::cout << "You win this round!\n";
                ++playerScore;
            }
            else {
                std::cout << "Computer wins this round!\n";
                ++computerScore;
            }

            ++round;

            std::cout << "\nPress Enter to exit...";
            std::cin.get();  // Waits for user input before closing terminal

        } while (round <= roundLimit);

        // Display final score
        std::cout << "\nFinal Score:\n"
            << "  You [" << playerScore << "]\n"
            << "  Computer [" << computerScore << "]\n"
            << "  Ties [" << ties << "]\n"
            << "Thanks for playing!\n\n";

        SetConsoleTextAttribute(hConsole, Color::LightGrey);
        std::cout << "Press Enter to exit...";
        std::cin.get();  // Waits for user input before closing terminal
    }

    void MenuRockSelected()
    {
        SetConsoleTextAttribute(hConsole, Color::White);
        std::cout << std::format(">   Rock   <") << std::endl;
        SetConsoleTextAttribute(hConsole, Color::Blue);
        std::cout << std::format("   Paper    ") << std::endl;
        SetConsoleTextAttribute(hConsole, Color::Red);
        std::cout << std::format("  Scissors  ") << std::endl;
        bRockSelected = true;
        bPaperSelected = false;
        bScissorsSelected = false;
    }

    void MenuPaperSelected()
    {
        SetConsoleTextAttribute(hConsole, Color::White);
        std::cout << std::format("    Rock    ") << std::endl;
        SetConsoleTextAttribute(hConsole, Color::Blue);
        std::cout << std::format(">  Paper   <") << std::endl;
        SetConsoleTextAttribute(hConsole, Color::Red);
        std::cout << std::format("  Scissors  ") << std::endl;
        bRockSelected = false;
        bPaperSelected = true;
        bScissorsSelected = false;
    }

    void MenuScissorsSelected()
    {
        SetConsoleTextAttribute(hConsole, Color::White);
        std::cout << std::format("    Rock    ") << std::endl;
        SetConsoleTextAttribute(hConsole, Color::Blue);
        std::cout << std::format("   Paper    ") << std::endl;
        SetConsoleTextAttribute(hConsole, Color::Red);
        std::cout << std::format("> Scissors <") << std::endl;
        bRockSelected = false;
        bPaperSelected = false;
        bScissorsSelected = true;
    }
}