// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); // Debug line

    PrintLine(TEXT("Welcome to the Bull Cow game!"));
    PrintLine(TEXT("Guess the %i letter word"), PlayerLives); // remove the number later
    PrintLine(TEXT("Type in you guess and press enter"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You guessed the word correctly!"));
    }
    else
    {
        PlayerLives--;
        PrintLine(TEXT("You guessed WRONG!"));
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("You have entered the wrong number of"));
            PrintLine(TEXT("characters!"));
        }

        if (PlayerLives <= 0)
        {
            PrintLine(TEXT("You have ran out of lives"));
            // ask player to try again
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("garden"); // generate random word
    PlayerLives = HiddenWord.Len(); // assign lives (lives = word size)
}