//This is the console executeable, that makes use of the BullCow class
//This acts as the view in a MVC pattern(Structure of Software), an is responsible for all user interaction
//For game logic see the FbullCowGame class.

#include"FBullCowGame.h"

void PrintIntro(); 
Ftext GetValidGuess(); //Get the player guess
bool AskToPlayAgain();
void PlayGame();
FBullCowGame BCGame; //instantiate(Khoi tao) a new game
void PrintGameSumary(); 


int32 main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	system("pause");
	return 0;
}

void PrintIntro() //Introduce the game
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//Loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess(); 

		//Submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	
	PrintGameSumary();
	return;
}

void PrintGameSumary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well Done - You Win!\n";
	}
	else
	{
		std::cout << "Oops, Out of turn :<"<<std::endl;
		std::cout << "Better luck next time!\n";
	}
}


Ftext GetValidGuess()
{
	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 MaxTry = BCGame.GetMaxTries();
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try (" << CurrentTry <<" of "<<MaxTry<< ") Enter your guess: ";
		std::getline(std::cin, Guess);
		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			//Assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	Ftext Response;
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
