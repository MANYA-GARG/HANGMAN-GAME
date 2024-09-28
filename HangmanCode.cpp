#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_ATTEMPTS 6
#define MAX_GUESSES 26
#define MAX_WORD_LENGTH 50

// Color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string CYAN = "\033[36m";
const string WHITE = "\033[97m";

class HangmanGame {
private:
    char secretWord[MAX_WORD_LENGTH];
    char currentWord[MAX_WORD_LENGTH];
    int attemptsLeft;
    bool guessedLetters[MAX_GUESSES];

    const char* fruits[25] = {
        "apple", "banana", "cherry", "grape", "kiwi", "strawberry", "watermelon", "pineapple", "mango",
        "blueberry", "raspberry", "blackberry", "peach", "plum", "apricot", "orange", "lemon", "lime",
        "pomegranate", "cantaloupe", "fig", "papaya", "pear", "guava", "lychee"
    };

    const char* music[25] = {
        "guitar", "piano", "drums", "violin", "flute", "saxophone", "clarinet", "trumpet", "harp",
        "cello", "trombone", "tuba", "keyboard", "xylophone", "accordion", "banjo", "harmonica",
        "mandolin", "sitar", "tambourine", "bagpipe", "oboe", "ukulele", "cymbals", "triangle"
    };

    const char* games[25] = {
        "chess", "poker", "soccer", "cricket", "tennis", "basketball", "hockey", "rugby", "volleyball",
        "baseball", "badminton", "tabletennis", "golf", "handball", "archery", "fencing", "boxing",
        "karate", "bowling", "cycling", "darts", "snooker", "squash", "surfing", "judo"
    };

    const char* colors[25] = {
        "red", "blue", "green", "yellow", "purple", "orange", "brown", "black", "white", "pink",
        "gray", "cyan", "magenta", "turquoise", "indigo", "violet", "maroon", "beige", "ivory",
        "coral", "olive", "navy", "salmon", "teal", "gold"
    };

    void chooseCategory() {
        int choice;
        cout << CYAN << "\nChoose a category: " << RESET << endl;
        cout << "1. Fruits" << endl;
        cout << "2. Music" << endl;
        cout << "3. Games" << endl;
        cout << "4. Colors" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                strcpy(secretWord, getRandomWord(fruits, sizeof(fruits) / sizeof(fruits[0])));
                cout << CYAN << "Category: Fruits" << RESET << endl;
                break;
            case 2:
                strcpy(secretWord, getRandomWord(music, sizeof(music) / sizeof(music[0])));
                cout << CYAN << "Category: Music" << RESET << endl;
                break;
            case 3:
                strcpy(secretWord, getRandomWord(games, sizeof(games) / sizeof(games[0])));
                cout << CYAN << "Category: Games" << RESET << endl;
                break;
            case 4:
                strcpy(secretWord, getRandomWord(colors, sizeof(colors) / sizeof(colors[0])));
                cout << CYAN << "Category: Colors" << RESET << endl;
                break;
            default:
                cout << YELLOW << "Invalid choice. Defaulting to Fruits." << RESET << endl;
                strcpy(secretWord, getRandomWord(fruits, sizeof(fruits) / sizeof(fruits[0])));
        }
    }

    const char* getRandomWord(const char* words[], int size) {
        int index = rand() % size;
        return words[index];
    }

    bool alreadyGuessed(char letter) {
        return guessedLetters[letter - 'a'];
    }

    bool updateCurrentWord(char letter) {
        bool correctGuess = false;
        guessedLetters[letter - 'a'] = true;
        for (int i = 0; secretWord[i] != '\0'; i++) {
            if (secretWord[i] == letter) {
                currentWord[i] = letter;
                correctGuess = true;
            }
        }
        return correctGuess;
    }

    void displayGameInfo() {
        cout << "============================" << RESET << endl;
        cout << "Word: " << currentWord << RESET << endl;
        cout << "Attempts left: " << attemptsLeft << RESET << endl;
        cout << "Guessed letters: ";
        for (int i = 0; i < MAX_GUESSES; i++) {
            if (guessedLetters[i]) {
                cout << WHITE << char('a' + i) << RESET << " ";
            }
        }
        cout << endl;
        cout << "============================" << RESET << endl;
    }

    void drawHangman(int attemptsLeft) {
        cout << RED << "   _____" << RESET << endl;
        cout << RED << "  |     |" << RESET << endl;

        if (attemptsLeft <= 5){
                cout << RED << "  |     O" << RESET << endl;
        }
        if (attemptsLeft <= 4){
                cout << RED << "  |     |" << RESET << endl;
        }
        if (attemptsLeft <= 3){
                cout << RED << "  |    /|\\" << RESET << endl;
        }
        if (attemptsLeft <= 3){
                cout << RED << "  |    / \\" << RESET << endl;
        }
        if (attemptsLeft <= 2){
                cout << RED << "  |________" << RESET << endl;
        }
        if (attemptsLeft == 0){
                cout << RED << "  |   (X_X)" << RESET << endl;
        }
        else {
                cout << RED << "  |" << RESET << endl;
        }
    }

    void displayGameStart() {
        cout << CYAN << "\n================================" << RESET << endl;
        cout << CYAN << "|     Starting Hangman Game!    |" << RESET << endl;
        cout << CYAN << "================================" << RESET << endl;
    }

    public:
    HangmanGame() {
        chooseCategory();
        attemptsLeft = MAX_ATTEMPTS;
        memset(guessedLetters, 0, sizeof(guessedLetters));
        memset(currentWord, '_', strlen(secretWord));
        currentWord[strlen(secretWord)] = '\0';
    }

    void play() {
        displayGameStart();
        cout << GREEN << "You have " << attemptsLeft << " attempts to guess the word." << RESET << endl;

        while (attemptsLeft > 0) {
            displayGameInfo();
            char guess;
            cout  << "Guess a letter: " << RESET;
            cin >> guess;

            if (isalpha(guess)) {
                guess = tolower(guess);
                if (alreadyGuessed(guess)) {
                    cout << YELLOW << "You've already guessed that letter." << RESET << endl;
                } else {
                    bool correctGuess = updateCurrentWord(guess);
                    if (correctGuess) {
                        cout << GREEN << "Good guess!" << RESET << endl;
                        if (strcmp(currentWord, secretWord) == 0) {
                            displayGameInfo();
                            cout << GREEN << "Congratulations! You guessed the word: " << secretWord << RESET << endl;
                            return;
                        }
                    } else {
                        cout << RED << "Incorrect guess." << RESET << endl;
                        attemptsLeft--;
                        drawHangman(attemptsLeft);
                    }
                }
            } else {
                cout << RED << "Please enter a valid letter." << RESET << endl;
            }
        }

        if (attemptsLeft == 0) {
            displayGameInfo();
            cout << RED << "You've run out of attempts. The word was: " << secretWord << RESET << endl;
        }
    }
};

void welcomeMessage() {
    cout << CYAN << "================================"  << endl;
    cout << CYAN << "|     Welcome to Hangman!       |" << endl;
    cout << CYAN << "================================" << RESET << endl;
    cout << "Choose a category and try to guess the word before you run out of attempts." << endl;
    cout << "Let's get started!" << endl;
}

int main() {
    welcomeMessage();
    char playAgain;
    do {
        HangmanGame game;
        game.play();
        cout << YELLOW << "Do you want to play again? (y/n): " << RESET;
        cin >> playAgain;
        system("cls");
    } while (playAgain == 'y' || playAgain == 'Y');
    return 0;
}
