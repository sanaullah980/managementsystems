#include <iostream>
#include <string>
#include <cctype>
#include <cmath>

class PasswordAnalyzer {
    std::string password;
    bool upper{}, lower{}, digit{}, symbol{}, common{};
    int length{}, score{};
    double entropy{};
public:
    explicit PasswordAnalyzer(std::string value) : password(std::move(value)) { analyze(); }
    void analyze() {
        int pool = 0; length = static_cast<int>(password.size());
        for (unsigned char c : password) {
            if (std::isupper(c)) upper = true;
            else if (std::islower(c)) lower = true;
            else if (std::isdigit(c)) digit = true;
            else symbol = true;
        }
        pool += upper ? 26 : 0; pool += lower ? 26 : 0;
        pool += digit ? 10 : 0; pool += symbol ? 32 : 0;
        entropy = length && pool ? length * std::log2(pool) : 0;
        std::string folded;
        for (unsigned char c : password) folded += static_cast<char>(std::tolower(c));
        const std::string weak[] = {"password", "123456", "qwerty", "admin", "letmein", "welcome"};
        for (const auto& word : weak) if (folded.find(word) != std::string::npos) common = true;
        score = 0;
        score += length >= 12 ? 25 : length >= 8 ? 15 : 0;
        score += upper ? 15 : 0; score += lower ? 15 : 0; score += digit ? 15 : 0; score += symbol ? 15 : 0;
        score += static_cast<int>(std::min(15.0, entropy / 5.0));
        if (common) score -= 25;
        if (score < 0) score = 0; if (score > 100) score = 100;
    }
    std::string strength() const {
        if (score >= 80) return "Very strong";
        if (score >= 60) return "Strong";
        if (score >= 40) return "Moderate";
        return "Weak";
    }
    void report() const {
        std::cout << "Length: " << length << "\nUppercase: " << (upper ? "yes" : "no")
                  << "\nLowercase: " << (lower ? "yes" : "no") << "\nNumbers: " << (digit ? "yes" : "no")
                  << "\nSymbols: " << (symbol ? "yes" : "no") << "\nCommon pattern detected: " << (common ? "yes" : "no")
                  << "\nEstimated search-space entropy: " << entropy << " bits\nScore: " << score << "/100 (" << strength() << ")\n";
        if (length < 12) std::cout << "Suggestion: use at least 12 characters.\n";
        if (!upper || !lower || !digit || !symbol) std::cout << "Suggestion: mix uppercase, lowercase, digits, and symbols.\n";
        if (common) std::cout << "Suggestion: avoid common words and sequences.\n";
        std::cout << "Do not enter or reuse a real account password in this demo.\n";
    }
};
int main() {
    std::cout << "Password Analyzer (local educational estimate)\nEnter sample text: ";
    std::string input; std::getline(std::cin, input);
    PasswordAnalyzer analyzer(input); analyzer.report();
}
