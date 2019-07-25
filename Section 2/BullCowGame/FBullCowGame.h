#pragma once
#include<iostream>
#include<string>

using int32 = int;
using Ftext = std::string;
using FString = std::string;

//all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame();//Constructor(same name with class)
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLenght() const;

	void Reset(); //TODO make a more rich return value
	
	EGuessStatus CheckGuessValidity(FString) const;

	FBullCowCount SubmitValidGuess(FString); 


private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
};