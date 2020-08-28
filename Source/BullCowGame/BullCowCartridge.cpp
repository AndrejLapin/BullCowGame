// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& Word)
        {
            return Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word);
        }
    );

    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{

    if (!bGameOver)
    {
        ProcessGuess(PlayerInput);
    }
    else
    {
        ClearScreen();
        SetupGame();
    }

}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() -1)];
    PlayerLives = HiddenWord.Len() * 2; // assign lives (lives = word size)
    bGameOver = false;

    PrintLine(TEXT("Welcome to the Bull Cow game!"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    //PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); // Debug line
    PrintLine(TEXT("You have %i lives"), PlayerLives);
    PrintLine(TEXT("Type in you guess and press enter"));

    //PrintLine(TEXT("The number of valid words is: %i."), Isograms.Num()); // Debug line

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You guessed the word correctly!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("You have entered the wrong number of \ncharacters! You have %i lives remaining"), PlayerLives);
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("There should be no repeating letters"));
        return;
    }

    PlayerLives--;
    PrintLine(TEXT("You have lost a life"));

    if (PlayerLives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have ran out lives"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);

    PrintLine(TEXT("And have %i lives remaining, guess again."), PlayerLives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
{
    //we run a for loop comparing every letter of word with every other letter
    for (int32 Index = 0; Index < Word.Len()-1; Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Comparison] == Word[Index])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 LetterIndex = 0; LetterIndex < Guess.Len(); LetterIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[LetterIndex] )
            {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}