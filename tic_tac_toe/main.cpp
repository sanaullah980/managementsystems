#include <iostream>
#include <array>
#include <limits>

class TicTacToe {
    std::array<char, 9> board{};
    char turn{'X'};
    bool finished{};
    char winner{' '};
    bool won(char mark) const {
        const int lines[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
        for (const auto& line : lines) if (board[line[0]] == mark && board[line[1]] == mark && board[line[2]] == mark) return true;
        return false;
    }
public:
    TicTacToe() { board.fill(' '); }
    void display() const {
        std::cout << "\n";
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                int i = r * 3 + c; std::cout << ' ' << (board[i] == ' ' ? char('1' + i) : board[i]) << ' ';
                if (c < 2) std::cout << '|';
            }
            if (r < 2) std::cout << "\n---+---+---\n";
        }
        std::cout << "\n";
    }
    bool move(int position) {
        if (finished || position < 1 || position > 9 || board[position - 1] != ' ') return false;
        board[position - 1] = turn;
        if (won(turn)) { finished = true; winner = turn; }
        else {
            bool full = true; for (char cell : board) if (cell == ' ') full = false;
            if (full) finished = true;
            else turn = turn == 'X' ? 'O' : 'X';
        }
        return true;
    }
    char current() const { return turn; }
    bool over() const { return finished; }
    char result() const { return winner; }
};
int main() {
    TicTacToe game;
    while (!game.over()) {
        game.display(); std::cout << "Player " << game.current() << ", choose a square (1-9): ";
        int position;
        if (!(std::cin >> position)) { std::cout << "Please enter a number.\n"; std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); continue; }
        if (!game.move(position)) std::cout << "That square is unavailable. Try again.\n";
    }
    game.display();
    if (game.result() == ' ') std::cout << "Draw!\n";
    else std::cout << "Player " << game.result() << " wins!\n";
}
