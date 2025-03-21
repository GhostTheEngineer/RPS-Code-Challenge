module driver;
import <iostream>;
import <regex>;
import <random>;
import <format>;
import <conio.h>;

namespace game
{
enum Color { Black = 0, LightGrey = 7, DarkGrey = 8, Blue = 9, Green = 10, Cyan = 11, Red = 12, Pink = 13, Yellow = 14, White = 15 };

#ifdef _WIN32
#include <windows.h>    //for  SetConsoleTextAttribute(hConsole, int);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	void ClearScreen() { system("cls"); }
	void SetColor(enum Color color){ SetConsoleTextAttribute(hConsole, color);}
	//std::cout << "\033[2J\033[1;1H"; //Fake clear screen - scrolls up to make it seem like an update

#else // UNIX:
	void ClearScreen() { std::system("clear"); }

	void SetColor(enum Color color)
	{
		if(color == Color::LightGrey) std::cout << "\033[0m";
		else if (color == Color::White) std::cout << "\033[37m";
		else if (color == Color::Red) std::cout << "\033[31m";
		else if (color == Color::Blue) std::cout << "\033[34m";
	}

#endif

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

	const int MIN_ROUNDS{ 1 };
	const int MAX_ROUNDS{ 100 };

	//void ClearScreen();
	void MenuSelectRounds(int& RoundLimit);
	int MenuSelectWeapon(const int& round, const int& roundLimit);
	void MenuWeaponList(const int& round, const int& roundLimit, const int& currentMenuPos);

	enum Choice { Rock = 1, Paper, Scissors };

	void run() {
		//SETUP
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(1, 3);

		int playerScore{ 0 }, computerScore{ 0 }, ties{ 0 }, round{ 1 }, roundLimit{ 5 }, userInput{ 0 }, playerChoice{ 0 };

		//WELCOME SCREEN & SELECT ROUNDS
		MenuSelectRounds(roundLimit);

		//MAIN GAME
		do{
		playerChoice = MenuSelectWeapon(round, roundLimit);

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

		std::cout << "\nPress Enter to continue...";
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

void MenuSelectRounds(int& RoundLimit)
{
	int userInput{ 0 };

	do {
		SetColor(Color::White);
		std::cout << "Welcome to Rock, Paper, Scissors!\n\n";
		std::cout << std::format("How many rounds would you like to play ({}-{})?", MIN_ROUNDS, MAX_ROUNDS);
		std::cout << ("\nUse arrow keys UP and DOWN, then press ENTER.\n\n");
		std::cout << std::format("Rounds: {}", RoundLimit);
		userInput = _getch();

		switch (userInput)
		{
		case KEY_UP:
			++RoundLimit;
			if (MAX_ROUNDS < RoundLimit) RoundLimit = MAX_ROUNDS;
			break;
		case KEY_DOWN:
			--RoundLimit;
			if (MIN_ROUNDS > RoundLimit) RoundLimit = MIN_ROUNDS;
			break;
		default:
			continue;
		}
		ClearScreen(); //Clear the console screen before repeating the loop
	} while (KEY_ENTER != userInput);
}


int MenuSelectWeapon(const int& round, const int& roundLimit)
{
	int userInput{ 0 };
	int currentMenuPos = Choice::Rock;
	MenuWeaponList(round, roundLimit, currentMenuPos); //Rock selected by default

	do {
		userInput = _getch();
		switch (userInput)
		{
		case KEY_UP:
			--currentMenuPos;
			if (currentMenuPos == 0) currentMenuPos = 3;
			break;
		case KEY_DOWN:
			++currentMenuPos;
			if (currentMenuPos == 4) currentMenuPos = 1;
			break;
		case KEY_ENTER:
			break;
		default:
			continue;
		}
		MenuWeaponList(round, roundLimit, currentMenuPos);
	} while (KEY_ENTER != userInput);

	return currentMenuPos;
}


void MenuWeaponList(const int& round, const int& roundLimit, const int& currentMenuPos)
{
	ClearScreen();
	SetColor(Color::White);
	std::cout << std::format("\nROUND: {}\\{}\n\n", round, roundLimit);

	std::cout << std::format("{}   Rock   {}", currentMenuPos==Choice::Rock ? ">" : " ", currentMenuPos == Choice::Rock ? "<" : " ") << std::endl;
	
	SetColor(Color::Blue);
	std::cout << std::format("{}  Paper   {}", currentMenuPos == Choice::Paper ? ">" : " ", currentMenuPos == Choice::Paper ? "<" : " ") << std::endl;
	
	SetColor(Color::Red);
	std::cout << std::format("{} Scissors {}", currentMenuPos == Choice::Scissors ? ">" : " ", currentMenuPos == Choice::Scissors ? "<" : " ") << std::endl;
}

} //namespace game