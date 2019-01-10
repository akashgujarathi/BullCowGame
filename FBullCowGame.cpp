#pragma once
#include "FBullCowGame.h"
#include <map>

// To make syntax unreal friendly
#define TMap std::map	
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // Default Constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

bool FBullCowGame::IsIsogram(FString Guess) const 
{ 
	if (Guess.length() <= 1) { return true; }	// Treat 0 or 1 letter word as isogram 
	TMap <char, bool> LetterSeen;	// set up our map

	for (auto Letter : Guess) // Loop each letter of "Guess" until EndofGuess
	{
		Letter = tolower(Letter); // Handle mixed letter
		if (LetterSeen[Letter])// Check if the letter is already present in the HashTable 
		{
			return false;	//if letter is available return false
		} else {
			LetterSeen[Letter] = true;//add letter seen to map
		}
	}
		
	return true; // for example incases where '/0' is entered
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

void FBullCowGame::Reset()
{
	const FString HiddenWord = "isogram";	// This must be a isogram
	MyCurrentTry = 1;

	MyHiddenWord = HiddenWord;
	bGameIsWon = false;
	return;
}


EnumGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))//If guess is not a isogram 
	{
		return EnumGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) //if guess is not in lowercase 
	{
		return EnumGuessStatus::Not_Lowercase;
	}
	else if (CheckHiddenWordLength() != Guess.length()) // if length is wrong
	{
		return EnumGuessStatus::Wrong_Length;
	}
	else
	{
		return EnumGuessStatus::Ok;
	}
}

int32 FBullCowGame::CheckHiddenWordLength() const { return MyHiddenWord.length(); }

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();	// assuming both the lengths will be equal

	// loop through all the letters in the HiddenWord
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// loop through all the letters in the GuessWord
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// compare against hidden word
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == CheckHiddenWordLength())
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

