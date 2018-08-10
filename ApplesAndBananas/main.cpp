/* This is the console executable, that makes use of the ApplesBananas class and acts as
the view in a MVC pattern, and is responsible for all user interaction. For game logic see the
FApplesBananasGame class.

*/
#pragma once

#include <iostream>
#include <string>
#include "FApplesBananasGame.h"

// to make syntax Unreal Engine friendly
using FText = std::string;


// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FApplesBananasGame BCGame; // instantiate a instance of a new game, which is re-uesed across playthroughs

// Entry point of application
int main() {

	bool bPlayAgain = false;
	do {
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
	
}

void PrintIntro() {

	    std::cout << "                     .\n";
	    std::cout << "                  .OOOO\n";
		std::cout << "                 .OOOO\n";
		std::cout << "                .OOOO'\n";
		std::cout << "                OOOO'\n";
		std::cout << "                OOO'\n";
		std::cout << "    .OOOOOOOOOO `O .OOOOOOOOO.\n";
		std::cout << "  .OOOOOOOOOOOOOOOOOOOOOOOOOOOO.\n";
		std::cout << " .OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO.\n";
		std::cout <<"OOOOOOOO%%OOOOOOOOOOOOOOOOOOOOOOOO.\n";
		std::cout <<"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                //\\\n";
        std::cout << "OOOOO%%%OOOOOOOOOOOOOOOOOOOOOOOOOOOOO.               V  \\\n";
        std::cout << "OOOOO%%%OOOOOOOOOOOOOOOOOOOOOOOOOOOOO.     Apples     \\  \\\n";
        std::cout << "OOOOO%%%OOOOOOOOOOOOOOOOOOOOOOOOOOOOO.        &        \\,'.`-. \n";                    
	    std::cout << "OOOOOO%%OOOOOOOOOOOOOOOOOOOOOOOOOOOOO.     Bananas      |\\ `. `.\n";
	    std::cout << "OOOOOOO%OOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                  ( \\  `. `-.                        _,.-:\\\n";
		std::cout <<"OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                    \\ \\   `.  `-._             __..--' ,-';/ \n";
		std::cout << "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                      \\ `.   `-.   `-..___..---'   _.--' ,'/\n";
		std::cout <<" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                        `. `.    `-._        __..--'    ,' / \n";
		std::cout << "  OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                          `. `-_     ``--..''       _.-'  ,'\n";
		std::cout << "   OOOOOOOOOOOOOOOOOOOOOOOOOOOOO.                              -_ `-.___        __,--'    ,'\n";
		std::cout << "    OOOOOOOOOOOOOOOOOOOOOOOOOOO'                                 -.__  `---------    __ .- \n";
		std::cout << "     OOOOOOOOOOOOOOOOOOOOOOOOO'                                      `--..____.. --'\n";
		std::cout << "      OOOOOOOOOO''OOOOOOOOOOO'\n";
		std::cout << "       OOOOOOOOO  OOOOOOOOOO'\n";


	std::cout << "\n\n A word game to challenge your brain!";
	std::cout << std::endl;
	std::cout << " A Apple means your guess contains a correct letter in the right place.\n";
	std::cout << " A Banana means your guess contains a correct letter , but in the wrong place.\n";
	std::cout << " Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}
//plays a single game to completion
void PlayGame() {

	BCGame.Reset();
	PrintIntro();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// Submit valid guess to the game
		FApplesBananasCount ApplesBananasCount = BCGame.SubmitValidGuess(Guess);

		//print number of apples and bananas
		std::cout << "Apples = " << ApplesBananasCount.Apples;
		std::cout << " Bananas= " << ApplesBananasCount.Bananas;
		std::cout << std::endl << std::endl;
	}

	PrintGameSummary();
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and recieve feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << " Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << " Please only use lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK); // keep looping until we get no errors 
	return Guess;
}

bool AskToPlayAgain() {

	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');

}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - You are a Winner!\n ";
	}
	else
	{
		std::cout << "Sorry the word was " << BCGame.GetHiddenWord() << std::endl;
		std::cout << "You are out of guesses - Better luck next time.\n";
	}
}
