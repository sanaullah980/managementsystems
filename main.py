# Word Guessing Game

from __future__ import annotations
import random
from typing import List


class WordGuessingGame:
    def __init__(self) -> None:
        self.words = [
            "planet",
            "library",
            "python",
            "doctor",
            "method",
            "system",
            "garden",
            "triangle",
            "market",
            "rocket",
        ]
        self.word = random.choice(self.words)
        self.guessed_letters: List[str] = []
        self.max_attempts = 6
        self.remaining_attempts = self.max_attempts
        self.game_over = False
        self.won = False

    def display_word(self) -> str:
        return " ".join(letter if letter in self.guessed_letters else "_" for letter in self.word)

    def make_guess(self, letter: str) -> bool:
        if self.game_over:
            return False

        guess = letter.lower()
        if guess in self.guessed_letters:
            print("You already guessed that letter.")
            return True

        self.guessed_letters.append(guess)
        if guess not in self.word:
            self.remaining_attempts -= 1

        if all(ch in self.guessed_letters for ch in set(self.word)):
            self.won = True
            self.game_over = True
        elif self.remaining_attempts <= 0:
            self.game_over = True

        return True

    def play(self) -> None:
        print("Welcome to the Word Guessing Game!")
        while not self.game_over:
            print(f"Word: {self.display_word()}")
            print(f"Attempts left: {self.remaining_attempts}")
            guess = input("Guess a letter: ").strip().lower()
            if not guess or len(guess) != 1:
                print("Please enter a single letter.")
                continue
            self.make_guess(guess)

        if self.won:
            print(f"You won! The word was '{self.word}'.")
        else:
            print(f"You lost! The word was '{self.word}'.")


if __name__ == "__main__":
    game = WordGuessingGame()
    game.play()
