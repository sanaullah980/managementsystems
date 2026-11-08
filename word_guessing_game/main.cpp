#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cctype>
#include <algorithm>

class WordGuessingGame {
    std::vector<std::string> words{"planet", "library", "python", "doctor", "method", "system", "garden", "market", "rocket"};
    std::string word;
    std::vector<char> guessed;
    int attempts{7};
    std::mt19937 random{std::random_device{}()};
    bool hasGuessed(char c) const { return std::find(guessed.begin(), guessed.end(), c) != guessed.end(); }
    bool complete() const { for (char c : word) if (!hasGuessed(c)) return false; return true; }
    void show() const {
        std::cout << "Word: ";
        for (char c : word) std::cout << (hasGuessed(c) ? c : '_') << ' ';
        std::cout << "\nAttempts remaining: " << attempts << "\nGuessed: ";
        for (char c : guessed) std::cout << c << ' ';
        std::cout << '\n';
    }
public:
    WordGuessingGame() {
        std::uniform_int_distribution<std::size_t> pick(0, words.size()-1);
        word = words[pick(random)];
    }
    bool guess(char c) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if (!std::isalpha(static_cast<unsigned char>(c))) { std::cout << "Enter a letter.\n"; return false; }
        if (hasGuessed(c)) { std::cout << "Already guessed.\n"; return false; }
        guessed.push_back(c);
        if (word.find(c) == std::string::npos) --attempts;
        return true;
    }
    void play() {
        std::cout << "Word Guessing Game: guess one letter per turn.\n";
        while (attempts > 0 && !complete()) {
            show(); std::cout << "Letter: "; char c;
            if (!(std::cin >> c)) return;
            guess(c);
        }
        show();
        if (complete()) std::cout << "You won! The word was " << word << ".\n";
        else std::cout << "Out of attempts. The word was " << word << ".\n";
    }
};
int main() { WordGuessingGame game; game.play(); }
