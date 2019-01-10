/*
	This is console executable, that makes use of BullCow class 
	This acts as the view in a MVC pattern, and is responsible for all user interaction.
	For game logic check BullCow class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax unreal friendly
using FText = std::string;
using int32 = int;

// Function prototypes outside a class

void GameIntro();
void PlayGame();
FText GetValidGuess();
bool AskPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game, which we reuse across play

int main() //Entry point for your application
{
	bool bPlayAgain = false; 
	do 
	{
		GameIntro();
		PlayGame();
		bPlayAgain = AskPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // Exit the application	
}

void GameIntro() // intorduce game to Player
{
	std::cout << "\n\nWelcome to Bulls and Cows\n";
	std::cout << "Can you guess " << BCGame.CheckHiddenWordLength();
	std::cout << " letter isogram that I'm thinking of?\n";

}
// plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// Loop for number of turns until game is not won
	// and there are still tries reaminig

	while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) ) 
	{
		FText Guess = GetValidGuess(); 
		
		           
		// Submit valid guess to game & recive the # of bulls and cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		// Print num of bulls and cows
		std::cout << "Bulls=" << BullCowCount.Bulls;
		std::cout << ". Cows=" << BullCowCount.Cows <<std::endl;
	}

	PrintGameSummary();	
	return;
}

FText GetValidGuess() 
{
	// Get a guess from Player
	FText Guess = "";
	EnumGuessStatus Status = EnumGuessStatus::Invaild;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\n Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ".	 Enter your guess: ";
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EnumGuessStatus::Not_Isogram:
			std::cout << "Input is not an isogram, please Enter an isogram. \n\n";
			break;
		case EnumGuessStatus::Wrong_Length:
			std::cout << "Invalid input length, please Enter an word of " << BCGame.CheckHiddenWordLength() << " letters. \n\n";
			break;
		case EnumGuessStatus::Not_Lowercase:
			std::cout << "Input is not in lowercase. \n\n";
			break;
		default:
			//assuming the input has no errors
			break;
		}
	} while (Status != EnumGuessStatus::Ok);
	return Guess;
}

bool AskPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again with same hidden word?(y/n)";
	getline(std::cin,Response);
	return (Response[0] == 'Y') || (Response[0] == 'y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nCONGRATULATIONS YOU WON....!!!\n\n";
	}
	else
	{
		std::cout << "BETTER LUCK NEXT TIME....!!!\n\n";
	}
	return;
}
