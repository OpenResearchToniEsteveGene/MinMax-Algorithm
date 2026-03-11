# Connect Four with Minimax — README

## Overview

This project is a **console-based Connect Four game in C** in which a human player competes against the computer, named **C3PO**. The AI uses the **Minimax algorithm** over a game tree of possible future moves, together with a **heuristic evaluation function** for non-terminal board positions.

The implementation includes:

- an **8×8 board**
- a **human vs computer** game mode
- **three difficulty levels**, controlled by search depth
- a **scoreboard** for wins, losses, and draws
- a **tree-based Minimax decision process**

---

## Project Structure

```
.
├── main.c
├── Minimax.c
├── Minimax.h
├── 4enratlla.c
└── 4enratlla.h
````

### File description

* **main.c**
  Contains the main menu, user interaction, difficulty selection, turn handling, scoreboard management, and the overall game loop.

* **Minimax.c**
  Implements the game tree generation, heuristic evaluation, Minimax recursion, move selection, and memory deallocation.

* **Minimax.h**
  Declares the `Node` structure and the main Minimax-related functions.

* **4enratlla.c**
  Implements board initialization, board display, and board-full detection.

* **4enratlla.h**
  Declares board-related functions.

---

## Game Rules

The objective is to place **four consecutive pieces** before your opponent does.

A player wins by aligning four of their pieces:

* horizontally
* vertically
* diagonally

If the board becomes full and no player has achieved four in a row, the game ends in a **draw**.

---

## How the AI Works

The computer chooses moves using a **Minimax game tree**.

### Game tree model

Each node in the tree represents a board state:

* the root node is the **current board**
* each child node corresponds to **one legal move**
* levels alternate between:

  * **computer move**
  * **player move**

The search depth depends on the selected difficulty:

* **Low** → depth `2`
* **Medium** → depth `4`
* **High** → depth `6`

---

## Mathematical Description of Minimax

Let $$s$$ be a board position and let $$\mathcal{A}(s)$$ be the set of legal actions from $$s$$.
Let $$T(s,a)$$ denote the successor state obtained after applying action $$a$$.

The Minimax value $$V(s)$$ is defined recursively as:

\[
V(s)=
\begin{cases}
\max\limits_{a \in \mathcal{A}(s)} V(T(s,a)), & \text{if it is the computer's turn} \\
\min\limits_{a \in \mathcal{A}(s)} V(T(s,a)), & \text{if it is the player's turn}
\end{cases}
\]

At terminal or cutoff states, the algorithm does not continue expanding the tree. Instead, it assigns a score through a heuristic evaluation function:

\[
V(s) = h(s)
\]

where $$h(s)$$ estimates how favorable the position is for the computer.

### Interpretation

* the **computer** tries to **maximize** the evaluation
* the **human player** is assumed to play optimally and therefore tries to **minimize** it

The chosen move is the action:

\[
a^* = \arg\max_{a \in \mathcal{A}(s)} V(T(s,a))
\]

for the computer’s turn.

---

## Heuristic Evaluation Function

Since exploring the full game tree is expensive, the program evaluates non-terminal positions with a heuristic based on all groups of **4 cells** on the board.

For each segment of 4 positions:

* **4 computer pieces** → very large positive score
* **3 computer pieces + 1 empty** → positive score
* **2 computer pieces + 2 empty** → smaller positive score
* **4 player pieces** → very large negative score
* **3 player pieces + 1 empty** → negative score
* **2 player pieces + 2 empty** → smaller negative score

The global board score is the sum over:

* horizontal windows
* vertical windows
* diagonal windows

So the board evaluation can be written conceptually as:

\[
h(s)=\sum_{w \in \mathcal{W}(s)} h_w(w)
\]

where:

* ( \mathcal{W}(s) ) is the set of all 4-cell windows in the board
* ( h_w(w) ) is the score assigned to each window

This lets the AI prefer positions that create threats and block the opponent’s opportunities.

---

## Tie-Breaking Strategy

If several moves have the same Minimax value, the implementation prefers the move **closest to the center column**.

This is a sensible practical choice because central columns usually provide more future alignment opportunities.

---

## Data Structure Used

The Minimax search tree is built using the following node structure:

```c
typedef struct node {
    char tauler[DIMENSIO][DIMENSIO];
    struct node **fills;
    int n_fills;
    int valor;
} Node;
```

### Meaning of fields

* `tauler` → board state
* `fills` → dynamic array of child pointers
* `n_fills` → number of legal moves from the node
* `valor` → Minimax/heuristic value

---

## How to Compile

This project can be compiled with `gcc`.

### Linux / macOS / MinGW

```bash
gcc -std=c11 -Wall -Wextra -O2 main.c Minimax.c 4enratlla.c -o connect4_minimax
```

---

## How to Run

After compilation:

```bash
./connect4_minimax
```

On Windows:

```bash
connect4_minimax.exe
```

---

## Requirements

* a C compiler such as:

  * `gcc`
  * `clang`
  * MinGW on Windows

No external libraries are required beyond the standard C library.

---

## How to Play

1. Run the executable.
2. Choose an option from the main menu.
3. Select the difficulty:

   * Low
   * Medium
   * High
4. Enter your name.
5. Choose who starts:

   * Player
   * Computer
6. On your turn, enter the **column number** where you want to place your piece.

---

## Menu Options

The main menu includes:

1. **Play a game**
2. **View the game rules**
3. **View the scoreboard**
4. **Reset the scoreboard**
5. **Exit**

---

## Notes on the Board Representation

The program uses the following internal symbols:

* `JUGADOR = '1'`
* `ORDINADOR = '2'`
* `BUIT = '0'`

When displayed in the terminal:

* the **player** appears as **O**
* the **computer** appears as **X**

The board is printed with ANSI color sequences for improved readability.

---

## Memory Management

The Minimax tree is dynamically allocated during the computer’s turn.
After the move is selected, the tree is recursively freed using:

```
esborraArbre(...)
```

This is important to avoid memory leaks.


## Possible Improvements

Some natural extensions of the project would be:

* **alpha-beta pruning** to reduce the number of explored nodes
* configurable board size
* configurable winning length
* better heuristic weighting
* move ordering
* graphical interface
* save/load game states


## Summary

This project is a solid implementation of **Connect Four in C** with a classical **Minimax-based AI**. It combines:

* recursive game tree generation
* heuristic evaluation
* strategic move selection
* a playable command-line interface

It is a good example of how combinatorial game search can be applied in practice using standard C.


## Authors / Academic Context

This repository appears to be part of an academic project involving:

* board representation
* adversarial search
* heuristic evaluation
* recursive tree algorithms
* decision-making in deterministic two-player games

