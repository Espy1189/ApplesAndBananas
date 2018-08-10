#pragma once

#include "FApplesBananasGame.h"
#include <fstream>
#include <time.h>

FApplesBananasGame::FApplesBananasGame() {
	LoadWordBank();
	Reset();
}

int32 FApplesBananasGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FApplesBananasGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FApplesBananasGame::GetIsogram() const { return FString(); }
FString FApplesBananasGame::GetHiddenWord() const { return MyHiddenWord; }

bool FApplesBananasGame::IsGameWon() const { return bGameIsWon; }

EResetStatus FApplesBananasGame::Reset() {
	int32 randomWordIndex;
	MyCurrentTry = 1;
	bGameIsWon = false;
	EResetStatus eValue = EResetStatus::Invalid_Status;

	// generate a random number for the size of the dictionary
	if (mapBank.size() > 0) {
		// seed the random number gnerator
		std::srand((unsigned)time(0));
		// get a random number
		randomWordIndex = (rand() % mapBank.size()) + 1;
		// get a word
		MyHiddenWord = mapBank[randomWordIndex];
		eValue = EResetStatus::OK;

	}
	else {
		MyHiddenWord = "";
		eValue = EResetStatus::No_Word_Bank;
	}

	return eValue;
}

int32 FApplesBananasGame::GetMaxTries() const {
	TMap < int32, int32 > WordLengthtToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,15 },{ 7,20 } };
	return WordLengthtToMaxTries[MyHiddenWord.length()];
}

bool FApplesBananasGame::IsIsogram(FString Word) const
{
	// treats 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	TMap < char, bool > LetterSeen;
	for (auto Letter : Word)  // for all letters for the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false;		// we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map
		}
	}
	return true;
}

bool FApplesBananasGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) { return false; }
	}
	return true;
}

// recieves a VALID guess, incriments turn, and returns count
FApplesBananasCount FApplesBananasGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FApplesBananasCount ApplesBananasCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

											  // loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {		// if they're in the same place
					ApplesBananasCount.Apples++;  //incriment apples
				}
				else {
					ApplesBananasCount.Bananas++;
				}
			}
		}
	}
	if (ApplesBananasCount.Apples == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return ApplesBananasCount;
}

EGuessStatus FApplesBananasGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //return an error
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; //return an error
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length; // return an error
	}
	else //otherwise
	{
		return EGuessStatus::OK; 	//return Ok;
	}
}

void FApplesBananasGame::LoadWordBank()
{
	const FString WORDBANK = "wordbank.txt";
	const int32 MAX_WORD_SIZE = 7;
	const int32 MIN_WORD_SIZE = 3;
	FString Line = "";
	int currentWord = 0;

	//attempt to open file
	std::ifstream fDictionaryFile(WORDBANK);

	//read in the file
	if (fDictionaryFile.is_open()) {
		// for each line in the file until the end
		do {
			getline(fDictionaryFile, Line);
			// check for end of file
			if (!fDictionaryFile.eof()) {
				// check if the word is an isogram before adding to the word bank
				if (IsIsogram(Line)
					&& (Line.length() >= MIN_WORD_SIZE) // check word for minimum length 
					&& (Line.length() <= MAX_WORD_SIZE) // check word for max length
					&& (Line.substr(Line.length() - 2) != "'s") // avoid apostrophe
					) {
					currentWord++;
					//add the item to the map
					mapBank[currentWord] = Line;
				}
			}
		} while (!fDictionaryFile.eof());

		//close the file
		fDictionaryFile.close();
	}
}
