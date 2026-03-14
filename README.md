# Blackjack Game

A simple console-based Blackjack game.

---

## Game Rules

* Both the player and dealer start with two cards.
* The dealer's first card is face down.
* The player may choose to:

  * **Hit** – request another card
  * **Stand** – stop drawing cards
* The player can continue drawing cards (**Hit**) until the total exceeds 21 points.
* When the player stops drawing cards, the dealer plays automatically.
* The dealer continues drawing cards until the game result can be determined.

---

## Betting System

* Both the player and the dealer start with 3 credits.
* Each round requires 1 credit as the bet.
* The program terminates when either side runs out of credits.

---

## Game Result

The winner of a round is determined according to the following rules:

### Player does NOT bust (Player ≤ 21)

* The dealer must have more points than the player to win.

### Player busts (Player > 21)

* The dealer only needs to reach at least 17 points to win.

### Tie

The game is considered a tie when:

* Both the player and dealer have exactly 21 points, or
* Both the player and dealer exceed 21 points.

---

## Card Values

* Cards **2–10** count as their face value.
* **J, Q, K** count as **10 points**.
* **Ace** counts as **1 or 11**, whichever benefits the player more.

---

## Features

* Complete playable Blackjack game
* Dealer and player simulation
* Credit-based betting system
* Automatic card dealing and shuffling
* Console-based menu interface

---

## Object-Oriented Design

This project contains several classes.

### Card

Represents a poker card.

**Attributes:**

* `pip` (card value)
* `suit`

---

### BJackPlayer

Represents a Blackjack player.

**Responsibilities:**

* Hold a hand of cards
* Calculate total card points
* Display cards on the screen

---

### BJackDealer 

Inherits from BJackPlayer

**Responsibilities:**

* Manage one or multiple decks of cards
* Deal cards to player and dealer
* Shuffle cards when necessary
* Determine game results

---

### BJackGame

Controls the entire game process.

**Responsibilities:**

* Control the game flow
* Process player actions
* Interact with the console menu
* Manage betting and credits

---

### ConsoleMenu

Provides a simple text-based menu interface for user interaction.

---

## Technologies

* C++
* Object-Oriented Programming
* ANSI terminal graphics
* Makefile build system

---

## Build & Run

Compile the program using the provided Makefile:

```bash
make
```

Run the program:

```bash
./BJ
```

Optional arguments:

```bash
./BlackJack [random_seed] [number_of_decks]
```
