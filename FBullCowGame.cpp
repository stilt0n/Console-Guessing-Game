#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <map>
#include <ctype.h>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "yodeling";
	constexpr int32 WORD_LENGTH = 8;
	MyCurrentTry = 0;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyWordLength = WORD_LENGTH;
	bWon = false;
	return;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

int32 FBullCowGame::GetMaxTries() const{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const{
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const{
	return bWon;
}

bool FBullCowGame::IsIsogram(FString Guess) const {

	TMap<char, bool> LetterSeen;

	if (Guess.length() < 2) { return true; }
	else {
		for (auto Letter : Guess) {
			Letter = tolower(Letter);
			if (LetterSeen.count(Letter)) { //note this works because booleans are 0 or non0
				return false;
			}
			else {
				LetterSeen[Letter] = true;
			}
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		if (isupper(Letter)) {
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	if (!IsIsogram(Guess) && !Guess.compare("done") == 0) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length() && Guess.compare("done") != 0) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}
//Assumes a valid guess has been entered
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	//setup return struct
	FBullCowCount BullCowCount;
	if (Guess.compare(MyHiddenWord) == 0) {
		bWon = true;
	}
	else {
		for (int32 i = 0; i < MyWordLength; i++) {
			if (MyHiddenWord.at(i) == Guess.at(i)) {
				BullCowCount.Bulls++;
			}
			else {
				BullCowCount.Cows++;
			}
		}
		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << std::endl;
	}
	//return bull cow count
	return BullCowCount;
}
