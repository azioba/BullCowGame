#include "stdafx.h"
#include "FBullCowGame.h"
#include<map>
#define TMap std::map



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetMyHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { //setting game dificulties by map
	TMap<int32, int32> WordLengthtoMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,13 },{ 7,16 } };
	return WordLengthtoMaxTries[MyHiddenWord.length()];
}

FBullCowGame::FBullCowGame() //default constructor
{
	reset();
}

void FBullCowGame::reset()
{
	const Fstring HIDDEN_WORD = "anti";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}




Eguessstatus FBullCowGame::CheckGuessvalidity(Fstring Guess) const
{
	if (!IsIsogram(Guess)) // if the gues isnt an isogram
	{
		return Eguessstatus::Not_isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isnt all lower case
	{
		return Eguessstatus::Not_Lowercase;
	}
	else if (MyHiddenWord.length() != Guess.length()) // if the guess length is wrong
	{
		return Eguessstatus::Wrong_Length;
	}
	else  // otherwise
	{
		return Eguessstatus::Ok;
	}

}

// receive a VALID guess,increments turns, and return counts
FBullCowCount FBullCowGame::submitValidGuess(Fstring Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

											  // loop through all letters in the word	
	for (int32 i = 0; i < WordLength; i++) {
		//compare letters against hidden word
		for (int32 j = 0; j < WordLength; j++) {
			// if they match then
			if (Guess[i] == MyHiddenWord[j]) {
				//if they are in the same place
				if (i == j) {
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //increment cows
				}

			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(Fstring Word) const
{
	// treat 0 and 1 letter word as isogram
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //set up our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //to be able to handle mixed cases
		if (LetterSeen[Letter]) {//if the letter is in the map
			return false; // we do not have isogram
		}
		else {
			LetterSeen[Letter] = true; //add the letter to the map as seen
		}


	}
	return true;
}

bool FBullCowGame::IsLowercase(Fstring Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // if is not a lower case
		{
			return false;
		}
	}
	return true;
}
