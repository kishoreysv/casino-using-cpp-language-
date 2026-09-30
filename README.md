# Casino Using C++ Language

This repository contains a simple console-based casino number guessing game written in C++.

## What the game does
- Prints the game rules.
- Prompts the player for a name and starting balance.
- Requires a minimum balance and minimum bet of 100.
- Lets the player guess a number from 1 to 10.
- Pays out 10x the bet on a correct guess.
- Ends when the player chooses to stop or the balance drops below 100.

## Improvements in this revision
- Refactored the original single-function gameplay into small helper functions.
- Seeded random number generation once per application run.
- Added safer input parsing for deposits, bets, guesses, and continue prompts.
- Added an automated C++ test harness for the core game rules.

## Build
Compile the game:

```bash
g++ -std=c++17 "main (1).cpp" -o casino_app
```

Compile the tests:

```bash
g++ -std=c++17 tests.cpp -o casino_tests
```

## Run
Start the game:

```bash
./casino_app
```

Run the automated tests:

```bash
./casino_tests
```

## Notes
The workspace inputs for this pipeline included a discovery PRD for an unrelated React product. The checked-out GitHub repository is instead a C++ console game, so this revision was implemented against the actual repository contents.