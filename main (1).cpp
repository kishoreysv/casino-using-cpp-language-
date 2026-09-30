#include <cctype>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>

using namespace std;

namespace casino {

struct RoundOutcome {
    bool won;
    int secretNumber;
    int balanceChange;
    int endingBalance;
};

int calculateWinnings(int betAmount) {
    return betAmount * 10;
}

RoundOutcome resolveRound(int balance, int betAmount, int guess, int secretNumber) {
    if (guess == secretNumber) {
        const int winnings = calculateWinnings(betAmount);
        return {true, secretNumber, winnings, balance + winnings};
    }

    return {false, secretNumber, -betAmount, balance - betAmount};
}

bool canContinueWithBalance(int balance) {
    return balance >= 100;
}

bool parseInteger(const string& rawValue, int& parsedValue) {
    istringstream stream(rawValue);
    stream >> parsedValue;
    return stream && stream.eof();
}

int promptForInteger(const string& promptMessage, const string& invalidMessage) {
    while (true) {
        cout << promptMessage;
        string rawValue;
        getline(cin, rawValue);

        int parsedValue = 0;
        if (parseInteger(rawValue, parsedValue)) {
            return parsedValue;
        }

        cout << invalidMessage << "\n";
    }
}

int promptForDeposit() {
    while (true) {
        const int deposit = promptForInteger(
            "Enter the money to deposit for the game: ",
            "Please enter a valid whole number."
        );

        if (canContinueWithBalance(deposit)) {
            return deposit;
        }

        cout << "Minimum starting balance is 100.\n";
    }
}

int promptForBet(int balance, const string& playerName) {
    while (true) {
        const int betAmount = promptForInteger(
            playerName + ", enter the money to bet (minimum 100): ",
            "Please enter a valid whole number."
        );

        if (betAmount > balance) {
            cout << "Money exceeds your balance.\n";
            continue;
        }

        if (betAmount < 100) {
            cout << "Minimum bet is 100.\n";
            continue;
        }

        return betAmount;
    }
}

int promptForGuess() {
    while (true) {
        const int guess = promptForInteger(
            "Guess a number between 1 to 10: ",
            "Please enter a valid whole number."
        );

        if (guess >= 1 && guess <= 10) {
            return guess;
        }

        cout << "Number exceeds the range.\n";
    }
}

bool promptToContinue() {
    while (true) {
        cout << "Do you want to continue? (y/n): ";
        string rawValue;
        getline(cin, rawValue);

        if (rawValue.size() == 1) {
            const char decision = static_cast<char>(tolower(static_cast<unsigned char>(rawValue[0])));
            if (decision == 'y') {
                return true;
            }
            if (decision == 'n') {
                return false;
            }
        }

        cout << "Please enter y or n.\n";
    }
}

int generateSecretNumber(mt19937& generator) {
    uniform_int_distribution<int> distribution(1, 10);
    return distribution(generator);
}

void rules() {
    cout << "-------------------------------------------------------\n";
    cout << "Rules\n";
    cout << "1) Enter a number between 1 to 10.\n";
    cout << "2) If you win, you will get 10 times your bet.\n";
    cout << "3) If you lose, you will lose your bet.\n";
    cout << "4) Minimum bet is 100.\n";
    cout << "5) The game continues until your balance drops below 100 or you choose to stop.\n";
    cout << "-------------------------------------------------------\n";
}

void playGame() {
    cout << "Enter your name: ";
    string name;
    getline(cin, name);

    while (name.empty()) {
        cout << "Name cannot be empty.\n";
        cout << "Enter your name: ";
        getline(cin, name);
    }

    cout << "\n";

    int balance = promptForDeposit();
    cout << "\nYour current balance is " << balance << "\n\n";

    random_device entropySource;
    mt19937 generator(entropySource());

    while (canContinueWithBalance(balance)) {
        const int betAmount = promptForBet(balance, name);
        cout << "\n";

        const int secretNumber = generateSecretNumber(generator);
        const int guess = promptForGuess();
        cout << "\n";

        const RoundOutcome outcome = resolveRound(balance, betAmount, guess, secretNumber);
        balance = outcome.endingBalance;

        if (outcome.won) {
            cout << "You have won: " << betAmount << "\n\n";
            cout << "You have won " << outcome.balanceChange << " as total.\n";
            cout << "Your new balance is: " << balance << "\n\n";
        } else {
            cout << "You have lost " << betAmount << "\n\n";
            cout << "The correct number was " << outcome.secretNumber << "\n\n";
            cout << "Now you have " << balance << " as balance.\n\n";
        }

        if (!canContinueWithBalance(balance)) {
            cout << "Your balance is less than 100. You can't continue playing. Have a nice day.\n";
            break;
        }

        if (!promptToContinue()) {
            cout << "Have a nice day.\n";
            break;
        }

        cout << "\n";
    }
}

}  // namespace casino

#ifndef CASINO_TEST
int main() {
    casino::rules();
    cout << "\n\n";
    casino::playGame();
    return 0;
}
#endif
