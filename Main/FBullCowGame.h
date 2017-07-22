#pragma once
#include <string>

using Fstring = std::string;
using int32 = int;

// initialise les valeurs à 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};



enum class Eguessstatus
{
	invalid_status,
	Ok,
	Not_isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();

	void reset();

	int32 GetMaxTries() const; //getter pour mes maxtries
	int32 GetCurrentTry() const; // getter pour mes currentries
	int32 GetMyHiddenWordLength() const;
	bool IsGameWon() const;
	Eguessstatus CheckGuessvalidity(Fstring) const;


	FBullCowCount submitValidGuess(Fstring);

private:
	int32 MyCurrentTry;
	Fstring MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(Fstring) const;
	bool IsLowercase(Fstring) const;
};
