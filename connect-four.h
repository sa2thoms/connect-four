#include <vector>

class Column {
private:
    char * cells;
    unsigned height;
    unsigned top;
public:
    Column(unsigned& height) : height(height) {
        cells = new char[height];
        top = 0;
        for (unsigned i = 0; i < height; i++) {
            cells[i] = 0;
        }
    }

    char operator[](unsigned const index) const {
        return cells[index];
    }
    void insert(char c) {
        if (top < height) {
            cells[top] = c;
            top++;
        }
    }
    char isRun(unsigned length) const {
        char currentRun = 0;
        unsigned currentRunLength = 0;
        for (unsigned i = 0; i < top; i++) {
            if (cells[i] == currentRun) {
                currentRunLength++;
                if (currentRunLength >= length) {
                    return currentRun;
                }
            } else {
                currentRun = cells[i];
                currentRunLength = 1;
            }
        }
        return 0;
    }

    ~Column() {
        delete[] cells;
    }
};

class ConnectFour {
private:
    unsigned width;
    unsigned height;
    std::vector<Column> columns;
    std::vector<char> players;
    unsigned turn;
public:
    ConnectFour(unsigned& height, unsigned& width, std::vector<char> players) : height(height), width(width) {
        this->players = players;
        turn = 0;
        columns = std::vector<Column>(width, Column(height));
    }
    bool takeTurn(unsigned& column) {
        columns[column].insert(players[turn]);
        turn = (turn + 1) % players.size;
        if (checkForWin()) {
            return true;
        }
    }
};
