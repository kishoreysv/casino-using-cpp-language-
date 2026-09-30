#define CASINO_TEST
#include "main (1).cpp"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void assertTrue(bool condition, const string& message) {
    if (!condition) {
        throw runtime_error(message);
    }
}

void testCalculateWinnings() {
    assertTrue(casino::calculateWinnings(100) == 1000, "calculateWinnings should return 10x the bet");
}

void testResolveRoundWin() {
    const casino::RoundOutcome outcome = casino::resolveRound(500, 100, 7, 7);
    assertTrue(outcome.won, "Winning round should set won to true");
    assertTrue(outcome.balanceChange == 1000, "Winning round should add 10x bet");
    assertTrue(outcome.endingBalance == 1500, "Winning round should increase balance correctly");
}

void testResolveRoundLoss() {
    const casino::RoundOutcome outcome = casino::resolveRound(500, 100, 3, 7);
    assertTrue(!outcome.won, "Losing round should set won to false");
    assertTrue(outcome.balanceChange == -100, "Losing round should subtract the bet");
    assertTrue(outcome.endingBalance == 400, "Losing round should decrease balance correctly");
}

void testCanContinueWithBalance() {
    assertTrue(casino::canContinueWithBalance(100), "Balance of 100 should allow another round");
    assertTrue(!casino::canContinueWithBalance(99), "Balance below 100 should stop the game");
}

void testParseInteger() {
    int parsedValue = 0;
    assertTrue(casino::parseInteger("250", parsedValue) && parsedValue == 250, "parseInteger should parse valid integers");
    assertTrue(!casino::parseInteger("25x", parsedValue), "parseInteger should reject trailing characters");
    assertTrue(!casino::parseInteger("", parsedValue), "parseInteger should reject empty input");
}

void testGenerateSecretNumberRange() {
    mt19937 generator(42);
    for (int index = 0; index < 100; ++index) {
        const int secretNumber = casino::generateSecretNumber(generator);
        assertTrue(secretNumber >= 1 && secretNumber <= 10, "Generated secret number should stay in 1..10 range");
    }
}

int main() {
    try {
        testCalculateWinnings();
        testResolveRoundWin();
        testResolveRoundLoss();
        testCanContinueWithBalance();
        testParseInteger();
        testGenerateSecretNumberRange();
        cout << "All tests passed.\n";
        return 0;
    } catch (const exception& error) {
        cerr << "Test failure: " << error.what() << "\n";
        return 1;
    }
}
