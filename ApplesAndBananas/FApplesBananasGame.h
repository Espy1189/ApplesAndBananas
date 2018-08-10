/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once

#include <string>
#include <map>

// to make syntax Unreal Engine friendly
#define TMap std::map
using FString = std::string;
using FText = std::string;
using int32 = int;

struct FApplesBananasCount {

	int32 Apples = 0;
	int32 Bananas = 0;
};

enum class EGuessStatus {

	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	No_Value

};

enum class EResetStatus
{
	Invalid_Status,
	OK,
	No_Word_Bank
};

class FApplesBananasGame {
public:
	FApplesBananasGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetIsogram() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	FApplesBananasCount SubmitValidGuess(FString);
	EResetStatus Reset();



private:
	int32 MyCurrentTry;
	FString MyHiddenWord; // This must be an isogram
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	TMap<int, FString> mapBank;
	void LoadWordBank();
};