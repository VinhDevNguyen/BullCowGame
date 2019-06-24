#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()	{ Reset(); }

int FBullCowGame::GetMaxTries()		const { return MyMaxTries; }

int FBullCowGame::GetCurrentTry()	const { return MyCurrentTry; }

bool FBullCowGame::IsGameWon() const
{
	return false;
}

int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;
	const FString HIDDEN_WORD = "donkey"; //The hidden word we want the player guess
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (false)	// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //return error
	}
	else if (false)	// if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; //return error
	}
	else if (GetHiddenWordLenght() != Guess.length()) // if the guess lenght is wrong
	{
		return EGuessStatus::Wrong_Lenght; //return error
	}
	else // otherwise
	{
		return EGuessStatus::OK; //return NOT A Error
	}
}

//receives a VALID guess, increments(Gia tang) turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLenght = MyHiddenWord.length(); // assuming same lenght as guess

	//loop through all letters in the hidden word

	for (int32 MHWchar = 0; MHWchar < WordLenght; MHWchar++)
	{
		for (int32 GChar = 0; GChar < WordLenght; GChar++) //compare letters against the guess
		{
			
			if (Guess[GChar]==MyHiddenWord[MHWchar])	// find they match then

			{
				if (MHWchar == GChar)	// if they're in the same place
				{
					BullCowCount.Bulls++; //Increment bulls
				}
				else	// incriment cows if not
				{
					BullCowCount.Cows++; //must be a cow
				}
					
			}
		}
	}
	return BullCowCount;
}



