
#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>

using namespace std;

enum GameChoices
{
	Rock = 1,
	Paper = 2,
	Scissors = 3
};

struct GameResult
{
	short NumberOfRounds;
	short ComputerWonTimes;
	short PlayerWonTimes;
	short DrawTimes;
	string FinalResult;
};

int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}

GameChoices GenerateComputerChoice()
{
	int ComputerChoice = RandomNumber(1, 3);

	return (GameChoices)ComputerChoice;
}

string ReturnPlayerChoice(GameChoices Choice)
{
	switch (Choice) 
	{
		case GameChoices::Paper:
			return "Paper";
		case GameChoices::Rock:
			return "Rock";
		case GameChoices::Scissors:
			return "Scissors";
	}
}

void ShowRoundResults(int RounderNumber, GameChoices PlayerChoice, GameChoices ComputerChoice, string Winner)
{
	cout << "________________________Round [" << RounderNumber << "]________________________\n";
	cout << "Player1 choice :  " << ReturnPlayerChoice(PlayerChoice) << "\n";
	cout << "Computer choice:  " << ReturnPlayerChoice(ComputerChoice) << "\n";
	cout << "Rounder Winner :  " << "[" << Winner << "]\n\n";
	cout << "__________________________________________________________\n\n";

}

string WhoWins(GameChoices PlayerChoice, GameChoices ComputerChoice)
{
	if (PlayerChoice == GameChoices::Paper && ComputerChoice == GameChoices::Rock)
		return "Player";
	else if (PlayerChoice == GameChoices::Paper && ComputerChoice == GameChoices::Scissors)
		return "Computer";
	else if (PlayerChoice == GameChoices::Scissors && ComputerChoice == GameChoices::Paper)
		return "Player";
	else if (PlayerChoice == GameChoices::Scissors && ComputerChoice == GameChoices::Rock)
		return "Computer";
	else if (PlayerChoice == GameChoices::Rock && ComputerChoice == GameChoices::Paper)
		return "Computer";
	else if (PlayerChoice == GameChoices::Rock && ComputerChoice == GameChoices::Scissors)
		return "Player";
	else
		return "No Winner";
}

short AskHowManyRounds()
{
	short NumberOfRounds = 0;

	do
	{
		cout << "How many rounds? [1 to 10]\n";
		cin >> NumberOfRounds;

	} while (NumberOfRounds < 1 || NumberOfRounds > 10);


	return NumberOfRounds;
}

GameChoices AskForUserChoice()
{
	int input = 0;

	do
	{
		cout << "Your choice: [1] Rock,  [2] Paper,  [3] Scissors?  ";
		cin >> input;

	} while (input < 1 || input > 3);

	return (GameChoices)input;

}


GameResult ShowRounds(short NumberOfRounds)
{
	GameResult GameResults;

	GameResults.ComputerWonTimes = 0;
	GameResults.DrawTimes = 0;
	GameResults.PlayerWonTimes = 0;

	GameChoices UserChoice, ComputerChoice;
	string TheWinner;


	for (short i = 1; i <= NumberOfRounds; i++)
	{
		cout << "\n\n\n\nRound [" << i << "] begins:\n\n";

		UserChoice = AskForUserChoice();
		ComputerChoice = GenerateComputerChoice();

		TheWinner = WhoWins(UserChoice, ComputerChoice);

		
		if (TheWinner == "No Winner")
		{
			system("color E0");
			GameResults.DrawTimes++;
		}
			
		else if (TheWinner == "Player")
		{
			system("color 2F");
			GameResults.PlayerWonTimes++;
		}
			
		else
		{
			Beep(1000, 300);
			system("color 4F");
			GameResults.ComputerWonTimes++ ;
		}
		system("cls");
		ShowRoundResults(i, UserChoice, ComputerChoice, TheWinner);
		
	}

	GameResults.NumberOfRounds = NumberOfRounds;

	if (GameResults.ComputerWonTimes > GameResults.PlayerWonTimes)
		GameResults.FinalResult = "Computer";
	else if (GameResults.ComputerWonTimes < GameResults.PlayerWonTimes)
		GameResults.FinalResult = "Player";
	else
		GameResults.FinalResult = "No one";

	return GameResults;
}


void ShowGameResult(GameResult GameResults)
{
	cout << "\n\n\n";
	cout << "------------------------------------------------------------\n";
	cout << "\t\t\tGame Over\t\t\n";
	cout << "------------------------------------------------------------\n\n";


	cout << "______________________[Game Results]___________________________\n";
	cout << "Game Rounds        : " << GameResults.NumberOfRounds << "\n";
	cout << "Player1 Won times  : " << GameResults.PlayerWonTimes << "\n";
	cout << "Computer Won times : " << GameResults.ComputerWonTimes << "\n";
	cout << "Draw times         : " << GameResults.DrawTimes << "\n";
	cout << "Final winner       : " << GameResults.FinalResult << "\n";
	cout << "------------------------------------------------------------\n\n";
}


bool WantToPlayAgain()
{
	int PlayAgain;

	cout << "Do you want to play again? [1] Yes  or [0] No\n";
	cin >> PlayAgain;

	while(PlayAgain < 0 || PlayAgain > 1)
	{
		cout << "Please enter a valid input  : ";
		cin >> PlayAgain;
    }

	return (bool)PlayAgain;

}


void StartGame()
{

	do
	{
		ShowGameResult(ShowRounds(AskHowManyRounds()));
		
	} while (WantToPlayAgain());
	
}



int main()
{
	srand(time(NULL));
	StartGame();

}


