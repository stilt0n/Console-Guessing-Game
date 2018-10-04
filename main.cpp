/* This is a console based word guessing game.  The variable names, aliases, ect. are intended to
make the code fit with the coding standards for Unreal Engine.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

void PrintIntro();
FText getGuess();
void printGuess(FText guess);
void playGame();
void exit();
FBullCowGame BCGame;
FBullCowCount BullCowCount;

int main() 
{
	std::cout << "Current try: " << BCGame.GetCurrentTry() << std::endl;
	PrintIntro();
	playGame();
	exit();

	return 0;
}


void PrintIntro()
{
	//introduce game
	std::cout << "Welcome to Bulls and Cows in this game you will try to guess" << std::endl;
	std::cout << "a " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram (word with no repeat letters).  The console will give you hints:" << std::endl;
	std::cout << "xA bull is a guess that is in the correct location.  A cow is an incorrect guess." << std::endl;
	std::cout << "Can you guess the word before you run out of attempts?" << std::endl;
	return;
}
FText getGuess()
{
	FText guess = "";
	int32 TriesLeft = BCGame.GetMaxTries() - BCGame.GetCurrentTry();
	std::cout << "You have " << TriesLeft << " tries left" << std::endl;
	std::cout << "\nenter your guess (or \"done\" to quit): " << std::endl;
	EGuessStatus Status = EGuessStatus::Invalid;
	
	do {

	std::getline(std::cin, guess);
	Status = BCGame.CheckGuessValidity(guess);
	switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter the correct word length \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "The word should have no repeating letters" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "The word should be lowercase" << std::endl;
			break;
		default:
			break;
		}
	std::cout << std::endl;
	} while (Status != EGuessStatus::OK);

	return guess;
}

void printGuess(FText guess)
{
	std::cout << "You guessed " << guess << "." << std::endl;
}

void playGame()
{
	FText guess = "";
	int32 MaxTry = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && !(guess.compare("done") == 0) 
		&& (BCGame.GetCurrentTry() < MaxTry))
	{
		guess = getGuess();
		if (!(guess.compare("done") == 0 ))
		{
			BCGame.SubmitGuess(guess); //This method incriments counter
		}
	}
}

void exit()
{
	if (BCGame.IsGameWon()) {
		std::cout << "YOU WIN!" << std::endl;
	}
	else {
		std::cout << "You ran out of guesses :'( " << std::endl;
	}
}