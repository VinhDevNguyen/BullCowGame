#include "FBullCowGame.h"
#include<map>
#define TMap std::map
FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int FBullCowGame::GetCurrentTry()	const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }

int FBullCowGame::GetMaxTries()	const 
{ 
	TMap<int32, int32> WordLenghtToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLenghtToMaxTries[GetHiddenWordLenght()];
}

void FBullCowGame::Reset()
{
	MyMaxTries = GetMaxTries();
	const FString HIDDEN_WORD = "planet"; //The hidden word we want the player guess (this must be an isogram)
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess))	// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowerCase(Guess))	// if the guess isn't all lowercase
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

			if (Guess[GChar] == MyHiddenWord[MHWchar])	// find they match then

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
	if (BullCowCount.Bulls == WordLenght)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> letterSeen; //Setup our map
	for (auto Letter : Word) // loop through all the letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if (letterSeen[Letter]) //if the letter is in the map
		{
			return false; //we do NOT have an isogram
		}
		else //otherwise
		{
			letterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true;	// for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
		return true;
	}
}
