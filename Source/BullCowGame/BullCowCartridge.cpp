// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to the Bull Cow game!"));

    SetupGame();
    PrintLine(TEXT("Guess the 5 letter word")); // remove the number later

    PrintLine(TEXT("Print something and hit enter"));
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
        if (PlayerLives <= 0)
        {
            PrintLine(TEXT("You have lost the game :'("));
            // ask player to try again
        }
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("steak"); // generate random word
    PlayerLives = 5; // assign lives (lives = word size)
}