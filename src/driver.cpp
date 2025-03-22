module driver;
import <random>;   //default_random_engine
import <conio.h>; //_getch
import <cstdio>; //puts, getchar
import <print>; //println

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
			std::puts(RESET);
			break;
		case Color::White:
			std::puts(WHITE);
			break;
		case Color::Red:
			std::puts(RED);
			break;
		case Color::Blue:
			std::puts(BLUE);
			break;
		case Color::Green:
			std::puts(GREEN);
			break;
		case Color::Yellow:
			std::puts(YELLOW);
			break;
		default:
			std::puts(RESET);
			break;
		}
	}

#endif

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

	const int MIN_ROUNDS{ 1 };
	const int MAX_ROUNDS{ 100 };

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
		SetColor(Color::White);
		std::println("\nYou chose:      {}", (playerChoice == Choice::Rock ? "Rock" : playerChoice == Choice::Paper ? "\033[34mPaper\033[37m" : "\033[31mScissors\033[37m"));
		std::println("Computer chose: {}", (computerChoice == Choice::Rock ? "Rock" : computerChoice == Choice::Paper ? "\033[34mPaper\033[37m" : "\033[31mScissors\033[37m"));

		// Determine the winner of the round
		if (playerChoice == computerChoice) {
			std::puts("\033[33m\nIt's a draw!\n\033[37m"); //Yellow color "It's a draw!" then White Color
			++ties;
		}
		else if ((playerChoice == Choice::Rock && computerChoice == Choice::Scissors) ||
			(playerChoice == Choice::Paper && computerChoice == Choice::Rock) ||
			(playerChoice == Choice::Scissors && computerChoice == Choice::Paper)) {
			std::puts("\033[32m\nYou win this round!\n\033[37m"); //Green color "You win this round!" then White Color
			++playerScore;
		}
		else {
			std::puts("\033[31m\nComputer wins this round!\n\033[37m"); //Red color "Computer wins this round!" then White Color
			++computerScore;
		}

		++round;

		if ((round > roundLimit) && (playerScore == computerScore)) //Tiebreaker
		{
				++roundLimit;
				std::puts("\033[33m\nMore rounds added! The winner takes it all!\033[37m"); //Yellow color "More rounds added! ..." then White Color
		}

		std::puts("\nPress Enter to continue...");
		std::getchar();

	} while (round <= roundLimit);

	// Display final score
	std::println("\nFinal Score:\n"
		"  You      [\033[32m{}\033[37m]\n" //Green  Color
		"  Computer [\033[31m{}\033[37m]\n" //Red    Color
		"  Draws    [\033[33m{}\033[37m]\n" //Yellow Color
		"\nThanks for playing!\n", playerScore, computerScore, ties);

	SetColor(Color::LightGrey);
	std::puts("\nPress Enter to exit...");
	std::getchar();  // Waits for user input before closing terminal
}

void MenuSelectRounds(int& RoundLimit)
{
	int userInput{ 0 };

	do {
		ClearScreen(); //Clear the console screen before repeating the loop
		SetColor(Color::White);

		std::println("Welcome to Rock, Paper, Scissors!\n\n"
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
	std::println("\nROUND: {}\\{}\n", round, roundLimit);
	std::println("{}   Rock   {}", currentMenuPos==Choice::Rock ? ">" : " ", currentMenuPos == Choice::Rock ? "<" : " ");
	SetColor(Color::Blue);
	std::println("{}  Paper   {}", currentMenuPos == Choice::Paper ? ">" : " ", currentMenuPos == Choice::Paper ? "<" : " ");
	SetColor(Color::Red);
	std::println("{} Scissors {}", currentMenuPos == Choice::Scissors ? ">" : " ", currentMenuPos == Choice::Scissors ? "<" : " ");
}
} //namespace game