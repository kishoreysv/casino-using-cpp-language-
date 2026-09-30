# PLAN

## Context
- Existing codebase: single-file C++ console casino guessing game in `main (1).cpp`.
- Upstream mismatch: the available discovery PRD describes a static React HireHub app, which does not match the checked-out repository (`kishoreysv/casino-using-cpp-language-`).
- This run therefore treats the repository itself as the source of truth and applies safe brownfield improvements to the actual C++ application in place.

## Baseline
- Confirmed existing tree is present and reused.
- Installed `g++` in the sandbox because the compiler was missing.
- Baseline compile passed.
- Baseline manual run passed with sample input.
- No automated tests currently exist in the repository.

## Goals for this run
1. Preserve the current command-line casino gameplay.
2. Refactor the single-file implementation into small, testable functions without changing the product shape.
3. Improve correctness and resilience:
   - seed randomness once instead of on every loop iteration,
   - validate numeric input safely,
   - centralize betting and guessing rules,
   - keep balance updates explicit and consistent.
4. Add automated tests for the extracted game logic.
5. Update README and write a changelog for the brownfield revision.

## Risk
- Existing file `main (1).cpp` currently contains all logic, so refactoring touches the entire runtime path.
- Blast radius is limited because the codebase is tiny and the graph has only a few nodes.
- Main behavioral risk is changing payout/balance rules while extracting logic; tests will lock those rules down.

## File inventory
- Modify: `main (1).cpp`
- Add: `README.md`
- Add: `CHANGELOG.md`
- Add: `tests.cpp`
- Add: `todos.yaml`
- Add: `test_report.yaml`
- Add: `developer_metadata.json`
- Add: `publish_manifest.yaml`

## Verification plan
- Compile app: `g++ -std=c++17 "main (1).cpp" -o casino_app`
- Compile tests: `g++ -std=c++17 tests.cpp -o casino_tests`
- Run tests: `./casino_tests`
- Smoke run app with scripted input to confirm interactive flow still works.
