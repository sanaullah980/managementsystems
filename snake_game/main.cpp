#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <string>
#include <algorithm>

class SnakeGame {
    int width, height, score{};
    bool running{true};
    std::vector<std::pair<int,int>> snake;
    std::pair<int,int> food;
    std::pair<int,int> direction{1,0};
    std::mt19937 random{std::random_device{}()};
    bool occupied(std::pair<int,int> p) const { return std::find(snake.begin(), snake.end(), p) != snake.end(); }
    void placeFood() {
        std::vector<std::pair<int,int>> free;
        for (int y=0;y<height;++y) for (int x=0;x<width;++x) if (!occupied({x,y})) free.push_back({x,y});
        if (free.empty()) { running = false; return; }
        std::uniform_int_distribution<std::size_t> pick(0, free.size()-1); food = free[pick(random)];
    }
public:
    SnakeGame(int w=12, int h=10) : width(w), height(h), snake{{4,4},{3,4},{2,4}} { placeFood(); }
    void draw() const {
        std::cout << "\nScore: " << score << "\n+" << std::string(width*2, '-') << "+\n";
        for (int y=0;y<height;++y) {
            std::cout << '|';
            for (int x=0;x<width;++x) {
                std::pair<int,int> p{x,y}; char cell = p == snake.front() ? 'H' : p == food ? '*' : occupied(p) ? 'o' : ' ';
                std::cout << cell << ' ';
            }
            std::cout << "|\n";
        }
        std::cout << "+" << std::string(width*2, '-') << "+\n";
    }
    bool setDirection(char key) {
        std::pair<int,int> next = direction;
        if (key=='w') next={0,-1}; else if (key=='s') next={0,1}; else if (key=='a') next={-1,0}; else if (key=='d') next={1,0}; else return false;
        if (next.first == -direction.first && next.second == -direction.second) return false;
        direction=next; return true;
    }
    void step() {
        auto head=snake.front(); std::pair<int,int> next{head.first+direction.first, head.second+direction.second};
        if (next.first<0 || next.first>=width || next.second<0 || next.second>=height) { running=false; return; }
        bool eating = next == food;
        for (std::size_t i=0;i<snake.size();++i) if (snake[i]==next && (eating || i+1<snake.size())) { running=false; return; }
        snake.insert(snake.begin(), next);
        if (eating) { score+=10; placeFood(); } else snake.pop_back();
    }
    void play() {
        while (running) {
            draw(); std::cout << "Direction w/a/s/d (q to quit), then Enter: ";
            char key; if (!(std::cin >> key)) break; if (key=='q') break;
            setDirection(key); step();
        }
        std::cout << "Game ended. Final score: " << score << '\n';
    }
};
int main() { SnakeGame game; game.play(); }
