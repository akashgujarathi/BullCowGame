/*
	The game logic (no view or direct user interaction)
	The game is simple guess the word game based on MasterMind
*/

#pragma once
#include <string>

// To make syntax unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EnumGuessStatus
{
	Invaild,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame();	// Constructor 
	int32 GetMaxTries() const; // Max tries player gets
	int32 GetCurrentTry() const; // Print current number of 

	int32 CheckHiddenWordLength() const;

	bool IsGameWon() const; // Check if player own or not ?
	EnumGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 

	FBullCowCount SubmitValidGuess(FString);

private:

	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
}; 
