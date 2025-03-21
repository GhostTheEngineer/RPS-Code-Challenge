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

	void ClearScreen() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD topLeft = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		GetConsoleScreenBufferInfo(hConsole, &screen);
		FillConsoleOutputCharacterA(hConsole, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(hConsole, screen.wAttributes, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		SetConsoleCursorPosition(hConsole, topLeft);
	}
	void SetColor(enum Color color){ SetConsoleTextAttribute(hConsole, color);}

#else // UNIX:
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

	void ClearScreen() { std::system("clear"); }

	void SetColor(enum Color color)
	{
		switch (color)
		{
		case Color::LightGrey:
			std::cout << RESET;
			break;
		case Color::White:
			std::cout << WHITE;
			break;
		case Color::Red:
			std::cout << RED;
			break;
		case Color::Blue:
			std::cout << BLUE;
			break;
		case Color::Green:
			std::cout << GREEN;
			break;
		case Color::Yellow:
			std::cout << YELLOW;
			break;
		default:
			std::cout << RESET;
			break;
		}
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
		std::cout << "\nYou chose:      " << (playerChoice == Choice::Rock ? "\033[37mRock" : playerChoice == Choice::Paper ? "\033[34mPaper\033[37m" : "\033[31mScissors\033[37m") << "\n";
		std::cout << "Computer chose: " << (computerChoice == Choice::Rock ? "\033[37mRock" : computerChoice == Choice::Paper ? "\033[34mPaper\033[37m" : "\033[31mScissors\033[37m") << "\n";

		// Determine the winner of the round
		if (playerChoice == computerChoice) {
			std::cout << "\033[33m"  << "\nIt's a draw!\n" << "\033[37m"; //Yellow color
			++ties;
		}
		else if ((playerChoice == Choice::Rock && computerChoice == Choice::Scissors) ||
			(playerChoice == Choice::Paper && computerChoice == Choice::Rock) ||
			(playerChoice == Choice::Scissors && computerChoice == Choice::Paper)) {
			std::cout << "\033[32m" << "\nYou win this round!\n" << "\033[37m";
			++playerScore;
		}
		else {
			std::cout << "\033[31m" << "\nComputer wins this round!\n" << "\033[37m";
			++computerScore;
		}

		++round;

		if ((round > roundLimit) && (playerScore == computerScore)) //Tiebreaker
		{
				++roundLimit;
				std::cout << "\033[33m" << "\nMore rounds added! The winner takes it all!" << "\033[37m";
		}

		std::cout << "\n\nPress Enter to continue...";
		std::cin.get();

	} while (round <= roundLimit);

	// Display final score
	std::cout << "\nFinal Score:\n"
		<< "  You      [" << "\033[32m" << playerScore << "\033[37m" << "]\n"
		<< "  Computer [" << "\033[31m" << computerScore << "\033[37m" << "]\n"
		<< "  Draws    [" << "\033[33m" << ties << "\033[37m" << "]\n"
		<< "\nThanks for playing!\n\n";

	SetColor(Color::LightGrey);
	std::cout << "\nPress Enter to exit...";
	std::cin.get();  // Waits for user input before closing terminal
}

void MenuSelectRounds(int& RoundLimit)
{
	int userInput{ 0 };

	do {
		ClearScreen(); //Clear the console screen before repeating the loop
		SetColor(Color::White);
		std::cout << std::format("Welcome to Rock, Paper, Scissors!\n\n"
		"How many rounds would you like to play ({}-{})?"
		"\nUse arrow keys UP and DOWN, then press ENTER.\n\n"
		"Rounds: {}", MIN_ROUNDS, MAX_ROUNDS, RoundLimit);
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