#include "connect-four.h"

int main(int argc, char * argv[]) {
    std::vector<char> players(2);
    players[0] = 'r';
    players[1] = 'b';

    unsigned width = 7;
    unsigned height = 6;
    unsigned winLength = 4;

    ConnectFour game(height, width, winLength, players);

    while (true) {
        unsigned move = 0;
        std::cin >> move;
        if (move < 0) {
            break;
        } else {
            unsigned actualMove = move % width;
            game.takeTurn(actualMove);
            game.printBoard();
            std::cout << "printing completed successfully" << std::endl;
            char winningChar = game.checkForWin();
            if (winningChar) {
                std::cout << winningChar << " wins!" << std::endl;
                break;
            }
        }
    }
    return 0;
}
