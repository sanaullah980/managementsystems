# Snake Game

from __future__ import annotations
import random
import time
from typing import List, Tuple


class SnakeGame:
    def __init__(self, width: int = 12, height: int = 12) -> None:
        self.width = width
        self.height = height
        self.snake: List[Tuple[int, int]] = [(5, 5), (4, 5), (3, 5)]
        self.direction = (1, 0)
        self.food = self._random_food()
        self.score = 0
        self.running = True

    def _random_food(self) -> Tuple[int, int]:
        occupied = set(self.snake)
        available = [
            (x, y)
            for x in range(self.width)
            for y in range(self.height)
            if (x, y) not in occupied
        ]
        if not available:
            return (-1, -1)
        return random.choice(available)

    def change_direction(self, new_direction: Tuple[int, int]) -> None:
        if (-new_direction[0], -new_direction[1]) == self.direction:
            return
        self.direction = new_direction

    def _step(self) -> None:
        head_x, head_y = self.snake[0]
        move_x, move_y = self.direction
        new_head = (head_x + move_x, head_y + move_y)

        if new_head[0] < 0 or new_head[0] >= self.width or new_head[1] < 0 or new_head[1] >= self.height:
            self.running = False
            return

        if new_head in self.snake:
            self.running = False
            return

        self.snake.insert(0, new_head)
        if new_head == self.food:
            self.score += 10
            self.food = self._random_food()
            if self.food == (-1, -1):
                self.running = False
                return
        else:
            self.snake.pop()

    def render(self) -> None:
        board = [[" " for _ in range(self.width)] for _ in range(self.height)]
        for x, y in self.snake:
            board[y][x] = "O"
        fx, fy = self.food
        board[fy][fx] = "*"
        print("\n" + "-" * (self.width * 2 + 1))
        for row in board:
            print("|" + " ".join(row) + "|")
        print("-" * (self.width * 2 + 1))
        print(f"Score: {self.score}")

    def run(self) -> None:
        while self.running:
            self.render()
            user_input = input("Move (w/a/s/d/q): ").strip().lower()
            if user_input == "w":
                self.change_direction((0, -1))
            elif user_input == "s":
                self.change_direction((0, 1))
            elif user_input == "a":
                self.change_direction((-1, 0))
            elif user_input == "d":
                self.change_direction((1, 0))
            elif user_input == "q":
                self.running = False
                break
            self._step()
            if not self.running:
                print("Game over! Final score:", self.score)


if __name__ == "__main__":
    game = SnakeGame()
    game.run()
