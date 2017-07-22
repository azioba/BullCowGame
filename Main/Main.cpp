// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int32;


void PrintIntro();
void PlayGame();
void PrintGameSummary();
Ftext GetValidGuess();
Ftext answer;
bool AskToPlayAgain();
int32 i = 0;

FBullCowGame BCGame;

// Main entry point of our game
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	std::cout << std::endl;
	return 0;
}



// introduce the game
void PrintIntro()
{
	//constexpr int32 WORLD_LENGTH = 5;
	std::cout << "\n\n welcome to BullCowGame" << std::endl;
	std::cout << "can you guess the" << " " << BCGame.GetMyHiddenWordLength() << " letter isogram i am thinking of?" << std::endl;
}

void PlayGame()
{
	BCGame.reset();

	int32 MaxTries = BCGame.GetMaxTries();
	//std::cout << MaxTries << std::endl;
	// loop for number of turns	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess();

		//submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.submitValidGuess(Guess);
		//print numbers of Bulls and Cows

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// get a guess from the user
Ftext GetValidGuess()
{
	Ftext Guess = "";
	Eguessstatus status = Eguessstatus::invalid_status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ".enter your Guess : ";
		getline(std::cin, Guess);

		// check status and give feedback
		status = BCGame.CheckGuessvalidity(Guess);
		switch (status)
		{
		case Eguessstatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetMyHiddenWordLength() << " letter word. \n";
			break;
		case Eguessstatus::Not_Lowercase:
			std::cout << "please enter the word in lower case \n";
			break;
		case Eguessstatus::Not_isogram:
			std::cout << "Please enter an Isogram word \n";
			break;
		default:
			// assume everything is ok
			break;
		}
		std::cout << std::endl;
	} while (status != Eguessstatus::Ok); // keep looping until we get valid input
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n) ?";
	Ftext answer = "";
	getline(std::cin, answer);
	return (answer[0] == 'y') || (answer[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done, You Win!" << std::endl;
	}
	else
	{
		std::cout << "Bad Luck , Maybe next time" << std::endl;
	}
}
