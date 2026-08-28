# Project: Quantitative Analysis and Financial Models (GigiQuant)

This project is an application written in the **C** language designed for processing financial data, analyzing asset volatility, determining opposite trading strategies through tree structures, and predicting market states using Markov Chains. The project is divided into 4 main tasks, each solving a specific economic and computational problem.

---

## 🚀 Features and Task Structure

### Task 1: Volatility and Sharpe Score Analysis (`lists.c`)
* **What it does:** Reads a series of historical prices of a financial asset from a text file.
* **Implementation:** Builds a singly linked list in which it calculates the percentage returns between consecutive days.
* **Result:** Calculates the average of returns, the volatility (standard deviation of returns), and the **Sharpe Index** (the ratio between the average return and volatility). Results are truncated to 3 decimal places and saved to the output file.

### Task 2: Detecting Arbitrage Opportunities (`stacks.c`)
* **What it does:** Monitors the price evolution of 3 assets (or different cities/markets) over the course of several days.
* **Implementation:** Uses **stacks** to store the price history read in reverse and a **queue** to record alert messages chronologically.
* **Result:** Identifies the days on which two markets have identical prices, but the third differs (signaling a discrepancy or opportunity). Messages formatted as `day X - difference - market_name` are saved in FIFO order.

### Task 3: Decision Tree for Opposite Pairs (`trees.c`)
* **What it does:** Classifies the behavior of a set of stocks based on their daily evolution (price increase or decrease).
* **Implementation:** Builds a **Binary Decision Tree** in which each node contains a list of stocks. Going depth-first, left represents a price decrease compared to the previous day, and right represents an increase.
* **Result:** Traverses the tree to find completely opposite strategies (stocks that are on mirror-symmetric paths, for example `s-d-s` vs `d-s-d`). Writes the inversely correlated pairs to the output file.

### Task 4: Stochastic Prediction - Markov Chains (`mark.c`)
* **What it does:** Models price transitions as percentages and exact fractions to calculate the probability of an asset reaching a target state from an initial state after `k` steps.
* **Implementation:** Maps real values into discrete intervals (states). Builds a matrix of graphs/fractions to preserve exact arithmetic precision (without floating-point errors, using the `grafic` structure with `up` and `down` simplified via GCD).
* **Result:** Generates the probability vector at each step of the `k` iterations and saves the evolution of the exact fractions for the target state.

---

## 🛠️ Compilation and File Structure

The project contains the following source files and headers:

| File | Role |
|---|---|
| `main.c` | The `main` function and argument parsing logic for each task |
| `lists.c` / `lists.h` | Logic for linked lists and statistics (Task 1) |
| `stacks.c` / `stacks.h` | Logic for stacks, queues, and opportunity detection (Task 2) |
| `trees.c` / `trees.h` | Building and traversing the decision tree (Task 3) |
| `mark.c` / `mark.h` | Markov chains and exact fraction arithmetic (Task 4) |

Compilation is done with a `Makefile`. Make sure to link the math library with the `-lm` flag:

```bash
gcc -Wall -o main main.c lists.c stacks.c trees.c mark.c -lm
```

---

## 📊 How to Run the Checker

To validate the correctness of the implementation, the project comes equipped with an automated testing script called `checker`. It runs the tests defined in the project configuration, checks matching against the reference files (`REFS`), analyzes memory leaks (`MEMORY` via Valgrind), and code style (`cppcheck`).

The checker can be run in two modes:

### 1. Normal Mode (Standard)
Runs all tests in the background, checks the output sequentially, and generates the final success or error logs.
```bash
./checker
```

### 2. Debug Mode
Displays the output of each test in real time, useful for debugging.
```bash
./checker debug
```

---

## 🧠 Implementation Details

### Exact Fraction Arithmetic (Task 4)

One of the most interesting design choices in this project is the complete avoidance of floating-point arithmetic in Task 4. Instead of working with `double`, the code uses the structure:

```c
typedef struct {
    int up;   // numerator
    int down; // denominator
} grafic;
```

All probability multiplication and addition operations are done on fractions, simplified at each step via GCD (Greatest Common Divisor). This eliminates the rounding errors that would accumulate over `k` iterations of the Markov chain and guarantees that the output is always an exact, irreducible fraction.

### Stack Structure for Arbitrage (Task 2)

The input file for Task 2 lists prices in chronological order (oldest first). The data is loaded directly into a stack (`push` for each price), which means the top of the stack will be the oldest price. The 3 stacks are traversed simultaneously node by node, thus simulating the passage of days from the oldest to the most recent.

### Detecting Opposite Pairs (Task 3)

The algorithm in `gasire_drum()` performs a DFS on the tree to find the path of a stock (for example `s-d-s`). Once the path is found, it is reversed character by character (`s↔d`) and the tree is traversed along the new path to find the opposite stocks from that leaf.

---

## 📁 How to Run (Examples)

The task is determined automatically from the number in the input file name (1-5 → Task 1, 6-10 → Task 2, 11-15 → Task 3, 16-20 → Task 4):

```bash
# Task 1 - Sharpe Ratio (test file with number 1-5)
./tema1 data1.in data1.out

# Task 2 - Arbitrage (test file with number 6-10)
./tema1 data6.txt data6.out

# Task 3 - Decision tree (test file with number 11-15)
./tema1 data11.in data11.out

# Task 4 - Markov Chains (test file with number 16-20)
./tema1 data16.in data16.out
```

---


*Project created for the Algorithm Design course — data structures applied in the financial domain.*