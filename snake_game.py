# Tic-Tac-Toe Game

from __future__ import annotations
from typing import List, Optional


class TicTacToeGame:
    def __init__(self) -> None:
        self.board: List[str] = [" " for _ in range(9)]
        self.current_player = "X"
        self.game_over = False
        self.winner: Optional[str] = None

    def display_board(self) -> None:
        print()
        for index, cell in enumerate(self.board):
            if index % 3 == 0 and index != 0:
                print("\n---+---+---")
            print(f" {cell} ", end="")
            if index % 3 != 2:
                print("|", end="")
        print("\n")

    def available_moves(self) -> List[int]:
        return [index for index, cell in enumerate(self.board) if cell == " "]

    def make_move(self, position: int) -> bool:
        if self.game_over or not 0 <= position < 9:
            return False
        if self.board[position] != " ":
            return False

        self.board[position] = self.current_player
        if self._check_winner():
            self.game_over = True
            self.winner = self.current_player
            return True

        if all(cell != " " for cell in self.board):
            self.game_over = True
            self.winner = "Draw"
            return True

        self.current_player = "O" if self.current_player == "X" else "X"
        return True

    def _check_winner(self) -> bool:
        winning_lines = [
            (0, 1, 2), (3, 4, 5), (6, 7, 8),
            (0, 3, 6), (1, 4, 7), (2, 5, 8),
            (0, 4, 8), (2, 4, 6),
        ]
        for a, b, c in winning_lines:
            if self.board[a] != " " and self.board[a] == self.board[b] == self.board[c]:
                return True
        return False

    def reset(self) -> None:
        self.board = [" " for _ in range(9)]
        self.current_player = "X"
        self.game_over = False
        self.winner = None

    def play(self) -> None:
        self.reset()
        while not self.game_over:
            self.display_board()
            move = input(f"Player {self.current_player}, choose a position (0-8): ")
            try:
                position = int(move)
            except ValueError:
                print("Please enter a valid integer.")
                continue
            if not self.make_move(position):
                print("Invalid move. Try again.")
                continue

        self.display_board()
        if self.winner == "Draw":
            print("It's a draw!")
        else:
            print(f"Player {self.winner} wins!")


if __name__ == "__main__":
    game = TicTacToeGame()
    game.play()
