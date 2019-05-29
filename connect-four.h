#ifndef __CONNECT_FOUR_H__
#define __CONNECT_FOUR_H__

#include <vector>
#include <iostream>

class Column {
public:
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
    unsigned runLength;
    Column ** columns;
    std::vector<char> players;
    unsigned turn;
public:
    ConnectFour(unsigned& height, unsigned& width, unsigned& runLength, std::vector<char> players) : height(height), width(width), runLength(runLength) {
        this->players = players;
        turn = 0;
        columns = new Column*[width];
        for (unsigned i = 0; i < width; i++) {
            columns[i] = new Column(height);
        }
    }
    bool takeTurn(unsigned& column) {
        columns[column]->insert(players[turn]);
        turn = (turn + 1) % players.size();
        if (checkForWin()) {
            return true;
        }
    }
    char checkForWin() const {
        // check vertical win
        for (unsigned i = 0; i < width; i++) {
            char win = columns[i]->isRun(runLength);
            if (win) {
                return win;
            }
        }
        // check horizontal win
        for (unsigned i = 0; i < height; i++) {
            char currentRun = 0;
            unsigned currentRunLength = 0;
            for (unsigned j = 0; j < width; j++) {
                if ((*columns[i])[j] == currentRun) {
                    currentRunLength++;
                    if (currentRunLength >= runLength) {
                        return currentRun;
                    }
                } else {
                    currentRun = (*columns[i])[j];
                    currentRunLength = 1;
                }
            }
        }
        // check diagonal win
        // up and to the right
        int starting_x = 1 - height;
        int starting_y = 0;
        while (starting_x < width) {
            int x = starting_x;
            int y = starting_y;
            char currentRun = 0;
            unsigned currentRunLength = 0;
            while (x < width && y < height) {
                if (x >= 0 && y >= 0) {
                    if ((*columns[x])[y] == currentRun) {
                        currentRunLength++;
                        if (currentRunLength >= runLength) {
                            return currentRun;
                        }
                    } else {
                        currentRun = (*columns[x])[y];
                        currentRunLength = 1;
                    }
                }
                x++;
                y++;
            }
            starting_x++;
        }
        // up and to the left
        starting_x = width + height - 2;
        starting_y = 0;
        while (starting_x > 0) {
            int x = starting_x;
            int y = starting_y;
            char currentRun = 0;
            unsigned currentRunLength = 0;
            while (x >= 0 && y < height) {
                if (x < width && y >= 0) {
                    if ((*columns[x])[y] == currentRun) {
                        currentRunLength++;
                        if (currentRunLength >= runLength) {
                            return currentRun;
                        }
                    } else {
                        currentRun = (*columns[x])[y];
                        currentRunLength = 1;
                    }
                }
                x--;
                y++;
            }
            starting_x--;
        }
        return 0;
    }
    void printBoard() const {
        for (int row = height - 1; row >= 0; row--) {
            // print the top thingy
            for (unsigned col = 0; col < width; col++) {
                std::cout << "+---";
            }
            std::cout << "+" << std::endl;
            // print the row values
            for (unsigned col = 0; col < width; col++) {
                char printee = (*columns[col])[row];
                if (printee == 0) printee = ' ';
                std::cout << "| " << printee << " ";
            }
            std::cout << '|' << std::endl;
        }
        // print the bottom thingy
        for (unsigned col = 0; col < width; col++) {
            std::cout << "+---";
        }
        std::cout << '+' << std::endl;
    }
    ~ConnectFour() {
        for (unsigned i = 0; i < width; i++) {
            delete columns[i];
        }
        delete[] columns;
    }
};

#endif // header guard
