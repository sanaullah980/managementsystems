# Independent C++ Projects

Each folder is a separate, standalone C++17 console project. Build and run one at a time from the repository root:

```sh
g++ -std=c++17 hospital_management/main.cpp -o hospital && ./hospital
g++ -std=c++17 library_management/main.cpp -o library && ./library
g++ -std=c++17 inventory_management/main.cpp -o inventory && ./inventory
g++ -std=c++17 password_analyzer/main.cpp -o analyzer && ./analyzer
g++ -std=c++17 tic_tac_toe/main.cpp -o tic_tac_toe && ./tic_tac_toe
g++ -std=c++17 snake_game/main.cpp -o snake && ./snake
g++ -std=c++17 word_guessing_game/main.cpp -o word_game && ./word_game
```

The projects use only the C++ standard library. The management examples keep data in memory for the current run; they are educational console applications, not production systems. Snake is turn-based: enter a direction (`w`, `a`, `s`, `d`) and press Enter for each move.
